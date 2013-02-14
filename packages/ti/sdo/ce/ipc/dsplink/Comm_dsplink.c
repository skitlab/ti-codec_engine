/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== Comm_dsplink.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_ipc_comm_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <ti/sdo/ce/osal/Memory.h>
#define MESSAGEQ_ENABLED 1
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Global.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/knl/GateThread.h>

#include <ti/sdo/ce/global/CESettings.h>

/*  ----------------------------------- DSP/BIOS Link                   */
#include <ti/sdo/ce/ipc/dsplink/_adapted_link_gpptypes.h>

#define STD_H
typedef void *Handle;
#include <ti/ipc/MessageQ.h>


/* TODO: We don't have Thread_sleep(), so we'll do this instead */
#ifdef xdc_target__os_Linux
#include <unistd.h>
#else
#define sleep(x)
#endif

/* Number of seconds to sleep for in timeout error spin loop */
#define MAXSLEEP 10

//extern SMAPOOL_Attrs Global_cePoolAttrs;
extern UInt32 ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout;

static Void initCePoolAttrs();
static Void destroyCePoolAttrs();

/*
 *  ======== Comm_Obj ========
 */
typedef struct Comm_Obj {
    MessageQ_Handle msgq;
} Comm_Obj;

/*
 *  ======== Comm_ATTRS ========
 *  Default creation attrs
 */
Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
Registry_Desc ti_sdo_ce_ipc_comm_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Int curInit = 0;     /* module init counter */
static GateThread_Handle moduleLock = NULL;

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    Int        retVal;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);
    Assert_isTrue(msg != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] Comm_alloc> "
            "Enter(poolId=0x%x, msg=0x%x, size=%d)",
            (IArg)poolId, (IArg)msg, (IArg)size);

    /* TODO:H temporary to make best-fit succeed; we allow only messages */
    /* smaller than the standard size */
#if 0
    assert(size <= Global_cePoolAttrs.bufSizes[poolId]);
    if (size < Global_cePoolAttrs.bufSizes[poolId]) {
        size = Global_cePoolAttrs.bufSizes[poolId];
    }
#endif

    *msg = (Comm_Msg)MessageQ_alloc(poolId, size);

    retVal = (*msg != NULL ? Comm_EOK : Comm_EFAIL);

    Log_print2(Diags_EXIT, "[+X] Comm_alloc> msg=0x%x, returning (%d)",
            (IArg)(*msg), (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Attrs *myAttrs)
{
    Comm_Obj *comm;
    MessageQ_Params mqParams;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_create> "
            "Enter(queueName='%s', myAttrs=0x%x)",
            (IArg)queueName, (IArg)myAttrs);

    if (myAttrs == NULL) {
        myAttrs = &Comm_ATTRS;
    }

    /* we only support PEND type since Link MSGQ does not appear to have
     * default MsgqAttrs and we don't know what to set the pend function to
     */
    if (myAttrs->type != Comm_PEND) {
        Log_print1(Diags_USER7, "[+7] Comm_create> Unsupported Comm_Attrs "
                "(0x%x)", (IArg)(myAttrs->type));
        return (NULL);
    }

    comm = Memory_alloc(sizeof(Comm_Obj), NULL);
    if (comm == NULL) {
        return (NULL);
    }

    MessageQ_Params_init(&mqParams);
    if ((comm->msgq = MessageQ_create(queueName, &mqParams)) == NULL) {
        Log_print1(Diags_USER6,
                "[+6] Comm_create('%s', ...) failed: MessageQ_create() failed",
                (IArg)queueName);

        Memory_free(comm, sizeof(Comm_Obj), NULL);
        comm = NULL;
    }

    Log_print1(Diags_EXIT, "[+X] Comm_create> return (0x%x)", (IArg)comm);

    return (comm);
}


/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle comm)
{
    Int status = 1;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_delete> Enter (comm=0x%x)", (IArg)comm);

    if (comm != NULL) {
        if ((status = MessageQ_delete(&comm->msgq)) < 0) {
            Log_print2(Diags_USER7,
                    "[+7] Comm_delete(0x%x) failed: MessageQ_delete() return"
                    "ed status 0x%x", (IArg)comm, (IArg)status);
        }

        Memory_free(comm, sizeof(Comm_Obj), NULL);
    }

    Log_print1(Diags_EXIT, "[+X] Comm_delete> return%s",
            (IArg)(status > 0 ? "" : " (note MessageQ_delete() failure)"));
}


/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    if (--curInit == 0) {
        if (moduleLock != NULL) {
            GateThread_delete(&moduleLock);
            moduleLock = NULL;
        }

        destroyCePoolAttrs();
    }
}


/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
    Int status;
    Int        retVal;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_free> Enter (msg=0x%x)", (IArg)msg);

    status = MessageQ_free((MessageQ_Msg)msg);
    retVal = (status >= 0 ? Comm_EOK : Comm_EFAIL);

    Log_print1(Diags_EXIT, "[+X] Comm_free> return (%d)", (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Handle comm, Comm_Msg *msg, UInt timeout)
{
    UInt32     maxTimeout = timeout;
    Int status;
    Int        retVal;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] Comm_get> "
            "Enter(comm=0x%x, msg=0x%x, timeout=%d)",
            (IArg)comm, (IArg)msg, (IArg)timeout);

    *msg = NULL;

    if (timeout > ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout) {
        Log_print2(Diags_USER2, "[+2] Comm_get> overriding timeout provided "
                "(0x%x) with max configured timeout (0x%x)",
                (IArg)timeout, (IArg)ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout);

        maxTimeout = ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout;
    }

    status = MessageQ_get(comm->msgq, (MessageQ_Msg *)msg,
             maxTimeout == Comm_FOREVER ? MessageQ_FOREVER : maxTimeout);

    if (status == MessageQ_E_TIMEOUT) {
        retVal = Comm_ETIMEOUT;

        if (timeout == Comm_FOREVER) {
            Log_print0(Diags_USER7, "[+7] Comm_get()> Error: "
                    "timeout occurred, spinning forever");
            while (1) {
                sleep(MAXSLEEP);
            }

            Assert_isTrue(FALSE, (Assert_Id)NULL);
        }
    }
    else {
        if (status >= 0) {
            retVal = Comm_EOK;
        }
        else {
            retVal = Comm_EFAIL;
        }
    }

    Log_print2(Diags_EXIT, "[+X] Comm_get> MSGQ_get() status=0x%x, return (%d)",
            (IArg)status, (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    return (MessageQ_getMsgSize((MessageQ_Msg)msg));
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSendersId(Comm_Msg msg, Comm_Id *msgqId)
{

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    *msgqId = (Comm_Id)MessageQ_getReplyQueue((MessageQ_Msg)msg);

    return (Comm_EOK);
}


/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
    GateThread_Params params;
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_ipc_comm_desc, Comm_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Comm_MODNAME);
        }
        regInit = 1;
    }

    if (curInit++ == 0) {
        initCePoolAttrs();

        GateThread_Params_init(&params);
        moduleLock = GateThread_create(&params, NULL);
        if (moduleLock == NULL) {
            Log_print0(Diags_USER7, "[+7] Comm_init> "
                    "ERROR: could not create pthread mutex.");
            Assert_isTrue(FALSE, (Assert_Id)NULL);
        }

        Global_atexit((Fxn)Comm_exit);
    }

    assert(sizeof(Comm_MsgHeader) >= sizeof(MessageQ_MsgHeader));

    return (TRUE);
}


/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Id *msgqId)
{
    Int status;
    Int retVal;
    IArg key;

    /* number of times to retry locate; generated by Global.xdt */
    extern Int Comm_LOCATERETRIES;

    Int retries = 1;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_locate> "
            "Enter(queueName='%s', msgqId=0x%x)",
            (IArg)queueName, (IArg)msgqId);

    *msgqId = Comm_INVALIDMSGQ;

    do {
        key = GateThread_enter(moduleLock);
        status = MessageQ_open(queueName, (MessageQ_QueueId *)msgqId);
        GateThread_leave(moduleLock, key);

        if (status < 0) {
            Log_print3(Diags_USER6, "[+6] Comm_locate> "
                    "Attempt %d of %d to locate Server's MSGQ '%s' failed. Retr"
                    "ying...",
                    (IArg)retries, (IArg)Comm_LOCATERETRIES, (IArg)queueName);
        }

        ++retries;
    } while ((retries <= Comm_LOCATERETRIES) && (status < 0));

    /* TODO:M other osals should do the same thing, not return what their */
    /* callees return */
    retVal = (status >= 0 ? Comm_EOK : Comm_EFAIL);

    if (status < 0) {
        Log_print2(Diags_USER7, "[+7] Comm_locate> "
                "Error: could not locate Server's MSGQ '%s' in %d retries. "
                "Check if you have the "
                "correct Server image, or increase the number of retries "
                "(see ti.sdo.ce.osal.Global's commLocateRetries config param.",
                (IArg)queueName, (IArg)(Comm_LOCATERETRIES ));
    }

    Log_print1(Diags_EXIT, "[+X] Comm_locate> return (%d)", (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Id msgqId, Comm_Msg msg)
{
    Int status;
    Int        retVal;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_put> Enter(msgqId=0x%x, msg=0x%x)",
            (IArg)msgqId, (IArg)msg);

    status = MessageQ_put((MessageQ_QueueId)msgqId, (MessageQ_Msg)msg);
    retVal = (status >= 0 ? Comm_EOK : Comm_EFAIL);

    Log_print1(Diags_EXIT, "[+X] Comm_put> return (%d)", (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Id msgqId)
{
    Int        retVal;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_release> Enter(msgqId=0x%x)",
            (IArg)msgqId);

    MessageQ_close((MessageQ_QueueId *)&msgqId);
    retVal = Comm_EOK;

    Log_print1(Diags_EXIT, "[+X] Comm_release> return (%d)", (IArg)retVal);

    return (retVal);
}


/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setReplyToHandle(Comm_Msg msg, Comm_Handle comm)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    MessageQ_setReplyQueue(comm->msgq, (MessageQ_Msg)msg);
}

/*
 *  ======== Comm_getId ========
 *  Get MessageQ_QueueId from MessageQ_Handle
 */
Comm_Id Comm_getId(Comm_Handle comm)
{
    return (Comm_Id)MessageQ_getQueueId(comm->msgq);
}



/*
 *  ======== Comm_staticMsgInit ========
 *  Initialize fields of a static Comm_Msg.
 */
Void Comm_staticMsgInit(Comm_Msg msg, UInt32 size)
{
    MessageQ_staticMsgInit((MessageQ_Msg)msg, size);
}


/* Number of BUF pools in the pool */
#define NUMMSGPOOLS     2

/* Number of messages in the first message pool */
extern  UInt32 Comm_NUMMSGS;                         /* defined in Global.xdt */

/* Number of messages in the second message pool */
#define NUMMSGINPOOL1   16

/* Sizes of buffers in each pool -- undefs to be set in the function below */
static UInt32 commBufSizes[ NUMMSGPOOLS ] =
{
    -1,                       /* undefined; will be set to Comm_MSGSIZE below */
    128,
};

/* Number of messages in each pool -- to be set in the function below */
static UInt32 commNumBuffers[ NUMMSGPOOLS ] =
{
    -1,                      /* will be set to Comm_NUMMSGS below */
    NUMMSGINPOOL1,
};

/*
 *  ======== initCePoolAttrs ========
 *  Based on Global configuration, fills in the Global_cePoolAttrs structure
 *  above to be used by Processor when it calls DSPLINK's POOL_open()
 */
static Void initCePoolAttrs()
{
    commBufSizes[0]   = Comm_MSGSIZE;
    commNumBuffers[0] = Comm_NUMMSGS;
}

/*
 *  ======== destroyCePoolAttrs ========
 *  Deletes any resources allocated for creation of pool attrs
 */
static Void destroyCePoolAttrs()
{
    /* nothing to do since we didn't allocate anything; all the space comes
     * from the DSPLINK segment on the DSP.
     */
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,1; 2-24-2012 19:30:02; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Comm_posix.c ========
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
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <xdc/runtime/Memory.h>
#define MESSAGEQ_ENABLED 0
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/global/CESettings.h>


#define MSGSIZE     0x1000  /* maximum message size */
#define MSGTYPE     43      /* must be > 0 */
#define MAXRETRY    10      /* number of times to try to locate a queue */

/* Big enough to hold "queue" + <ID> */
#define MAXCOMMNAMELEN 30

typedef struct Comm_Obj {
    Int             id;
    Comm_QType      type;
    Ptr             callHandle;
    Comm_CallFxn    callFxn;
} Comm_Obj;

/*
 *  ======== Comm_ATTRS ========
 *  Default creation attrs
 */
Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

static Int nameToId(String name);
static String userName = "";

Registry_Desc ti_sdo_ce_ipc_comm_desc;

static UInt32 curCommId = 0; /* ID of Comm queue */

static Int regInit = 0;      /* Registry_addModule() called */
static Int curInit = 0;      /* module init counter */

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    Comm_Msg   mbuf;
    Int        retVal = Comm_EFAIL;    /* pessimistic */

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);
    Assert_isTrue(msg != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] Comm_alloc> "
            "Enter(poolId=0x%x, msg=0x%x, size=%d)",
            (IArg)poolId, (IArg)msg, (IArg)size);

    if ((mbuf = (Comm_Msg)Memory_alloc(NULL, size, 0, NULL)) != NULL) {
        mbuf->size = size;
        *((long *)mbuf) = MSGTYPE; /* must be > 0 */
        *msg = mbuf;
        retVal = Comm_EOK;
    }

    Log_print2(Diags_EXIT, "[+X] Comm_alloc> msg=0x%x, returning (%d)",
            (IArg)(*msg), (IArg)retVal);

    return (retVal);
}

/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Attrs *attrs)
{
    Comm_Obj   *comm;
    UInt32      commId;
    Char        commName[ MAXCOMMNAMELEN ];
    key_t       key;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_create> "
            "Enter(queueName='%s', attrs=0x%x)", (IArg)queueName, (IArg)attrs);

    if (attrs == NULL) {
        attrs = &Comm_ATTRS;
    }

    if (queueName == NULL) {
        /* Generate a name to use */
        // TODO: Increment curCommId atomically
        commId = curCommId++;
        sprintf(commName, "queue_%lu_%u", Global_getProcessId(), (Uns)commId);
        key = nameToId(commName);
    }
    else {
        key = nameToId(queueName);
    }

    comm = (Comm_Obj *)Memory_alloc(NULL, sizeof(Comm_Obj), 0, NULL);
    if (comm == NULL) {
        return (NULL);
    }

    comm->type = attrs->type;

    if (comm->type == Comm_PEND) {
        ;
    }
    else if (comm->type == Comm_CALL) {
        comm->callHandle = attrs->callHandle;
        comm->callFxn    = attrs->callFxn;
    }
    else {
        Assert_isTrue(FALSE, (Assert_Id)NULL);  /* unknown Comm type */
    }

    /*
     * Create a new message queue id for the "name" key
     */
    if ((comm->id = msgget(key, IPC_CREAT | 0644)) < 0) {
        fprintf(stderr, "msgget key = 0x%x\n", key);
        perror("Comm_create:msgget");
        Memory_free(NULL, comm, sizeof(Comm_Obj));
        return (NULL);
    }

    Log_print1(Diags_EXIT, "[+X] Comm_create> return (0x%x)", (IArg)comm);

    return (comm);
}

/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle comm)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_delete> Enter (comm=0x%x)", (IArg)comm);

    if (comm != NULL) {
        if (comm->id >= 0) {
            msgctl(comm->id, IPC_RMID, NULL);
        }
        Memory_free(NULL, comm, sizeof(Comm_Obj));
    }

    Log_print1(Diags_EXIT, "[+X] Comm_delete> return", (IArg)comm);
}


/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    if (--curInit == 0) {
    }
}


/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_free> Enter (msg=0x%x)", (IArg)msg);

    Memory_free(NULL, msg, msg->size);

    return (Comm_EOK);
}


/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Handle comm, Comm_Msg *msg, UInt timeout)
{
    Comm_Msg tmp;
    Int len;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] Comm_get> "
            "Enter(comm=0x%x, msg=0x%x, timeout=%d)",
            (IArg)comm, (IArg)msg, (IArg)timeout);

    *msg = NULL;

    if (Comm_alloc(0, &tmp, MSGSIZE) == Comm_EOK) {
        do {
            len = msgrcv(comm->id, tmp, MSGSIZE - sizeof(long), MSGTYPE, 0);
            if (len >= 0) {
                tmp->size = MSGSIZE;
                *msg = tmp;
                return (Comm_EOK);
            }
        } while (errno == EINTR);

        perror("Comm_get");
        Comm_free(tmp);
    }

    return (Comm_EFAIL);
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    return (msg->size);
}


/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSendersId(Comm_Msg msg, Comm_Id *msgqId)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    *msgqId = msg->reserved4;     /* was: srcId */
    return (Comm_EOK);
}


/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
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
        /* TODO:M not process safe (right?) */
        userName = getenv("LOGNAME");
        if (userName == NULL) {
            userName = "";
        }
    }

    return (TRUE);
}


/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Id *msgqId)
{
    key_t key = nameToId(queueName);
    Int qid;
    Int i;

    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_locate> "
            "Enter(queueName='%s', msgqId=0x%x)",
            (IArg)queueName, (IArg)msgqId);

    for (i = 0; (qid = msgget(key, 0644)) < 0; i++) {
        if (i >= MAXRETRY) {
            perror("Comm_locate:msgget");
            return (Comm_EFAIL);
        }
        sleep(1);
    }

    *msgqId = qid;

    return (Comm_EOK);
}


/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Id msgqId, Comm_Msg msg)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY, "[+E] Comm_put> Enter(msgqId=0x%x, msg=0x%x)",
            (IArg)msgqId, (IArg)msg);

    if (msgsnd(msgqId, msg, msg->size - sizeof(long), IPC_NOWAIT) < 0) {
        perror("Comm_put");
        return (Comm_EFAIL);
    }

    Comm_free(msg);
    return (Comm_EOK);
}


/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Id msgqId)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] Comm_release> Enter(msgqId=0x%x)",
            (IArg)msgqId);

    return (Comm_EOK);
}


/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setReplyToHandle(Comm_Msg msg, Comm_Handle comm)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    msg->reserved4 = comm->id;
}

/*
 *  ======== Comm_getId ========
 *  Get MessageQ_QueueId from MessageQ_Handle
 */
Comm_Id Comm_getId(Comm_Handle comm)
{
    /* TODO!  this is most likely broken! */
    return (comm->id);
}


/*
 *  ======== Comm_staticMsgInit ========
 *  Initialize fields of a static Comm_Msg.
 */
Void Comm_staticMsgInit(Comm_Msg msg, UInt32 size)
{
    msg->size = size;
    *((long *)msg) = MSGTYPE; /* must be > 0 */
}

/*
 *  ======== nameToId ========
 *  This function must map name to an id, such that:
 *      1. the same name always results in the same id, and
 *      2. different names must result in different ids.
 */
static Int nameToId(String name)
{
    Int sum = 0;
    Int id = 0;
    Char *cp;

    Log_print1(Diags_ENTRY, "[+E] nameToId> Enter(name=%s)", (IArg)name);

    if ((cp = strchr(name, '#')) != NULL) {
        id = atoi(cp + 1) << 16;
    }

    for (cp = name; *cp != '\0'; cp++) {
        sum += (Int)*cp;
    }
    id = (name - cp) + id;

    /* add user name to allow multiple developers to run tests concurrently */
    for (cp = userName; *cp != '\0'; cp++) {
        sum += (Int)*cp;
    }
    id = (sum << 6) + (userName - cp) + id;

    Log_print1(Diags_EXIT, "[+X] nameToId> Exit(id=0x%x)", (IArg)id);

    return (id);
}
/*
 *  @(#) ti.sdo.ce.ipc.linux; 2, 0, 1,1; 2-24-2012 19:30:10; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


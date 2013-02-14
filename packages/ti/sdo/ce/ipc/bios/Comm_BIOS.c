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
 *  ======== Comm_BIOS.c ========
 *
 *  Note that the implementation of this module assumes that
 *  Comm_EOK == 0 as it often returns "whatever MessageQ returns".
 */

/* Build library with MessageQ by default. */
#ifndef MESSAGEQ_ENABLED
#define MESSAGEQ_ENABLED 1
#endif

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>

#if MESSAGEQ_ENABLED
#include <ti/ipc/MessageQ.h>
//#include <ti/sdo/ipc/transports/TransportNull.h>

#include <xdc/runtime/knl/ISync.h>
#include <ti/sysbios/syncs/SyncSem.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <ti/sdo/ce/ipc/Comm.h>


typedef struct Comm_Obj {
#if MESSAGEQ_ENABLED
    MessageQ_Handle   msgq;
    SyncSem_Handle    sem;
#else
    Int               dummy;
#endif
} Comm_Obj;

Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Attrs *myAttrs)
{
    Comm_Obj       *comm;
#if MESSAGEQ_ENABLED
    MessageQ_Params params;
    SyncSem_Params  syncParams;
#endif

    if (myAttrs == NULL) {
        myAttrs = &Comm_ATTRS;
    }

    comm = (Comm_Obj *)Memory_alloc(NULL, sizeof(Comm_Obj), 0, NULL);
    if (comm == NULL) {
        return (NULL);
    }

#if MESSAGEQ_ENABLED
    MessageQ_Params_init(&params);
#endif
    if (myAttrs->type == Comm_PEND) {
        /* Create a synchronization object that will be used by MessageQ */

#if MESSAGEQ_ENABLED
        /*
         *  TODO: (jeh) Check with Todd if this correctly replaces the BIOS 5
         *  code.
         *
         *      SEM_new(&comm->sem, 0);
         *      attrs.notifyHandle = &comm->sem;
         *      attrs.pend         = (MSGQ_Pend)SEM_pendBinary;
         *      attrs.post         = (MSGQ_Post)SEM_postBinary;
         */
        SyncSem_Params_init(&syncParams);

        comm->sem = SyncSem_create(&syncParams, NULL);
        if (comm->sem == NULL) {
            Memory_free(NULL, comm, sizeof(Comm_Obj));
        }
        params.synchronizer = (ISync_Handle)comm->sem;
#endif
    }
    else if (myAttrs->type == Comm_CALL) {
#if 0  // TODO: (jeh) (Node_create uses Comm_CALL)
        attrs.notifyHandle = myAttrs->callHandle;
        attrs.post         = (MSGQ_Post)myAttrs->callFxn;
#endif
    }
    else {
        assert(FALSE);  /* unknown Comm type */
    }

#if MESSAGEQ_ENABLED
    comm->msgq = MessageQ_create(queueName, &params);
    if (comm->msgq == NULL) {
        Memory_free(NULL, comm, sizeof(Comm_Obj));
        return (NULL);
    }
#endif

    return (comm);
}

/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle comm)
{
    if (comm != NULL) {
#if MESSAGEQ_ENABLED
        if (comm->msgq) {
            MessageQ_delete(&(comm->msgq));
        }
        if (comm->sem) {
            SyncSem_delete(&(comm->sem));
        }
#endif
        Memory_free(NULL, comm, sizeof (Comm_Obj));
    }
}


/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Id *msgqId)
{
    Int status = Comm_EOK;
#if MESSAGEQ_ENABLED
    Int rv;
#endif

#if MESSAGEQ_ENABLED
    rv = MessageQ_open(queueName, (MessageQ_QueueId *)msgqId);
    if (rv != MessageQ_S_SUCCESS) {
        status = Comm_EFAIL;
    }
#endif

    return (status);
}

/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Id msgqId)
{
    // TODO: (jeh)
    //return (MSGQ_release((MSGQ_Queue)msgqQueue));
    return (Comm_EFAIL);
}

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    Int status = Comm_EOK;

#if MESSAGEQ_ENABLED
    *(MessageQ_Msg *)msg = MessageQ_alloc(poolId, size);

    if (*msg == NULL) {
        status = Comm_EFAIL;
    }
#endif

    return (status);
}

/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
#if MESSAGEQ_ENABLED
    MessageQ_free((MessageQ_Msg)msg);
#endif

    return (Comm_EOK);
}

/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Id msgqId, Comm_Msg msg)
{
    Int status = Comm_EOK;
#if MESSAGEQ_ENABLED
    Int rv;
#endif

#if MESSAGEQ_ENABLED
    rv = MessageQ_put((MessageQ_QueueId)msgqId, (MessageQ_Msg)msg);
    if (rv != MessageQ_S_SUCCESS) {
        status = Comm_EFAIL;
    }
#endif

    return (status);
}

/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Handle comm, Comm_Msg *msg, UInt timeout)
{
    Int       status = Comm_EOK;
#if MESSAGEQ_ENABLED
    Int rv;
#endif

#if MESSAGEQ_ENABLED
    if (timeout == Comm_FOREVER) {
        timeout = MessageQ_FOREVER;
    }
    rv = MessageQ_get(comm->msgq, (MessageQ_Msg *)msg, timeout);

    if (rv != MessageQ_S_SUCCESS) {
        status = Comm_EFAIL;
    }
#endif

    return (status);
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
#if MESSAGEQ_ENABLED
    return (MessageQ_getMsgSize((MessageQ_Msg)msg));
#else
    return (0);
#endif
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSendersId(Comm_Msg msg, Comm_Id *msgqId)
{
    Int status = Comm_EOK;

#if MESSAGEQ_ENABLED
    *msgqId = (Comm_Id)MessageQ_getReplyQueue((MessageQ_Msg)msg);
    if (*msgqId == MessageQ_INVALIDMESSAGEQ) {
        status = Comm_EFAIL;
    }
#endif
    return (status);
}

/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setReplyToHandle(Comm_Msg msg, Comm_Handle comm)
{
#if MESSAGEQ_ENABLED
    MessageQ_setReplyQueue(comm->msgq, (MessageQ_Msg)msg);
#endif
}

/*
 *  ======== Comm_getId ========
 *  Get MessageQ_QueueId from MessageQ_Handle
 */
Comm_Id Comm_getId(Comm_Handle comm)
{
#if MESSAGEQ_ENABLED
    return (Comm_Id)MessageQ_getQueueId(comm->msgq);
#else
    return (0); // TODO: Is this the correct value to return?
#endif
}

/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
#if MESSAGEQ_ENABLED
    assert(sizeof (Comm_MsgHeader) >= sizeof (MessageQ_MsgHeader));

    /* Register the NULL heap to heap Id 0 */
    MessageQ_registerHeap(NULL, 0);
#endif

    return (TRUE);
}

/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
}

/*
 *  ======== Comm_staticMsgInit ========
 *  Initialize fields of a static Comm_Msg.
 */
Void Comm_staticMsgInit(Comm_Msg msg, UInt32 size)
{
#if MESSAGEQ_ENABLED
    MessageQ_staticMsgInit((MessageQ_Msg)msg, size);
#endif
}
/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,1; 2-24-2012 19:29:56; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


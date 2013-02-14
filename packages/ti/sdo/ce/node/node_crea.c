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
 *  ======== node_crea.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_node_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/knl/Thread.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/ipc/Comm.h>

#include <assert.h>

#include "node.h"
#include "_node.h"

#define SUSPENDED     (-1)

NODE_Attrs NODE_ATTRS = {
    1,    /* Minimum priority */
    2048, /* Thread_ATTRS.stacksize */
    0,    /* Thread_ATTRS.stackseg */
};

extern Registry_Desc ti_sdo_ce_node_desc;

static Void runStub();
static Void callStub(NODE_Handle node);
static NODE_Status _NODE_createFxn(Int argLen, Char *argBuf, String nodeName,
    NODE_Handle node);

/*
 *  ======== NODE_create ========
 */
NODE_Status NODE_create(NODE_Desc *desc, Int argLen, String argBuf,
    Comm_Id sendId, String instName, NODE_Handle *nodeOut)
{
    NODE_Handle node;
    Comm_Attrs msgqAttrs;
    NODE_Status status = NODE_EOK;
    NODE_Attrs *nodeAttrs = desc->nodeAttrs;
    Thread_Params tskAttrs;

    if (!nodeAttrs) {
        nodeAttrs = &NODE_ATTRS;
    }

    if ((node = Memory_alloc(NULL, sizeof(NODE_Obj), 0, NULL)) == NULL) {
        Log_print0(Diags_USER6, "[+6] NODE_create: Failed to allocate "
                "node object");
        status = NODE_EOUTOFMEMORY;
    }

    if (status == NODE_EOK) {
        /* initialize fields (needed in case we fail and have to clean up) */
        node->self = NULL;
        node->moreEnv = NULL;

        node->skelFxns = desc->skelFxns;
        msgqAttrs = Comm_ATTRS;

        /* HACK: we should only be setting callFxn when node->fxns->exec
         * is NULL; we set the call Fxn in advance in case we run with an
         * OSAL that does not support separate Thread threads
         */
        msgqAttrs.callFxn = (Comm_CallFxn)callStub;
        msgqAttrs.callHandle = (Ptr)node;
#if 0 /* TODO:H cring - is removing this okay?  What is this for? */
        if (node->fxns->exec == NULL) {
            msgqAttrs.type = Comm_CALL;
        }
#endif

        /* create node's input queue */
        node->recv = Comm_create(instName, &msgqAttrs);
        if (node->recv == NULL) {
            status = NODE_ERESOURCE;
        }
    }

    if (status == NODE_EOK) {
        /* call node's state create fxn and, if necessary, create its thread */
        node->send = sendId;
        node->initPriority = nodeAttrs->initPriority;
        node->self = NULL;

        /* create node *before* creating the thread to ensure that the thread
         * does not start using node before it is completely formed
         */
        status = _NODE_createFxn(argLen, argBuf, desc->name, node);

        if (status == NODE_EOK) {
            Thread_Params_init(&tskAttrs);
            tskAttrs.osPriority = SUSPENDED;
            tskAttrs.stackSize = nodeAttrs->stackSize;
            tskAttrs.tls = node;
            node->self = Thread_create((Thread_RunFxn)runStub, &tskAttrs, NULL);

            if (node->self == NULL) {
                status = NODE_ETASK;
            }
        }
    }

    if (status != NODE_EOK) {
        if (node) {
            NODE_delete(node);
            node = NULL;
        }
    }

    *nodeOut = node;

    return (status);
}

/*
 *  ======== runStub ========
 */
static Void runStub(IArg arg)
{
    NODE_Handle node;

    node = Thread_getTls(Thread_self(NULL));

    node->status = NODE_EXECFXN(node);
}

/*
 *  ======== callStub ========
 */
static Void callStub(NODE_Handle node)
{
    Comm_Msg    msg;
    Int         status;
    VISA_Handle visaHandle = NODE_getEnv(node);

    status = Comm_get(node->recv, &msg, Comm_FOREVER);

    if (status == Comm_EOK) {
        node->skelFxns->call(visaHandle, (VISA_Msg)msg);  /* ? rm cast */
        if ((status = Comm_put(node->send, msg)) != Comm_EOK) {
            Log_print2(Diags_USER6, "[+6] NODE callStub(visa = 0x%x): "
                    "Comm_put() failure (%d)", (IArg)visaHandle, (IArg)status);
        }
    }
    else {
        Log_print2(Diags_USER6, "[+6] NODE callStub(visa = 0x%x): "
                "Comm_get() failure (%d)", (IArg)visaHandle, (IArg)status);
    }
}

/*
 *  ======== _NODE_createFxn ========
 */
NODE_Status _NODE_createFxn(Int argLen, Char *argBuf, String nodeName,
    NODE_Handle node)
{
    Void * handle = NULL;

    /* do the create */
    if ((node != NULL) && (node->skelFxns != NULL) &&
        (node->skelFxns->apiCreate != NULL)) {

        if (argLen == 0) {
            handle = node->skelFxns->apiCreate(NULL, nodeName, NULL);
        }
        else {
            handle = node->skelFxns->apiCreate(NULL, nodeName, argBuf);
        }

        NODE_setEnv(node, handle);
    }

    return (handle == NULL ? NODE_EFAIL : NODE_EOK);
}

/*
 *  @(#) ti.sdo.ce.node; 1, 0, 0,1; 2-24-2012 19:30:15; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Server.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_Server_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/global/CESettings.h>


#include <ti/sdo/ce/Engine.h>

#include <ti/sdo/ce/Server.h>



#define GETENGINEHANDLE(s) (Engine_Handle)s

static Server_Status getServerStatus(Engine_Error err);

static Void cleanup(Void);

extern Int Global_useLinkArbiter;

/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
Bool Server_holdingTraceToken = FALSE;
static Bool init = FALSE;

Registry_Desc ti_sdo_ce_Server_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== Server_connectTrace ========
 */
Server_Status Server_connectTrace(Server_Handle server, Int * token)
{
    Engine_Error engineStatus;
    Server_Status status;
    Int gotToken = FALSE;

    Log_print2(Diags_ENTRY, "[+E] Server_connectTrace('0x%x', 0x%x)",
            (IArg)server, (IArg)token);

    Assert_isTrue(((server != NULL) && (token != NULL)), (Assert_Id)NULL);

    /* first check if process already connected for trace */
    if (Server_holdingTraceToken == TRUE) {
        status = Server_EINUSE;
    }

    /* else, request connect token from RMS */
    else {

        /* call Engine function to attempt connection */
        engineStatus = Engine_requestTraceToken(server);
        status = getServerStatus(engineStatus);

        /* if success, set flag indicating this process holds trace token */
        if (status == Server_EOK) {
            Server_holdingTraceToken = TRUE;
            gotToken = TRUE;
        }
    }

    /* set token value to return to caller: TRUE if *this* call got token */
    *token = gotToken;

    Log_print2(Diags_EXIT, "[+X] Server_connectTrace> token(%d), return(%d)",
            (IArg)gotToken, (IArg)status);

    return (status);
}

/*
 *  ======== Server_disconnectTrace ========
 */
Server_Status Server_disconnectTrace(Server_Handle server, Int token)
{
    Server_Status status = Server_EOK;

    Log_print2(Diags_ENTRY, "[+E] Server_disconnectTrace('0x%x', 0x%x)",
            (IArg)server, (IArg)token);

    Assert_isTrue((server != NULL), (Assert_Id)NULL);

    /*
     * if client passes token == TRUE, then companion call to connect actually
     * acquired the trace token, so release it back to RMS; else, if
     * token === FALSE, can simply ignore the request, and return Server_EOK
     */
    if (token == TRUE) {

        /* call Engine function to attempt disconnect */
        if (Engine_releaseTraceToken(server)) {
            /* if success, reset process-holding-token flag */
            Server_holdingTraceToken = FALSE;
        }
        else {
            status = Server_ERUNTIME;
        }
    }

    Log_print1(Diags_EXIT, "[+X] Server_connectTrace> return(%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== Server_fwriteTrace ========
 */
Int Server_fwriteTrace(Server_Handle server, String prefix, FILE *out)
{
    Log_print3(Diags_ENTRY, "[+E] Server_fwriteTrace('0x%x', %s, 0x%x)",
            (IArg)server, (IArg)prefix, (IArg)out);

    Assert_isTrue((server != NULL), (Assert_Id)NULL);

    /* call Engine function to write the trace data */
    return(Engine_fwriteTrace(GETENGINEHANDLE(server), prefix, out));
}

/*
 *  ======== Server_getCpuLoad ========
 */
Int Server_getCpuLoad(Server_Handle server)
{
    Int load;

    Log_print1(Diags_ENTRY, "[+E] Server_getCpuLoad('0x%x')", (IArg)server);

    Assert_isTrue((server != NULL), (Assert_Id)NULL);

    /* call Engine function to get server's CPU load */
    load = Engine_getCpuLoad(GETENGINEHANDLE(server));

    return (load);
}

/*
 *  ======== Server_getMemStat ========
 */
Server_Status Server_getMemStat(Server_Handle server, Int segId,
    Server_MemStat *stat)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    Log_print3(Diags_ENTRY, "[+E] Server_getMemStat('0x%x', %d, 0x%x)",
            (IArg)server, (IArg)segId, (IArg)stat);

    Assert_isTrue((server != NULL) && (stat != NULL), (Assert_Id)NULL);

    /* Call Engine function to get heap info */
    err = Engine_getMemStat(server, segId, (Engine_MemStat *)stat);
    status = getServerStatus(err);

    Assert_isTrue((status == Server_EOK) || (status == Server_ENOTFOUND)
            || (status == Server_ERUNTIME), (Assert_Id)NULL);

    return (status);
}

/*
 *  ======== Server_getNumMemSegs ========
 */
Server_Status Server_getNumMemSegs(Server_Handle server, Int *numSegs)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    Log_print2(Diags_ENTRY, "[+E] Server_getNumMemSegs('0x%x', 0x%x)",
            (IArg)server, (IArg)numSegs);

    Assert_isTrue((server != NULL) && (numSegs != NULL), (Assert_Id)NULL);

    /* Call Engine function to get number of memory heaps on the DSP */
    err = Engine_getNumMemSegs(server, numSegs);
    status = getServerStatus(err);

    Assert_isTrue((status == Server_EOK) || (status == Server_ERUNTIME),
            (Assert_Id)NULL);

    if (status != Server_EOK) {
        *numSegs = 0;
    }

    return (status);
}

/*
 *  ======== Server_init ========
 */
Void Server_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_Server_desc,
                Server_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Server_MODNAME);
        }
        regInit = 1;
    }

    if (init == FALSE) {
        init = TRUE;


        Log_print0(Diags_ENTRY, "[+E] Server_init()");

        /*
         * TODO:M - though benign, should we grab Server_holdingTraceToken
         * if we're a single processor app?  Should Server_init() even be
         * called?
         */

        /* For non-LAD systems, set flag, this process owns all DSP trace */
        Log_print1(Diags_ENTRY, "[+E] Server_init> Global_useLinkArbiter = %d",
                (IArg)Global_useLinkArbiter);
        if (!Global_useLinkArbiter) {
            Server_holdingTraceToken = TRUE;
        }

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== Server_redefineHeap ========
 */
Server_Status Server_redefineHeap(Server_Handle server, String name,
        Uint32 base, Uint32 size)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    Log_print4(Diags_ENTRY, "[+E] Server_redefineHeap('0x%x', %s, 0x%x, 0x%x)",
            (IArg)server, (IArg)name, (IArg)base, (IArg)size);

    Assert_isTrue(server != NULL, (Assert_Id)NULL);
    Assert_isTrue(!(base & 0x7), (Assert_Id)NULL);    /* base must be 8-byte aligned */

    /* Call engine function to change algorithm heap base and size */
    err = Engine_redefineHeap(server, name, base, size);
    status = getServerStatus(err);

    Assert_isTrue((status == Server_EOK) || (status == Server_EINVAL) ||
            (status == Server_ENOTFOUND) || (status == Server_EINUSE) ||
            (status == Server_ERUNTIME), (Assert_Id)NULL);

    return (status);
}

/*
 *  ======== Server_restoreHeap ========
 */
Server_Status Server_restoreHeap(Server_Handle server, String name)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    Log_print2(Diags_ENTRY, "[+E] Server_restoreHeap('0x%x %s)",
            (IArg)server, (IArg)name);

    Assert_isTrue(server != NULL, (Assert_Id)NULL);

    /* Call Engine function to reset the named heap's base and size */
    err = Engine_restoreHeap(server, name);
    status = getServerStatus(err);

    Assert_isTrue((status == Server_EOK) || (status == Server_EINVAL) ||
            (status == Server_ENOTFOUND) || (status == Server_EINUSE) ||
            (status == Server_ERUNTIME), (Assert_Id)NULL);

    return (status);
}

/*
 *  ======== Server_setTrace ========
 */
Int Server_setTrace(Server_Handle server, String mask)
{
    Engine_Error engineStatus;

    Log_print2(Diags_ENTRY, "[+E] Server_setTrace('0x%x', %s)",
            (IArg)server, (IArg)mask);

    Assert_isTrue((server != NULL), (Assert_Id)NULL);

    /* call Engine function set the server's trace mask */
    engineStatus = Engine_setTrace(GETENGINEHANDLE(server), mask);

    return(getServerStatus(engineStatus));
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    if (init != FALSE) {
        init = FALSE;

        /* reinitialize static vars */
        Server_holdingTraceToken = FALSE;
    }
}

/*
 *  ======== getServerStatus ========
 *  Convert Engine error code to server status.
 */
static Server_Status getServerStatus(Engine_Error err)
{
    switch (err) {
        case Engine_EOK:
            return (Server_EOK);
        case Engine_ENOSERVER:
            return (Server_ENOSERVER);
        case Engine_ENOMEM:
            return (Server_ENOMEM);
        case Engine_ERUNTIME:
            return (Server_ERUNTIME);
        case Engine_EINVAL:
            return (Server_EINVAL);
        case Engine_EWRONGSTATE:
            return (Server_EWRONGSTATE);
        case Engine_EINUSE:
            return (Server_EINUSE);
        case Engine_ENOTFOUND:
            return (Server_ENOTFOUND);
        default:
            return (Server_EFAIL);
    }
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:25; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


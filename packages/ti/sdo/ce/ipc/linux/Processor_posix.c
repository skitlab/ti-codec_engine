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
 *  ======== Processor_posix.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_ipc_processor_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include <xdc/runtime/Memory.h>
#include <ti/sdo/ce/ipc/Processor.h>

#include <ti/sdo/ce/global/CESettings.h>

#define MSGSIZE     0x1000  /* maximum message size */

static String myCoreName = "CORE0";

static String argv[] = {"", NULL};

Processor_Attrs Processor_ATTRS = {
    "dsp0",
    1,
    argv
};

/*
 *  ======== Processor_Obj ========
 */
typedef struct Processor_Obj {
    Int pid;
} Processor_Obj;


Registry_Desc ti_sdo_ce_ipc_processor_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Int curInit = 0;     /* module init counter */

/*
 *  ======== Processor_create ========
 */
Processor_Handle Processor_create(String imageName, String linkCfg,
    Processor_Attrs *attrs)
{
    Processor_Handle proc;

    Log_print2(Diags_ENTRY, "[+E] Processor_create> "
            "Enter(imageName='%s', attrs=0x%x)", (IArg)imageName, (IArg)attrs);

    if (attrs == NULL) {
        attrs = &Processor_ATTRS;
    }

    if ((proc = Memory_alloc(NULL, sizeof (Processor_Obj), 0, NULL)) == NULL) {
        Log_print0(Diags_USER7, "[+7] Processor_create> "
                "ERROR: Memory_alloc failed");
        return (NULL);
    }

    if ((proc->pid = fork()) == 0) {
        execv(imageName, attrs->argv);
        perror("Processor_create: execv failed");
    }
    if (proc->pid < 0) {
        Processor_delete(proc);
        proc = NULL;
    }

    Log_print1(Diags_EXIT, "[+X] Processor_create> return (0x%x)", (IArg)proc);

    return (proc);
}

/*
 *  ======== Processor_delete ========
 */
Void Processor_delete(Processor_Handle proc)
{
    Log_print1(Diags_ENTRY, "[+E] Processor_delete> Enter(proc=0x%x)",
            (IArg)proc);

    if (proc != NULL) {
        if (proc->pid > 0) {
            kill(proc->pid, SIGHUP);
        }

        Log_print1(Diags_USER1,
                "[+1] Processor_delete(0x%x) freeing object ...", (IArg)proc);
        Memory_free(NULL, proc, sizeof (Processor_Obj));
    }

    Log_print0(Diags_EXIT, "[+X] Processor_delete> return.");
}


/*
 *  ======== Processor_init ========
 */
Void Processor_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_ipc_processor_desc, Processor_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Processor_MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;
    }
}

/*
 *  ======== Processor_wait ========
 */
Int Processor_wait(Processor_Handle proc)
{
    Int status;
    if (waitpid(proc->pid, &status, 0) < 0) {
        status = -1;
    }

    return (status);
}


/*
 *  ======== Processor_getCoreName ========
 */
String Processor_getCoreName(UInt32 id)
{
    if (id == 0) {
        return (myCoreName);
    }
    else {
        return (NULL);
    }
}


/*
 *  ======== Processor_getId ========
 */
UInt32 Processor_getCoreId(String name)
{
    if (!strcmp(name, myCoreName)) {
        return (0);
    }
    else {
        return (-1);
    }
}


/*
 *  ======== Processor_getNumProcs ========
 */
UInt32 Processor_getNumProcs(Void)
{
    return(1);
}

/*
 *  ======== Processor_myCoreId ========
 */
UInt32 Processor_myCoreId(Void)
{
    return (0);
}

/*
 *  ======== Processor_getHeapId ========
 */
UInt16 Processor_getHeapId(UInt32 coreId)
{
    return (0);
}

/*
 *  ======== Processor_getMsgSize ========
 */
UInt32 Processor_getMsgSize(UInt32 coreId)
{
    Int32 msgSize = MSGSIZE;

    return(msgSize);
}

/*
 *  ======== Processor_getNumMsgs ========
 */
UInt32 Processor_getNumMsgs(UInt32 coreId)
{
    return (0);
}


/*
 *  ======== Processor_getSharedRegionId ========
 */
UInt16 Processor_getSharedRegionId(UInt32 coreId)
{
    return (0);
}

/*
 *  ======== Processor_getUserCreatedHeapFlag ========
 */
Bool Processor_getUserCreatedHeapFlag(UInt32 coreId)
{
    return (FALSE);
}


/*
 *  @(#) ti.sdo.ce.ipc.linux; 2, 0, 1,1; 2-24-2012 19:30:10; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


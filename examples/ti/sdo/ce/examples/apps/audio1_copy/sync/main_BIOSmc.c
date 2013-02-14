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
 *  ======== main_BIOS.c ========
 */
/**
 *  @file       ti/sdo/ce/examples/apps/audio1_copy/sync/main_BIOSmc.c
 *
 *  @brief      This is a BIOS main() routine
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/knl/Thread.h>
#include <ti/ipc/MultiProc.h>

#include <ti/sdo/ce/CERuntime.h>

#include <stdio.h>

#include "smain.h"

#include <ti/sdo/ce/osal/bios/Global_BIOS.h>

static Void workerFxn(IArg arg);

static String taskName = "audio1_copy";

/**
 *  @brief      The BIOS main() entry point.
 *
 *  @remark     The purpose of this function is to create several BIOS worker
 *              tasks, one for each core including the one running this app,
 *              each of which will execute this simple example.
 *
 *  @remark     This is called during initialization, but before the BIOS
 *              scheduler has begun running.
 */
Void main(Int argc, String argv[])
{
    Thread_Params threadParams;
    int i;
    int numCores;

    sprintf(ti_sdo_ce_osal_bios_Global_CE_DEBUG, "1");
    ti_sdo_ce_osal_bios_Global_CE_DEBUG[0] = '2';
    ti_sdo_ce_osal_bios_Global_CE_DEBUG[1] = '\0';

    /* init Codec Engine */
    CERuntime_init();

    /* Enable all trace for xdc.runtime.Main */
    Diags_setMask("xdc.runtime.Main+EX1234567");

    Log_print0(Diags_USER2, "main> ti.sdo.ce.examples.apps.audio1_copy.sync");

    /* Determine number of cores on this device */
    numCores = MultiProc_getNumProcessors();

    /* Unfortunately, the rts library pre-built with CCS only supports 10
     * open files at a time (and 3 are reserved for stdin, stdout, stderr.
     * This app creates a thread for each core, and each thread requires 2
     * file handles.  So, if numCores is > 3, we will run out of file handles
     * _with the prebuilt rtslib.  You can modify the rtslib to support more
     * than 10 handles, and link that lib in, but that's beyond the scope of
     * this app.  We limit the number to 3 cores here.
     *
     * If you rebuild rtslib to support more open file handles, you can remove
     * the following numCores limiting assignment.
     */
    if (numCores > 3) {
        numCores = 3;
    }

    /* create a thread to communicate with each remote core */
    for (i = 0; i < numCores; i++) {
        Thread_Params_init(&threadParams);

        /* 6K stack size */
        threadParams.stackSize = 6 * 1024;

        /* priority - thread 0 gets lower pri as it uses a local alg */
        threadParams.priority = (i == 0) ? Thread_Priority_BELOW_NORMAL :
            Thread_Priority_ABOVE_NORMAL;

        /* task name */
        /* TODO, would be better if this taskName were unique for each task */
        threadParams.instance->name = taskName;

        /* unique arg for each thread - so in/out file names are unique */
        threadParams.arg = i;

        if (Thread_create(workerFxn, &threadParams, NULL) == NULL) {
            System_abort("main: failed to create smain thread.");
        }
    }

    BIOS_start();
}

#define MAXFILENAME 20

static Void workerFxn(IArg arg)
{
    Char inFile[MAXFILENAME];
    Char outFile[MAXFILENAME];
    String procId;
    String engineName;

    sprintf(inFile, "./in%d.dat", arg);
    sprintf(outFile, "./out%d.dat", arg);

    procId = MultiProc_getName(arg);
    engineName = (arg == 0) ? "local_engine" : "audio1_copy";

    smain("audio1_copy", procId, engineName, inFile, outFile);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_copy.sync; 1, 0, 0,1; 2-24-2012 19:27:40; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


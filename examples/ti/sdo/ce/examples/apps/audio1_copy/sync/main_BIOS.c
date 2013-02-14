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
 *  @file       ti/sdo/ce/examples/apps/audio1_copy/sync/main_BIOS.c
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

#include <ti/sdo/ce/CERuntime.h>

#include <stdio.h>

#include "smain.h"

static Void workerFxn(IArg arg);

/* trace info: module name, mask */
#define MOD_NAME "ti.sdo.ce.examples.apps.audio1_copy.sync"

static String taskName = "audio1_copy";

/**
 *  @brief      The BIOS main() entry point.
 *
 *  @remark     The purpose of this function is to create a BIOS worker task
 *              to house our example.
 *
 *  @remark     This is called during BIOS_init, but before the scheduler
 *              has begun running.
 */
Void main(Int argc, String argv[])
{
    Thread_Params threadParams;

    /* init Codec Engine */
    CERuntime_init();

    /* Enable all trace for xdc.runtime.Main */
    Diags_setMask("xdc.runtime.Main+EX1234567");

    Log_print0(Diags_USER2, "main> " MOD_NAME "");

    Thread_Params_init(&threadParams);

    /* 6K stack size */
    threadParams.stackSize = 6 * 1024;
    /* task name */
    threadParams.instance->name = taskName;

    /* used for in/out file names */
    threadParams.arg = 0;

    if (Thread_create(workerFxn, &threadParams, NULL) == NULL) {
        System_abort("main: failed to create smain thread.");
    }

    BIOS_start();
}

#define MAXFILENAME 20

static Void workerFxn(IArg arg)
{
    Char inFile[MAXFILENAME];
    Char outFile[MAXFILENAME];

    sprintf(inFile, "./in%d.dat", arg);
    sprintf(outFile, "./out%d.dat", arg);

    smain("audio1_copy", "unused", "audio1_copy", inFile, outFile);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_copy.sync; 1, 0, 0,1; 2-24-2012 19:27:40; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


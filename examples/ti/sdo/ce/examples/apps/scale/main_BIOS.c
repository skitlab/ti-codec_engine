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
 *  @file       ti/sdo/ce/examples/apps/scale/main_BIOS.c
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

#include <smain.h>

static Void workerFxn(IArg arg);

static String taskName = "scale";

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

    /* Enable all trace for this module */
    Diags_setMask("xdc.runtime.Main+EX012345678");

    Log_print0(Diags_USER2, "[+2] main> Welcome to app's main().");

    Thread_Params_init(&threadParams);
    threadParams.stackSize = 6 * 1024;
    threadParams.instance->name = taskName;

    if (Thread_create(workerFxn, &threadParams, NULL) == NULL) {
        System_abort("main: failed to create smain thread.");
    }

    BIOS_start();
}

#define MAXFILENAME 20

static Void workerFxn(IArg arg)
{
    smain("scale", "unused", "scale", "./in.dat", "./out.dat");
}

/*
 *  @(#) ti.sdo.ce.examples.apps.scale; 1, 0, 0,1; 2-24-2012 19:28:00; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


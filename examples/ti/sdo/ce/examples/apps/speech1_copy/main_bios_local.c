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
 *  ======== main_bios_local.c ========
 */
/**
 *  @file       ti/sdo/ce/examples/apps/speech1_copy/main_bios_local.c
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

#include <ti/sdo/ce/speech1/sphdec1.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/xdais/dm/examples/sphdec1_copy/sphdec1_copy_ti.h>
#include <ti/xdais/dm/examples/sphenc1_copy/sphenc1_copy_ti.h>

#include <stdio.h>

#include "smain.h"

#include <ti/sdo/ce/osal/bios/Global_BIOS.h>

static Void workerFxn(IArg arg);

static String taskName = "speech1_copy";

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
    Engine_Desc    engDesc;
    Engine_AlgDesc algDesc;
    Engine_Error status;

    sprintf(ti_sdo_ce_osal_bios_Global_CE_DEBUG, "1");
    ti_sdo_ce_osal_bios_Global_CE_DEBUG[0] = '2';
    ti_sdo_ce_osal_bios_Global_CE_DEBUG[1] = '\0';

    /* init Codec Engine */
    CERuntime_init();

    /* Enable all trace for xdc.runtime.Main */
    Diags_setMask("xdc.runtime.Main+EX1234567");

    Log_print0(Diags_USER2, "main> ti.sdo.ce.examples.apps.speech1_copy");

    /*
     *  Create the Engine and add our sphdec1_copy and sphenc1_copy algs to
     *  it.  Note, this can also be done in a config script.
     */
     Engine_initDesc(&engDesc);
     engDesc.name = "speech1_copy";
     engDesc.remoteName = NULL;

    status = Engine_add(&engDesc);
    if (status != Engine_EOK) {
        Log_print1(Diags_ERROR, "main-> ERROR: Runtime Engine_add() "
                "failed (0x%x)\n", status);
        /* don't continue */
        while (1) {}
    }

    /*
         *  Add the "sphdecl_copy" and "sphenc1_copy" algs to the
         *  "speech1_copy" engine.
         */

    Engine_initAlgDesc(&algDesc); /* Set fields to defaults */

    algDesc.name = "sphdec1_copy";
    algDesc.fxns = (IALG_Fxns *)&SPHDEC1COPY_TI_ISPHDEC1COPY;
    algDesc.idmaFxns = NULL;
    algDesc.isLocal = TRUE;
    algDesc.groupId = 0;
    algDesc.iresFxns = NULL;
    algDesc.types = SPHDEC1_VISATYPE;

    status = Engine_addAlg("speech1_copy", NULL, NULL, &algDesc);

    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "App-> ERROR: can't add Alg (0x%x)\n",
                (IArg)status);
        /* don't continue */
        while (1) {}
    }

    algDesc.name = "sphenc1_copy";
    algDesc.fxns = (IALG_Fxns *)&SPHENC1COPY_TI_ISPHENC1COPY;
    algDesc.idmaFxns = NULL;
    algDesc.isLocal = TRUE;
    algDesc.groupId = 0;
    algDesc.iresFxns = NULL;
    algDesc.types = SPHENC1_VISATYPE;

    status = Engine_addAlg("speech1_copy", NULL, NULL, &algDesc);

    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "App-> ERROR: can't add Alg (0x%x)\n",
                (IArg)status);
        /* don't continue */
        while (1) {}
    }

    /* Spawn a task to run once the BIOS scheduler is started */
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

    /* Start the BIOS scheduler */
    BIOS_start();
}

#define MAXFILENAME 20

static Void workerFxn(IArg arg)
{
    Char inFile[MAXFILENAME];
    Char outFile[MAXFILENAME];

    sprintf(inFile, "./in%d.dat", arg);
    sprintf(outFile, "./out%d.dat", arg);

    smain("speech1_copy", "unused", "speech1_copy", "./in.dat", "./out.dat");
}

/*
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,1; 2-24-2012 19:28:07; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


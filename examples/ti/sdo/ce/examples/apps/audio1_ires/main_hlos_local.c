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
 *  ======== main_hlos_local.c ========
 */
/**
 *  @file       ti/sdo/ce/examples/apps/audio1_ires/main_hlos_local.c
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ce/CERuntime.h>

#include <ti/xdais/ires.h>

#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/sdo/ce/audio1/audenc1.h>
#include <ti/sdo/fc/ires/examples/codecs/auddec1/auddec1_ti.h>
#include <ti/xdais/dm/examples/audenc1_copy/audenc1_copy_ti.h>

#include <ti/sdo/fc/ires/bufres/bufres.h>
#include <ti/sdo/fc/rman/rman.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "smain.h"


/*
 *  Include FCSettings.h to  get FC trace before CERuntime_init() is called.
 *  This allows us to get trace on the RMAN_register() call. Since this is
 *  called before CERuntime_init(), setting the environment variable, CE_DEBUG,
 *  will not help.
 */
#include <ti/sdo/fc/global/FCSettings.h>

#define BUFLEN 0x400

UInt32 BUFMEM_base;
UInt32 BUFMEM_end;

Char buffer[BUFLEN];

extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int n);
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int n);

/* trace info: module name, mask */
#define MOD_NAME "ti.sdo.ce.examples.apps.audio1_ires"

static String usage = "%s [-p procId] [-e engineName] input-file output-file\n";

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
    String procId;
    String engineName;
    String inFile;
    String outFile;
    Char defaultEngineName[32];
    String options = "e:p:";
    Int option;
    Engine_Desc    engDesc;
    Engine_AlgDesc algDesc;
    BUFRES_Params  config;
    IRES_Status     status;

    /* Initialize defaults. */
    procId = "DSP";
    engineName = defaultEngineName;
    sprintf(defaultEngineName, "audio1_ires");
    inFile = "./in.dat";
    outFile = "./out.dat";

    while ((option = getopt(argc, argv, options)) != -1) {
        switch (option) {
          case 'e':
            engineName = optarg;

            break;

          case 'p':
            procId = optarg;

            break;

          default:
            Log_print1(Diags_USER7, " unrecognized option '%c'\n", option);

            break;
        }
    }

    if (argc == (optind + 1)) {
        inFile = argv[optind];
    }
    else if (argc == (optind + 2)) {
        inFile = argv[optind];
        outFile = argv[optind + 1];
    }
    else if (argc != optind) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    /* Enable all trace for this module */
    Diags_setMask("xdc.runtime.Main+EX12345678");

    Log_print0(Diags_USER2, "[+2] main> " MOD_NAME "");

    /* init Codec Engine */
    CERuntime_init();

    // Uncomment the lines below to get RMAN_init() and RMAN_register() trace
    //FCSettings_init();
    //Diags_setMask(FCSETTINGS_MODNAME"+EX1234567");

    /* Enable all trace for xdc.runtime.Main */
    Diags_setMask("xdc.runtime.Main+EX1234567");

    Log_print0(Diags_USER2, "main> ti.sdo.ce.examples.apps.audio1_ires");

    /*
     *  Configure and register BUFRES resource. This code is used for both
     *  local and remote Linux apps. In the remote case, registering will
     *  not have any affect, since the IRES codec will be run on the DSP.
     */
    config.iresConfig.size = sizeof(BUFRES_Params);
    config.iresConfig.allocFxn = _ALG_allocMemory;
    config.iresConfig.freeFxn = _ALG_freeMemory;

    config.base = (Void *)buffer;
    config.length = BUFLEN;

    status = RMAN_register(&BUFRES_MGRFXNS, (IRESMAN_Params *)&config);
    Log_print1(Diags_USER2, "[+2] main>  RMAN_register returned 0x%x",
            (IArg)status);

    /* Add a "speechl_copy" engine */
    Engine_initDesc(&engDesc);
    engDesc.name = "audio1_ires";

    status = Engine_add(&engDesc);
    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "App-> ERROR: can't add engine (0x%x)\n",
                (IArg)status);
        return (0);
    }

    /*
         *  Add the "auddecl_ires" and "audenc1_copy" algs to the
         *  "speech1_copy" engine.
         */

    Engine_initAlgDesc(&algDesc); /* Set fields to defaults */

    algDesc.name = "auddec1_ires";
    algDesc.fxns = (IALG_Fxns *)&AUDDEC1_TI_AUDDECIRES;
    algDesc.idmaFxns = NULL;
    algDesc.isLocal = TRUE;
    algDesc.groupId = 0;
    algDesc.iresFxns = &AUDDEC1_TI_IRES;
    algDesc.types = AUDDEC1_VISATYPE;

    status = Engine_addAlg("audio1_ires", NULL, NULL, &algDesc);

    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "App-> ERROR: can't add Alg (0x%x)\n",
                (IArg)status);
        return (0);
    }

    algDesc.name = "audenc1_copy";
    algDesc.fxns = (IALG_Fxns *)&AUDENC1COPY_TI_IAUDENC1COPY;
    algDesc.idmaFxns = NULL;
    algDesc.isLocal = TRUE;
    algDesc.groupId = 0;
    algDesc.iresFxns = NULL;
    algDesc.types = AUDENC1_VISATYPE;

    status = Engine_addAlg("audio1_ires", NULL, NULL, &algDesc);

    if (status == Engine_EOK) {
        return (smain(argv[0], procId, engineName, inFile, outFile));
    }
    else {
        Log_print1(Diags_USER7, "App-> ERROR: can't add Alg (0x%x)\n",
                (IArg)status);
    }

    Log_print0(Diags_USER1, "[+1] app done.");
    return (0);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_ires; 1,0,0,1; 2-24-2012 19:27:31; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


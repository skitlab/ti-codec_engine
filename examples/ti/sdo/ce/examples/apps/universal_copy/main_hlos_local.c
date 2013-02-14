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
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/ce/universal/universal.h>
#include <ti/xdais/dm/examples/universal_copy/universal_copy_ti.h>

#include <unistd.h>
#include <stdlib.h>

#include "smain.h"


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
    Engine_Error status;

    /* Initialize defaults. */
    procId = "DSP";
    engineName = defaultEngineName;
    sprintf(defaultEngineName, "remote_copy_%s", procId);
    inFile = "./in.dat";
    outFile = "./out.dat";

    while ((option = getopt(argc, argv, options)) != -1) {
        switch (option) {
          case 'e':
            engineName = optarg;

            break;

          case 'p':
            procId = optarg;
            sprintf(defaultEngineName, "remote_copy_%s", procId);

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

    /* init Codec Engine */
    CERuntime_init();

    /* Enable all trace for xdc.runtime.Main */
    Diags_setMask("xdc.runtime.Main+EX1234567");

    Log_print0(Diags_USER2, "[+2] main> ti.sdo.ce.examples.apps.universal_copy");

    /* Add a "universal_copy" engine */
    Engine_initDesc(&engDesc);
    engDesc.name = "universal_copy";

    status = Engine_add(&engDesc);
    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "App-> ERROR: can't add engine (0x%x)\n",
                (IArg)status);
        return (0);
    }

    /* Add the "universal_copy" alg to the "universal_copy" engine */

    Engine_initAlgDesc(&algDesc); /* Set fields to defaults */

    algDesc.name = "universal_copy";
    algDesc.fxns = (IALG_Fxns *)&UNIVERSALCOPY_TI_IUNIVERSALCOPY;
    algDesc.idmaFxns = NULL;
    algDesc.isLocal = TRUE;
    algDesc.groupId = 0;
    algDesc.iresFxns = NULL;
    algDesc.types = UNIVERSAL_VISATYPE;

    status = Engine_addAlg("universal_copy", NULL, NULL, &algDesc);

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
 *  @(#) ti.sdo.ce.examples.apps.universal_copy; 1, 0, 0,1; 2-24-2012 19:28:15; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


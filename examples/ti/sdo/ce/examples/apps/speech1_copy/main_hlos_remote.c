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
 *  ======== main_native.c ========
 */
/**
 *  @file       ti/sdo/ce/examples/apps/speech1_copy/main_hlos_remote.c
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/speech1/sphdec1.h>
#include <ti/sdo/ce/speech1/sphenc1.h>

#include <unistd.h>
#include <stdlib.h>

#include "smain.h"


static String usage = "%s [-p procId] [-e engineName] [-m mapFileName] [-s serverSuffix] input-file output-file\n";


#define MAXSERVERNAMELEN 128

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
    String procId;
    String procSuffix;
    String engineName;
    String mapFileName = NULL;
    String inFile;
    String outFile;
    Char defaultEngineName[32];
    Bool useExtLoader = FALSE;  /* Set to TRUE if using external loader */
    String options = "e:m:p:s:";
    Int option;
    char serverName[MAXSERVERNAMELEN];
    Engine_Error retVal;
    Engine_Desc engDesc;

    /* Initialize defaults. */
    procId = "DSP";
    procSuffix = "x64P";
    engineName = defaultEngineName;
    sprintf(defaultEngineName, "remote_copy_%s", procId);
    inFile = "./in.dat";
    outFile = "./out.dat";

    while ((option = getopt(argc, argv, options)) != -1) {
        switch (option) {
          case 'e':
            engineName = optarg;

            break;

          case 'm':
              /*
               *  If specifying the slave's memory mapping, then assume that
               *  Codec Engine will be loading the slave.
               */
            mapFileName = optarg;
            useExtLoader = FALSE;

            break;

          case 'p':
            procId = optarg;
            sprintf(defaultEngineName, "remote_copy_%s", procId);

            break;

          case 's':
            procSuffix = optarg;

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

    Log_print0(Diags_USER2, "[+2] main> Welcome to app's main().");

    /*
     * Create the Engine with a remote Server and add register the
     * appropriate stub functions.
     *
     * Note, this can also be done in a config script.
     */
    retVal = Engine_addStubFxns("SPHDEC1_STUBS", (IALG_Fxns *)&SPHDEC1_STUBS);
    if (retVal != Engine_EOK) {
        printf("App-> ERROR: Runtime Engine_addStubFxns() failed (0x%x)\n",
                retVal);
        /* don't continue */
        while (1) {}
    }

    retVal = Engine_addStubFxns("SPHENC1_STUBS", (IALG_Fxns *)&SPHENC1_STUBS);
    if (retVal != Engine_EOK) {
        printf("App-> ERROR: Runtime Engine_addStubFxns() failed (0x%x)\n",
                retVal);
        /* don't continue */
        while (1) {}
    }

    Engine_initDesc(&engDesc);
    engDesc.name = engineName;
    engDesc.memMap = mapFileName;
    engDesc.useExtLoader = useExtLoader;
    sprintf(serverName, "all_%s.%s", procId, procSuffix);
    engDesc.remoteName = serverName;

    retVal = Engine_add(&engDesc);
    if (retVal != Engine_EOK) {
        Log_print1(Diags_ERROR, "main-> ERROR: Runtime Engine_add() "
                "failed (0x%x)\n", retVal);
        /* don't continue */
        while (1) {}
    }

    return (smain(argv[0], procId, engineName, inFile, outFile));
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,1; 2-24-2012 19:28:07; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


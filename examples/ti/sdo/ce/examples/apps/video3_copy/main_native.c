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
 *  @file       ti/sdo/ce/examples/apps/video3_copy/main_native.c
 */
#include <xdc/std.h>

#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/Engine.h>

#include <unistd.h>
#include <stdlib.h>

#include "smain.h"


static String usage = "%s [-p procId] [-e engineName] [-m mapFileName] [-s serverSuffix] input-file output-file\n";

/**
 *  @brief      The main() entry point.
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
    Engine_Error status;
    String options = "e:m:p:s:";
    Int option;
    Engine_Desc desc;

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

    Log_print0(Diags_ENTRY, "[+E] main> ti.sdo.ce.examples.apps.video3_copy");

    /*
     *  Set the memory map in the engine's descriptor, and change to use
     *  (or not use) an external loader for loading.  If using an external
     *  loader, then desc.memMap should be set to NULL;
     */
    status = Engine_getDesc(engineName, &desc);
    desc.useExtLoader = useExtLoader;
    desc.memMap = mapFileName;

    status = Engine_setDesc(engineName, &desc);
    if (status != Engine_EOK) {
        Log_print2(Diags_USER6, "[+2] main> Unable to change \'useExtLoader\' "
                "in descriptor for engine %s to %s", (IArg)engineName,
                (IArg)(useExtLoader ? "TRUE" : "FALSE"));
    }

    return (smain(argv[0], procId, engineName, inFile, outFile));
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video3_copy; 1, 0, 0,1; 2-24-2012 19:28:29; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


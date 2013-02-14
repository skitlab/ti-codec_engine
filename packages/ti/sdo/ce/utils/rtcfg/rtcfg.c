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
 *  ======== rtcfg.c ========
 *  Common variables and functions used by non-RTSC config examples.
 */

/*
 */

#include <xdc/std.h>

#include <ti/xdais/ialg.h>

#include <ti/sdo/ce/Engine.h>

/*
 *  Extern declarations of stub funcions that will be linked into the
 *  app.
 */
extern IALG_Fxns VIDDEC_STUBS;
extern IALG_Fxns VIDENC_STUBS;
extern IALG_Fxns VIDDEC1_STUBS;
extern IALG_Fxns VIDENC1_STUBS;
extern IALG_Fxns IMGDEC_STUBS;
extern IALG_Fxns IMGENC_STUBS;
extern IALG_Fxns IMGDEC1_STUBS;
extern IALG_Fxns IMGENC1_STUBS;
extern IALG_Fxns SPHENC_STUBS;
extern IALG_Fxns SPHDEC_STUBS;
extern IALG_Fxns SPHENC1_STUBS;
extern IALG_Fxns SPHDEC1_STUBS;
extern IALG_Fxns AUDDEC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDDEC1_STUBS;
extern IALG_Fxns AUDENC1_STUBS;
extern IALG_Fxns SCALE_STUBS;
extern IALG_Fxns VIDDEC2_STUBS;
extern IALG_Fxns VIDTRANSCODE_STUBS;
extern IALG_Fxns VIDANALYTICS_STUBS;
extern IALG_Fxns VIDDEC2FRONT_STUBS;
extern IALG_Fxns VIDDEC2BACK_STUBS;
extern IALG_Fxns UNIVERSAL_STUBS;

/*
 * ======== ti.sdo.ce.alg.Settings Configuration ========
 */

/*
 *  The following variable is the base value of a group of IDs for the up to 20
 *  multi-process semaphores created by the alg module. In the case of Linux,
 *  the 20 consecutive interger values starting with this base will be used
 *  for internal Linux IPC objects. In the case of WinCE, these values will
 *  be converted to strings for creating named semaphores.
 *  This value should only be changed (in the remote chance) that it conflicts
 *  with another Linux IPC object in the system (Linux), or another named
 *  semaphore (WinCE).
 */
UInt32 ti_sdo_ce_alg_ipcKey = 0x4f474c41;
UInt32 ti_sdo_ce_alg_Algorithm_ipcKey = 0x4f474c41;



/*
 *  ====================================================
 *  None of the code below this line should be modified!
 *  ====================================================
 */

#include <xdc/runtime/knl/SemProcess.h>

UInt32 ti_sdo_ce_alg_Algorithm_MAXGROUPID = 20;


xdc_runtime_knl_SemProcess_Handle _ALG_sems[20];


IALG_Handle _Algorithm_lockOwner[20] = {
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
};

int _ALG_groupUsed[20] = {
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
};

int _ALG_groupRefCount[20] = {
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
};

/*
 * ======== ti.sdo.ce.CERuntime ========
 */

#include <xdc/runtime/Diags.h>

#include <ti/sdo/ce/global/CESettings.h>
#include <ti/sdo/fc/global/FCSettings.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Loader.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/ipc/Processor.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/Server.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

extern Void Rtcfg_fcInit();

Void RtCfg_init();


/*
 *  ======== CERuntime_init ========
 */
Void CERuntime_init(Void)
{
    CESettings_init();
    FCSettings_init();


    /* if CE_DEBUG is set, turn on tracing and DSP auto trace collection */
    if (Global_getenv("CE_DEBUG") != NULL) {
        extern Bool   Engine_alwaysCollectDspTrace;
        extern String Engine_ceDebugDspTraceMask;

        Engine_alwaysCollectDspTrace = TRUE;

        /*
         * Note the strategy for setting trace masks below...
         * For any mods not yet registered, we set the
         * [FC|CE]SETTINGS_MODNAME mask.  For any mods already
         * registered, we Diags_setMask() them.
         */

        if (Global_getenv("CE_DEBUG")[0] == '1') {
            /* Turn on CE/FC levels 6 and 7 */
            xdc_runtime_Diags_setMask(CESETTINGS_MODNAME"+67");
            xdc_runtime_Diags_setMask(FCSETTINGS_MODNAME"+67");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+67");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+67");

            /* Same for any Servers */
            Engine_ceDebugDspTraceMask = "ti.sdo.ce.%+67;ti.sdo.fc.%+67";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '2') {
            //GT_set(
            //    "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
            // * -> ti.sdo.ce.%, ti.sdo.fc.%
            xdc_runtime_Diags_setMask(CESETTINGS_MODNAME"+EX1234567");
            xdc_runtime_Diags_setMask(FCSETTINGS_MODNAME"+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+EX1234567");

            // CE-3 -> ti.sdo.ce.Engine-3
            xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-3");

            // OG, OM, SemMP -> ti.sdo.xdcruntime.linux
            //xdc_runtime_Diags_setMask("ti.sdo.xdcruntime.linux.%+EX1234567");

            Engine_ceDebugDspTraceMask =
                // Former GT mask:
                //"*+01234567,CR=67,ti.sdo.fc.dman3-2,ti.sdo.fc.dskt2-2,GT_prefix=1235,GT_time=3";
                // Current Diags mask: (time=2 ==> display time in delta usec
                "ti.sdo.ce.%+EX1234567;ti.sdo.fc.%+EX12345678;ti.sdo.ce.rms=67;ti.sdo.fc.dman3-2;ti.sdo.fc.dskt2-2;time=2";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '0') {
            /* Don't set anything if someone tries to turn CE_DEBUG off */
        } else {
            //GT_set("*+01234567,CE-3,GT_time=0,GT_prefix=12345");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+EX1234567");
            //TEMP (jeh) xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-3");
            //xdc_runtime_Diags_setMask("ti.sdo.xdcruntime.linux.%+EX1234567");

            //Engine_ceDebugDspTraceMask = "*+01234567,GT_prefix=12345,GT_time=3";
            Engine_ceDebugDspTraceMask =
                "time=2;ti.sdo.fc.%+EX1234567;ti.sdo.ce.%+EX1234567;ti.sdo.fc.dskt2-2";
        }
    }
    else {
        //xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-EX1234567");
        //xdc_runtime_Diags_setMask("ti.sdo.ce.VISA-EX1234567");
    }

    if (Global_getenv("CE_CHECK") != NULL) {
        extern Bool VISA_checked;

        /*
         * Currently just change _this_ processor's value... perhaps we should
         * enable remote processors as well?
         */
        if (Global_getenv("CE_CHECK")[0] == '1') {
            VISA_checked = TRUE;
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+7");
        } else if (Global_getenv("CE_CHECK")[0] == '0') {
            VISA_checked = FALSE;
        } else {
            /* leave it whatever it was... maybe we should drop a warning? */
        }
    }

    /* allow user to over-ride via CE_TRACE. */
    if (Global_getenv("CE_TRACE") != NULL) {
        xdc_runtime_Diags_setMask(Global_getenv("CE_TRACE"));
    }
    Global_init();


    ti_sdo_ce_osal_Memory_init();
    Comm_init();
    Processor_init();

    Rtcfg_fcInit();
    Algorithm_init();
    XdmUtils_init();

    Engine_init();
    _VISA_init();
    Loader_init();
    Server_init();
    if ((Global_getenv("CE_DEBUG") != NULL) &&
        (Global_getenv("CE_DEBUG")[0] == '2')) {

        /* set up masks that must be deferred until the modules have been init'd */
        //    "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
        //xdc_runtime_Diags_setMask(Comm_MODNAME"-EX12345");
        xdc_runtime_Diags_setMask("ti.sdo.ce.osal.%-EX123");
        //xdc_runtime_Diags_setMask(Algorithm_MODNAME"-EX12345");

        // CE-3 -> ti.sdo.ce.Engine-3
        xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-3");

        // OC=67 -> ti.sdo.ce.ipc.Comm=67
        xdc_runtime_Diags_setMask("ti.sdo.ce.ipc.Comm=67");
    }

    RtCfg_init();

    /*
     *  Allow user to over-ride via CE_TRACE. Putting this after module
     *  initialization, since it will have no effect may have no effect
     *  if called before. Only wildcard settings seem to work when placed
     *  before module initialization.
     */
    if (Global_getenv("CE_TRACE") != NULL) {
        xdc_runtime_Diags_setMask(Global_getenv("CE_TRACE"));
    }

}

/*
 *  ======== CERuntime_exit ========
 */
Void CERuntime_exit(Void)
{
    Global_exit();
}

/* for backward compatibility with xdc-m based tools */
Void ti_sdo_ce_CERuntime_init__F(Void) {
    CERuntime_init();
}

/* Should we auto-add remote algs to the Engine? */
Bool ti_sdo_ce_Engine_initFromServer = TRUE;

/*
 * ======== ti.sdo.ce.ipc.linux.Ipc ========
 */



Void IPC_generatedInit()
{
}

Void RtCfg_init()
{
    Engine_addStubFxns("AUDDEC_STUBS",   &AUDDEC_STUBS);
    Engine_addStubFxns("AUDENC_STUBS",   &AUDENC_STUBS);
    Engine_addStubFxns("AUDDEC1_STUBS",  &AUDDEC1_STUBS);
    Engine_addStubFxns("AUDENC1_STUBS",  &AUDENC1_STUBS);
    Engine_addStubFxns("IMGDEC_STUBS",   &IMGDEC_STUBS);
    Engine_addStubFxns("IMGENC_STUBS",   &IMGENC_STUBS);
    Engine_addStubFxns("IMGDEC1_STUBS",  &IMGDEC1_STUBS);
    Engine_addStubFxns("IMGENC1_STUBS",  &IMGENC1_STUBS);
    Engine_addStubFxns("SPHDEC_STUBS",   &SPHDEC_STUBS);
    Engine_addStubFxns("SPHENC_STUBS",   &SPHENC_STUBS);
    Engine_addStubFxns("SPHDEC1_STUBS",  &SPHDEC1_STUBS);
    Engine_addStubFxns("SPHENC1_STUBS",  &SPHENC1_STUBS);
    Engine_addStubFxns("VIDDEC_STUBS",   &VIDDEC_STUBS);
    Engine_addStubFxns("VIDENC_STUBS",   &VIDENC_STUBS);
    Engine_addStubFxns("VIDDEC1_STUBS",  &VIDDEC1_STUBS);
    Engine_addStubFxns("VIDENC1_STUBS",  &VIDENC1_STUBS);
    Engine_addStubFxns("VIDDEC2_STUBS",  &VIDDEC2_STUBS);
    Engine_addStubFxns("VIDDEC2FRONT_STUBS", &VIDDEC2FRONT_STUBS);
    Engine_addStubFxns("VIDDEC2BACK_STUBS",  &VIDDEC2BACK_STUBS);
    Engine_addStubFxns("VIDTRANSCODE_STUBS", &VIDTRANSCODE_STUBS);
    Engine_addStubFxns("VIDANALYTICS_STUBS", &VIDANALYTICS_STUBS);
    Engine_addStubFxns("UNIVERSAL_STUBS",    &UNIVERSAL_STUBS);
}

/* List of all packages and their versions and paths, for diagnostics */
String Global_buildInfo[] = {
    NULL
};
/*
 *  @(#) ti.sdo.ce.utils.rtcfg; 1, 0, 1,1; 2-24-2012 19:31:35; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


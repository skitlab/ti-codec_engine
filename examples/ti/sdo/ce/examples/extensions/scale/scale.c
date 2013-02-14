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
 *  ======== scale.c ========
 *  Scaling API, exposed to the application.
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  SCALE skeletons (scale_skel.c) call these API's to create instances on the
 *  remote CPU.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_examples_extensions_scale_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/xdais/ialg.h>
#include <ti/sdo/ce/visa.h>

//#include <ti/sdo/ce/osal/Log.h>

#include <ti/sdo/ce/global/CESettings.h>

#include "scale.h"
#include "_scale.h"

#define MODNAME "ti.sdo.ce.examples.extensions.SCALE"


Registry_Desc ti_sdo_ce_examples_extensions_scale_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/* default params*/
SCALE_Params SCALE_PARAMS = {
   sizeof(SCALE_Params),
    1      /* default scale factor */
};


/*
 *  ======== SCALE_create ========
 */
SCALE_Handle SCALE_create(Engine_Handle engine, String name,
    SCALE_Params *params)
{
    Registry_Result   result;
    SCALE_Handle visa;
    static Bool curInit = FALSE;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_examples_extensions_scale_desc,
                MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;
    }

    Log_print3(Diags_ENTRY, "[+E] SCALE_create> "
            "Enter (engine=0x%x, name='%s', params=0x%x)",
            (IArg)engine, (IArg)name, (IArg)params);

    if (params == NULL) {
        params = &SCALE_PARAMS;
    }

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_SCALE_Msg), "ti.sdo.ce.examples.extensions.scale.ISCALE");

    Log_print1(Diags_EXIT, "[+X] SCALE_create> return (0x%x)", (IArg)visa);

    return (visa);
}


/*
 *  ======== SCALE_delete ========
 */
Void SCALE_delete(SCALE_Handle handle)
{
    Log_print1(Diags_ENTRY, "[+E] SCALE_delete> Enter (handle=0x%x)",
            (IArg)handle);

    VISA_delete(handle);

    Log_print0(Diags_EXIT, "[+X] SCALE_delete> return");
}


/*
 *  ======== SCALE_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).
 */
XDAS_Int32 SCALE_process(SCALE_Handle handle, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, SCALE_InArgs *inArgs, SCALE_OutArgs *outArgs)
{
    XDAS_Int32 retVal = SCALE_EFAIL;

    Log_print5(Diags_ENTRY, "[+E] SCALE_process> "
            "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
            "outArgs=0x%x)",
            (IArg)handle, (IArg)inBuf, (IArg)outBuf, (IArg)inArgs,
            (IArg)outArgs);

    if (handle) {
        ISCALE_Fxns *fxns =
            (ISCALE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISCALE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            /*
             * To better enable data visualization tooling, drop a
             * well-formed breadcrumb describing what we're doing.
             */
            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SCALE:process",
            //    (Arg)handle, (Arg)0);
            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBuf, outBuf, inArgs, outArgs);
            VISA_exit((VISA_Handle)handle);
        }
    }

    Log_print2(Diags_EXIT, "[+X] SCALE_process> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}


/*
 *  ======== SCALE_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* image decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 SCALE_control(SCALE_Handle handle, SCALE_Cmd id,
    SCALE_DynamicParams *params)
{
    XDAS_Int32 retVal = SCALE_EFAIL;

    Log_print3(Diags_ENTRY, "[+E] SCALE_control> "
            "Enter (handle=0x%x, id=%d, params=0x%x",
            (IArg)handle, (IArg)id, (IArg)params);

    if (handle) {
        ISCALE_Fxns *fxns =
            (ISCALE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISCALE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            /*
             * To better enable data visualization tooling, drop a
             * well-formed breadcrumb describing what we're doing.
             */
            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SCALE:control",
            //    (Arg)handle, (Arg)0);
            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, id, params);
            VISA_exit((VISA_Handle)handle);
        }
    }

    Log_print2(Diags_EXIT, "[+X] SCALE_control> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,1; 2-24-2012 19:29:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


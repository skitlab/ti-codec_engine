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
 *  ======== viddec2.c ========
 *  The xDM split IVIDDEC2 compliant video decode API's
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  VIDDEC2 skeletons (viddec2_skel.c) call these API's to create instances on
 *  the remote CPU.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_video2_split_viddec2front_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/global/CESettings.h>
//#include <ti/sdo/ce/osal/Log.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/split/ividdec2.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec2.h"
#include "_viddec2front.h"

#define MODNAME "ti.sdo.ce.video2.split.VIDDEC2"


Registry_Desc ti_sdo_ce_video2_split_viddec2front_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== VIDDEC2FRONT_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC2FRONT_control(VIDDEC2FRONT_Handle handle, VIDDEC2_Cmd id,
        VIDDEC2_DynamicParams *params, XDM_Context *context,
        VIDDEC2FRONT_Status *status)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    VIDDEC2_DynamicParams refDynParams;
    XDAS_Int32 refStatusSize;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    Log_print6(Diags_ENTRY, "[+E] VIDDEC2FRONT_control> "
            "Enter (handle=0x%x, id=%d, params=0x%x (size=0x%x), "
            "context=0x%x, status=0x%x",
            (IArg)handle, (IArg)id, (IArg)params, (IArg)(params->size),
            (IArg)context, (IArg)status);

    if (handle) {
        IVIDDEC2FRONT_Fxns *fxns =
            (IVIDDEC2FRONT_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC2FRONT_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC2FRONT:control",
            //    (Arg)handle, (Arg)0);

            if (checked) {
                /*
                 * Make a reference copy of params, status->size, and
                 * status->data.bufSize so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refDynParams = *params;
                refStatusSize = status->fullStatus.size;
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, id, params, context, status);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* ensure the codec didn't modify the read-only dynParams */
                if (memcmp(&refDynParams, params, sizeof(*params)) != 0) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only params "
                            "struct!", (IArg)handle);
                }

                /* ensure the codec didn't change status->size */
                if (status->fullStatus.size != refStatusSize) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only status->size "
                            "field!", (IArg)handle);
                }

            }
        }
    }

    Log_print2(Diags_EXIT, "[+X] VIDDEC2FRONT_control> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}


/*
 *  ======== VIDDEC2FRONT_create ========
 */
VIDDEC2FRONT_Handle VIDDEC2FRONT_create(Engine_Handle engine, String name,
    VIDDEC2_Params *params)
{
    Registry_Result   result;
    VIDDEC2FRONT_Handle visa;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_video2_split_viddec2front_desc,
                MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    Log_print3(Diags_ENTRY, "[+E] VIDDEC2FRONT_create> "
            "Enter (engine=0x%x, name='%s', params=0x%x)",
            (IArg)engine, (IArg)name, (IArg)params);

    visa = VISA_create(engine, name, (IALG_Params *)params,
            sizeof (_VIDDEC2FRONT_Msg), "ti.sdo.ce.video2.split.IVIDDEC2FRONT");

    Log_print1(Diags_EXIT, "[+X] VIDDEC2FRONT_create> return (0x%x)",
            (IArg)visa);

    return (visa);
}


/*
 *  ======== VIDDEC2FRONT_delete ========
 */
Void VIDDEC2FRONT_delete(VIDDEC2_Handle handle)
{
    Log_print1(Diags_ENTRY, "[+E] VIDDEC2FRONT_delete> Enter (handle=0x%x)",
            (IArg)handle);

    VISA_delete(handle);

    Log_print0(Diags_EXIT, "[+X] VIDDEC2FRONT_delete> return");
}


/*
 *  ======== VIDDEC2FRONT_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC2FRONT_process(VIDDEC2FRONT_Handle handle,
        VIDDEC2_InArgs *inArgs, XDM_Context *context,
        VIDDEC2FRONT_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    VIDDEC2_InArgs refInArgs;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    Log_print4(Diags_ENTRY, "[+E] VIDDEC2FRONT_process> "
            "Enter (handle=0x%x, inArgs=0x%x, context=0x%x, outArgs=0x%x)",
            (IArg)handle, (IArg)inArgs, (IArg)context, (IArg)outArgs);

    if (handle) {
        IVIDDEC2FRONT_Fxns *fxns =
            (IVIDDEC2FRONT_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC2FRONT_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC2FRONT:process",
            //    (Arg)handle, (Arg)0);

            if (checked) {

                /* validate inArgs with ranges. */
                if (inArgs->inputID == 0) {

                    Log_print2(Diags_USER7,
                            "[+7] ERROR> app provided codec (0x%x) with out of range"
                            " inArgs->inputID field (0x%x)",
                            (IArg)alg, (IArg)(inArgs->inputID));
                }

                /*
                 * Validate inBufs and outBufs.
                 */
//                XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
//                XdmUtils_validateSparseBufDesc(outBufs, "outBufs");

                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;

                /* inArgs->inputID == 0 is an application error */
                if (inArgs->inputID == 0) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) received invalid "
                            "inArgs->inputID == 0!", (IArg)handle);
                }
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inArgs, context, outArgs);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* ensure the codec didn't modify the read-only inArgs */
                if (memcmp(&refInArgs, inArgs, sizeof(*inArgs)) != 0) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only inArgs "
                            "struct!", (IArg)handle);
                }
            }

        }
    }

    Log_print2(Diags_EXIT, "[+X] VIDDEC2FRONT_process> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,1; 2-24-2012 19:32:10; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


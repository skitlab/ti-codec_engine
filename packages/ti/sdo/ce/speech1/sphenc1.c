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
 *  ======== sphenc1.c ========
 *  The XDM ISPHENC1-compliant speech encode APIs
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  SPHENC1 skeletons (sphenc1_skel.c) call these API's to create instances on
 *  the remote CPU.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_speech1_sphenc1_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/global/CESettings.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/isphenc1.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "sphenc1.h"
#include "_sphenc1.h"

#define MODNAME "ti.sdo.ce.speech1.SPHENC1"

Registry_Desc ti_sdo_ce_speech1_sphenc1_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== SPHENC1_create ========
 */
SPHENC1_Handle SPHENC1_create(Engine_Handle engine, String name,
    SPHENC1_Params *params)
{
    Registry_Result   result;
    SPHENC1_Handle visa;
    Int paramsSize;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_speech1_sphenc1_desc, MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    Log_print3(Diags_ENTRY, "[+E] SPHENC1_create> "
            "Enter (engine=0x%x, name='%s', params=0x%x)",
            (IArg)engine, (IArg)name, (IArg)params);

    /*
     * NOTE!  SPHENC1_Params do _not_ meet the XDAIS spec which requires the
     * first field of the creation params to be a size field of type Int.  As
     * a result, we have to use VISA_create2() rather than the preferred
     * VISA_create() function here.
     */
    paramsSize = params ? (Int)params->size : 0;
    visa = VISA_create2(engine, name, (IALG_Params *)params, paramsSize,
        sizeof (_SPHENC1_Msg), SPHENC1_VISATYPE);

    Log_print1(Diags_EXIT, "[+X] SPHENC1_create> return (0x%x)", (IArg)visa);

    return (visa);
}


/*
 *  ======== SPHENC1_delete ========
 */
Void SPHENC1_delete(SPHENC1_Handle handle)
{
    Log_print1(Diags_ENTRY, "[+E] SPHENC1_delete> Enter (handle=0x%x)",
            (IArg)handle);

    VISA_delete(handle);

    Log_print0(Diags_EXIT, "[+X] SPHENC_delete> return");
}


/*
 *  ======== SPHENC1_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* speech encoders (both high and low complexity
 *  encoders are invoked using this method).
 */
XDAS_Int32 SPHENC1_process(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs,
    SPHENC1_OutArgs *outArgs)
{
    XDAS_Int32 retVal = SPHENC1_EFAIL;

    SPHENC1_InArgs refInArgs;

    /*
     * Note, we assign "VISA_isChecked()" results to a local variable
     * rather than repeatedly query it throughout this fxn because
     * someday we may allow dynamically changing the global
     * 'VISA_isChecked()' value on the fly.  If we allow that, we need
     * to ensure the value stays consistent in the context of this
     * call.
     */
    Bool checked = VISA_isChecked();

    Log_print5(Diags_ENTRY, "[+E] SPHENC1_process> "
            "Enter (handle=0x%x, inBuf=0x%x, outBuf=0x%x, inArgs=0x%x, "
            "outArgs=0x%x)",
            (IArg)handle, (IArg)inBuf, (IArg)outBuf, (IArg)inArgs,
            (IArg)outArgs);

    if (handle) {
        ISPHENC1_Fxns *fxns =
            (ISPHENC1_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISPHENC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            if (checked) {
                /*
                 * Zero out the outArgs struct (except for .size field);
                 * it's write-only to the codec, so the app shouldn't pass
                 * values through it, nor should the codec expect to
                 * receive values through it.
                 */
                memset((void *)((XDAS_Int32)(outArgs) + sizeof(outArgs->size)),
                    0, (sizeof(*outArgs) - sizeof(outArgs->size)));

                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;
            }

            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SPHENC1:process",
            //    (Arg)handle, (Arg)0);

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBuf, outBuf, inArgs, outArgs);
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

    Log_print2(Diags_EXIT, "[+X] SPHENC1_process> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}


/*
 *  ======== SPHENC1_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* speech encoders (both high and low complexity
 *  encoders are invoked using this method).
 */
XDAS_Int32 SPHENC1_control(SPHENC1_Handle handle, SPHENC1_Cmd id,
        SPHENC1_DynamicParams *dynParams, SPHENC1_Status *status)
{
    XDAS_Int32 retVal = SPHENC1_EFAIL;

    SPHENC1_DynamicParams refDynParams;
    XDAS_Int32 refStatusSize;
    XDAS_Int32 refStatusDataBufSize;

    /*
     * Note, we assign "VISA_isChecked()" results to a local variable
     * rather than repeatedly query it throughout this fxn because
     * someday we may allow dynamically changing the global
     * 'VISA_isChecked()' value on the fly.  If we allow that, we need
     * to ensure the value stays consistent in the context of this
     * call.
     */
    Bool checked = VISA_isChecked();

    if (checked) {
        /* Ensure dynParams and status are non-NULL, per the XDM spec */

        if ((!(XdmUtils_validateExtendedStruct(dynParams, sizeof(*dynParams),
                "dynParams"))) || (!(XdmUtils_validateExtendedStruct(status,
                sizeof(*status), "status")))) {
            /* for safety, return here before dereferencing and crashing */
            return (retVal);
        }
    }

    Log_print6(Diags_ENTRY, "[+E] SPHENC1_control> "
            "Enter (handle=0x%x, id=%d, dynParams=0x%x (size=0x%x), "
            "status=0x%x (size=0x%x)",
            (IArg)handle, (IArg)id, (IArg)dynParams, (IArg)(dynParams->size),
            (IArg)status, (IArg)(status->size));

    if (handle) {
        ISPHENC1_Fxns *fxns =
            (ISPHENC1_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISPHENC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            if (checked) {
                /*
                 * Make a reference copy of dynParams, status->size, and
                 * status->data.bufSize so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refDynParams = *dynParams;
                refStatusSize = status->size;
                refStatusDataBufSize = status->data.bufSize;
            }

            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SPHENC1:control",
            //    (Arg)handle, (Arg)0);

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, id, dynParams, status);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* ensure the codec didn't modify the read-only dynParams */
                if (memcmp(&refDynParams, dynParams, sizeof(*dynParams)) != 0) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only dynParams "
                            "struct!", (IArg)handle);
                }

                /* ensure the codec didn't change status->size */
                if (status->size != refStatusSize) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only status->size "
                            "field!", (IArg)handle);
                }

                /* ensure the codec didn't change status->data.bufSize */
                if (status->data.bufSize != refStatusDataBufSize) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only "
                            "status->data.bufSize field!", (IArg)handle);
                }
            }
        }
    }

    Log_print2(Diags_EXIT, "[+X] SPHENC1_control> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.speech1; 1, 0, 1,1; 2-24-2012 19:30:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


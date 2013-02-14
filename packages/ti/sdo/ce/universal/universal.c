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
 *  ======== universal.c ========
 *  The XDM IUNIVERSAL-compliant algorithm APIs
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server;
 *  the UNIVERSAL skeletons (universal_skel.c) call these APIs
 *  to create instances on the remote CPU.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_universal_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <string.h>  /* for memcpy and memset. */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/global/CESettings.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iuniversal.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "universal.h"
#include "_universal.h"

#define MODNAME "ti.sdo.ce.universal.UNIVERSAL"

Registry_Desc ti_sdo_ce_universal_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== UNIVERSAL_create ========
 */
UNIVERSAL_Handle UNIVERSAL_create(Engine_Handle engine, String name,
    UNIVERSAL_Params *params)
{
    Registry_Result   result;
    UNIVERSAL_Handle visa;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_universal_desc, MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    Log_print4(Diags_ENTRY, "[+E] UNIVERSAL_create> "
            "Enter (engine=0x%x, name='%s', params=0x%x (size=0x%x))",
            (IArg)engine, (IArg)name, (IArg)params,
            (IArg)((params == NULL) ? 0 : params->size));

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_UNIVERSAL_Msg), UNIVERSAL_VISATYPE);

    Log_print1(Diags_EXIT, "[+X] UNIVERSAL_create> return (0x%x)", (IArg)visa);

    return (visa);
}


/*
 *  ======== UNIVERSAL_delete ========
 */
Void UNIVERSAL_delete(UNIVERSAL_Handle handle)
{
    Log_print1(Diags_ENTRY, "[+E] UNIVERSAL_delete> Enter (handle=0x%x)",
            (IArg)handle);

    VISA_delete(handle);

    Log_print0(Diags_EXIT, "[+X] UNIVERSAL_delete> return");
}


/*
 *  ======== UNIVERSAL_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* universal algs.
 */
XDAS_Int32 UNIVERSAL_process(UNIVERSAL_Handle handle,
        XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
        IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)
{
    XDAS_Int32 retVal = UNIVERSAL_EFAIL;

    UNIVERSAL_InArgs refInArgs;

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
        /* Ensure inArgs and outArgs are non-NULL, per the XDM spec */

        if ((!(XdmUtils_validateExtendedStruct(inArgs, sizeof(*inArgs),
                "inArgs"))) || (!(XdmUtils_validateExtendedStruct(outArgs,
                sizeof(*outArgs), "outArgs")))) {
            /* for safety, return here before dereferencing and crashing */
            return (retVal);
        }
    }

    Log_print6(Diags_ENTRY, "[+E] UNIVERSAL_process> "
            "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inOutBufs=0x%x, "
            "inArgs=0x%x, outArgs=0x%x)",
            (IArg)handle, (IArg)inBufs, (IArg)outBufs, (IArg)inOutBufs,
            (IArg)inArgs, (IArg)outArgs);

    if (handle) {
        IUNIVERSAL_Fxns *fxns =
            (IUNIVERSAL_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IUNIVERSAL_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            if (checked) {
                /*
                 * Validate inBufs and outBufs.  Note that the IUNIVERSAL
                 * spec allows for NULL bufdescs - that's not an error.
                 */
                if (inBufs) {
                    XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
                }
                if (outBufs) {
                    XdmUtils_validateSparseBufDesc1(outBufs, "outBufs");
                }
                if (inOutBufs) {
                    XdmUtils_validateSparseBufDesc1(inOutBufs, "inOutBufs");
                }

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

            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"UNIVERSAL:process",
            //    (Arg)handle, (Arg)0);

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBufs, outBufs, inOutBufs, inArgs,
                    outArgs);
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

    Log_print2(Diags_EXIT, "[+X] UNIVERSAL_process> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}


/*
 *  ======== UNIVERSAL_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* universal algs.
 */
XDAS_Int32 UNIVERSAL_control(UNIVERSAL_Handle handle,
    IUNIVERSAL_Cmd id, UNIVERSAL_DynamicParams *dynParams,
    UNIVERSAL_Status *status)
{
    XDAS_Int32 retVal = UNIVERSAL_EFAIL;

    UNIVERSAL_DynamicParams refDynParams;
    XDAS_Int32 refStatusSize;
    XDAS_Int32 refStatusDataNumBufs;

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

    Log_print6(Diags_ENTRY, "[+E] UNIVERSAL_control> "
            "Enter (handle=0x%x, id=%d, dynParams=0x%x (size=0x%x), "
            "status=0x%x (size=0x%x)",
            (IArg)handle, (IArg)id, (IArg)dynParams, (IArg)(dynParams->size),
            (IArg)status, (IArg)(status->size));

    if (handle) {
        IUNIVERSAL_Fxns *fxns =
            (IUNIVERSAL_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IUNIVERSAL_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            if (checked) {
                /*
                 * Make a reference copy of dynParams, status->size, and
                 * status->data.numBufs so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refDynParams = *dynParams;
                refStatusSize = status->size;
                refStatusDataNumBufs = status->data.numBufs;
            }

            //Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"UNIVERSAL:control",
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

                /* ensure the codec didn't change status->data.numBufs */
                if (status->data.numBufs != refStatusDataNumBufs) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only "
                            "status->data.numBufs field!", (IArg)handle);
                }
            }
        }
    }

    Log_print2(Diags_EXIT, "[+X] UNIVERSAL_control> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.universal; 1, 0, 0,1; 2-24-2012 19:31:35; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Algorithm_BIOS.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_algorithm_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <assert.h>
#include <string.h>

#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/dskt2/dskt2_mem.h>
#include <ti/sdo/fc/dman3/dman3.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/xdais/idma3.h>
#include <ti/xdais/ires.h>
#include <ti/xdais/ialg.h>


#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/global/CESettings.h>

#include "Algorithm.h"


/*
 *  ======== Algorithm_Obj ========
 */
typedef struct Algorithm_Obj {
    IALG_Handle alg;
    Int         groupId;
    IDMA3_Fxns  *idma3Fxns;
    IRES_Fxns   *iresFxns;
} Algorithm_Obj;


extern Void DMAN3_CE_init();
extern Void DMAN3_CE_exit();

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */

Registry_Desc ti_sdo_ce_algorithm_desc;

static Bool curInit = FALSE;
static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== Algorithm_acquireLock ========
 */
Void Algorithm_acquireLock(Int groupId, IALG_Handle alg)
{

    Log_print2(Diags_ENTRY, "[+E] Algorithm_acquireLock> Enter(alg=0x%x,"
            " groupId=%d)", (IArg)alg, (IArg)groupId);

    Log_print0(Diags_ENTRY, "[+E] Algorithm_acquireLock> Feature not "
            "supported on BIOS (yet).");

    Log_print0(Diags_EXIT, "[+X] Algorithm_acquireLock> Exit");
}

/*
 *  ======== Algorithm_activate ========
 */
Void Algorithm_activate(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;

    Log_print1(Diags_ENTRY, "[+E] Algorithm_activate> Enter(alg=0x%x)",
            (IArg)alg);

    DSKT2_activateAlg(pObject->groupId, pObject->alg);

    if (pObject->iresFxns) {
        RMAN_activateAllResources(pObject->alg, pObject->iresFxns,
                pObject->groupId);
    }

    Log_print0(Diags_EXIT, "[+X] Algorithm_activate> Exit");
}


/*
 *  ======== Algorithm_addGroup ========
 */
Bool Algorithm_addGroup(Int groupId)
{
    Bool    retVal = TRUE;

    Log_print1(Diags_ENTRY, "[+E] Algorithm_addGroup> Enter(groupId=%d)",
            (IArg)groupId);

    Log_print1(Diags_EXIT, "[+X] Algorithm_addGroup> Exit (status = %d)",
            (IArg)retVal);

    return (retVal);
}

/*
 *  ======== Algorithm_create ========
 */
Algorithm_Handle Algorithm_create(IALG_Fxns *fxns, Void *idma3FxnsVoid,
        Void *iresFxnsVoid, IALG_Params *params, Algorithm_Attrs *attrs)
{
    Algorithm_Obj *pObject = NULL;
    IDMA3_Fxns *idma3Fxns = (IDMA3_Fxns *)idma3FxnsVoid;
    IRES_Fxns  *iresFxns = (IRES_Fxns *)iresFxnsVoid;
    IRES_Status iresStatus;

    Log_print5(Diags_ENTRY, "[+E] Algorithm_create> Enter("
            "fxns=0x%x, idma3Fxns=0x%x, iresFxns=0x%x, params=0x%x, "
            "attrs=0x%x)",
            (IArg)fxns, (IArg)idma3Fxns, (IArg)iresFxns, (IArg)params,
            (IArg)attrs);

    assert(attrs != NULL);

    pObject = Memory_alloc(sizeof(Algorithm_Obj), NULL);
    if (pObject == NULL) {
        Log_print0(Diags_USER7, "[+7] Algorithm_create> "
                "Alloc for a small object FAILED -- out of memory?");
        goto Algorithm_create_return;
    }

    /*
     * Note that we don't have to validate groupId as that's done at
     * config time.
     */
    pObject->idma3Fxns = NULL;
    pObject->iresFxns = NULL;
    pObject->groupId = attrs->groupId;

    /* Call appropriate DSKT2 function, depending on attrs->useExtHeap */
    if (attrs->useExtHeap == FALSE) {
        /*
         *  Create alg normally, attempting to allocate algorithm memory
         *  in the requested memory spaces.
         */
        pObject->alg = DSKT2_createAlg(attrs->groupId, fxns, NULL, params);
    }
    else {
        /*
         *  Create alg with all algorithm memory allocated in external memory.
         */
        pObject->alg = DSKT2_createAlgExt(attrs->groupId, fxns, NULL, params);
    }

    if (pObject->alg == NULL) {
        Log_print0(Diags_USER7, "[+7] Algorithm_create> "
                "Algorithm creation FAILED; make sure that 1) alg params are "
                "correct/appropriate, 2) there is enough internal and external "
                "algorithm memory available -- check DSKT2 settings for heap "
                "assignments and scratch allocation");
        Algorithm_delete(pObject);
        pObject = NULL;
        goto Algorithm_create_return;
    }

    /* if the alg implements IDMA3, we need to negotiate DMA resources */
    if (idma3Fxns != NULL) {
        Int status;
        status = DMAN3_grantDmaChannels(pObject->groupId, &pObject->alg,
                &idma3Fxns, 1);

        if (status != DMAN3_SOK) {
            Log_print1(Diags_USER7, "[+7] Algorithm_create> "
                    "Granting DMA channels to algorithm through DMAN3 FAILED"
                    " (0x%x)", (IArg)status);
            Algorithm_delete(pObject);
            pObject = NULL;
            goto Algorithm_create_return;
        }

        pObject->idma3Fxns = idma3Fxns;  /* tell Algorithm_delete to release */
    }

    /* If alg implements IRES, allocate resources */
    if (iresFxns != NULL) {
        iresStatus = RMAN_assignResources(pObject->alg, iresFxns,
                pObject->groupId);

        if (iresStatus != IRES_OK) {
            Log_print1(Diags_USER7, "[+7] Algorithm_create> Assignment of "
                    "alg resources through RMAN FAILED (0x%x)",
                    (IArg)iresStatus);

            /* Free DMAN3 channels, if allocated */
            if (idma3Fxns != NULL) {
                DMAN3_releaseDmaChannels(&(pObject->alg),
                        &(pObject->idma3Fxns), 1);
            }

            Algorithm_delete(pObject);
            pObject = NULL;
            goto Algorithm_create_return;
        }
        pObject->iresFxns = iresFxns;
    }

Algorithm_create_return:

    Log_print1(Diags_EXIT, "[+X] Algorithm_create> return (0x%x)",
            (IArg)pObject);

    return (pObject);
}


/*
 *  ======== Algorithm_deactivate ========
 */
Void Algorithm_deactivate(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;

    Log_print1(Diags_ENTRY, "[+E] Algorithm_deactivate> Enter(alg=0x%x)",
            (IArg)alg);

    if (pObject->iresFxns) {
        RMAN_deactivateAllResources(pObject->alg, pObject->iresFxns,
                pObject->groupId);
    }

    DSKT2_deactivateAlg(pObject->groupId, pObject->alg);

    Log_print0(Diags_EXIT, "[+X] Algorithm_deactivate> Exit");
}


/*
 *  ======== Algorithm_delete ========
 */
Void Algorithm_delete(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;
    IRES_Status status;

    Log_print1(Diags_ENTRY, "[+E] Algorithm_delete> Enter(alg=0x%x)",
            (IArg)alg);

    if (pObject != NULL) {
        if (pObject->iresFxns) {
            /* Call RMAN fuction to free resources */
            status = RMAN_freeResources(pObject->alg, pObject->iresFxns,
                    pObject->groupId);
            if (status != IRES_OK) {
                Log_print1(Diags_USER7, "[+7] Algorithm_delete> Freeing "
                        "of alg resources through RMAN FAILED (0x%x)",
                        (IArg)status);
            }
        }

        if (pObject->idma3Fxns) {
            Log_print0(Diags_USER4, "[+4] Algorithm_delete> releasing "
                    "DMA resources");
            DMAN3_releaseDmaChannels(&(pObject->alg), &(pObject->idma3Fxns),1);
        }

        if (pObject->alg) {
            DSKT2_freeAlg(pObject->groupId, pObject->alg);
        }

        Memory_free(pObject, sizeof (*pObject), NULL);
    }

    Log_print0(Diags_EXIT, "[+X] Algorithm_delete> Exit");
}


/*
 *  ======== Algorithm_exit ========
 */
Void Algorithm_exit()
{
    if (curInit != FALSE) {
        curInit = FALSE;
        DMAN3_CE_exit();
        RMAN_exit();
    }
}


/*
 *  ======== Algorithm_getAlgHandle ========
 */
IALG_Handle Algorithm_getAlgHandle(Algorithm_Handle handle)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)handle;

    /* reach into the internal object and return the iAlg handle */
    return (pObject->alg);
}


/*
 *  ======== Algorithm_getMemRecs ========
 */
Int Algorithm_getMemRecs(Algorithm_Handle handle, IALG_MemRec *memTab,
        Int size)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)handle;
    Int nRecs;

    nRecs = DSKT2_getMemRecs(pObject->alg, memTab, size);

    return (nRecs);
}

/*
 *  ======== Algorithm_getNumRecs ========
 */
Int Algorithm_getNumRecs(Algorithm_Handle handle)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)handle;
    Int            nRecs;

    nRecs = DSKT2_getNumMemRecs(pObject->alg);

    return (nRecs);
}

/*
 *  ======== Algorithm_init ========
 */
Void Algorithm_init()
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_algorithm_desc,
                Algorithm_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Algorithm_MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;
        RMAN_init();
        DMAN3_CE_init();
        Global_atexit((Fxn)Algorithm_exit);
    }
}


/*
 *  ======== Algorithm_releaseLock ========
 */
Void Algorithm_releaseLock(Int groupId, IALG_Handle alg)
{
    Log_print2(Diags_ENTRY, "[+E] Algorithm_releaseLock> Enter(alg=0x%x,"
            " groupId=%d)", (IArg)alg, (IArg)groupId);

    Log_print0(Diags_ENTRY, "[+E] Algorithm_releaseLock> Feature not "
            "supported on BIOS (yet).");

    Log_print0(Diags_EXIT, "[+X] Algorithm_releaseLock> Exit");
}

/*
 *  ======== Algorithm_removeGroup ========
 */
Void Algorithm_removeGroup(Int groupId)
{
    Log_print1(Diags_ENTRY, "[+E] Algorithm_removeGroup> Enter(groupId=%d)",
            (IArg)groupId);

    Log_print0(Diags_EXIT, "[+X] Algorithm_removeGroup> Exit");
}
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,1; 2-24-2012 19:27:09; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


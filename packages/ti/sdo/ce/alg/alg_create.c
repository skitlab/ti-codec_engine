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
 *  ======== alg_create.c ========
 *  This file contains a simple implementation of the ALG_create API operation.
 */
#if _TI_
#pragma CODE_SECTION(ALG_create, ".text:create")
#pragma CODE_SECTION(ALG_delete, ".text:delete")
#endif

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_alg_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/xdais/ialg.h>
#include <stdlib.h>

#include "alg.h"
#include "_alg.h"



extern Registry_Desc ti_sdo_ce_alg_desc;

/*
 *  ======== ALG_create ========
 */
ALG_Handle ALG_create(Int scratchId, IALG_Fxns *fxns, IALG_Handle parent,
        IALG_Params *params, UInt32 useCacheMem)
{
    IALG_Fxns *fxnsPtr;
    ALG_Handle alg;
    Int numRecs;
    IALG_MemRec *memTab;
    Int i;
    Int  status;

    Log_print5(Diags_ENTRY, "[+E] ALG_create> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
            "useCacheMem=%d)", (IArg)scratchId,
            (IArg)fxns, (IArg)parent, (IArg)params, (IArg)useCacheMem);

    if (fxns != NULL) {
        /* determine size of the memTab structure */
        numRecs = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;
        Log_print1((Diags_USER4 | Diags_USER2),
                "[+24] ALG_create> algNumAlloc %d memory recs", (IArg)numRecs);

        /* allocate a memTab based on number of records alg specified */
        if ((memTab = (IALG_MemRec *)malloc(numRecs * sizeof (IALG_MemRec)))) {

            /* call alg's algAlloc fxn to fill in memTab[]  */
            numRecs = fxns->algAlloc(params, &fxnsPtr, memTab);
            if (numRecs <= 0) {
                return (NULL);
            }

            Log_print1((Diags_USER4 | Diags_USER2),
                    "[+24] ALG_create> algAlloc returned numRecs=%d",
                    (IArg)numRecs);
            for (i = 0; i < numRecs; i++) {

                Log_print5(Diags_USER4, "[+4] ALG_create> "
                        " Memory requested memTab[%d]: size=0x%x, align=0x%x, "
                        "space=0x%x, attrs=0x%x",
                        (IArg)i, (IArg)(memTab[i].size),
                        (IArg)(memTab[i].alignment), (IArg)(memTab[i].space),
                        (IArg)(memTab[i].attrs));

            }
            if (_ALG_allocMemory2(memTab, numRecs, useCacheMem)) {
                /* set alg object handle, and set instance's function pointer */
                alg = (IALG_Handle)memTab[0].base;
                alg->fxns = fxns;
                /* call alg initialize function with the memory it requested */
                /* if algInit successful return the alg object's handle */
                status = fxns->algInit(alg, memTab, parent, params);
                if (status == IALG_EOK) {
                    Log_print0(Diags_USER4,
                            "[+4] ALG_create> algInit returned IALG_EOK");
                    free(memTab);

                    Log_print1(Diags_EXIT,
                            "[+X] ALG_create> Exit (algHandle=0x%x)",
                            (IArg)alg);

                    return (alg);
                }
                Log_print1(Diags_USER7, "[+7] ALG_create> "
                        "algInit call failed %d", (IArg)status);

                /*
                 * Call algFree to free all instance memory, saved memTab recs.
                 */
                fxns->algFree(alg, memTab);
                _ALG_freeMemory2(memTab, numRecs, useCacheMem);
            }

            free(memTab);
        }
    }

    Log_print0(Diags_EXIT, "[+X] ALG_create> Exit (algHandle=NULL)");

    return (NULL);
}

/*
 *  ======== ALG_delete ========
 */
Void ALG_delete(Int scratchId, ALG_Handle alg, UInt32 useCachedMem)
{
    IALG_MemRec *memTab;
    Int n;
    IALG_Fxns *fxns;

    Log_print2(Diags_ENTRY, "[+E] ALG_delete> Enter (scratchId=%d, alg=0x%x)",
            (IArg)scratchId, (IArg)alg);

    if (alg != NULL && alg->fxns != NULL) {
        fxns = alg->fxns;
        n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

        if ((memTab = (IALG_MemRec *)malloc(n * sizeof (IALG_MemRec)))) {
            memTab[0].base = alg;
            n = fxns->algFree(alg, memTab);
            _ALG_freeMemory2(memTab, n, useCachedMem);

            free(memTab);
        }
    }

    Log_print0(Diags_EXIT, "[+X] ALG_delete> Exit");
}

/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,1; 2-24-2012 19:27:09; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


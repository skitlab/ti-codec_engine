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
 *  ======== rtcfg_fcinit.c ========
 *  FC configuration for non-RTSC config examples. Compile this file as is,
 *  with apps that don't use the individual FC components here.. For apps whose
 *  local codecs use RMAN or DMAN3 etc, copy this file and modify as needed.
 */

/*
 *  Set USE_RMAN to 1 if the app uses RMAN, otherwise set to 0. If USE_RMAN
 *  is set to 1, the user may need to modify RMAN_PARAMS structure
 */
#define USE_RMAN 1

/*
 *  Set USE_DMAN3 to 1 if the app has a local codec that uses DMAN3, otherwise
 *  set to 0. If USE_DMAN3 is set to 1, the user may need to modify the
 *  fields of the DMAN3_PARAMS structure.
 */
#define USE_DMAN3 1



#include <xdc/std.h>

#include <xdc/runtime/IHeap.h>

#if USE_RMAN
#include <ti/sdo/fc/rman/rman.h>
#endif

#if USE_DMAN3
#include <ti/sdo/fc/dman3/dman3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>
#endif

#include <ti/sdo/fc/dskt2/dskt2.h>

extern xdc_runtime_IHeap_Handle INT_HEAP;
extern xdc_runtime_IHeap_Handle EXT_HEAP;

void Rtcfg_fcInit()
{

    static __FAR__ Uns qdma_channels[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    /* Configure DSKT2 */
    DSKT2_daram0Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_daram1Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_daram2Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_saram0Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_saram1Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_saram2Heap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_iprogHeap = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DSKT2_eprogHeap = (xdc_runtime_IHeap_Handle)EXT_HEAP;
    DSKT2_esdataHeap = (xdc_runtime_IHeap_Handle)EXT_HEAP;
    _DSKT2_heap = (xdc_runtime_IHeap_Handle)EXT_HEAP;


#if USE_RMAN
    /* Configure RMAN */

#endif

#if USE_DMAN3
    /* Configure DMAN3 */
    DMAN3_PARAMS.paRamBaseIndex = 80;
    DMAN3_PARAMS.numPaRamEntries = 48;
    DMAN3_PARAMS.numQdmaChannels = 8;
    DMAN3_PARAMS.qdmaChannels = qdma_channels;
    DMAN3_PARAMS.tccAllocationMaskH = 0xffffffff;
    DMAN3_PARAMS.tccAllocationMaskL = 0x0;

    DMAN3_PARAMS.heapInternal = (xdc_runtime_IHeap_Handle)INT_HEAP;
    DMAN3_PARAMS.heapExternal = (xdc_runtime_IHeap_Handle)EXT_HEAP;

#endif

/* Add other FC configuration as necessary, this is only an example */
}



#if USE_RMAN
#else

/* PLEASE DO NOT MODIFY CODE BELOW */

/* If not using RMAN, the RMAN functions need to be stubbed out. */

#include <ti/xdais/ires.h>   /* for IRES types */

IRES_Status RMAN_activateAllResources(IALG_Handle algHandle,
        IRES_Fxns *resFxns, Int scratchId)
{
    return (IRES_OK);
}

IRES_Status RMAN_assignResources(IALG_Handle algHandle, IRES_Fxns *resFxns, 
        Int scratchGroupId)
{
    return (IRES_OK);
}

IRES_Status RMAN_deactivateAllResources(IALG_Handle algHandle, 
        IRES_Fxns * resFxns, Int scratchId)
{
    return (IRES_OK);
}

IRES_Status RMAN_freeResources(IALG_Handle algHandle, IRES_Fxns * resFxns, 
        Int scratchGroupId)
{
    return (IRES_OK);
}

IRES_Status RMAN_init(void)
{
    return (IRES_OK);
}

IRES_Status RMAN_exit(void)
{
    return (IRES_OK);
}

#endif


#if USE_DMAN3
/*
 *  Base key value for DMAN3 Linux IPC objects. The only reason for modifying
 *  this, is if the value is the same as the key of another Linux IPC object.
 */
// Can disappear for fixed versions of FC
//UInt32 _DMAN3_ipcKeyBase = 0x4e414d44;


/*
 *  ======== ti.sdo.fc.acpy3.ACPY3 ========
 */

// Can disappear for fixed versions of FC
//__FAR__ UInt32 ti_sdo_fc_acpy3_ACPY3_ipcKeyBase = 0x33504341;

/*
 *  ======== DMAN3_CE_init  ========
 */
Void DMAN3_CE_init()
{
    extern __FAR__ DMAN3_Params DMAN3_PARAMS;

    /* Configure DMAN3 */
    DMAN3_PARAMS.heapInternal = NULL;
    DMAN3_PARAMS.heapExternal = NULL;

    DMAN3_init();
    ACPY3_init();
}

/*
 *  ======== DMAN3_CE_exit  ========
 */
Void DMAN3_CE_exit()
{
    DMAN3_exit();
    ACPY3_exit();
}

#else

/* PLEASE DO NOT MODIFY CODE BELOW */
/*
 *  No IDMA3 using algs in the system, and DMAN3 is not configured into the
 *  system.  Stubbing out these fxn calls.
 */
Void DMAN3_CE_init()
{
}

Void DMAN3_CE_exit()
{
}

int DMAN3_grantDmaChannels(int groupId, void *algHandles, void *dmaFxns,
        int numAlgs)
{
    return (0);
}

int DMAN3_releaseDmaChannels(void *algHandles, void * dmaFxns, int numAlgs)
{
    return (0);
}

#endif
/*
 *  @(#) ti.sdo.ce.examples.servers; 1, 0, 0,1; 2-24-2012 19:29:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


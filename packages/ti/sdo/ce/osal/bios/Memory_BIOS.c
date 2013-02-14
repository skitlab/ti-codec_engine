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
 *  ======== Memory_BIOS.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_osal_Memory_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#define xdc_runtime_Memory__nolocalnames
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Registry.h>

#include <string.h>


/*
 *  ti/sysbios/hal/Cache.h does not have a wbInbAll() function, but the
 *  ti/sysbios/family/c64p/Cache.h does. We need this for
 *  Memory_cacheWbInvAll().
 */
//#ifdef xdc_target__isaCompatible_64P
//#include <ti/sysbios/family/c64p/Cache.h>
//#else
#include <ti/sysbios/hal/Cache.h>
//#endif

#include <ti/sysbios/heaps/HeapMem.h>

#include <ti/sdo/ce/global/CESettings.h>

#include <ti/sdo/ce/osal/Memory.h>

Registry_Desc ti_sdo_ce_osal_Memory_desc;


/*
 *  This function is auto-generated with RTSC config.  It initializes the
 *  ti_sdo_ce_osal_Memory_heapList[] array.
 */
extern Void ti_sdo_ce_osal_Memory_cfgInit();

/* Symbols uto-generated with RTSC config */
extern Int ti_sdo_ce_osal_Memory_numHeaps;
extern String ti_sdo_ce_osal_Memory_heapNames[];
extern ti_sysbios_heaps_HeapMem_Handle ti_sdo_ce_osal_Memory_heapList[];

/*
 * Memory_DEFAULTPARAMS should be set such that legacy Memory_alloc behavior
 * is achieved (where "legacy" means before params were added).
 */
Memory_AllocParams Memory_DEFAULTPARAMS = {
    Memory_SEG,
    Memory_NONCACHED,
    0,
    0                   /* will get assigned in Memory_init */
};

/*
 *  Arrays to keep track of initial base and size of memory segments, in
 *  case they are redefined, so they can be restored later.
 */
static UInt32 *Memory_originalBase = NULL;
static UInt32 *Memory_originalSize = NULL;

/*
 *  ======== segAlloc ========
 */
static inline Ptr segAlloc(IHeap_Handle heap, UInt size, UInt align)
{
    if (align == Memory_DEFAULTALIGNMENT) {
        align = 0;
    }

    return (xdc_runtime_Memory_alloc(heap, size, align, NULL));
}

/*
 *  ======== segFree ========
 */
static inline Void segFree(IHeap_Handle heap, Ptr addr, UInt size)
{
    xdc_runtime_Memory_free(heap, addr, size);
}

/*
 *  ======== Memory_alloc ========
 */
Ptr Memory_alloc(UInt size, Memory_AllocParams *params)
{
    Ptr addr;

    Log_print2(Diags_ENTRY, "[+E] Memory_alloc> Enter(size=0x%x, params=0x%x)",
            (IArg)size, (IArg)params);

    if (params == NULL) {
        params = &Memory_DEFAULTPARAMS;
    }

    addr = segAlloc((IHeap_Handle)params->seg, size, params->align);

    Log_print1(Diags_EXIT, "[+X] Memory_alloc> return (0x%x)", (IArg)addr);

    return addr;
}


/*
 *  ======== Memory_cacheInv ========
 */
Void Memory_cacheInv(Ptr addr, Int sizeInBytes)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_cacheInv> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_inv(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_EXIT, "[+X] Memory_cacheInv> return");
}


/*
 *  ======== Memory_cacheWb ========
 */
Void Memory_cacheWb(Ptr addr, Int sizeInBytes)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_cacheWb> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_wb(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_EXIT, "[+X] Memory_cacheWb> return");
}


/*
 *  ======== Memory_cacheWbInv ========
 */
Void Memory_cacheWbInv(Ptr addr, Int sizeInBytes)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_cacheWbInv> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_wbInv(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_EXIT, "[+X] Memory_cacheWbInv> return");
}


/*
 *  ======== Memory_cacheWbInvAll ========
 */
Void Memory_cacheWbInvAll()
{
    Log_print0(Diags_ENTRY, "[+E] Memory_cacheWbInvAll> Enter()");

//#ifdef xdc_target__isaCompatible_64P
    Cache_wbInvAll();
//#endif
    Log_print0(Diags_EXIT, "Memory_cacheWbInvAll> return");
}

/*
 *  ======== Memory_contigAlloc ========
 */
Ptr Memory_contigAlloc(UInt size, UInt align)
{
    Ptr addr;

    Log_print2(Diags_ENTRY, "[+E] Memory_contigAlloc> "
            "Enter(size=%d, align=%d)", (IArg)size, (IArg)align);

    addr = segAlloc(xdc_runtime_Memory_defaultHeapInstance, size, align);

    Log_print1(Diags_EXIT, "[+X] Memory_contigAlloc> return (0x%x)",
            (IArg)addr);

    return addr;
}


/*
 *  ======== Memory_contigFree ========
 */
Bool Memory_contigFree(Ptr addr, UInt size)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_contigFree> "
            "Enter(addr=0x%x, size=%d)", (IArg)addr, (IArg)size);

    segFree(xdc_runtime_Memory_defaultHeapInstance, addr, size);

    Log_print0(Diags_EXIT, "[+X] Memory_contigFree> Exit");

    return (TRUE);
}


/*
 *  ======== Memory_free ========
 */
Bool Memory_free(Ptr addr, UInt size, Memory_AllocParams *params)
{
    Bool retVal;

    Log_print3(Diags_ENTRY, "[+E] Memory_free> "
            "Enter(addr=0x%x, size=0x%x, params=0x%x)",
            (IArg)addr, (IArg)size, (IArg)params);

    if (params == NULL) {
        params = &Memory_DEFAULTPARAMS;
    }

    /*
     * TODO:M  Is there a way to validate that params->seg is valid?
     * If so, we should validate and set retVal accordingly
     */
    retVal = TRUE;

    segFree((IHeap_Handle)params->seg, addr, size);

    Log_print0(Diags_EXIT, "[+X] Memory_free> Exit");

    return (retVal);
}


#ifdef xdc_target__isaCompatible_64P
extern cregister volatile Uns DNUM;

static inline UInt32 Memory_LOC_TO_GLOB(UInt32 loc_addr)
{
    UInt32 tmp = loc_addr;

    if ((tmp & 0xFF000000) == 0) {
        return ((1 << 28) | (DNUM << 24) | tmp);
    }
    else {
       return (loc_addr);
    }
}
#else
#define Memory_LOC_TO_GLOB(addr) (addr)
#endif


/*
 *  ======== Memory_getBufferPhysicalAddress ========
 *  Note, in this implementation, the first arg "virtualAddress" is
 *  a multicore device's 'localAddr'.
 */
UInt32 Memory_getBufferPhysicalAddress(Ptr virtualAddress, Int sizeInBytes,
    Bool *isContiguous)
{
    Log_print3(Diags_ENTRY,
            "[+E] Memory_getBufferPhysicalAddress(0x%x, 0x%x, 0x%x)",
            (IArg)virtualAddress, (IArg)sizeInBytes, (IArg)isContiguous);

    if (isContiguous != NULL) {
        *isContiguous = TRUE;
    }
    return (Memory_LOC_TO_GLOB((UInt32)virtualAddress));
}


/*
 *  ======== Memory_getBufferVirtualAddress ========
 *  TODO:H - for multicore devices, we probably need to implement a GLOB_TO_LOC!
 */
Ptr Memory_getBufferVirtualAddress(
        UInt32 physicalAddress, Int sizeInBytes)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_getBufferVirtualAddress(0x%x, 0x%x)",
            (IArg)physicalAddress, (IArg)sizeInBytes);

    return ((Ptr)physicalAddress);
}

/*
 *  ======== Memory_getHeapId ========
 */
Int Memory_getHeapId(String name)
{
    Int     i;

    for (i = 0; i < ti_sdo_ce_osal_Memory_numHeaps; i++) {
        if (strcmp(name, ti_sdo_ce_osal_Memory_heapNames[i]) == 0) {
            return (i);
        }
    }

    return (-1);
}

/*
 *  ======== Memory_getNumHeaps ========
 */
Int Memory_getNumHeaps()
{
    return (ti_sdo_ce_osal_Memory_numHeaps);
}

/*
 *  ======== Memory_init ========
 */
Bool Memory_init(Void)
{
    Registry_Result   result;
    Int               i;
    Memory_Stat       stat;

    static Bool curInit = FALSE;

    if (curInit != TRUE) {
        curInit = TRUE;
        Memory_DEFAULTPARAMS.seg = (UInt)xdc_runtime_Memory_defaultHeapInstance;

        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_osal_Memory_desc,
                Memory_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Memory_MODNAME);
        }

        ti_sdo_ce_osal_Memory_cfgInit(); 

        /*
         *  Note: Memory_originalBase and Memory_originalSize are only
         *  accessed through the RMS server thread, so we don't need to
         *  alloc these buffers inside a Gate_enter() call.
         */
        if (Memory_originalBase == NULL) {
            Memory_originalBase = xdc_runtime_Memory_alloc(NULL,
                    ti_sdo_ce_osal_Memory_numHeaps * sizeof(Uint32), 0, NULL);
            if (Memory_originalBase == NULL) {
                Log_print0(Diags_USER7, "Memory_init> Memory_alloc() failed");
                return (FALSE);
            }
        }

        if (Memory_originalSize == NULL) {
            Memory_originalSize = xdc_runtime_Memory_alloc(NULL,
                    ti_sdo_ce_osal_Memory_numHeaps * sizeof(Uint32), 0, NULL);
            if (Memory_originalSize == NULL) {
                xdc_runtime_Memory_free(NULL, Memory_originalBase,
                        sizeof(Uint32) * ti_sdo_ce_osal_Memory_numHeaps);
                Log_print0(Diags_USER7, "Memory_init> Memory_alloc() failed");
                return (FALSE);
            }
        }

        /*
         *  Keep track of original size and base of memory heaps in case
         *  someone does a Memory_redefine() then a Memory_restoreHeap().
         */
        for (i = 0; i < ti_sdo_ce_osal_Memory_numHeaps; i++) {
            if (!Memory_segStat(i, &stat)) {
                Log_print1(Diags_USER7, "Memory_init> Memory_segStat(%d) "
                        "failed!", (IArg)i);
                Memory_originalBase[i] = (UInt32)-1;
                Memory_originalSize[i] = 0;
            }
            else {
                Memory_originalBase[i] = stat.base;
                Memory_originalSize[i] = stat.size;
            }
        }
    }

    return (TRUE);
}


/*
 *  ======== Memory_exit ========
 */
Void Memory_exit(Void)
{
    /*
     * Probably should manage curInit here, but BIOS-based systems typically
     * don't methodically tear down.
     */
}

/*
 *  ======== Memory_redefine ========
 */
Bool ti_sdo_ce_osal_Memory_redefine(Int segId, Uint32 base, Uint32 size)
{
    HeapMem_Params params;
    HeapMem_Handle heap;
    Memory_Stat    stat;

    if ((segId < 0) || (segId >= ti_sdo_ce_osal_Memory_numHeaps)) {
        Log_print2(Diags_USER7, "Memory_redefine> segId (%d) out of range. "
                "Should be < %d", (IArg)segId,
                (IArg)ti_sdo_ce_osal_Memory_numHeaps);
        return (FALSE);
    }

    if (!Memory_segStat(segId, &stat)) {
        Log_print0(Diags_USER7, "Memory_redefine> Memory_segStat() failed!");
        return (FALSE);
    }

    if (stat.used > 0) {
        Log_print0(Diags_USER7, "Memory_redefine> Heap in use!");
        return (FALSE);
    }

    heap = ti_sdo_ce_osal_Memory_heapList[segId];

    HeapMem_destruct(HeapMem_struct(heap));

    HeapMem_Params_init(&params);
    params.size = size;
    params.buf = (Ptr)base;

    HeapMem_construct(HeapMem_struct(heap), &params);

    return (TRUE);
}

/*
 *  ======== Memory_restoreHeap ========
 */
Bool ti_sdo_ce_osal_Memory_restoreHeap(Int segId)
{
    Bool    retVal;

    retVal = Memory_redefine(segId, Memory_originalBase[segId],
            Memory_originalSize[segId]);

    return (retVal);
}

/*
 *  ======== Memory_segStat ========
 */
Bool Memory_segStat(Int segId, Memory_Stat *statbuf)
{
    HeapMem_ExtendedStats    extStats;
    xdc_runtime_Memory_Stats memStats;
    HeapMem_Handle           heap;
    Int                      numHeaps;

    // numHeaps = HeapMem_Object_count();
    numHeaps = ti_sdo_ce_osal_Memory_numHeaps;

    if ((segId < 0) || (segId >= numHeaps)) {
        return (FALSE);
    }

    //heap = HeapMem_Object_get(NULL, segId);
    heap = ti_sdo_ce_osal_Memory_heapList[segId];
    xdc_runtime_Memory_getStats((xdc_runtime_IHeap_Handle)heap, &memStats);
    HeapMem_getExtendedStats(heap, &extStats);

    statbuf->name = ti_sdo_ce_osal_Memory_heapNames[segId];

    statbuf->base = (UInt32)extStats.buf;
    statbuf->size = (UInt)memStats.totalSize;
    statbuf->used = statbuf->size - (UInt)memStats.totalFreeSize;
    statbuf->length = (UInt)memStats.largestFreeSize;

    return (TRUE);
}


#if 0
/*
 *  ======== Memory_registerContigBuf ========
 */
Void Memory_registerContigBuf(
    UInt32 virtualAddress, UInt32 sizeInBytes, UInt32 physicalAddress )
{
}

/*
 *  ======== Memory_unregisterContigBuf ========
 */
Void Memory_unregisterContigBuf( UInt32 virtualAddress, UInt32 sizeInBytes )
{
}

/*
 *  ======== Memory_dumpKnownContigBufs ========
 */
Void Memory_dumpKnownContigBufsList()
{
}
#endif
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,1; 2-24-2012 19:30:18; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


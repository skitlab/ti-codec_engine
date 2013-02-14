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
 *  ======== Memory_noOS.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_osal_Memory_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>



/* default memory segment is something that is ignored outside of BIOS */
#define DEFAULTSEGMENT 0

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

static Void cleanup(Void);

/*
 * Memory_DEFAULTPARAMS should be set such that legacy Memory_alloc behavior
 * is achieved (where "legacy" means before params were added).
 *
 * The implementation herein doesn't use the params at all, so these default
 * params are here for completeness.
 */
Memory_AllocParams Memory_DEFAULTPARAMS = {
    Memory_MALLOC,
    Memory_NONCACHED,
    0,
    DEFAULTSEGMENT
};

Registry_Desc ti_sdo_ce_osal_Memory_desc;

static Int regInit = 0;     /* Registry_addModule() called */


/*
 *  ======== Memory_alloc ========
 */
Ptr Memory_alloc(UInt size, Memory_AllocParams *params)
{
    Log_print1(Diags_ENTRY, "[+E] Memory_alloc(0x%lx)", (IArg)size);

    return (Memory_segAlloc(DEFAULTSEGMENT, size, 0));
}


/*
 *  ======== Memory_cacheInv ========
 */
Void Memory_cacheInv(Ptr addr, Int sizeInBytes)
{
}


/*
 *  ======== Memory_cacheWb ========
 */
Void Memory_cacheWb(Ptr addr, Int sizeInBytes)
{
}


/*
 *  ======== Memory_cacheWbInv ========
 */
Void Memory_cacheWbInv(Ptr addr, Int sizeInBytes)
{
}


/*
 *  ======== Memory_cacheWbInvAll ========
 */
Void Memory_cacheWbInvAll()
{
}

/*
 *  ======== Memory_contigAlloc ========
 */
Ptr Memory_contigAlloc(UInt size, UInt align)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_contigAlloc(0x%lx, 0x%lx)",
            (IArg)size, (IArg)align);

    return (Memory_segAlloc(DEFAULTSEGMENT, size, align));
}


/*
 *  ======== Memory_contigFree ========
 */
Bool Memory_contigFree(Ptr addr, UInt size)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_contigFree(0x%lx, 0x%lx)",
            (IArg)addr, (IArg)size);

    return (Memory_segFree(DEFAULTSEGMENT, addr, size));
}


/*
 *  ======== Memory_contigStat ========
 */
Bool Memory_contigStat(Memory_Stat *statbuf)
{
    Log_print1(Diags_ENTRY, "[+E] Memory_contigStat(0x%lx)", (IArg)statbuf);

    return (Memory_segStat(DEFAULTSEGMENT, statbuf));
}


/*
 *  ======== Memory_free ========
 */
Bool Memory_free(Ptr addr, UInt size, Memory_AllocParams *params)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_free(0x%lx, 0x%lx)",
            (IArg)addr, (IArg)size);

    return (Memory_segFree(DEFAULTSEGMENT, addr, size));
}


/*
 *  ======== Memory_getBufferPhysicalAddress ========
 */
UInt32 Memory_getBufferPhysicalAddress(Ptr virtualAddress, Int sizeInBytes,
    Bool *isContiguous)
{
    Log_print3(Diags_ENTRY,
            "[+E] Memory_getBufferPhysicalAddress(0x%lx, 0x%lx, 0x%lx)",
            (IArg)virtualAddress, (IArg)sizeInBytes, (IArg)isContiguous);

    if (isContiguous != NULL) {
        *isContiguous = TRUE;
    }
    return ((Uint32)virtualAddress);
}


/*
 *  ======== Memory_getBufferVirtualAddress ========
 */
Ptr Memory_getBufferVirtualAddress(
        UInt32 physicalAddress, Int sizeInBytes)
{
    Log_print2(Diags_ENTRY,
            "[+E] Memory_getBufferVirtualAddress(0x%lx, 0x%lx)",
            (IArg)physicalAddress, (IArg)sizeInBytes);

    return ((Ptr)physicalAddress);
}

/*
 *  ======== Memory_init ========
 */
Bool Memory_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_osal_Memory_desc,
                Memory_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Memory_MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;
        Global_atexit((Fxn)cleanup);
    }

    return (TRUE);
}

/*
 *  ======== Memory_exit ========
 */
Void Memory_exit(Void)
{
}

/*
 *  ======== Memory_getHeapId ========
 */
Int Memory_getHeapId(String name)
{
    /* unsupported, return -1 */
    return (-1);
}

/*
 *  ======== Memory_getNumHeaps ========
 */
Int Memory_getNumHeaps()
{
    return (1);
}

/*
 *  ======== Memory_redefine ========
 */
Bool Memory_redefine(Int segId, Uint32 base, Uint32 size)
{
    /* unsupported, return FALSE */
    return (FALSE);
}

/*
 *  ======== Memory_restoreHeap ========
 */
Bool Memory_restoreHeap(Int segId)
{
    /* unsupported, return FALSE */
    return (FALSE);
}

/*
 *  ======== Memory_segAlloc ========
 */
Ptr Memory_segAlloc(Int segid, UInt size, UInt align)
{
    Ptr buf = malloc(size);

    Log_print3(Diags_ENTRY, "[+E] Memory_segAlloc(0x%lx, 0x%lx, 0x%lx)",
            (IArg)segid, (IArg)size, (IArg)align);

    if (buf == NULL) {
        return (NULL);
    }

    memset(buf, '\0', size);

    return (buf);
}


/*
 *  ======== Memory_segFree ========
 */
Bool Memory_segFree(Int segid, Ptr addr, UInt size)
{
    Log_print3(Diags_ENTRY, "[+E] Memory_segFree(0x%lx, 0x%lx, 0x%lx)",
            (IArg)segid, (IArg)addr, (IArg)size);

    free(addr);

    return (TRUE);
}


/*
 *  ======== Memory_segStat ========
 */
Bool Memory_segStat(Int segid, Memory_Stat *statbuf)
{
    Log_print2(Diags_ENTRY, "[+E] Memory_segStat(0x%lx, 0x%lx)",
            (IArg)segid, (IArg)statbuf);

    statbuf->name   = NULL;
    statbuf->size   = 0;
    statbuf->used   = 0;
    statbuf->length = 0;

    /* Only return TRUE if segid is 0 */
    return (!segid);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    if (curInit != FALSE) {
        curInit = FALSE;
    }
}


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
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,1; 2-24-2012 19:30:21; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


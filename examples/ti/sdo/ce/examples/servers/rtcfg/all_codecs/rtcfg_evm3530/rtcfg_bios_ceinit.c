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
 *  ======== rtcfg_bios_ceinit.c ========
 *  Codec Engine configuration for non-RTSC config examples. Compile this file
 *  as is, or copy this file to your source directory and modify as needed.
 */

#include <xdc/std.h>

#include <ti/sysbios/heaps/HeapMem.h>

/*
 *  Modify this section if you are planning to use Server APIs for getting
 *  server memory statistics, or redefining server heaps. Otherwise this
 *  file can be left as is.
 */

/*
 *  If not using any Server APIs from the host to obtain the servers
 *  memory statistics or to redefine server heaps, then set USEDEFAULT
 *  to TRUE.
 *  Otherwise, set USEDEFAULT to FALSE and configure the variables below.
 */
#define USEDEFAULT FALSE

/*
 *  If using Server APIs for memory stats or redefining heaps, set this to
 *  the number of ti.sysbios.heaps.HeapMem objects configured in the server.
 */
#define NUMHEAPS 3

/*
 *  ======== Memory_numHeaps ========
 *  The number of ti.sysbios.heaps.HeapMem objects configured in the server.
 */
#if USEDEFAULT
/* Default ti_sdo_ce_osal_Memory_numHeaps value */
Int ti_sdo_ce_osal_Memory_numHeaps = 0;
#else
/* Example ti_sdo_ce_osal_Memory_numHeaps value*/
Int ti_sdo_ce_osal_Memory_numHeaps = NUMHEAPS;
#endif

/*
 *  ======== Memory_heapNames ========
 *  Array containing names for the heaps configured on the target.
 */
#if USEDEFAULT
/* Default ti_sdo_ce_osal_Memory_heapNames array */
String *ti_sdo_ce_osal_Memory_heapNames = NULL;
#else
/*
 *  Example ti_sdo_ce_osal_Memory_heapNames[] array.
 *  If using Server APIs for memory stats or redefining heaps, set these array
 *  entries to names with which you would like to identify each of the
 *  ti.sysbios.heaps.HeapMem objects.
 */
String ti_sdo_ce_osal_Memory_heapNames[NUMHEAPS] = {
    "EXT_HEAP",
    "INT_HEAP",
    "EXTALG_HEAP",
};
#endif

/*
 *  ======== Memory_heapList ========
 *  Array of handles of ti.sysbios.heaps.HeapMem objects configured in the
 *  server. This array must be initialized in the Memory_cfgInit() function
 *  below.
 */
#if USEDEFAULT
/* Default ti_sdo_ce_osal_Memory_heapList array */
ti_sysbios_heaps_HeapMem_Handle *ti_sdo_ce_osal_Memory_heapList = NULL;
#else
/* Example ti_sdo_ce_osal_Memory_heapList[] array */
ti_sysbios_heaps_HeapMem_Handle ti_sdo_ce_osal_Memory_heapList[NUMHEAPS];

/*
 *  Example declarations of externally defined ti.sysbios.heaps.HeapMem
 *  handles.
 *  If using Server APIs for memory stats or redefining heaps, add the
 *  extern declarations of each of the ti.sysbios.heaps.HeapMem handles.
 */
extern ti_sysbios_heaps_HeapMem_Handle EXT_HEAP;
extern ti_sysbios_heaps_HeapMem_Handle INT_HEAP;
extern ti_sysbios_heaps_HeapMem_Handle EXTALG_HEAP;
#endif

/*
 *  ======== Memory_cfgInit ========
 *  Set up table of HeapMem handles that correspond to array of heap names.
 *  This is only used for getting memory heap statistics.
 */
Void ti_sdo_ce_osal_Memory_cfgInit()
{
#if USEDEFAULT
    /* No initialization needed if not using Server APIs*/
#else
    /* Example initialization of Memory_heapList array */
    /*
     *  Make sure the handles are ordered correctly with respect to
     *  the names in ti_sdo_ce_osal_Memory_heapNames[].
     */
    ti_sdo_ce_osal_Memory_heapList[0] = EXT_HEAP;
    ti_sdo_ce_osal_Memory_heapList[1] = INT_HEAP;
    ti_sdo_ce_osal_Memory_heapList[2] = EXTALG_HEAP;
#endif
}
/*
 *  @(#) ti.sdo.ce.examples.servers; 1, 0, 0,1; 2-24-2012 19:29:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Process.h ========
 */
#ifndef ti_sdo_ce_ipc_Processor_
#define ti_sdo_ce_ipc_Processor_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for Processor
 *              functions. For example,
 *                  Diags_setMask(Processor_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define Processor_MODNAME "ti.sdo.ce.ipc.Processor"

/*
 *  ======== Processor_GTNAME ========
 */
#define Processor_GTNAME "OP"  /* TODO: Should this be changed? */

#define Processor_INVALID -1


/*
 *  Invalid processer ID
 */
#define Processor_INVALIDID 0xFFFF

/*
 *  ======== Processor_Handle ========
 */
typedef struct Processor_Obj *Processor_Handle;

/*
 *  ======== Processor_Attrs ========
 */
typedef struct Processor_Attrs {
    String  cpuId;   /* identifies the cpu to load */
    Int     argc;
    String  *argv;   /* argument array to pass to loaded process's main */
    Bool    useExtLoader;  /* TRUE if external loader is used to load slave */
} Processor_Attrs;

/*
 *  ======== Processor_CommDesc ========
 */
typedef struct Processor_CommDesc {
    Int32 numMsgs;              /* number of MessageQ messages in heap */
    Int32 msgSize;              /* size of each MessageQ message in heap */
    Int16 sharedRegionId;       /* Shared Region ID for HeapBufMP */
    Int16 heapId;               /* heap ID for MessageQ usage */
    Bool userCreatedHeap;       /* flag for controlling HeapBufMP creation */
} Processor_CommDesc;

/*
 *  ======== Processor_ATTRS ========
 */
extern Processor_Attrs Processor_ATTRS; /* default attrs */

/*
 *  ======== Processor_create ========
 */
extern Processor_Handle Processor_create(String imageName, String memMap,
    Processor_Attrs *attrs);

/*
 *  ======== Processor_delete ========
 */
extern Void Processor_delete(Processor_Handle proc);

/*
 *  ======== Processor_init ========
 */
extern Void Processor_init(Void);

/*
 *  ======== Processor_getCoreName ========
 */
extern String Processor_getCoreName(UInt32 id);

/*
 *  ======== Processor_getCoreId ========
 */
extern UInt32 Processor_getCoreId(String name);

/*
 *  ======== Processor_getNumProcs ========
 */
extern UInt32 Processor_getNumProcs(Void);

/*
 *  ======== Processor_myCoreId ========
 */
extern UInt32 Processor_myCoreId(Void);

/*
 *  ======== Processor_getHeapId ========
 */
extern UInt16 Processor_getHeapId(UInt32 coreId);

/*
 *  ======== Processor_getMsgSize ========
 */
extern UInt32 Processor_getMsgSize(UInt32 coreId);

/*
 *  ======== Processor_getNumMsgs ========
 */
extern UInt32 Processor_getNumMsgs(UInt32 coreId);

/*
 *  ======== Processor_getSharedRegionId ========
 */
extern UInt16 Processor_getSharedRegionId(UInt32 coreId);

/*
 *  ======== Processor_getUserCreatedHeapFlag ========
 */
extern Bool Processor_getUserCreatedHeapFlag(UInt32 coreId);

/*
 *  ======== Processor_wait ========
 */
extern Int Processor_wait(Processor_Handle proc);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.ipc; 2, 0, 1,1; 2-24-2012 19:29:53; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


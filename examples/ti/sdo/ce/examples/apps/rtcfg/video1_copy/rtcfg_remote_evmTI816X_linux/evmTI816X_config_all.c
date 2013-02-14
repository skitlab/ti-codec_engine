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
 * ======== examples.rtcfg.video1_copy.rtcfg_remote_evmTI816X ========
 */

#include <xdc/std.h>


/*
 *  ======== Global Configuration ========
 */

Bool Memory_skipVirtualAddressTranslation = FALSE;

UInt32 Memory_maxCbListSize = 100;


/* Arm-side DSPLINK configuration
 * ==============================
 */

/*
 * ======== ti.sdo.ce.ipc.dsplink.Processor TEMPLATE ========
 */


#include <ti/sdo/ce/ipc/Processor.h>

/*
 *  Set the Processor module defaults for communication between the
 *  ARM and the slave processors. These will be used when no per-core value
 *  is specified in the Processor_commDescs[] array (see below).
 *
 *      Processor_defaultSharedRegionId: The shared region to create a heap
 *          for allocating messages.
 *      Processor_defaultHeapId: The id of a heap that is registered with
 *          MessageQ.
 *      Processor_defaultNumMsgs: Used for the number of blocks when creating
 *          a heap for MessageQ.
 *      Processor_defaultMsgSize: Used for the block size when creating a heap
 *          for MessageQ.
 */
Int16 ti_sdo_ce_ipc_dsplink__Processor_defaultSharedRegionId = 1;
Int16 ti_sdo_ce_ipc_dsplink__Processor_defaultHeapId = 0;
Int32 ti_sdo_ce_ipc_dsplink__Processor_defaultNumMsgs = 64;
Int32 ti_sdo_ce_ipc_dsplink__Processor_defaultMsgSize = 4096;

/*
 *  Use Processor module default values for Codec Engine's MessageQ heap.
 *  Codec Engine will allocate one heap and register it with MessageQ. This
 *  heap will be used to allocate messages for inter-processor communication
 *  between the HOST and each of the slave processors.
 */
Processor_CommDesc ti_sdo_ce_ipc_dsplink__Processor_commDescs[] = {
    {
        -1,                     /* numMsgs */
        -1,                     /* msgSize */
        -1,                     /* sharedRegionId */
        -1,                     /* heapId */
        FALSE,                  /* userCreatedHeap */
    }
};

UInt32 ti_sdo_ce_ipc_dsplink__Processor_numCommDescs = 1;

/* Max timeout for MessageQ_get() allowed. */
UInt32 ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout = 4294967295UL; /* 0xFFFFFFFF */

/* configuration for interprocessor communication */

/* configure number of retries Comm_locate should do before giving up */
UInt32 Comm_LOCATERETRIES = 20;

/* size of the communication message */
UInt32 Comm_MSGSIZE = 4096;    /* Deprecated, do not modify */

/* number of Comm_MSGSIZE-sized messages in the system */
UInt32 Comm_NUMMSGS = 64;      /* Deprecated, do not modify */

#include <ti/sdo/ce/osal/Global.h>

/* Arm-side DspLink configuration tables { */

Int Global_useLinkArbiter = FALSE;



/*
 *  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,1; 2-24-2012 19:27:23; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


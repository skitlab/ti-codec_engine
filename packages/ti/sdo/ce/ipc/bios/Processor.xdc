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
/*!
 *  ======== Processor ========
 *  Empty module to enable logging for Processor.
 */

@Template("./Processor.xdt")

metaonly module Processor {
    /*
     * sharedRegionIndex & clientHeapId - default values to use for all
     * Processor instances when no per-core values are provided in the
     * coreComm[] array.  The default values for numMsgs & msgSize in
     * CommDesc are taken from the existing Ipc.armCommNumMsgs &
     * Ipc.armCommMsgSize.
     */
    config UInt16 sharedRegionId = 0;
    config UInt16 heapId = 0;

    struct CommDesc {
        UInt32 numMsgs;
        UInt32 msgSize;
        UInt16 sharedRegionId;
        UInt16 heapId;
        Bool userCreatedHeap;
    };
    config CommDesc coreComm[];

    function close();
}
/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,1; 2-24-2012 19:29:56; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


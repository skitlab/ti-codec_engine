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
 *  ======== Ipc ========
 *  BIOS ipc settings.
 */
@Template("./Ipc.xdt")

metaonly module Ipc inherits ti.sdo.ce.ipc.IIpc {
    /*!
     *  ======== armCommMsgSize ========
     *  Default size for the Arm-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where DSP Link is used.
     */
    config UInt32 armCommMsgSize = 4 * 1024;

    /* TODO:H - review this name and usage */
    config UInt32 hostCommNumMsgs = 64;

    /*
     *  ======== dspCommNumMsgQueues ========
     *  Number of message queues (that can receive and store messages) on the
     *  DSP side. Each DSP node (task) needs one message queue.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     *
     *  @_nodoc
     */
//    config UInt32 dspCommNumMsgQueues = 64;

    /*!
     *  ======== dspCommMsgSize ========
     *  Default size for the inter-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where DSP Link is not used, in special
     *  circumstances.
     *
     * @_nodoc
     */
    config UInt32 dspCommMsgSize = 1024;

    /*!
     *  ======== dspCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     *
     *  Applies only to configurations where DSP Link is not used, in special
     *  circumstances.
     *
     * @_nodoc
     */
    config UInt32 dspCommNumMsgs = 64;

    /*!
     *  ======== usePowerManagement ========
     *  Enable power Management
     *
     *  If set to true, will attempt to include power-management code
     *  where applicable.
     *
     *  This feature may not be available on all devices.
     *
     *  @_nodoc
     */
    config bool usePowerManagement = false;

    /*!
     *  ======== powerSaveMemoryBlockName ========
     *  Memory segment name for context save/restore.
     *
     *  The name of the segment to which power should be saved; if left null,
     *  will default to defaultMemSegId.
     *
     *  This feature may not be available on all devices.
     *
     *  @_nodoc
     */
    config String powerSaveMemoryBlockName = null;

    /*!
     *  ======== manageIpc ========
     *  Ipc calls will be built into the app.
     *
     *  If set to true, calls to Ipc_attach(), Ipc_detach(), etc, will be
     *  auto-generated.  If false, the app must manage these calls.
     *
     *  @_nodoc
     */
    config bool manageIpc = true;

    /*!
     * ======== dspLinkUsed ========
     * Returns true if the executable should be built with DSP Link
     *
     * @_nodoc
     */
    bool dspLinkUsed();

    /*!
     * ======== messageqUsed ========
     * Returns true if ti.sdo.ipc.MessageQ is used
     *
     * @_nodoc
     */
    bool messageqUsed();
}
/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,1; 2-24-2012 19:29:56; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


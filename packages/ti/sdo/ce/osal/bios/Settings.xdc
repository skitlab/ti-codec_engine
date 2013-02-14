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
 *  ======== Settings ========
 *  Global OS Abstract Layer Configuration
 */
@Template("./Settings.xdt")

metaonly module Settings inherits ti.sdo.ce.osal.IOsal
{
    /*!
     *  ======== traceBufferSize ========
     *  Size of the server trace buffer, in MAUs.
     *
     *  The server trace buffer is a circular buffer of characters written
     *  to by clients of ti.sdo.ce.osal.Trace (and ti.sdo.utils.trace.GT) and
     *  read by the Engine_*Trace() methods.
     *
     *  All the trace data in the target memory is stored into a globally
     *  visible character buffer
     *       Char Global_traceBuffer[ <traceBufferSize> ];
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config Int traceBufferSize = 32768;

}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,1; 2-24-2012 19:30:18; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


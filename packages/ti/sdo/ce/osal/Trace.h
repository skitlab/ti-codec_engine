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
 *  ======== Trace.h ========
 */
#ifndef ti_sdo_ce_osal_Trace_
#define ti_sdo_ce_osal_Trace_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

/*
 *  ======== Trace_getSize ========
 */
extern UInt32 Trace_getSize(Void);

/*
 *  ======== Trace_init ========
 */
extern Void Trace_init(Void);

/*
 *  ======== Trace_print ========
 */
extern Void Trace_print(String fmt, ...);

/*
 *  ======== Trace_putc ========
 */
extern Void Trace_putc(Char c);

/*
 *  ======== Trace_vprint ========
 */
extern Void Trace_vprint(String fmt, va_list va);

/*
 *  ======== Trace_fillBuf ========
 *  Fill buf with trace. Return the number of bytes copied. Store the
 *  number of remaining available bytes in 'avail', store the number of
 *  bytes that were lost due to wrapping, in 'lost'.
 */
extern UInt32 Trace_fillBuf(Char *buf, UInt32 size, UInt32 *avail,
        UInt32 *lost);

/*
 *  ======== Trace_outputFxn ========
 *  If the xdc.runtime.System support proxy is set to SysMin, this function
 *  can be configured for the SysMin outputFxn, which is called on
 *  System_flush().
 */
extern Void Trace_outputFxn(Char *buf, UInt size);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:13; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Trace.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/CBuf.h>

#include <stdio.h>
#include <stdarg.h>

#include <ti/sdo/ce/osal/Trace.h>
//#include <ti/sdo/ce/osal/CBuf.h>

#define MAXLINE 128

//CBuf_Handle Trace_system = NULL;

/*
 *  ======== Trace_bind ========
 */
Void Trace_bind(CBuf_Handle trace)
{
    //Trace_system = trace;
}

/*
 *  ======== Trace_fillBuf ========
 *  Fill buf with trace.
 */
UInt32 Trace_fillBuf(Char *buf, UInt32 size, UInt32 *avail, UInt32 *lost)
{
    return (0);
}

/*
 *  ======== Trace_getSize ========
 */
UInt32 Trace_getSize()
{
    return (0);
}

/*
 *  ======== Trace_outputFxn ========
 *  Fuction to set SysMin outputFunc to. This function gets called by
 *  SysMin_flush()
 */
Void Trace_outputFxn(Char *buf, UInt size)
{
}

/*
 *  ======== Trace_init ========
 */
Void Trace_init(Void)
{
}

/*
 *  ======== Trace_print ========
 */
Void Trace_print(String fmt, ...)
{
    va_list va;

    va_start(va, fmt);
    Trace_vprint(fmt, va);
    va_end(va);
}

/*
 *  ======== Trace_putc ========
 */
Void Trace_putc(Char c)
{
    //if (Trace_system != NULL) {
        //CBuf_putc(Trace_system, c);
    //}
}

/*
 *  ======== Trace_putBuf ========
 */
Void Trace_putBuf(Char *buf, UInt len)
{
    Int     i;
    Char   *c;

    //if (Trace_system != NULL) {
        for (i = 0, c = buf; i < len; i++, c++) {
            //CBuf_putc(Trace_system, *c);
        }
    //}
}

/*
 *  ======== Trace_vprint ========
 */
Void Trace_vprint(String fmt, va_list va)
{
    Char buf[MAXLINE];

    //if (Trace_system != NULL) {

        /* generate formated output into buf */
        vsnprintf(buf, sizeof(buf), fmt, va);
        buf[MAXLINE - 1] = '\0';
    
        /* copy to circular buffer */
        //CBuf_puts(Trace_system, buf);
    //}
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,1; 2-24-2012 19:30:22; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


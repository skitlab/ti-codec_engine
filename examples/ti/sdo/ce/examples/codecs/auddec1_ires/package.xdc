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
requires ti.sdo.fc.ires.examples.codecs.auddec1;

/*!
 *  ======== package.xdc ========
 *  Codec Engine compatible audio decoder (with IRES) codec.
 *
 *  This package wraps the audio decode IRES copy codec distributed with
 *  Framework Components, implementing the ICodec interface to enable easy
 *  integration into the Codec Engine environment.
 *
 *  A package dependency (the 'requires' statement above) is established
 *  allowing the FC package to provide the [unmodified] codec library
 *  while this package provides merely the CE-specific metadata necessary
 *  for integration.
 */
package ti.sdo.ce.examples.codecs.auddec1_ires [1, 0, 0] {
    module AUDDEC1_IRES;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.auddec1_ires; 1, 0, 0,1; 2-24-2012 19:28:47; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */

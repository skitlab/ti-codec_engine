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
 *  ======== ti.sdo.ce ========
 *  Codec Engine Core Runtime
 *
 *  This package provides the top-level Engine APIs; i.e., the APIs that are
 *  algorithm independent.  This package also provides the SPIs (System
 *  Programming Interfaces) used by individual algorithms runnable
 *  via the Codec Engine.
 *
 *  For information on using debug libraries when linking your executable,
 *  see the {@link ti.sdo.ce.global.Settings#profile} config param.
 *
 *  NOTE: If you change the version here, please update the valuse of
 *  ti_sdo_ce__versionStrring in Engine.c.
 *
 */
package ti.sdo.ce [1, 0, 6] {
    module Engine, Server;
    module VISA;
    module CERuntime;
    module Settings;
    interface ICodec;
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:26; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
function viewInitBasic(view)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var engine = xdc.useModule('ti.sdo.ce.views.CodecEngine');

    var addr = Program.getSymbolValue("Engine_config");

    var engine_config = Program.fetchStruct(engine.Engine_Config$fetchDesc, addr, true);

    var engine_desc = Program.fetchStruct(engine.Engine_Desc$fetchDesc, engine_config.engineTab, true);


    for (var i = 0;i < engine_desc.numAlgs;i++) {
        var viewElem = Program.newViewStruct('ti.sdo.ce.views.CodecEngine', 'Basic');

        view.elements.$add(viewElem);

        var alg_desc = Program.fetchStruct(engine.Engine_AlgDesc$fetchDesc, engine_desc.algTab, true);

        viewElem.algName = Program.fetchString(alg_desc.name, true);
        viewElem.isLocal = alg_desc.isLocal;
        viewElem.heapId  = engine_desc.heapId;

        engine_desc.algTab = engine_desc.algTab + engine.Engine_AlgDesc.$sizeof();
    }


 }
/*
 *  @(#) ti.sdo.ce.views; 1, 0, 0,1; 2-24-2012 19:32:16; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


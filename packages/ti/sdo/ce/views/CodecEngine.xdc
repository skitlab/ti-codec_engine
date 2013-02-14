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
package ti.sdo.ce.views;
import xdc.rov.ViewInfo;

module CodecEngine {

        struct NODE_Uuid {
        UInt32 data;
        };

        enum Engine_CachedMemType {
            Engine_USECACHEDMEM_DEFAULT = -1,  /**< Use default cache setting */
            Engine_USECACHEDMEM_NONCACHED = 0, /**< Use non-cached memory */
            Engine_USECACHEDMEM_CACHED = 1     /**< Use cached memory */
        };

        struct Engine_AlgDesc {
            String      name;           /**< Name of algorithm. */
            NODE_Uuid   uuid;           /**< Fixed length perfect hash of name. */
            Ptr         fxns;          /**< If null, served by RMS. */
            Ptr         idmaFxns;       /**< DMA resource negotiation when not null. */
            String      *typeTab;       /**< inheritance hierarchy. */
            Bool        isLocal;        /**< if TRUE, run locally. */
            Int         groupId;        /**< Resource sharing group Id. */
            Int         rpcProtocolVersion; /**< Protocol version. */
            Ptr         iresFxns;       /**< IRES_Fxns when not null. */
            Ptr        codecClassConfig; /**< codec class config data, if any */
            Engine_CachedMemType memType;  /**< Memory type for alg's mem reqs. */
        };

        struct Engine_Desc {
            String          name;       /**< Name of this Engine. */
            Engine_AlgDesc  *algTab;    /**< Table of algs available in this Engine. */
            String          remoteName; /**< Optional name of Server image to load. */
            String          linkCfg;    /**< Optional Link config (when using LAD). */
            Int             numAlgs;    /**< Number of algorithms in algTab */
            Int             heapId;     /**< Heap ID for engine allocs. */
        };

        struct Engine_Config {
            Engine_Desc *engineTab;
            String      localEngine;
        };

        metaonly struct Engine_Meta {
        String algName;
        Bool   isLocal;
        Int    heapId;
    };

    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Basic', {type: ViewInfo.MODULE_DATA, viewInitFxn: 'viewInitBasic', structName: 'Engine_Meta'}],
            ]
        });


}
/*
 *  @(#) ti.sdo.ce.views; 1, 0, 0,1; 2-24-2012 19:32:16; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


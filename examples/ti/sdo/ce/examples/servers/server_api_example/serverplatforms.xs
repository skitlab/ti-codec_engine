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
 *  ======== serverplatforms.xs ========
 *  This script builds the platforms specific to servers in this package.
 *  It is included by the package-specific _config.bld.
 */
/*
 *  Codec Engine Memory Map for ti.platforms.evm3530
 *
 *  8000_0000 - 87FF_FFFF  (128 MB)     External Memory
 *  ----------------------------------------------------
 *  8000_0000 - 84FF_FFFF  (  80 MB)     Linux (reserved)
 *  8500_0000 - 85FF_FFFF  (  16 MB)     CMEM (reserved)
 *  8600_0000 - 877F_FFFF  (  24 MB)     DDRALGHEAP (Codecs dynamic heap)
 *  8780_0000 - 87AF_FFFF  (   3 MB)     DDR2 (BIOS, Codecs, Applications)
 *  87B0_0000 - 87CF_FFFF  (   2 MB)     SR1 (SysLink IPC)
 *  87D0_0000 - 87FF_FFFF  (   3 MB)     SYSLINK (SysLink shared memory)
 */
var evm3530_ExtMemMap = {
        DDRALGHEAP: {
            name: "DDRALGHEAP",
            base: 0x86000000,
            len:  0x01800000,
            space: "data"
        },
        DDR2: {
            name: "DDR2",
            base: 0x87800000,
            len:  0x00300000,
            space: "code/data"
        },
        SR1: {
            name: "SR1",
            base: 0x87B00000,
            len:  0x00200000,
            space: "data"
        },
        SYSLINK: {
            name: "SYSLINK",
            base: 0x87D00000,
            len:  0x00300000,
            space: "data"
        }
};

Build.platformTable["ti.platforms.evm3530:DSP"] = {
    externalMemoryMap: [
        [ "DDR2",       evm3530_ExtMemMap.DDR2 ],
        [ "DDRALGHEAP", evm3530_ExtMemMap.DDRALGHEAP ],
        [ "SR1",        evm3530_ExtMemMap.SR1 ],
        [ "SYSLINK",    evm3530_ExtMemMap.SYSLINK ]
    ],
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var DM8148_DSP_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x01800000    /* 24 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the C674",
                name: "DDRALGHEAP",
                base: 0x8C800000,
                len:  0x00800000    /* 8 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F000000,
                len:  0x01000000    /* 16 MB */
            },
};

var DM8148_VIDEOM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x02000000    /* 32 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F000000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8F600000,
                len:  0x00200000    /* 2 MB */
            },
};

var DM8148_VPSSM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x02000000    /* 32 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F800000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8FE00000,
                len:  0x00200000    /* 2 MB */
            },
};

/* platform instances used by this package */
Build.platformTable["ti.platforms.evmDM8148:DSP"] = {
    externalMemoryMap: [
        [ "DDR3_DSP",   DM8148_DSP_ExtMemMap.DDR3_DSP ],
        [ "DDRALGHEAP", DM8148_DSP_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_DSP_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_DSP_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_DSP",
    dataMemory: "DDR3_DSP",
    stackMemory: "DDR3_DSP"
};

Build.platformTable["ti.platforms.evmDM8148:VIDEO-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    DM8148_VIDEOM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", DM8148_VIDEOM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_VIDEOM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_VIDEOM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

Build.platformTable["ti.platforms.evmDM8148:VPSS-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    DM8148_VPSSM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", DM8148_VPSSM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_VPSSM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_VPSSM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

/* platform instances used by this package */
Build.platformTable["ti.platforms.evmTI814X:DSP"] = {
    externalMemoryMap: [
        [ "DDR3_DSP",   DM8148_DSP_ExtMemMap.DDR3_DSP ],
        [ "DDRALGHEAP", DM8148_DSP_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_DSP_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_DSP_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_DSP",
    dataMemory: "DDR3_DSP",
    stackMemory: "DDR3_DSP"
};

Build.platformTable["ti.platforms.evmTI814X:VIDEO-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    DM8148_VIDEOM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", DM8148_VIDEOM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_VIDEOM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_VIDEOM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

Build.platformTable["ti.platforms.evmTI814X:VPSS-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    DM8148_VPSSM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", DM8148_VPSSM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   DM8148_VPSSM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   DM8148_VPSSM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

var TI813X_VIDEOM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0D000000    /* 196 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F000000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8F600000,
                len:  0x00200000    /* 2 MB */
            },
};

var TI813X_VPSSM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0D000000    /* 196 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F800000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8FE00000,
                len:  0x00200000    /* 2 MB */
            },
};

Build.platformTable["ti.platforms.evmTI813X:VIDEO-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    TI813X_VIDEOM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", TI813X_VIDEOM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   TI813X_VIDEOM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   TI813X_VIDEOM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

Build.platformTable["ti.platforms.evmTI813X:VPSS-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    TI813X_VPSSM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", TI813X_VPSSM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   TI813X_VPSSM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   TI813X_VPSSM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

var TI816X_DSP_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x01800000    /* 24 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the C674",
                name: "DDRALGHEAP",
                base: 0x8C800000,
                len:  0x00800000    /* 8 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F000000,
                len:  0x01000000    /* 16 MB */
            },
};

var TI816X_VIDEOM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x02000000    /* 32 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F000000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8F600000,
                len:  0x00200000    /* 2 MB */
            },
};

var TI816X_VPSSM3_ExtMemMap = {
            DDR3_HOST: {
                comment: "DDR3 Memory reserved for use by the A8",
                name: "DDR3_HOST",
                base: 0x80000000,
                len:  0x0B000000    /* 176 MB */
            },
            DDR3_DSP: {
                comment: "DDR3 Memory reserved for use by the C674",
                name: "DDR3_DSP",
                base: 0x8B000000,
                len:  0x02000000    /* 32 MB */
            },
            DDR3_SR1: {
                comment: "DDR3 Memory reserved for use by SharedRegion 1",
                name: "DDR3_SR1",
                base: 0x8D000000,
                len:  0x00C00000    /* 12 MB */
            },
            DDR3_HDVPSS: {
                comment: "DDR3 Memory reserved for use by HDVPSS",
                name: "DDR3_HDVPSS",
                base: 0x8DC00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_V4L2: {
                comment: "DDR3 Memory reserved for use by V4L2",
                name: "DDR3_V4L2",
                base: 0x8DE00000,
                len:  0x00200000    /* 2 MB */
            },
            DDR3_SR0: {
                comment: "DDR3 Memory reserved for use by SharedRegion 0",
                name: "DDR3_SR0",
                base: 0x8E000000,
                len:  0x01000000    /* 16 MB */
            },
            DDR3_M3: {
                comment: "DDR3 Memory reserved for use by the M3 core",
                name: "DDR3_M3",
                base: 0x8F800000,
                len:  0x00600000    /* 6 MB */
            },
            DDRALGHEAP: {
                comment: "DDR3 Memory reserved for use by algorithms on the M3",
                name: "DDRALGHEAP",
                base: 0x8FE00000,
                len:  0x00200000    /* 2 MB */
            },
};

/* platform instances used by this package */
Build.platformTable["ti.platforms.evmTI816X:DSP"] = {
    externalMemoryMap: [
        [ "DDR3_DSP",   TI816X_DSP_ExtMemMap.DDR3_DSP ],
        [ "DDRALGHEAP", TI816X_DSP_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   TI816X_DSP_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   TI816X_DSP_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_DSP",
    dataMemory: "DDR3_DSP",
    stackMemory: "DDR3_DSP"
};

Build.platformTable["ti.platforms.evmTI816X:VIDEO-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    TI816X_VIDEOM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", TI816X_VIDEOM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   TI816X_VIDEOM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   TI816X_VIDEOM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

Build.platformTable["ti.platforms.evmTI816X:VPSS-M3"] = {
    externalMemoryMap: [
        [ "DDR3_M3",    TI816X_VPSSM3_ExtMemMap.DDR3_M3 ],
        [ "DDRALGHEAP", TI816X_VPSSM3_ExtMemMap.DDRALGHEAP ],
        [ "DDR3_SR1",   TI816X_VPSSM3_ExtMemMap.DDR3_SR1 ],
        [ "DDR3_SR0",   TI816X_VPSSM3_ExtMemMap.DDR3_SR0 ]
    ],
    codeMemory: "DDR3_M3",
    dataMemory: "DDR3_M3",
    stackMemory: "DDR3_M3"
};

/*
 *  Multicore app-specific external memory map for ti.platforms.evm6472
 *
 *  E000_0000 - EFFF_FFFF  (256 MB)     External Memory
 *  ----------------------------------------------------
 *  E000_0000 - E3FF_FFFF  ( 64 MB)     Core 0 App Data Buffers
 *  E400_0000 - E5FF_FFFF  ( 32 MB)     Core 0 .text
 *  E600_0000 - E7FF_FFFF  ( 32 MB)     Core 1 .text
 *  E800_0000 - E9FF_FFFF  ( 32 MB)     Core 2 .text
 *  EA00_0000 - EBFF_FFFF  ( 32 MB)     Core 3 .text
 *  EC00_0000 - EDFF_FFFF  ( 32 MB)     Core 4 .text
 *  EE00_0000 - EFFF_FFFF  ( 32 MB)     Core 5 .text
 *
 * Note that only the servers (core 1-5) are configured in this file.  The
 * server memory maps must align with the app memory map (on core 0).
 */
var ti_platforms_evm6472_serverMemoryMap_core1 = [
    [ "DDR2", {
        name: "DDR2",
        base: 0xE6000000,
        len:  0x2000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6472:CORE1"] = {
    externalMemoryMap: ti_platforms_evm6472_serverMemoryMap_core1,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var ti_platforms_evm6472_serverMemoryMap_core2 = [
    [ "DDR2", {
        name: "DDR2",
        base: 0xE8000000,
        len:  0x2000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6472:CORE2"] = {
    externalMemoryMap: ti_platforms_evm6472_serverMemoryMap_core2,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var ti_platforms_evm6472_serverMemoryMap_core3 = [
    [ "DDR2", {
        name: "DDR2",
        base: 0xEA000000,
        len:  0x2000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6472:CORE3"] = {
    externalMemoryMap: ti_platforms_evm6472_serverMemoryMap_core3,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var ti_platforms_evm6472_serverMemoryMap_core4 = [
    [ "DDR2", {
        name: "DDR2",
        base: 0xEC000000,
        len:  0x2000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6472:CORE4"] = {
    externalMemoryMap: ti_platforms_evm6472_serverMemoryMap_core4,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var ti_platforms_evm6472_serverMemoryMap_core5 = [
    [ "DDR2", {
        name: "DDR2",
        base: 0xEE000000,
        len:  0x2000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6472:CORE5"] = {
    externalMemoryMap: ti_platforms_evm6472_serverMemoryMap_core5,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

/*
 *  Multicore app-specific external memory map for ti.platforms.evm6474
 *
 *  8000_0000 - 87FF_FFFF  (128 MB)     External Memory
 *  ----------------------------------------------------
 *  8000_0000 - 81FF_FFFF  ( 32 MB)     IPC Shared Memory
 *  8200_0000 - 83FF_FFFF  ( 32 MB)     Core 0 .text + App Data Buffers
 *  8400_0000 - 85FF_FFFF  ( 32 MB)     Core 1 .text
 *  8600_0000 - 87FF_FFFF  ( 32 MB)     Core 2 .text
 *
 * Note that only the servers (core 1-2) are configured in this file.  The
 * server memory maps must align with the app memory map (on core 0).
 */
var ti_platforms_evm6474_serverMemoryMap_core1 = [
        ["SYMGEML2RAM", {
            comment:    "1024K L2 RAM/CACHE memory",
            name:       "L2RAM",
            base:       0x00800000,
            len:        0x00100000,
            space:      "code/data",
            access:     "RWX"
        }],
        [ "DDR2_IPC", {
            name: "DDR2_IPC",
            base: 0x80000000,
            len:  0x02000000,
            space: "code/data"
        }],
        [ "DDR2", {
            name: "DDR2",
            base: 0x84000000,
            len:  0x02000000,
            space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6474:CORE1"] = {
    customMemoryMap: ti_platforms_evm6474_serverMemoryMap_core1,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

var ti_platforms_evm6474_serverMemoryMap_core2 = [
/*        ["SYMGEML2RAM", {
            comment:    "1024K L2 RAM/CACHE memory",
            name:       "L2RAM",
            base:       0x00800000,
            len:        0x00100000,
            space:      "code/data",
            access:     "RWX"
        }],
        [ "DDR2_IPC", {
            name: "DDR2_IPC",
            base: 0x80000000,
            len:  0x02000000,
            space: "code/data"
        }],*/
        [ "DDR2", {
            name: "DDR2",
            base: 0x86000000,
            len:  0x02000000,
            space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6474:CORE2"] = {
//    customMemoryMap: ti_platforms_evm6474_serverMemoryMap_core2,
    externalMemoryMap: ti_platforms_evm6474_serverMemoryMap_core2,
    codeMemory: "DDR2",
    dataMemory: "DDR2",
    stackMemory: "DDR2"
};

/*
 *  Multicore app-specific external memory map for ti.platforms.evm6678
 *
 *  8000_0000 - 9FFF_FFFF  (512 MB)     External Memory
 *  ----------------------------------------------------
 *  8000_0000 - 83FF_FFFF  ( 64 MB)     Core 0 .text and App Data Buffers
 *  8400_0000 - 87FF_FFFF  ( 64 MB)     Core 1 .text
 *  8800_0000 - 8BFF_FFFF  ( 64 MB)     Core 2 .text
 *  8C00_0000 - 8FFF_FFFF  ( 64 MB)     Core 3 .text
 *  9000_0000 - 93FF_FFFF  ( 64 MB)     Core 4 .text
 *  9400_0000 - 97FF_FFFF  ( 64 MB)     Core 5 .text
 *  9800_0000 - 9BFF_FFFF  ( 64 MB)     Core 6 .text
 *  9C00_0000 - 9FFF_FFFF  ( 64 MB)     Core 7 .text
 *
 * Note that only the servers (core 1-7) are configured in this file.  The
 * server memory maps must align with the app memory map (on core 0).
 */
var ti_platforms_evm6678_serverMemoryMap_core1 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x84000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE1"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core1,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core2 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x88000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE2"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core2,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core3 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x8C000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE3"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core3,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core4 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x90000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE4"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core4,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core5 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x94000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE5"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core5,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core6 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x98000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE6"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core6,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};

var ti_platforms_evm6678_serverMemoryMap_core7 = [
    [ "DDR3", {
        name: "DDR3",
        base: 0x9C000000,
        len:  0x4000000,   /* 32 MB */
        space: "code/data"
        }
    ]
];
Build.platformTable["ti.platforms.evm6678:CORE7"] = {
    externalMemoryMap: ti_platforms_evm6678_serverMemoryMap_core7,
    codeMemory: "DDR3",
    dataMemory: "DDR3",
    stackMemory: "DDR3"
};
/*
 *  @(#) ti.sdo.ce.examples.servers.server_api_example; 1, 0, 0,1; 2-24-2012 19:29:47; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


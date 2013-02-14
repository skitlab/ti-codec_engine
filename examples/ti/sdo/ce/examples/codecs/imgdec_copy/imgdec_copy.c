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
 *  ======== imgdec_copy.c ========
 *  Image decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IIMGDEC interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iimgdec.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(IMGDECCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(IMGDECCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(IMGDECCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(IMGDECCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(IMGDECCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "imgdec_copy_ti.h"
#include "imgdec_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &IMGDECCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    IMGDECCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    IMGDECCOPY_TI_free, /* free */                              \
    IMGDECCOPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== IMGDECCOPY_TI_IIMGDEC ========
 *  This structure defines TI's implementation of the IIMGDEC interface
 *  for the IMGDECCOPY_TI module.
 */
IIMGDEC_Fxns IMGDECCOPY_TI_IMGDECCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    IMGDECCOPY_TI_process,
    IMGDECCOPY_TI_control,
};

/*
 *  ======== IMGDECCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the IMGDECCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("IMGDECCOPY_TI_IALG .set IMGDECCOPY_TI_IMGDECCOPY");

#else

/* Symbol has a single leading underscore */
asm("_IMGDECCOPY_TI_IALG .set _IMGDECCOPY_TI_IMGDECCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns IMGDECCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif


/*
 *  ======== IMGDECCOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGDECCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(IMGDECCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== IMGDECCOPY_TI_free ========
 */
Int IMGDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (IMGDECCOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== IMGDECCOPY_TI_initObj ========
 */
Int IMGDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    return (IALG_EOK);
}


/*
 *  ======== IMGDECCOPY_TI_process ========
 */
XDAS_Int32 IMGDECCOPY_TI_process(IIMGDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IIMGDEC_InArgs *inArgs, IIMGDEC_OutArgs *outArgs)
{
    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IIMGDEC_EFAIL);
    }

    /*
     * A couple constraints for this simple "copy" codec:
     *    - Image decoding presumes a single input buffer, so only one input
     *      buffer will be decoded, regardless of inBufs->numBufs.
     *    - Given a different size of an input and output buffers, only
     *      decode (i.e., copy) the lesser of the sizes.
     */
    memcpy(outBufs->bufs[0], inBufs->bufs[0], inArgs->numBytes);

    /* outArgs->bytesconsumed reports the total number of bytes consumed */
    outArgs->bytesconsumed = inArgs->numBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->currentAU = 0;  /* TODO */
    outArgs->currentScan = 0;  /* TODO */

    return (IIMGDEC_EOK);
}


/*
 *  ======== IMGDECCOPY_TI_control ========
 */
XDAS_Int32 IMGDECCOPY_TI_control(IIMGDEC_Handle handle, IIMGDEC_Cmd id,
    IIMGDEC_DynamicParams *params, IIMGDEC_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        return (IIMGDEC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->extendedError = 0;
            status->outputHeight = 0;  /* TODO */
            status->outputWidth = 0;  /* TODO */
            status->imageWidth = 0;  /* TODO */
            status->outChromaformat = 0;  /* TODO */
            status->totalAU = 0;  /* TODO */
            status->totalScan = 0;  /* TODO */

            /* Note, intentionally no break here so we fill in bufInfo, too */

        case XDM_GETBUFINFO:
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IIMGDEC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = IIMGDEC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IIMGDEC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgdec_copy; 1, 0, 0,1; 2-24-2012 19:28:59; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


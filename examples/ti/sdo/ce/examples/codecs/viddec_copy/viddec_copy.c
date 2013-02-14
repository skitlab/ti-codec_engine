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
 *  ======== viddec_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the deprecated IVIDDEC interface
 *  defined by XDM.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_examples_codecs_viddec_copy_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <string.h>

#include <ti/xdais/dm/ividdec.h>

#include <ti/sdo/ce/global/CESettings.h>

#include "viddec_copy_ti.h"
#include "viddec_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDDECCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    VIDDECCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    VIDDECCOPY_TI_free, /* free */                              \
    VIDDECCOPY_TI_initObj, /* init */                           \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDECCOPY_TI_IVIDDEC ========
 *  This structure defines TI's implementation of the IVIDDEC interface
 *  for the VIDDECCOPY_TI module.
 */
IVIDDEC_Fxns VIDDECCOPY_TI_VIDDECCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    VIDDECCOPY_TI_process,
    VIDDECCOPY_TI_control,
};

/*
 *  ======== VIDDEC_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDECCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDDECCOPY_TI_IALG .set VIDDECCOPY_TI_VIDDECCOPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDDECCOPY_TI_IALG .set _VIDDECCOPY_TI_VIDDECCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDECCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/* Logging information */
#define MODNAME "ti.sdo.ce.examples.codecs.viddec_copy"

Registry_Desc ti_sdo_ce_examples_codecs_viddec_copy_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  ======== VIDDECCOPY_TI_alloc ========
 */
Int VIDDECCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    Registry_Result   result;


    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_examples_codecs_viddec_copy_desc,
                MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    Log_print3(Diags_ENTRY, "[+E] VIDDECCOPY_TI_alloc(0x%lx, 0x%lx, 0x%lx)",
            (IArg)algParams, (IArg)pf, (IArg)memTab);

    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDECCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== VIDDECCOPY_TI_free ========
 */
Int VIDDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    Log_print2(Diags_ENTRY, "[+E] VIDDECCOPY_TI_free(0x%lx, 0x%lx)",
            (IArg)handle, (IArg)memTab);

    VIDDECCOPY_TI_alloc(NULL, NULL, memTab);
    return (1);
}


/*
 *  ======== VIDDECCOPY_TI_initObj ========
 */
Int VIDDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    Log_print4(Diags_ENTRY, "[+E] VIDDECCOPY_TI_initObj(0x%lx, 0x%lx, 0x%lx, "
            "0x%lx)", (IArg)handle, (IArg)memTab, (IArg)p, (IArg)algParams);

    return (IALG_EOK);
}


/*
 *  ======== VIDDECCOPY_TI_process ========
 */
XDAS_Int32 VIDDECCOPY_TI_process(IVIDDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC_InArgs *inArgs, IVIDDEC_OutArgs *outArgs)
{
    XDAS_Int32 curBuf;
    XDAS_Int32 minSamples;

    Log_print5(Diags_ENTRY, "[+E] VIDDECCOPY_TI_process(0x%lx, 0x%lx, 0x%lx, "
            "0x%lx, 0x%lx)",
            (IArg)h, (IArg)inBufs, (IArg)outBufs, (IArg)inArgs, (IArg)outArgs);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        Log_print2(Diags_ENTRY, "[+E] VIDDECCOPY_TI_process, unsupported size "
                "(0x%lx, 0x%lx)", (IArg)(inArgs->size), (IArg)(outArgs->size));

        return (IVIDDEC_EFAIL);
    }

    /* outArgs->bytesConsumed reports the total number of bytes consumed */
    outArgs->bytesConsumed = 0;

    /*
     * A couple constraints for this simple "copy" codec:
     *    - Given a different number of input and output buffers, only
     *      decode (i.e., copy) the lesser number of buffers.
     *    - Given a different size of an input and output buffers, only
     *      decode (i.e., copy) the lesser of the sizes.
     */

    for (curBuf = 0; (curBuf < inBufs->numBufs) &&
        (curBuf < outBufs->numBufs); curBuf++) {

        /* there's an available in and out buffer, how many samples? */
        minSamples = inBufs->bufSizes[curBuf] < outBufs->bufSizes[curBuf] ?
            inBufs->bufSizes[curBuf] : outBufs->bufSizes[curBuf];

        /* process the data: read input, produce output */
        memcpy(outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);

        Log_print1(Diags_USER2, "[+2] VIDDECCOPY_TI_process> "
                "Processed %d bytes.", (IArg)(minSamples ));
        outArgs->bytesConsumed += minSamples;
    }

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->decodedFrameType = 0;     /* TODO */
    outArgs->outputID = inArgs->inputID;
    outArgs->displayBufs.numBufs = 0;  /* important: indicate no displayBufs */

    return (IVIDDEC_EOK);
}


/*
 *  ======== VIDDECCOPY_TI_control ========
 */
XDAS_Int32 VIDDECCOPY_TI_control(IVIDDEC_Handle handle, IVIDDEC_Cmd id,
    IVIDDEC_DynamicParams *params, IVIDDEC_Status *status)
{
    XDAS_Int32 retVal;

    Log_print4(Diags_ENTRY, "[+E] VIDDECCOPY_TI_control(0x%lx, 0x%lx, 0x%lx, "
            "0x%lx)", (IArg)handle, (IArg)id, (IArg)params, (IArg)status);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        Log_print2(Diags_ENTRY, "[+E] VIDDECCOPY_TI_control, unsupported size "
                "(0x%lx, 0x%lx)", (IArg)(params->size), (IArg)(status->size));

        return (IVIDDEC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->extendedError = 0;
            status->outputHeight = 0;  /* TODO */
            status->outputWidth = 0;  /* TODO */
            status->frameRate = 0;  /* TODO */
            status->bitRate = 0;  /* TODO */
            status->contentType = 0;  /* TODO */
            status->outputChromaFormat = 0;  /* TODO */

            /* Note, intentionally no break here so we fill in bufInfo, too */

        case XDM_GETBUFINFO:
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDDEC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = IVIDDEC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IVIDDEC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec_copy; 1, 0, 0,1; 2-24-2012 19:29:24; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


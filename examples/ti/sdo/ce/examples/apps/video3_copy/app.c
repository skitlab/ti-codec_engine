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
 *  ======== app.c ========
 */
#include <xdc/std.h>

#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/video3/viddec3.h>
#include <ti/sdo/ce/video2/videnc2.h>

#include <string.h>  /* for memset */

#include <stdio.h>
#include <stdlib.h>

/*
 * If an XDAIS algorithm _may_ use DMA, buffers provided to it need to be
 * aligned on a cache boundary.
 */

#ifdef CACHE_ENABLED

/*
 * If buffer alignment isn't set on the compiler's command line, set it here
 * to a default value.
 */
#ifndef BUFALIGN
#define BUFALIGN 128
#endif
#else

/* Not a cached system, no buffer alignment constraints */
#define BUFALIGN Memory_DEFAULTALIGNMENT

#endif


#define NSAMPLES    1024  /* must be multiple of 128 for cache/DMA reasons */
#define IFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* raw frame (input) */
#define EFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* encoded frame */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* decoded frame (output) */
#define MAXVERSIONSIZE 128

static XDAS_Int8 *inBuf;
static XDAS_Int8 *encodedBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

static String decoderName  = "viddec3_copy";
static String encoderName  = "videnc2_copy";

static Void encode_decode(VIDENC2_Handle enc, VIDDEC3_Handle dec, FILE *in,
    FILE *out);

/*
 *  ======== createInFileIfMissing ========
 */
static void createInFileIfMissing(char *inFileName)
{
    int i;
    FILE *f = fopen(inFileName, "rb");
    if (f == NULL) {
        printf("Input file '%s' not found, generating one.\n", inFileName);
        f = fopen(inFileName, "wb");
        for (i = 0; i < 1024; i++) {
            fwrite(&i, sizeof(i), 1, f);
        }
    }
    fclose(f);
}

/*
 *  ======== smain ========
 */
Int smain(String progName, String procId, String engineName,
          String inFile, String outFile)
{
    Engine_Handle ce = NULL;
    Engine_Attrs attrs;
    VIDDEC3_Handle dec = NULL;
    VIDENC2_Handle enc = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    Memory_AllocParams allocParams;

    /* create the input file if it doesn't already exist */
    createInFileIfMissing(inFile);

    Log_print4(Diags_USER1, "[+1] App-> Application started, procId %s "
               "engineName %s input-file %s output-file %s.",
               (IArg)procId, (IArg)engineName, (IArg)inFile, (IArg)outFile);

    /* allocate buffers */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = BUFALIGN;
    allocParams.seg = 0;

    inBuf = (XDAS_Int8 *)Memory_alloc(IFRAMESIZE, &allocParams);
    encodedBuf = (XDAS_Int8 *)Memory_alloc(EFRAMESIZE, &allocParams);
    outBuf = (XDAS_Int8 *)Memory_alloc(OFRAMESIZE, &allocParams);
    versionBuf = (XDAS_Int8 *)Memory_alloc(MAXVERSIONSIZE, &allocParams);

    if ((inBuf == NULL) || (encodedBuf == NULL) || (outBuf == NULL) ||
            (versionBuf == NULL)) {

        goto end;
    }

    /* open file streams for input and output */
    if ((in = fopen(inFile, "rb")) == NULL) {
        printf("App-> ERROR: can't read file %s\n", inFile);
        goto end;
    }
    if ((out = fopen(outFile, "wb")) == NULL) {
        printf("App-> ERROR: can't write to file %s\n", outFile);
        goto end;
    }

    /* Initialize attrs fields to default values, and set the procId */
    Engine_initAttrs(&attrs);
    attrs.procId = procId;

    /* Open the Engine */
    if ((ce = Engine_open(engineName, &attrs, NULL)) == NULL) {
        fprintf(stderr, "%s: error: can't open engine %s\n",
            progName, engineName);
        goto end;
    }

    /* allocate and initialize video decoder on the engine */
    dec = VIDDEC3_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    /* allocate and initialize video encoder on the engine */
    enc = VIDENC2_create(ce, encoderName, NULL);
    if (enc == NULL) {
        fprintf(stderr, "%s: error: can't open codec %s\n",
            progName, encoderName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    encode_decode(enc, dec, in, out);

end:
    /* teardown the codecs */
    if (enc) {
        VIDENC2_delete(enc);
    }
    if (dec) {
        VIDDEC3_delete(dec);
    }

    /* close the engine */
    if (ce) {
        Engine_close(ce);
    }

    /* close the files */
    if (in) {
        fclose(in);
    }
    if (out) {
        fclose(out);
    }

    /* free buffers */
    if (inBuf) {
        Memory_free(inBuf, IFRAMESIZE, &allocParams);
    }
    if (encodedBuf) {
        Memory_free(encodedBuf, EFRAMESIZE, &allocParams);
    }
    if (outBuf) {
        Memory_free(outBuf, OFRAMESIZE, &allocParams);
    }
    if (versionBuf) {
        Memory_free(versionBuf, MAXVERSIONSIZE, &allocParams);
    }

    Log_print0(Diags_USER1, "app done.");
    return (0);
}

/*
 *  ======== encode_decode ========
 */
static Void encode_decode(VIDENC2_Handle enc, VIDDEC3_Handle dec, FILE *in,
    FILE *out)
{
    Int                         n;
    Int32                       status;

    VIDDEC3_InArgs              decInArgs;
    VIDDEC3_OutArgs             decOutArgs;
    VIDDEC3_DynamicParams       decDynParams;
    VIDDEC3_Status              decStatus;

    VIDENC2_InArgs              encInArgs;
    VIDENC2_OutArgs             encOutArgs;
    VIDENC2_DynamicParams       encDynParams;
    VIDENC2_Status              encStatus;

    IVIDEO2_BufDesc             encInBufDesc;
    XDM2_BufDesc                encOutBufDesc;

    XDM2_BufDesc                decInBufDesc;
    XDM2_BufDesc                decOutBufDesc;

    /* initialize the buffer descriptors */
    encOutBufDesc.numBufs = decInBufDesc.numBufs =
        decOutBufDesc.numBufs = 1;

    encInBufDesc.numPlanes = 1;       /* Just one plane of data to encode */
    encInBufDesc.numMetaPlanes = 0;   /* No meta data */
    encInBufDesc.dataLayout = 0;      /* TODO */

    encInBufDesc.planeDesc[0].bufSize.bytes =
            encOutBufDesc.descs[0].bufSize.bytes =
            decInBufDesc.descs[0].bufSize.bytes =
            decOutBufDesc.descs[0].bufSize.bytes = NSAMPLES;

    encInBufDesc.planeDesc[0].memType = XDM_MEMTYPE_ROW;
    encInBufDesc.planeDesc[0].buf = inBuf;

    encOutBufDesc.descs[0].buf = encodedBuf;
    encOutBufDesc.descs[0].memType = XDM_MEMTYPE_ROW;
    decInBufDesc.descs[0].buf = encodedBuf;
    decInBufDesc.descs[0].memType = XDM_MEMTYPE_ROW;
    decOutBufDesc.descs[0].buf = outBuf;
    decOutBufDesc.descs[0].memType = XDM_MEMTYPE_ROW;

    encInBufDesc.imageRegion.topLeft.x = 0;  /* TODO */
    encInBufDesc.imageRegion.topLeft.y = 0;  /* TODO */
    encInBufDesc.imageRegion.bottomRight.x = 0;  /* TODO */
    encInBufDesc.imageRegion.bottomRight.y = 0;  /* TODO */
    encInBufDesc.activeFrameRegion.topLeft.x = 0;  /* TODO */
    encInBufDesc.activeFrameRegion.topLeft.y = 0;  /* TODO */
    encInBufDesc.activeFrameRegion.bottomRight.x = 0;  /* TODO */
    encInBufDesc.activeFrameRegion.bottomRight.y = 0;  /* TODO */
    encInBufDesc.imagePitch[0] = 0;  /* TODO */
    encInBufDesc.imagePitch[1] = 0;  /* TODO */
    encInBufDesc.imagePitch[2] = 0;  /* TODO */
    encInBufDesc.frameType      = IVIDEO_FRAMETYPE_DEFAULT;  /* TODO */
    encInBufDesc.topFieldFirstFlag = XDAS_FALSE;   /* TODO */
    encInBufDesc.repeatFirstFieldFlag = XDAS_FALSE;     /* TODO */

    /* initialize all "sized" fields */
    encInArgs.size    = sizeof(encInArgs);
    decInArgs.size    = sizeof(decInArgs);
    encOutArgs.size   = sizeof(encOutArgs);
    decOutArgs.size   = sizeof(decOutArgs);
    encDynParams.size = sizeof(encDynParams);
    decDynParams.size = sizeof(decDynParams);
    encStatus.size    = sizeof(encStatus);
    decStatus.size    = sizeof(decStatus);

    /*
     * Note that we use versionBuf in both the encoder and decoder.  In this
     * application, this is okay, as there is always only one user of
     * the buffer.  Not all applications can make this assumption.
     */
    encStatus.data.buf     = decStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = decStatus.data.bufSize = MAXVERSIONSIZE;

    /* if the codecs support it, dump their versions */
    status = VIDDEC3_control(dec, XDM_GETVERSION, &decDynParams, &decStatus);
    Log_print1(Diags_USER1, "Decoder version:  %s",
        (status == VIDDEC3_EOK ? ((IArg)decStatus.data.buf) : (IArg)"[unknown]"));

    status = VIDENC2_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    Log_print1(Diags_USER1, "Encoder version:  %s",
        (status == VIDENC2_EOK ? ((IArg)encStatus.data.buf) : (IArg)"[unknown]"));

    /*
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = VIDENC2_control(enc, XDM_GETBUFINFO, &encDynParams, &encStatus);
    if (status != VIDENC2_EOK) {
        /* failure, report error and exit */
        Log_print1(Diags_USER7, "encode control status = %ld", status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((encInBufDesc.numPlanes < encStatus.bufInfo.minNumInBufs) ||
            (IFRAMESIZE < encStatus.bufInfo.minInBufSize[0].bytes) ||
            (encStatus.bufInfo.inBufMemoryType[0] != XDM_MEMTYPE_ROW) ||
            (encOutBufDesc.numBufs < encStatus.bufInfo.minNumOutBufs) ||
            (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0].bytes) ||
            (encStatus.bufInfo.outBufMemoryType[0] != XDM_MEMTYPE_ROW)) {

        /* failure, report error and exit */
        Log_print0(Diags_USER7, "Error:  encoder codec feature conflict");
        return;
    }

    status = VIDDEC3_control(dec, XDM_GETBUFINFO, &decDynParams, &decStatus);
    if (status != VIDDEC3_EOK) {
        /* failure, report error and exit */
        Log_print1(Diags_USER7, "decode control status = %ld", status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((decInBufDesc.numBufs < decStatus.bufInfo.minNumInBufs) ||
        (EFRAMESIZE < decStatus.bufInfo.minInBufSize[0].bytes) ||
        (decOutBufDesc.numBufs < decStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < decStatus.bufInfo.minOutBufSize[0].bytes)) {

        /* failure, report error and exit */
        Log_print0(Diags_USER7,
            "App-> ERROR: decoder does not meet buffer requirements.");
        return;
    }

    /* Make sure we know how big our VIDDEC3_OutArgs struct needs to be! */
    status = VIDDEC3_control(dec, XDM_GETSTATUS, &decDynParams, &decStatus);
    if (status != VIDDEC3_EOK) {
        /* failure, report error and exit */
        Log_print1(Diags_USER7, "decode control status = %ld", status);
        return;
    }

    if (decStatus.maxOutArgsDisplayBufs != 1) {
        /*
         * This app doesn't support more than one display buf returned,
         * report error and exit
         */
        Log_print1(Diags_USER7, "Error:  decoder supports 0x%x display bufs, "
                "this app only supports 1.", decStatus.maxOutArgsDisplayBufs);
        return;
    }


    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {

#ifdef CACHE_ENABLED
#if defined(xdc_target__isaCompatible_64P) || \
    defined(xdc_target__isaCompatible_64T)
        /*
         *  fread() on this processor is implemented using CCS's stdio, which
         *  is known to write into the cache, not physical memory.  To meet
         *  XDAIS DMA Rule 7, we must writeback the cache into physical
         *  memory.  Also, per DMA Rule 7, we must invalidate the buffer's
         *  cache before providing it to any xDAIS algorithm.
         */
        Memory_cacheWbInv(inBuf, IFRAMESIZE);
#else
#error Unvalidated config - add appropriate fread-related cache maintenance
#endif
        /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
        Memory_cacheInv(encodedBuf, EFRAMESIZE);
#endif

        Log_print1(Diags_USER1, "App-> Processing frame %d...", n);

        /*
         * Encode the frame.
         *
         * Note, inputID == 0 is an error.  This example doesn't account
         * for the case where 'n + 1' wraps to zero.
         */
        encInArgs.inputID = n + 1;
        encInArgs.control = IVIDENC2_CTRL_NONE;
        status = VIDENC2_process(enc, &encInBufDesc, &encOutBufDesc, &encInArgs,
            &encOutArgs);

        Log_print2(Diags_USER2,
                "App-> Encoder frame %d process returned - 0x%x)", n, status);

        if (status != VIDENC2_EOK) {
            Log_print3(Diags_USER7,
                "App-> Encoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x", n, status, encOutArgs.extendedError);
            break;
        }

#ifdef CACHE_ENABLED
        /*
         * Conditionally writeback the encoded buf from the previous
         * call.  Also, as encodedBuf is an inBuf to the next process
         * call, conditionally invalidate it as well.
         */
        if (XDM_ISACCESSMODE_WRITE(encOutBufDesc.descs[0].accessMask)) {
            Memory_cacheWbInv(encOutBufDesc.descs[0].buf, EFRAMESIZE);
        }

        /*
         * Per DMA Rule 7, our output buffer cache lines (for the
         * upcoming decoder) must be cleaned.
         */
        Memory_cacheInv(outBuf, OFRAMESIZE);
#endif

        /* decode the frame */
        decInArgs.numBytes = EFRAMESIZE;
        decInArgs.inputID = 1;  /* typically this varies by each frame */
        status = VIDDEC3_process(dec, &decInBufDesc, &decOutBufDesc,
            &decInArgs, &decOutArgs);

        Log_print2(Diags_USER2,
             "App-> Decoder frame %d process returned - 0x%x)", n, status);

        if (status != VIDDEC3_EOK) {
            Log_print2(Diags_USER7,
                "App-> Decoder frame %d processing FAILED, status = 0x%x",
                n, status);
            break;
        }

        /* again, validate our assumption that we don't get out-of-order bufs */
        if (decOutArgs.decodedBufs.planeDesc[0].buf != outBuf) {
            Log_print0(Diags_USER7,
                    "App-> Internal error.  Unsupported decoder");
            break;
        }

#ifdef CACHE_ENABLED
        /* Conditionally writeback the decoded buf */
        if (XDM_ISACCESSMODE_WRITE(
                decOutArgs.decodedBufs.planeDesc[0].accessMask)) {
            Memory_cacheWb(outBuf, OFRAMESIZE);
        }
#endif

        /* write to file */
        fwrite(outBuf, OFRAMESIZE, 1, out);
    }

    Log_print1(Diags_USER1, "%d frames encoded/decoded", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video3_copy; 1, 0, 0,1; 2-24-2012 19:28:28; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


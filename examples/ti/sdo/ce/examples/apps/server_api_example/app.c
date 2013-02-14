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
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/audio/auddec.h>
#include <ti/sdo/ce/audio/audenc.h>

#include <ti/sdo/ce/Server.h>

#include <string.h>  /* for memset */

#include <stdio.h>
#include <stdlib.h>


/* Name of the heap used for allocating algorithm memory */
#define ALGHEAP "EXTALG_HEAP"

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
#define BUFALIGN 0

#endif

#define NSAMPLES    1024  /* must be multiple of 128 for cache/DMA reasons */
#define IFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* raw frame (input) */
#define EFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* encoded frame */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* decoded frame (output) */

static XDAS_Int8 *inBuf;
static XDAS_Int8 *encodedBuf;
static XDAS_Int8 *outBuf;

static String decoderName  = "auddec_copy";
static String encoderName  = "audenc_copy";

static Void encode_decode(AUDENC_Handle enc, AUDDEC_Handle dec, FILE *in,
    FILE *out);
static Void enumAlgs(String name);
static Server_Status getMemStats(Server_Handle server);


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
 *  ======== traceDump ========
 *  dump contents of DSP trace -- this is a "pull" trace dumping: we read
 *  DSP's trace log whenever we think there might be something there.
 */
static void traceDump(Engine_Handle ce)
{
    //Engine_fwriteTrace(ce, "[DSP] ", stdout);
}

/*
 *  ======== smain ========
 */
Int smain(String progName, String procId, String engineName,
          String inFile, String outFile)
{
    Server_Handle  server = NULL;
    Engine_Handle ce = NULL;
    Engine_Attrs  attrs;
    AUDDEC_Handle dec = NULL;
    AUDENC_Handle enc = NULL;
    FILE          *in = NULL;
    FILE          *out = NULL;
    Ptr           algHeapBase = NULL;
    UInt32        algHeapSize = 0x1000;
    Memory_AllocParams allocParams;
    Uint32        base;
    Server_Status serr = Server_EOK;


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

    if ((inBuf == NULL) || (encodedBuf == NULL) || (outBuf == NULL)) {
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

    /* List all algorithms configured in this engine and their properties. */
    //enumAlgs(engineName);

    /* Initialize attrs fields to default values, and set the procId */
    Engine_initAttrs(&attrs);
    attrs.procId = procId;

    /* Open the Engine */
    if ((ce = Engine_open(engineName, &attrs, NULL)) == NULL) {
        fprintf(stderr, "%s: error: can't open engine %s\n",
            progName, engineName);
        goto end;
    }
    else {
        printf("App> opened engine %s\n", engineName);
    }

    /* Get a handle the the Engine's Server */
    server = Engine_getServer(ce);
    if (server == NULL) {
        fprintf(stderr, "Failed to get server handle\n");
        goto end;
    }

    /* Print out initial memory configuration. */
    printf("\nOriginal configuration of server heaps:\n");
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
        goto end;
    }

    /*
     *  First try to create codecs with the original algorithm heap configured
     *  in the server. This should fail since the heap size is too small.
     */
    dec = AUDDEC_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf("App-> Can't open codec %s.  Will try again after "
                "reconfiguring memory.\n", decoderName);
    }
    else {
        printf("\nApp-> Opened codec %s\n", decoderName);
    }

    /* allocate and initialize video encoder on the engine */
    enc = AUDENC_create(ce, encoderName, NULL);
    if (enc == NULL) {
        printf("App-> Can't open codec %s.  Will try again after "
        "reconfiguring memory.\n", encoderName);
    }
    else {
        printf("App-> Opened codec %s\n", encoderName);
    }

    if ((enc == NULL) || (dec == NULL)) {
        printf("App-> Will attempt to recreate codecs after reconfiguring"
                " algorithm heap\n");
        if (enc != NULL) {
            AUDENC_delete(enc);
            enc = NULL;
        }
        if (dec != NULL) {
            AUDDEC_delete(dec);
            dec = NULL;
        }
    }

    /*
     *  Allocate a buffer to be used for algorithm heap. Buffer must be
     *  aligned on an 8-byte boundary.
     */
    /* allocate buffers */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = 0x8;
    allocParams.seg = 0;
    algHeapBase = Memory_alloc(algHeapSize, &allocParams);

    /* Get the DSP address of the buffer. */
    base = Memory_getBufferPhysicalAddress(algHeapBase, algHeapSize, NULL);
    printf("New base, size of %s: 0x%lx 0x%lx\n", ALGHEAP, base, algHeapSize);

    /*  dump contents of DSP trace -- this is a "pull" trace dumping: we read
     *  DSP's trace log whenever we think there might be something there.
     */
    traceDump(ce);

    /*
     *  Set the new base and size of the algorithm heap. This should fail
     *  if the codecs were created successfully.
     */
    serr = Server_redefineHeap(server, ALGHEAP, base, algHeapSize);
    if (serr != Server_EOK) {
        printf("Server_redefineHeap returned [%d], should have"
                " returned Server_EOK\n", serr);
        goto end;
    }

    printf("\nConfiguration of server heaps after reconfiguration:\n");

    /* Verify that this really happened on the target. */
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
        goto end;
    }

    /*
     *  Allocate and initialize audio encoder and decoder on the engine. This
     *  time it should succeed.
     */
    enc = AUDENC_create(ce, encoderName, NULL);
    if (enc == NULL) {
        printf("App-> ERROR: can't open codec %s\n", encoderName);
        goto end;
    }
    traceDump(ce);

    /* allocate and initialize audio decoder on the engine */
    dec = AUDDEC_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf("App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    printf("\nConfiguration of server heaps after creating algs:\n");
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
        goto end;
    }

    /* use engine to encode, then decode the data */
    encode_decode(enc, dec, in, out);

end:
    /* teardown the codecs */
    if (enc) {
        AUDENC_delete(enc);
    }
    if (dec) {
        AUDDEC_delete(dec);
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

    Log_print0(Diags_USER1, "[+1] app done.");
    return (0);
}

/*
 *  ======== encode_decode ========
 */
static Void encode_decode(AUDENC_Handle enc, AUDDEC_Handle dec, FILE *in,
    FILE *out)
{
    Int                         n;
    Int32                       status;

    AUDDEC_InArgs               decInArgs;
    AUDDEC_OutArgs              decOutArgs;
    AUDDEC_DynamicParams        decDynParams;
    AUDDEC_Status               decStatus;

    AUDENC_InArgs               encInArgs;
    AUDENC_OutArgs              encOutArgs;
    AUDENC_DynamicParams        encDynParams;
    AUDENC_Status               encStatus;

    XDM_BufDesc                 inBufDesc;
    XDAS_Int8                  *src[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  inBufSizes[XDM_MAX_IO_BUFFERS];

    XDM_BufDesc                 encodedBufDesc;
    XDAS_Int8                  *encoded[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  encBufSizes[XDM_MAX_IO_BUFFERS];

    XDM_BufDesc                 outBufDesc;
    XDAS_Int8                  *dst[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  outBufSizes[XDM_MAX_IO_BUFFERS];

    /* clear and initialize the buffer descriptors */
    memset(src,     0, sizeof(src[0])     * XDM_MAX_IO_BUFFERS);
    memset(encoded, 0, sizeof(encoded[0]) * XDM_MAX_IO_BUFFERS);
    memset(dst,     0, sizeof(dst[0])     * XDM_MAX_IO_BUFFERS);

    src[0]     = inBuf;
    encoded[0] = encodedBuf;
    dst[0]     = outBuf;

    inBufDesc.numBufs = encodedBufDesc.numBufs = outBufDesc.numBufs = 1;

    inBufDesc.bufSizes      = inBufSizes;
    encodedBufDesc.bufSizes = encBufSizes;
    outBufDesc.bufSizes     = outBufSizes;

    inBufSizes[0] = encBufSizes[0] = outBufSizes[0] = NSAMPLES;

    inBufDesc.bufs      = src;
    encodedBufDesc.bufs = encoded;
    outBufDesc.bufs     = dst;

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
     * Query the encoder and decoder.
     * This app expects the encoder to accept 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = AUDENC_control(enc, XDM_GETSTATUS, &encDynParams, &encStatus);
    if (status != AUDENC_EOK) {
        /* failure, report error and exit */
        Log_print1(Diags_USER7, "[+7] encode control status = %ld",
                (IArg)status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((inBufDesc.numBufs < encStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < encStatus.bufInfo.minInBufSize[0]) ||
        (encodedBufDesc.numBufs < encStatus.bufInfo.minNumOutBufs) ||
        (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        Log_print0(Diags_USER7, "[+7] Error:  encoder codec feature conflict");
        return;
    }

    status = AUDDEC_control(dec, XDM_GETSTATUS, &decDynParams, &decStatus);
    if (status != AUDDEC_EOK) {
        /* failure, report error and exit */
        Log_print1(Diags_USER7, "[+7] decode control status = %ld",
                (IArg)status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((encodedBufDesc.numBufs < decStatus.bufInfo.minNumInBufs) ||
        (EFRAMESIZE < decStatus.bufInfo.minInBufSize[0]) ||
        (outBufDesc.numBufs < decStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < decStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        Log_print0(Diags_USER7,
                "[+7] App-> ERROR: decoder does not meet buffer requirements.");
        return;
    }

    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {

        /* Deal with cache issues, if necessary */
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

        Log_print1(Diags_USER1, "[+1] App-> Processing frame %d...", (IArg)n);

        /* encode the frame */
        status = AUDENC_process(enc, &inBufDesc, &encodedBufDesc, &encInArgs,
            &encOutArgs);

        Log_print2(Diags_USER2,
                "[+2] App-> Encoder frame %d process returned - 0x%x)",
                (IArg)n, (IArg)status);

#ifdef CACHE_ENABLED
        /* Writeback this outBuf from the previous call.  Also, as encodedBuf
         * is an inBuf to the next process call, we must invalidate it also, to
         * clean buffer lines.
         */
        Memory_cacheWbInv(encodedBuf, EFRAMESIZE);

        /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
        Memory_cacheInv(outBuf, OFRAMESIZE);
#endif

        if (status != AUDENC_EOK) {
            Log_print3(Diags_USER7,
                    "[+7] App-> Encoder frame %d processing FAILED, status = 0x%x, "
                    "extendedError = 0x%x",
                    (IArg)n, (IArg)status, (IArg)(encOutArgs.extendedError));
            break;
        }

        /* decode the frame */
        decInArgs.numBytes = EFRAMESIZE;
        status = AUDDEC_process(dec, &encodedBufDesc, &outBufDesc, &decInArgs,
           &decOutArgs);

        Log_print2(Diags_USER2,
                "[+2] App-> Decoder frame %d process returned - 0x%x)",
                (IArg)n, (IArg)status);

        if (status != AUDDEC_EOK) {
            Log_print3(Diags_USER7,
                    "[+7] App-> Decoder frame %d processing FAILED, status = 0x%x, "
                    "extendedError = 0x%x",
                    (IArg)n, (IArg)status, (IArg)(decOutArgs.extendedError));
            break;
        }

#ifdef CACHE_ENABLED
        /* Writeback the outBuf. */
        Memory_cacheWb(outBuf, OFRAMESIZE);
#endif
        /* write to file */
        fwrite(dst[0], OFRAMESIZE, 1, out);
    }

    Log_print1(Diags_USER1, "[+1] %d frames encoded/decoded", (IArg)n);
}

/*
 *  ======== enumAlgs ========
 */
static Void enumAlgs(String name)
{
    Engine_AlgInfo      algInfo;
    Int                 numAlgs;
    Int                 i;
    String              loc;
    Engine_Error        status;

    status = Engine_getNumAlgs(name, &numAlgs);

    if (status == Engine_EOK) {
        printf("%s: numAlgs = %d\n", name, numAlgs);
    }
    else {
        printf("Engine_getNumAlgs(%s) error: %d\n", name, status);
        return;
    }

    algInfo.algInfoSize = sizeof(Engine_AlgInfo);

    for (i = 0; i < numAlgs; i++) {
        status = Engine_getAlgInfo(name, &algInfo, i);
        if (status == Engine_EOK) {
            loc = (algInfo.isLocal) ? "local" : "remote";
            printf("  alg[%d].name = %s: %s\n", i, algInfo.name, loc);
        }
        else {
            printf("Engine_getAlgInfo(%s) error: %d\n", name, status);
            return;
        }
    }
}

/*
 *  ======== getMemStats ========
 */
static Server_Status getMemStats(Server_Handle server)
{
    Server_MemStat stat;
    Int            i;
    Int            numSegs;
    Server_Status  serr = Server_EOK;

    serr = Server_getNumMemSegs(server, &numSegs);
    if (serr != Server_EOK) {
        printf("Server_getNumMemSegs() error: %d\n", serr);
        return (serr);
    }

    /* Check memory usage */
    printf("       %12s %10s %12s %12s %14s\n", "name", "base",
            "size", "used", "max block");
    for (i = 0; i < numSegs; i++) {
        serr = Server_getMemStat(server, i, &stat);
        if (serr != Server_EOK) {
            printf("Server_getMemStat() error: %d\n", serr);
            return (serr);
        }
        printf("Seg %d: [%12s] [0x%08lx] [0x%08lx] [0x%08lx] [0x%08lx]\n",
                i, stat.name, stat.base, stat.size,
                stat.used, stat.maxBlockLen);
    }

    return (serr);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.server_api_example; 1, 0, 0,1; 2-24-2012 19:27:53; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


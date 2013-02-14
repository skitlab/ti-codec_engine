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
 *  ======== app_config.c ========
 *  App config for non-RTSC example.
 */

#include <xdc/std.h>


/*
 *  ======== Engine Configuration ========
 */
#include <ti/sdo/ce/CERuntime.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/* Include these headers for VISA type defines */
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/sdo/ce/audio1/audenc1.h>
#include <ti/sdo/ce/speech1/sphdec1.h>
#include <ti/sdo/ce/speech1/sphenc1.h>

extern IALG_Fxns AUDDEC1COPY_TI_IAUDDEC1COPY;

extern IALG_Fxns AUDENC1COPY_TI_IAUDENC1COPY;
extern IALG_Fxns SPHDEC1COPY_TI_ISPHDEC1COPY;
extern IALG_Fxns SPHENC1COPY_TI_ISPHENC1COPY;
/*
 *  Set up the alg table.
 */
CE_BEGIN_ALG_TABLE(local_table)

    CE_LOCAL_ALG2(
        "sphdec1_copy",               /* alg name */
        &SPHDEC1COPY_TI_ISPHDEC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        1,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT,  /* Memory type: cached, non-cached etc */
        SPHDEC1_VISATYPE)

    CE_LOCAL_ALG2(
        "sphenc1_copy",                 /* alg name */
        &SPHENC1COPY_TI_ISPHENC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        1,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT,  /* Memory type: cached, non-cached etc */
        SPHENC1_VISATYPE)

    /* Codecs that can be used with audio1_copy */
    CE_LOCAL_ALG2(
        "auddec1_copy",               /* alg name */
        &AUDDEC1COPY_TI_IAUDDEC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        1,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT,  /* Memory type: cached, non-cached etc */
        AUDDEC1_VISATYPE)

    CE_LOCAL_ALG2(
        "audenc1_copy",               /* alg name */
        &AUDENC1COPY_TI_IAUDENC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        1,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT,  /* Memory type: cached, non-cached etc */
        AUDENC1_VISATYPE)

CE_END_ALG_TABLE(local_table)

CE_BEGIN_ENGINE_TABLE(engineTab)
    CE_ENGINE(
        local_table,            /* CE_LOCAL_ALG() table name */
        "local",                /* Engine name */
        NULL,                   /* Server name */
        NULL,                   /* memMap */
        0,                      /* useExtLoader */
        0)                      /* Heap Id */
CE_END_ENGINE_TABLE(engineTab)


/*
 *  ======== ti.sdo.ce Settings Configuration ========
 *  Set to TRUE for 'checked' builds.
 */
Bool VISA_checked = FALSE;
/*
 *  @(#) ti.sdo.ce.examples.servers; 1, 0, 0,1; 2-24-2012 19:29:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


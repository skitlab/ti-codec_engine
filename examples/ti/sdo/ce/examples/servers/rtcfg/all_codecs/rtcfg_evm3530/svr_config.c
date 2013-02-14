/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 * Copyright (c) 2011, Texas Instruments Incorporated
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
 *  ======== svr_config.c ========
 *  Server config for non-RTSC example.
 */

#include <xdc/std.h>


/*
 *  ======== Server Configuration ========
 */
#include <ti/sdo/ce/CERuntime.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/*
 *  ======== Server Configuration ========
 *  Do not modify following; it is automatically generated from the template
 *  Server.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
#include <ti/sdo/ce/node/node.h>
#include <ti/sdo/ce/rms.h>

Int ti_sdo_ce_Server_skelCachingPolicy = 0;

static NODE_Attrs nodeAttrs13 = {
    4, 10024, 0
};
extern SKEL_Fxns SPHDEC1_SKEL;

static NODE_Attrs nodeAttrs14 = {
    4, 10024, 0
};
extern SKEL_Fxns SPHENC1_SKEL;

static NODE_Attrs nodeAttrs15 = {
    4, 10024, 0
};
extern SKEL_Fxns AUDDEC1_SKEL;

static NODE_Attrs nodeAttrs16 = {
    4, 10024, 0
};
extern SKEL_Fxns AUDENC1_SKEL;


/*  table of all "codec server" nodes available in this server */
NODE_Desc RMS_nodeTab[] = {
    {
        "sphdec1_copy",                 /* Name */
        {996074855U},                   /* uuid */
        &SPHDEC1_SKEL,                  /* skel fxns */
        &nodeAttrs13,                   /* params */
        0,                              /* protocol */
        "SPHDEC1_STUBS",                /* Name of stub fxns */
        "ti.sdo.ce.speech1.ISPHDEC1"},  /* typeTab string */
    {
        "sphenc1_copy",                 /* Name */
        {948634151U},                   /* uuid */
        &SPHENC1_SKEL,                  /* skel fxns */
        &nodeAttrs14,                   /* params */
        0,                              /* protocol */
        "SPHENC1_STUBS",                /* Name of stub fxns */
        "ti.sdo.ce.speech1.ISPHENC1"},  /* typeTab string */
    {
        "auddec1_copy",                 /* Name */
        {2426520118U},                  /* uuid */
        &AUDDEC1_SKEL,                  /* skel fxns */
        &nodeAttrs15,                   /* params */
        1,                              /* protocol */
        "AUDDEC1_STUBS",                /* Name of stub fxns */
        "ti.sdo.ce.audio1.IAUDDEC1"},   /* typeTab string */
    {
        "audenc1_copy",                 /* Name */
        {2473862518U},                  /* uuid */
        &AUDENC1_SKEL,                  /* skel fxns */
        &nodeAttrs16,                   /* params */
        1,                              /* protocol */
        "AUDENC1_STUBS",                /* Name of stub fxns */
        "ti.sdo.ce.audio1.IAUDENC1"},   /* typeTab string */
    {NULL}  /* NULL terminate RMS_nodeTab[] */
};


RMS_Config RMS_config = {
    1,       /* RMS server's priority */
    4096,    /* RMS server's stack size */
    0,       /* RMS server's stack memory seg */
};
/*
 *  @(#) ti.sdo.ce.examples.servers; 1, 0, 0,1; 2-24-2012 19:29:36; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


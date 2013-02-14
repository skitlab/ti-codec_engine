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

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_utils_xdm_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/global/CESettings.h>

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>

#include "XdmUtils.h"

#define MODNAME "ti.sdo.ce.utils.xdm"


/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

Registry_Desc ti_sdo_ce_utils_xdm_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 * ======== XdmUtils_init ========
 */
Void XdmUtils_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_utils_xdm_desc, MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;
    }
}


#if 0
/*
 * ======== XdmUtils_exit ========
 */
Void XdmUtils_exit()
{
    if (curInit == FALSE) {
        return;
    }
    curInit = FALSE;

}
#endif


/*
 *  ======== XdmUtils_validateExtendedStruct ========
 */
Bool XdmUtils_validateExtendedStruct(void *pStruct, UInt minSize, char *name)
{
    Bool fRetVal;
    UInt32 providedSize;

    Log_print3(Diags_ENTRY, "[+E] XdmUtils_validateExtendedStruct> "
            "Enter (pStruct=0x%x, minSize=0x%x, name=%s)",
            (IArg)pStruct, (IArg)minSize, (IArg)name);

    if (pStruct == NULL) {
        Log_print1(Diags_USER7, "[+7] ERROR> extended struct (%s) is NULL",
                (IArg)name);
        fRetVal = FALSE;
    }
    else {
        providedSize = (*((UInt32 *)pStruct));

        if (providedSize < minSize) {
            Log_print3(Diags_USER7, "[+7] ERROR> invalid extended struct (%s)"
                    " detected - only %d of required %d bytes were provided!",
                    (IArg)name, (IArg)providedSize, (IArg)minSize);
            fRetVal = FALSE;
        }
        else {
            fRetVal = TRUE;
        }
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateExtendedStruct> return "
            "(0x%x)", (IArg)fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateSparseBufDesc ========
 */
Bool XdmUtils_validateSparseBufDesc(XDM_BufDesc *bufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal;

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateSparseBufDesc> "
            "Enter (bufDesc=0x%x, name=%s)", (IArg)bufDesc, (IArg)name);

    if (bufDesc == NULL) {
        Log_print1(Diags_USER7, "[+7] ERROR> bufDesc (%s) pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    for (i = 0, numValidBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (bufDesc->bufs[i] != NULL) {
            numValidBufs++;
        }
    }

    /* finding more buffers than declared is okay, but finding fewer is not */
    if (numValidBufs < bufDesc->numBufs) {
        Log_print3(Diags_USER7, "[+7] ERROR> invalid bufDesc (%s) detected - "
                "%d of %d expected bufs were found!",
                (IArg)name, (IArg)numValidBufs, (IArg)(bufDesc->numBufs));
        fRetVal = FALSE;
    }
    else {
        fRetVal = TRUE;
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateSparseBufDesc> return "
            "(0x%x)", (IArg)fRetVal);

    return (fRetVal);
}

/*
 *  ======== XdmUtils_validateSparseBufDesc1 ========
 */
Bool XdmUtils_validateSparseBufDesc1(XDM1_BufDesc *bufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal;

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateSparseBufDesc1> "
            "Enter (bufDesc=0x%x, name=%s)", (IArg)bufDesc, (IArg)name);

    if (bufDesc == NULL) {
        Log_print1(Diags_USER7, "[+7] ERROR> bufDesc (%s) pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    for (i = 0, numValidBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (bufDesc->descs[i].buf != NULL) {
            numValidBufs++;
        }
    }

    /* finding more buffers than declared is okay, but finding fewer is not */
    if (numValidBufs < bufDesc->numBufs) {
        Log_print3(Diags_USER7, "[+7] ERROR> invalid bufDesc (%s) detected - "
                "%d of %d expected bufs were found!",
                (IArg)name, (IArg)numValidBufs, (IArg)(bufDesc->numBufs));
        fRetVal = FALSE;
    }
    else {
        fRetVal = TRUE;
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateSparseBufDesc1> return "
            "(0x%x)", (IArg)fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateSparseBufDesc2 ========
 */
Bool XdmUtils_validateSparseBufDesc2(XDM2_BufDesc *bufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal;

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateSparseBufDesc2> "
            "Enter (bufDesc=0x%x, name=%s)", (IArg)bufDesc, (IArg)name);

    if (bufDesc == NULL) {
        Log_print1(Diags_USER7, "[+7] ERROR> bufDesc (%s) pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    for (i = 0, numValidBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (bufDesc->descs[i].buf != NULL) {
            numValidBufs++;
        }
    }

    /* finding more buffers than declared is okay, but finding fewer is not */
    if (numValidBufs < bufDesc->numBufs) {
        Log_print3(Diags_USER7, "[+7] ERROR> invalid bufDesc (%s) detected - "
                "%d of %d expected bufs were found!",
                (IArg)name, (IArg)numValidBufs, (IArg)(bufDesc->numBufs));
        fRetVal = FALSE;
    }
    else {
        fRetVal = TRUE;
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateSparseBufDesc2> return "
            "(0x%x)", (IArg)fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateVideoBufDesc ========
 */
Bool XdmUtils_validateVideoBufDesc(IVIDEO_BufDesc *vidBufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal = TRUE;   /* optimistic */

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateVideoBufDesc> "
            "Enter (vidBufDesc=0x%x, name=%s)", (IArg)vidBufDesc, (IArg)name);

    if (vidBufDesc == NULL) {
        Log_print1(Diags_USER7,
                "[+7] ERROR> IVIDEO_BufDesc \"%s\" pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    numValidBufs = vidBufDesc->numBufs;

    if ((numValidBufs < 0) || (numValidBufs > XDM_MAX_IO_BUFFERS)) {
        Log_print2(Diags_USER7, "[+7] ERROR> %s->numBufs (%d) is invalid",
                (IArg)name, (IArg)(vidBufDesc->numBufs));
        return (FALSE);
    }

    for (i = 0; i < numValidBufs; i++) {
        if (vidBufDesc->bufs[i] == NULL) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->numBufs is %d, but %s->bufs[%d] is NULL!",
                    (IArg)name, (IArg)(vidBufDesc->numBufs), (IArg)name,
                    (IArg)i);
            return (FALSE);
        }
        if (vidBufDesc->bufSizes[i] <= 0) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->bufSizes[%d] is invalid - %d (0x%x)!",
                    (IArg)name, (IArg)i, (IArg)(vidBufDesc->bufSizes[i]),
                    (IArg)(vidBufDesc->bufSizes[i]));
            return (FALSE);
        }
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateVideoBufDesc> return (0x%x)",
            (IArg)fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateVideo1BufDesc ========
 */
Bool XdmUtils_validateVideo1BufDesc(IVIDEO1_BufDesc *vidBufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal = TRUE;   /* optimistic */

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateVideo1BufDesc> "
            "Enter (vidBufDesc=0x%x, name=%s)", (IArg)vidBufDesc, (IArg)name);

    if (vidBufDesc == NULL) {
        Log_print1(Diags_USER7,
                "[+7] ERROR> IVIDEO_BufDesc \"%s\" pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    numValidBufs = vidBufDesc->numBufs;

    if ((numValidBufs < 0) || (numValidBufs > IVIDEO_MAX_YUV_BUFFERS)) {
        Log_print2(Diags_USER7, "[+7] ERROR> %s->numBufs (%d) is invalid",
                (IArg)name, (IArg)(vidBufDesc->numBufs));
        return (FALSE);
    }

    for (i = 0; i < numValidBufs; i++) {
        if (vidBufDesc->bufDesc[i].buf == NULL) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->numBufs is %d, but %s->bufDesc[%d].buf is "
                    "NULL!",
                    (IArg)name, (IArg)(vidBufDesc->numBufs), (IArg)name,
                    (IArg)i);
            return (FALSE);
        }
        if (vidBufDesc->bufDesc[i].bufSize <= 0) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->bufDesc[%d].bufSize is invalid - %d (0x"
                    "%x)!",
                    (IArg)name, (IArg)i, (IArg)(vidBufDesc->bufDesc[i].bufSize),
                    (IArg)(vidBufDesc->bufDesc[i].bufSize));
            return (FALSE);
        }
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateVideo1BufDesc> return "
            "(0x%x)", (IArg)fRetVal);

    return (fRetVal);
}

/*
 *  ======== XdmUtils_validateVideo1BufDescIn ========
 */
Bool XdmUtils_validateVideo1BufDescIn(IVIDEO1_BufDescIn *vidBufDescIn,
        char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal = TRUE;   /* optimistic */

    Log_print2(Diags_ENTRY, "[+E] XdmUtils_validateVideo1BufDescIn> "
            "Enter (vidBufDescIn=0x%x, name=%s)", (IArg)vidBufDescIn,
            (IArg)name);

    if (vidBufDescIn == NULL) {
        Log_print1(Diags_USER7,
                "[+7] ERROR> IVIDEO1_BufDescIn \"%s\" pointer is NULL",
                (IArg)name);
        return (FALSE);
    }

    numValidBufs = vidBufDescIn->numBufs;

    if ((numValidBufs < 0) || (numValidBufs > XDM_MAX_IO_BUFFERS)) {
        Log_print2(Diags_USER7, "[+7] ERROR> %s->numBufs (%d) is invalid",
                (IArg)name, (IArg)(vidBufDescIn->numBufs));
        return (FALSE);
    }

    for (i = 0; i < numValidBufs; i++) {
        if (vidBufDescIn->bufDesc[i].buf == NULL) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->numBufs is %d, but %s->bufDesc[%d].buf "
                    "is NULL!", (IArg)name, (IArg)(vidBufDescIn->numBufs),
                    (IArg)name, (IArg)i);
            return (FALSE);
        }
        if (vidBufDescIn->bufDesc[i].bufSize <= 0) {
            Log_print4(Diags_USER7,
                    "[+7] ERROR> %s->bufDesc[%d].bufSize is invalid - "
                    "%d (0x%x)!", (IArg)name, (IArg)i,
                    (IArg)(vidBufDescIn->bufDesc[i].bufSize),
                    (IArg)(vidBufDescIn->bufDesc[i].bufSize));
            return (FALSE);
        }
    }

    Log_print1(Diags_EXIT, "[+X] XdmUtils_validateVideo1BufDescIn> "
            "return (0x%x)", (IArg)fRetVal);

    return (fRetVal);
}
/*
 *  @(#) ti.sdo.ce.utils.xdm; 1, 0, 2,1; 2-24-2012 19:31:45; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


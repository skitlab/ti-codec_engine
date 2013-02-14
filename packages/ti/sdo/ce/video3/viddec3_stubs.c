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
 *  ======== viddec3_stubs.c ========
 *  This file contains an implemenation of the IVIDDEC3 interface for the
 *  video decoder class of algorithms.
 *
 *  These functions are the "client-side" of a "remote" implementation.
 *
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_video3_viddec3_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ti/sdo/ce/osal/Memory.h>

#include <string.h>  /* for memcpy and memset. */

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec3.h"
#include "_viddec3.h"

extern Registry_Desc ti_sdo_ce_video3_viddec3_desc;


static XDAS_Int32 process(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs);
static XDAS_Int32 processAsync(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs);
static XDAS_Int32 processWait(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    UInt timeout);
static XDAS_Int32 control(IVIDDEC3_Handle h, IVIDDEC3_Cmd id,
    IVIDDEC3_DynamicParams *params, IVIDDEC3_Status *status);
static XDAS_Int32 marshallMsg(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    _VIDDEC3_Msg **pmsg);
static XDAS_Int32 unmarshallMsg(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    _VIDDEC3_Msg *msg, XDAS_Int32 retVal);
static Bool p2vVideo2BufDesc(IVIDEO2_BufDesc *pBufDesc);

IVIDDEC3_Fxns VIDDEC3_STUBS = {
    {&VIDDEC3_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};


/*
 *  ======== marshallMsg ========
 */
static XDAS_Int32 marshallMsg(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    _VIDDEC3_Msg **pmsg)
{
    XDAS_Int32 retVal = IVIDDEC3_EOK;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC3_Msg *msg;
    Int i;
    IVIDDEC3_OutArgs *pMsgOutArgs;
    Int numBufs;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((inArgs == NULL) || (inArgs->size < sizeof(IVIDDEC3_InArgs)) ||
            (outArgs == NULL) || (outArgs->size < sizeof(IVIDDEC3_OutArgs))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC3_EFAIL);
    }

    /*
     * Initialize extendedError to zero so we don't return something
     * uninitialized in extendedError.
     */
    outArgs->extendedError = 0;

    if (pmsg == NULL) {
        return (IVIDDEC3_EFAIL);
    }

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) + sizeof(*inBufs) + sizeof(*outBufs) +
            inArgs->size + outArgs->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        Log_print2(Diags_USER6,
                "[+6] process> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (IVIDDEC3_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC3_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (IVIDDEC3_EFAIL);
    }

    /* zero out msg->cmd (not msg->visa!) */
    memset(&(msg->cmd), 0, sizeof(msg->cmd));

    /*
     * Marshall the command: copy the client-passed arguments into flattened
     * message data structures, converting every pointer address to alg.
     * data buffer into physical address.
     */

    /* First specify the processing command that the skeleton should do */
    msg->visa.cmd = _VIDDEC3_CPROCESS;

    /* commentary follows for marshalling the inBufs argument: */

    /* 1) initialize the whole inBufs struct */
    msg->cmd.process.inBufs = *inBufs;

    /* 2) translate pointers present in the inBufs */
    for (i = 0, numBufs = 0;
         ((numBufs < inBufs->numBufs) && (i < XDM_MAX_IO_BUFFERS)); i++) {
        if (inBufs->descs[i].buf != NULL) {

            /* valid member of sparse array, convert it */
            msg->cmd.process.inBufs.descs[i].buf = (XDAS_Int8 *)
                Memory_getBufferPhysicalAddress(inBufs->descs[i].buf,
                    inBufs->descs[i].bufSize.bytes, NULL);

            if (msg->cmd.process.inBufs.descs[i].buf == NULL) {
                retVal = IVIDDEC3_EFAIL;
                goto exit;
            }

            /* Clear .accessMask; the local processor won't access this buf */
            inBufs->descs[i].accessMask = 0;

            /* found, and handled, another buffer. */
            numBufs++;
        }
        else {
            /* empty member of sparse array, no conversion needed. */
            msg->cmd.process.inBufs.descs[i].bufSize.bytes = 0;
            msg->cmd.process.inBufs.descs[i].buf = NULL;
        }
    }

    if (VISA_isChecked()) {
        /* check that we found inBufs->numBufs pointers in inBufs->bufs[] */
        Assert_isTrue(inBufs->numBufs == numBufs, (Assert_Id)NULL);
    }

    /* we're done (with inBufs). Because msg->cmd.process is non-cacheable
     * and contiguous (it has been allocated by MSGQ), we don't have to do
     * anything else.
     */

    /* translate outBufs. */
    msg->cmd.process.outBufs.numBufs = outBufs->numBufs;

    for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (outBufs->descs[i].buf != NULL) {
            /* initialize the buf desc, then translate the addr if needed */
            msg->cmd.process.outBufs.descs[i] = outBufs->descs[i];

            /* valid member of sparse array, convert it */
            if (outBufs->descs[i].memType == XDM_MEMTYPE_RAW) {
                msg->cmd.process.outBufs.descs[i].buf =  (XDAS_Int8 *)
                    Memory_getBufferPhysicalAddress(outBufs->descs[i].buf,
                        outBufs->descs[i].bufSize.bytes, NULL);
            }
            else {
                /* Does tiled memory need to be tranlated?!? */
                Log_print1(Diags_USER4,
                        "[+4] Tiled memory buffer detected (0x%x), no addr "
                        "translation", (IArg)outBufs->descs[i].buf);
            }

            if (msg->cmd.process.outBufs.descs[i].buf == NULL) {
                /* TODO:M - should add at least a trace statement when trace
                 * is supported.  Another good idea is to return something
                 * more clear than EFAIL.
                 */
                retVal = IVIDDEC3_EFAIL;
                goto exit;
            }

            /* found, and handled, another buffer.  See if it's the last one */
            if (++numBufs == outBufs->numBufs) {
                break;
            }
        }
        else {
            /* empty member of sparse array, no conversion needed */
            msg->cmd.process.outBufs.descs[i].bufSize.bytes = 0;
            msg->cmd.process.outBufs.descs[i].buf = NULL;
        }
    }

    if (VISA_isChecked()) {
        /* check that we found outBufs->numBufs pointers in outBufs->bufs[] */
        Assert_isTrue(outBufs->numBufs == numBufs, (Assert_Id)NULL);
    }

    /* inArgs has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.process.inArgs), inArgs, inArgs->size);

    /* point at outArgs and set the "size" */
    pMsgOutArgs = (IVIDDEC3_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    /* set the size field - the rest is filled in by the codec */
    pMsgOutArgs->size = outArgs->size;

    *pmsg = msg;

    return (retVal);

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== unmarshallMsg ========
 */
static XDAS_Int32 unmarshallMsg(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    _VIDDEC3_Msg *msg, XDAS_Int32 retVal)
{
    VISA_Handle visa = (VISA_Handle)h;
    Int i;
    IVIDDEC3_OutArgs *pMsgOutArgs;
    Int numBufs;
    Bool success;

    /*
     * Do a wholesale replace of skeleton returned structure.
     * Pointer conversion of fields in outArgs is done below (only
     * in the case of a successful return value).
     */
    pMsgOutArgs = (IVIDDEC3_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    if (VISA_isChecked()) {
        /* ensure the codec didn't change outArgs->size */
        Assert_isTrue(pMsgOutArgs->size == outArgs->size, (Assert_Id)NULL);
    }

    memcpy(outArgs, pMsgOutArgs, outArgs->size);

    /* if VISA_call was successful, unmarshall the necessary buffers. */
    if (retVal == IVIDDEC3_EOK) {
        /* unmarshall the output data in outBufs and outArgs. */

        if (VISA_isChecked()) {
            /* ensure the codec didn't send back "too many" buffers */
            Assert_isTrue(
                    msg->cmd.process.outBufs.numBufs < XDM_MAX_IO_BUFFERS,
                    (Assert_Id)NULL);
        }

        /* The outBufs may have changed (right?), so init the outBufs struct. */
        *outBufs = msg->cmd.process.outBufs;

        for (i = 0, numBufs = 0;
             ((numBufs < outBufs->numBufs) && (i < XDM_MAX_IO_BUFFERS)); i++) {

            if (outBufs->descs[i].buf != NULL) {
                /* valid member of sparse array, convert it */
                if (outBufs->descs[i].memType == XDM_MEMTYPE_RAW) {
                    outBufs->descs[i].buf = (XDAS_Int8 *)
                            Memory_getBufferVirtualAddress(
                                (UInt32)outBufs->descs[i].buf,
                                outBufs->descs[i].bufSize.bytes);
                }
                else {
                    /* Does tiled memory need to be translated?!? */
                    Log_print1(Diags_USER4,
                            "Tiled memory buffer detected (0x%x), no addr "
                            "translation", (IArg)outBufs->descs[i].buf);
                }

                if (outBufs->descs[i].buf == NULL) {
                    /* TODO:L - return something more clear than EFAIL? */
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> address translation of "
                            "outBufs->descs[0x%x].buf failed", i);

                    retVal = IVIDDEC3_EFAIL;
                    goto exit;
                }

                /* found, and handled, another buffer. */
                numBufs++;
            }
            else {
                /* empty member of sparse array, no conversion needed */
                outBufs->descs[i].bufSize.bytes = 0;
                outBufs->descs[i].buf = NULL;
            }
        }

    }

    /*
     * Note that buffers can also be returned if IVIDDEC_EFAIL is returned
     * with a non-fatal .extendedError in displayBufs[] and decodedBufs.
     */

    /* address translate the decoded buffers if non-fatal error */
    if ((retVal == IVIDDEC3_EOK) ||
            (!(XDM_ISFATALERROR(outArgs->decodedBufs.extendedError)))) {

        success = p2vVideo2BufDesc(&(outArgs->decodedBufs));
        if (!success) {
            retVal = IVIDDEC3_EFAIL;
            goto exit;
        }
    }

    if (outArgs->displayBufsMode == IVIDDEC3_DISPLAYBUFS_EMBEDDED) {

        /* the display buffers are embedded in the outArgs struct */
        for (i = 0; (outArgs->outputID[i] != 0) && (i < IVIDEO2_MAX_IO_BUFFERS);
                i++) {

            if ((retVal == IVIDDEC3_EOK) ||
                    (!(XDM_ISFATALERROR(outArgs->
                               displayBufs.bufDesc[i].extendedError)))) {
                success = p2vVideo2BufDesc(&(outArgs->displayBufs.bufDesc[i]));

                if (!success) {
                    retVal = IVIDDEC3_EFAIL;
                    goto exit;
                }
            }
        }
    }
    else {
        /* the display buffers are pointed to in the outArgs struct */
        for (i = 0; (outArgs->outputID[i] != 0) && (i < IVIDEO2_MAX_IO_BUFFERS);
                i++) {

            success = p2vVideo2BufDesc(outArgs->displayBufs.pBufDesc[i]);

            if (!success) {
                return (VISA_EFAIL);
            }
        }
    }

    /* Note that we did *nothing* with inBufs nor inArgs.  This should be ok. */

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== process ========
 *  This is the sync stub implementation for the process method
 */
static XDAS_Int32 process(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC3_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != IVIDDEC3_EOK) {
        return (retVal);
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* Regardless of return value, unmarshall outArgs. */
    retVal = unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg, retVal);

    return (retVal);
}

/*
 *  ======== processAsync ========
 *  This is the async stub implementation for the process method
 */
static XDAS_Int32 processAsync(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC3_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != IVIDDEC3_EOK) {
        return (retVal);
    }

    /* send the message to the skeleton without waiting for completion */
    retVal = VISA_callAsync(visa, (VISA_Msg *)&msg);

    return (retVal);
}

/*
 *  ======== processWait ========
 */
static XDAS_Int32 processWait(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal;
    _VIDDEC3_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    Assert_isTrue(!VISA_isLocal(visa), (Assert_Id)NULL);

    /* wait for completion of "last" message */
    retVal = VISA_wait(visa, (VISA_Msg *)&msg, timeout);

    /* Unmarshall outArgs if there is a msg to unmarshall. */
    if (msg != NULL) {
        Assert_isTrue(msg->visa.cmd == _VIDDEC3_CPROCESS, (Assert_Id)NULL);

        retVal = unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg,
                retVal);
    }

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(IVIDDEC3_Handle h, IVIDDEC3_Cmd id,
     IVIDDEC3_DynamicParams *params, IVIDDEC3_Status *status)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC3_Msg *msg;
    IVIDDEC3_Status *pMsgStatus;
    XDAS_Int8 *virtAddr = NULL;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((params == NULL) || (params->size < sizeof(IVIDDEC3_DynamicParams)) ||
            (status == NULL) || (status->size < sizeof(IVIDDEC3_Status))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC3_EFAIL);
    }

    /*
     * Initialize extendedError to zero so we don't return something
     * uninitialized in extendedError.
     */
    status->extendedError = 0;

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) + sizeof(id) + params->size +
            status->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        Log_print2(Diags_USER6,
                "[+6] control> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (IVIDDEC3_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC3_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (IVIDDEC3_EFAIL);
    }

    /* marshall the command */
    msg->visa.cmd = _VIDDEC3_CCONTROL;

    msg->cmd.control.id = id;

    /* params has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.control.params), params, params->size);

    /* unmarshall status based on the "size" of params */
    pMsgStatus = (IVIDDEC3_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    /*
     * Initialize the .size and .data fields - the rest are filled in by
     * the codec.
     */
    pMsgStatus->size = status->size;

    if (status->data.buf != NULL) {
        pMsgStatus->data.bufSize = status->data.bufSize;

        /* save it for later */
        virtAddr = status->data.buf;

        pMsgStatus->data.buf = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(status->data.buf,
                status->data.bufSize, NULL);

        if (pMsgStatus->data.buf == NULL) {
            retVal = IVIDDEC3_EFAIL;
            goto exit;
        }
    }
    else {
        /* Place null into the msg so the skel knows it's invalid */
        pMsgStatus->data.buf = NULL;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* ensure we get CCONTROL msg (ensure async CPROCESS pipeline drained) */
    Assert_isTrue(msg->visa.cmd == _VIDDEC3_CCONTROL, (Assert_Id)NULL);

    /* unmarshall status */
    pMsgStatus = (IVIDDEC3_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    if (VISA_isChecked()) {
        /* ensure codec didn't modify status->size */
        Assert_isTrue(pMsgStatus->size == status->size, (Assert_Id)NULL);

        /*
         * TODO:L  Should we also check that pMsgStatus->data.buf is the same
         * after the call as before?
         */
    }

    memcpy(status, pMsgStatus, status->size);

    /*
     * And finally, restore status->data.buf to its original value.  Note that
     * this works even when status->data.buf was NULL because virtAddr is
     * initialized to NULL.
     *
     * While potentially more confusing, this is just as correct as
     * (and faster than!) calling Memory_getVirtualBuffer().
     */
    status->data.buf = virtAddr;

    /* Clear .accessMask; the local processor didn't access the buffer */
    status->data.accessMask = 0;

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== VIDDEC3_processAsync ========
 */
XDAS_Int32 VIDDEC3_processAsync(VIDDEC3_Handle handle, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, VIDDEC3_InArgs *inArgs, VIDDEC3_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC3_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    Log_print5(Diags_ENTRY, "[+E] VIDDEC3_processAsync> "
            "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
            "outArgs=0x%x)",
            (IArg)handle, (IArg)inBufs, (IArg)outBufs, (IArg)inArgs,
            (IArg)outArgs);

    if (handle) {
        IVIDDEC3_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /* validate inArgs with ranges. */
                if (inArgs->inputID == 0) {

                    Log_print2(Diags_USER7,
                            "[+7] ERROR> app provided codec (0x%x) with out "
                            "of range inArgs->inputID field (0x%x)",
                            (IArg)alg, inArgs->inputID);
                }

                /* Validate inBufs and outBufs. */
//todo                XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
//todo                XdmUtils_validateSparseBufDesc(outBufs, "outBufs");
            }

            retVal = processAsync(alg, inBufs, outBufs, inArgs, outArgs);
        }
    }

    Log_print2(Diags_EXIT, "[+X] VIDDEC3_processAsync> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}

/*
 *  ======== VIDDEC3_processWait ========
 */
XDAS_Int32 VIDDEC3_processWait(VIDDEC3_Handle handle, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, VIDDEC3_InArgs *inArgs, VIDDEC3_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal = VIDDEC3_EFAIL;
    VIDDEC3_InArgs refInArgs;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    Log_print5(Diags_ENTRY, "[+E] VIDDEC3_processWait> "
            "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
            "outArgs=0x%x)",
            (IArg)handle, (IArg)inBufs, (IArg)outBufs, (IArg)inArgs,
            (IArg)outArgs);

    if (handle) {
        IVIDDEC3_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;
            }

            retVal = processWait(alg, inBufs, outBufs, inArgs, outArgs,
                    timeout);

            if (checked) {
                /* ensure the codec didn't modify the read-only inArgs */
                if (memcmp(&refInArgs, inArgs, sizeof(*inArgs)) != 0) {
                    Log_print1(Diags_USER7,
                            "[+7] ERROR> codec (0x%x) modified read-only inArgs "
                            "struct!", (IArg)handle);
                }
            }
        }
    }

    Log_print2(Diags_EXIT, "[+X] VIDDEC3_processWait> "
            "Exit (handle=0x%x, retVal=0x%x)", (IArg)handle, (IArg)retVal);

    return (retVal);
}

/*
 * ======== p2vVideo2BufDesc ========
 * Translate all phys addrs to virt addrs in an IVIDEO2_BufDesc
 */
static Bool p2vVideo2BufDesc(IVIDEO2_BufDesc *pBufDesc)
{
    Int i;

    /* Check for a spec violation - probably should be an assert! */
    if ((pBufDesc->numPlanes >= 3) || (pBufDesc->numMetaPlanes >= 3)) {
        Log_print3(Diags_USER7,
                "[+7] ERROR> pBufDesc (0x%x) has invalid .numPlanes (0x%x) "
                "and/or .numMetaPlanes (0x%x) fields!",
                (IArg)pBufDesc, pBufDesc->numPlanes, pBufDesc->numMetaPlanes);
        return (FALSE);
    }

    for (i = 0; i < pBufDesc->numPlanes; i++) {
        if (pBufDesc->planeDesc[i].buf != NULL) {

            if (pBufDesc->planeDesc[i].memType == XDM_MEMTYPE_RAW) {
                pBufDesc->planeDesc[i].buf = Memory_getBufferVirtualAddress(
                        (UInt32)pBufDesc->planeDesc[i].buf,
                        pBufDesc->planeDesc[i].bufSize.bytes);
            } else {
                /* TODO:H how do we addr translate tiled bufs? */
            }

            /* Clear .accessMask; the local processor didn't access this buf. */
            pBufDesc->planeDesc[i].accessMask = 0;
        }
    }

    for (i = 0; i < pBufDesc->numMetaPlanes; i++) {
        if (pBufDesc->metadataPlaneDesc[i].buf != NULL) {

            if (pBufDesc->metadataPlaneDesc[i].memType == XDM_MEMTYPE_RAW) {
                pBufDesc->metadataPlaneDesc[i].buf =
                        Memory_getBufferVirtualAddress(
                            (UInt32)pBufDesc->metadataPlaneDesc[i].buf,
                            pBufDesc->metadataPlaneDesc[i].bufSize.bytes);
            } else {
                /* TODO:H how do we addr translate tiled bufs? */
            }

            /* Clear .accessMask; the local processor didn't access this buf. */
            pBufDesc->metadataPlaneDesc[i].accessMask = 0;
        }
    }
    return (TRUE);
}
/*
 *  @(#) ti.sdo.ce.video3; 1, 0, 0,1; 2-24-2012 19:32:16; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


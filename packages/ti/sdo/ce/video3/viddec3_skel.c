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
 *  ======== viddec3_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  IVIDDEC3 class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  viddec3_stubs.c
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_video3_viddec3_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "viddec3.h"
#include "_viddec3.h"

extern Registry_Desc ti_sdo_ce_video3_viddec3_desc;

static Bool writebackVideo2BufDesc(IVIDEO2_BufDesc *pBufDesc);

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDDEC3_Msg *msg  = (_VIDDEC3_Msg *)visaMsg;
    VIDDEC3_Handle handle = (VIDDEC3_Handle)visaHandle;
    Int i;
    XDM2_BufDesc inBufs;
    XDM2_BufDesc outBufs;
    IVIDDEC3_OutArgs *pOutArgs;
    IVIDDEC3_Status *pStatus;
    IVIDDEC3_CodecClassConfig *codecClassConfig;
    Int numBufs;
    Bool success;

    /* get stub/skeleton config data; can be NULL (for old codecs) */
    codecClassConfig =
            (IVIDDEC3_CodecClassConfig *)VISA_getCodecClassConfig(visaHandle);

    /* perform the requested VIDDEC2 operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDDEC3_CPROCESS: {
            /* unmarshall inBufs and outBufs */
            inBufs           = msg->cmd.process.inBufs;
            outBufs          = msg->cmd.process.outBufs;

            /* invalidate cache for all input buffers */
            for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                if (inBufs.descs[i].buf != NULL) {
                    /* valid member of sparse array,
                     * invalidate it unless user configured it not to
                     */
                    if (codecClassConfig != NULL &&
                        codecClassConfig->manageInBufsCache[i] == FALSE) {
                       /* do nothing, i.e. don't invalidate */
                    } else {
                        if (inBufs.descs[i].memType == XDM_MEMTYPE_RAW) {
                            Memory_cacheInv(inBufs.descs[i].buf,
                                    inBufs.descs[i].bufSize.bytes);
                        } else {
                            /* TODO:H are tiled buffers cacheable? */
                        }
                    }

                    if (++numBufs == inBufs.numBufs) {
                        break;
                    }
                }
            }

            /* invalidate cache for all output buffers */
            for (i = 0, numBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
                if (outBufs.descs[i].buf != NULL) {
                    /* valid member of sparse array,
                     * invalidate it unless user configured it not to
                     */
                    if (codecClassConfig != NULL &&
                        codecClassConfig->manageOutBufsCache[i] == FALSE) {
                       /* do nothing, i.e. don't invalidate */
                    } else {
                        if (outBufs.descs[i].memType == XDM_MEMTYPE_RAW) {
                            Memory_cacheInv(outBufs.descs[i].buf,
                                    outBufs.descs[i].bufSize.bytes);
                        } else {
                            /* TODO:H are tiled buffers cacheable? */
                        }
                    }

                    if (++numBufs == outBufs.numBufs) {
                        break;
                    }
                }
            }

            /* unmarshall outArgs based on the "size" of inArgs */
            pOutArgs = (IVIDDEC3_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                msg->cmd.process.inArgs.size);

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->decodedBuf bufs nor pOutArgs->displayBufs
             * bufs as the app doesn't provide OUT buffers to the
             * algorithm via these fields.
             */

            /* make the process call */
            msg->visa.status = VIDDEC3_process(handle,
                &inBufs, &outBufs, &(msg->cmd.process.inArgs), pOutArgs);

            /*
             * We probably should only be doing this if msg->visa.status
             * is IVIDDEC3_EOK or _EFAIL and .extendedError is non-fatal.
             */

            /*
             * Writeback cache for all output buffers:
             *   - .decodedBufs
             *   - .displayBufs
             */
            /*
             * ======== .decodedBufs ========
             */

            success = writebackVideo2BufDesc(&pOutArgs->decodedBufs);
            if (!success) {
                return (VISA_EFAIL);
            }

            /*
             * ======== .displayBufs ========
             */

            /* identify which mode the displayBufs are returned as */
            if (pOutArgs->displayBufsMode == IVIDDEC3_DISPLAYBUFS_EMBEDDED) {

                /* the display buffers are embedded in the outArgs struct */
                for (i = 0; (pOutArgs->outputID[i] != 0) &&
                        (i < IVIDEO2_MAX_IO_BUFFERS); i++) {

                    success = writebackVideo2BufDesc(
                            &(pOutArgs->displayBufs.bufDesc[i]));

                    if (!success) {
                        return (VISA_EFAIL);
                    }
                }
            }
            else {
                /* the display buffers are pointed to in the outArgs struct */
                for (i = 0; (pOutArgs->outputID[i] != 0) &&
                        (i < IVIDEO2_MAX_IO_BUFFERS); i++) {

                    success = writebackVideo2BufDesc(
                            pOutArgs->displayBufs.pBufDesc[i]);

                    if (!success) {
                        return (VISA_EFAIL);
                    }
                }
            }

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _VIDDEC3_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus = (IVIDDEC3_Status *)((UInt)(&(msg->cmd.control.params)) +
                msg->cmd.control.params.size);

            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }

            msg->visa.status = VIDDEC3_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.params), pStatus);

            /* writeback data buffer */
            if ((pStatus->data.buf != NULL) &&
                XDM_ISACCESSMODE_WRITE(pStatus->data.accessMask)) {

                Memory_cacheWb(pStatus->data.buf, pStatus->data.bufSize);

                /*
                 * Since we've cacheWb this buffer, we arguably should
                 * reflect this cache state and clear the WRITE bit in
                 * the .accessMask field.  However, we know the stub
                 * doesn't propogate this field to the calling app, so
                 * this extra buffer management detail isn't necessary:
                 *
                 * XDM_CLEARACCESSMODE_WRITE(pStatus->data.accessMask);
                 */
            }

            break;
        }

        default: {
            msg->visa.status = VISA_EFAIL;

            break;
        }
    }
    return (VISA_EOK);
}

static Bool writebackVideo2BufDesc(IVIDEO2_BufDesc *pBufDesc)
{
    Int i;

    /* Check for a spec violation - probably should be an assert! */
    if ((pBufDesc->numPlanes >=3) || (pBufDesc->numMetaPlanes >= 3)) {
        Log_print3(Diags_USER7,
            "[+7] ERROR> pBufDesc (0x%x) has invalid .numPlanes (0x%x) and/or "
            ".numMetaPlanes (0x%x) fields!", (IArg)pBufDesc,
            pBufDesc->numPlanes, pBufDesc->numMetaPlanes);
        return (FALSE);
    }

    for (i = 0; i < pBufDesc->numPlanes; i++) {
        if ((pBufDesc->planeDesc[i].buf != NULL) &&
                (XDM_ISACCESSMODE_WRITE(pBufDesc->planeDesc[i].accessMask))) {

            if (pBufDesc->planeDesc[i].memType == XDM_MEMTYPE_RAW) {
                Memory_cacheWb(pBufDesc->planeDesc[i].buf,
                        pBufDesc->planeDesc[i].bufSize.bytes);
            } else {
                /* TODO:H are tiled buffers cacheable? */
            }
        }

        /*
         * Since we've cacheWb this buffer, we arguably should reflect
         * this cache state and clear the WRITE bit in the .accessMask
         * field.  However, we know the stub doesn't propogate this
         * field to the calling app, so this extra buffer management
         * detail isn't necessary:
         *
         * XDM_CLEARACCESSMODE_WRITE(pBufDesc->planeDesc[i].accessMask);
         */
    }

    for (i = 0; i < pBufDesc->numMetaPlanes; i++) {
        if ((pBufDesc->metadataPlaneDesc[i].buf != NULL) &&
                (XDM_ISACCESSMODE_WRITE(
                    pBufDesc->metadataPlaneDesc[i].accessMask))) {

            if (pBufDesc->metadataPlaneDesc[i].memType == XDM_MEMTYPE_RAW) {
                Memory_cacheWb(pBufDesc->metadataPlaneDesc[i].buf,
                        pBufDesc->metadataPlaneDesc[i].bufSize.bytes);
            } else {
                /* TODO:H are tiled buffers cacheable? */
            }
        }

        /*
         * Since we've cacheWb this buffer, we arguably should
         * reflect this cache state and clear the WRITE bit in
         * the .accessMask field.  However, we know the stub
         * doesn't propogate this field to the calling app, so
         * this extra buffer management detail isn't necessary:
         *
         * XDM_CLEARACCESSMODE_WRITE(pBufDesc->metadataPlaneDesc[i].accessMask);
         */
    }
    return (TRUE);
}

/*
 *  ======== VIDDEC2_SKEL ========
 */
SKEL_Fxns VIDDEC3_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDDEC3_create,
    (SKEL_DESTROYFXN)&VIDDEC3_delete,
};
/*
 *  @(#) ti.sdo.ce.video3; 1, 0, 0,1; 2-24-2012 19:32:16; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


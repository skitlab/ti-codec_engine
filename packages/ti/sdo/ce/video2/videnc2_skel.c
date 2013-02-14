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
 *  ======== videnc2_skel.c ========
 *  This file contains the implemenation of the SKEL interface for the
 *  VIDENC2 class of algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  videnc2_stubs.c
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_video2_videnc2_desc

#include <xdc/std.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "videnc2.h"
#include "_videnc2.h"

extern Registry_Desc ti_sdo_ce_video2_videnc2_desc;

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _VIDENC2_Msg *msg  = (_VIDENC2_Msg *)visaMsg;
    VIDENC2_Handle handle = (VIDENC2_Handle)visaHandle;
    Int i;
    IVIDEO2_BufDesc inBufs;
    XDM2_BufDesc outBufs;
    IVIDENC2_OutArgs *pOutArgs;
    IVIDENC2_Status *pStatus;
    IVIDENC2_CodecClassConfig *codecClassConfig;
    Int numBufs;

    /* get stub/skeleton config data; can be NULL (for old codecs) */
    codecClassConfig = (IVIDENC2_CodecClassConfig *)
                        VISA_getCodecClassConfig(visaHandle);

    /* perform the requested VIDENC2 operation by parsing message. */
    switch (msg->visa.cmd) {

        case _VIDENC2_CPROCESS: {
            /* unmarshall inBufs and outBufs */
            inBufs           = msg->cmd.process.inBufs;
            outBufs          = msg->cmd.process.outBufs;
            /* Should assert inBufs.numPlanes and inBufs.numMetaPlanes
             * are < 3.
             */

            /* invalidate cache for all input plane buffers */
            for (i = 0; i < inBufs.numPlanes; i++) {
                if (inBufs.planeDesc[i].buf != NULL) {
                    if ((codecClassConfig != NULL) &&
                        (codecClassConfig->manageInBufsPlaneDescCache[i] == FALSE)) {
                       /* do nothing, i.e. don't invalidate */
                    } else {
                        if (inBufs.planeDesc[i].memType ==
                                XDM_MEMTYPE_ROW) {
                            Memory_cacheInv(inBufs.planeDesc[i].buf,
                                inBufs.planeDesc[i].bufSize.bytes);
                        } else {
                            /* TODO:H are tiled buffers cacheable? */
                        }
                    }
                }
            }

            /* invalidate cache for all input meta plane buffers */
            for (i = 0; i < inBufs.numMetaPlanes; i++) {
                if (inBufs.metadataPlaneDesc[i].buf != NULL) {
                    if ((codecClassConfig != NULL) &&
                        (codecClassConfig->manageInBufsMetaPlaneDescCache[i] == FALSE)) {
                       /* do nothing, i.e. don't invalidate */
                    } else {
                        if (inBufs.metadataPlaneDesc[i].memType ==
                                XDM_MEMTYPE_ROW) {
                            Memory_cacheInv(inBufs.metadataPlaneDesc[i].buf,
                                inBufs.metadataPlaneDesc[i].bufSize.bytes);
                        } else {
                            /* TODO:H are tiled buffers cacheable? */
                        }
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
                        if (outBufs.descs[i].memType == XDM_MEMTYPE_ROW) {
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
            pOutArgs = (IVIDENC2_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
                msg->cmd.process.inArgs.size);

            /*
             * Note, there's no need to invalidate cache for
             * pOutArgs->encodedBuf bufs nor pOutArgs->reconBufs bufs as they're
             * not _really_ OUT buffers.  Rather they're references to
             * the _real_ OUT buffers that are provided in outBufs - which
             * were already invalidated above.
             */

            /* make the process call */
            msg->visa.status = VIDENC2_process(handle,
                &inBufs, &outBufs, &(msg->cmd.process.inArgs), pOutArgs);

#if 0 /* TODO! */
            /* writeback cache for recon buffers  */
            for (i = 0; ((i < pOutArgs->reconBufs.numBufs) &&
                     (i < IVIDEO_MAX_YUV_BUFFERS)); i++) {
                if ((pOutArgs->reconBufs.bufDesc[i].buf != NULL) &&
                    (XDM_ISACCESSMODE_WRITE(
                        pOutArgs->reconBufs.bufDesc[i].accessMask))) {

                    Memory_cacheWb(pOutArgs->reconBufs.bufDesc[i].buf,
                        pOutArgs->reconBufs.bufDesc[i].bufSize);

                    /*
                     * Since we've cacheWb this buffer, we arguably should
                     * reflect this cache state and clear the WRITE bit in
                     * the .accessMask field.  However, we know the stub
                     * doesn't propogate this field to the calling app, so
                     * this extra buffer management detail isn't necessary:
                     *
                     * XDM_CLEARACCESSMODE_WRITE(
                     *         pOutArgs->reconBufs.bufDesc[i].accessMask);
                     */
                }
            }
#endif /* TODO! */

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _VIDENC2_CCONTROL: {
            /* unmarshall status based on the "size" of params */
            pStatus = (IVIDENC2_Status *)((UInt)(&(msg->cmd.control.params)) +
                msg->cmd.control.params.size);

            /* invalidate data buffer */
            if (pStatus->data.buf != NULL) {
                Memory_cacheInv(pStatus->data.buf, pStatus->data.bufSize);
            }

            msg->visa.status = VIDENC2_control(handle, msg->cmd.control.id,
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

/*
 *  ======== VIDENC1_SKEL ========
 */
SKEL_Fxns VIDENC2_SKEL = {
    call,
    (SKEL_CREATEFXN)&VIDENC2_create,
    (SKEL_DESTROYFXN)&VIDENC2_delete,
};
/*
 *  @(#) ti.sdo.ce.video2; 1, 0, 3,1; 2-24-2012 19:31:59; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


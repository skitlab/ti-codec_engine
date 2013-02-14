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
 *  ======== node_dele.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_node_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/knl/Thread.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/ipc/Comm.h>

#include <node.h>
#include <_node.h>

extern Registry_Desc ti_sdo_ce_node_desc;

/*
 *  ======== NODE_delete ========
 */
Int NODE_delete(NODE_Handle node)
{
    Void   *handle;

    /* Should be a DBC_requires */
    Assert_isTrue(node != NULL, (Assert_Id)NULL);
    Assert_isTrue(node->skelFxns != NULL, (Assert_Id)NULL);
    Assert_isTrue(node->skelFxns->apiDestroy != NULL, (Assert_Id)NULL);

    /* delete thread *before* destroying node to ensure thread has no access
     * to node as we are freeing it
     */
    if (node->self) {
        Log_print1(Diags_ENTRY, "[+E] NODE_delete(0x%x)", (IArg)node);

        Thread_delete(&(node->self));
    }

    handle = NODE_getEnv(node);

    if (handle) {
        node->skelFxns->apiDestroy(handle);
    }

    if (node->recv != Comm_INVALIDHANDLE) {
        Comm_delete(node->recv);
    }

    Memory_free(NULL, node, sizeof(NODE_Obj));

    return (NODE_EOK);
}
/*
 *  @(#) ti.sdo.ce.node; 1, 0, 0,1; 2-24-2012 19:30:15; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


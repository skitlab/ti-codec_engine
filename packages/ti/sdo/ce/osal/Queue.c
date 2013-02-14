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
 *  ======== Queue.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Gate.h>

#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/osal/Global.h>

#include <assert.h>


/*
 *  ======== Queue_get ========
 */
Ptr Queue_get(Queue_Handle queue)
{
    Ptr elem;
    IArg key;

    key = Gate_enterSystem();   /* atomic begin */

    elem = Queue_dequeue(queue);

    Gate_leaveSystem(key); /* atomic end */

    return (elem);
}

/*
 *  ======== Queue_put ========
 */
Void Queue_put(Queue_Handle queue, Ptr elem)
{
    IArg key;

    key = Gate_enterSystem();   /* atomic begin */

    Queue_enqueue(queue, elem);

    Gate_leaveSystem(key); /* atomic end */
}

/*
 *  ======== Queue_extract ========
 */
Void Queue_extract(Queue_Elem *elem)
{
    IArg key;

    key = Gate_enterSystem();   /* atomic begin */

    Queue_remove(elem);

    Gate_leaveSystem(key); /* atomic end */
}

/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:13; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Loader.h ========
 */


/**
 * @brief       Name to pass to Diags_setMask() to enable logging for Loader
 *              functions. For example,
 *                  Diags_setMask(Loader_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define Loader_MODNAME "ti.sdo.ce.osal.Loader"

#define Loader_GTNAME "ti.sdo.ce.osal.Loader"

typedef struct Loader_Object *Loader_Handle;


/*
 *  ======== Loader_getSymbol ========
 */
UInt32 Loader_getSymbol(Loader_Handle lib, String name);

/*
 *  ======== Loader_init ========
 */
Void Loader_init(Void);

/*
 *  ======== Loader_loadLibrary ========
 */
Loader_Handle Loader_loadLibrary(String name);

/*
 *  ======== Loader_setSearchPath ========
 *  Set the search path for libraries loaded with Loader_loadLibrary().
 *  Returns TRUE if successful, FALSE otherwise.
 */
Bool Loader_setSearchPath(String path);

/*
 *  ======== Loader_unloadLibrary ========
 */
Void Loader_unloadLibrary(Loader_Handle lib);
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:12; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


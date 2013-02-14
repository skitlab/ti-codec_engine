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
 *  ======== Loader_noOS.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_osal_Loader_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/ce/global/CESettings.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/Loader.h>


typedef struct Loader_Object {
    Int     dummy;
} Loader_Object;


static Void    cleanup(Void);

Registry_Desc ti_sdo_ce_osal_Loader_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Int curInit = 0;


/*
 *  ======== Loader_getSymbol ========
 */
UInt32 Loader_getSymbol(Loader_Handle lib, String name)
{
    return (NULL);
}


/*
 *  ======== Loader_init ========
 */
Void Loader_init(Void)
{
    Registry_Result   result;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_osal_Loader_desc,
                Loader_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Loader_MODNAME);
        }
        regInit = 1;
    }

    if (curInit++ == 0) {
        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== Loader_loadLibrary ========
 */
Loader_Handle Loader_loadLibrary(String name)
{
    Loader_Object *lib = NULL;

    if ((lib = Memory_alloc(NULL, sizeof(Loader_Object), 0, NULL)) == NULL) {
        Log_print0(Diags_USER7, "[+7] Loader_load> Memory_alloc failed");
        return (NULL);
    }

    return (lib);
}

/*
 *  ======== Loader_setSearchPath ========
 */
Bool Loader_setSearchPath(String path)
{
    return (TRUE);
}

/*
 *  ======== Loader_unloadLibrary ========
 */
Void Loader_unloadLibrary(Loader_Handle lib)
{
    if (lib) {
        Memory_free(NULL, lib, sizeof(Loader_Object));
    }   
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    Assert_isTrue(curInit > 0, (Assert_Id)NULL);

    if (--curInit == 0) {
        /* Nothing to do */
    }
}

/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,1; 2-24-2012 19:30:18; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


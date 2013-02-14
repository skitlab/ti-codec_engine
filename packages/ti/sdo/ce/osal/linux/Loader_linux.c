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
 *  ======== Loader_linux.c ========
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

#include <dlfcn.h>
#include <string.h>


/*
 *  ======== Loader_Object ========
 */
typedef struct Loader_Object {
    String  name;     /* Name of library */
    void   *handle;   /* Handle the opened library */
} Loader_Object;


static Void    cleanup(Void);

Registry_Desc ti_sdo_ce_osal_Loader_desc;

static Int regInit = 0;     /* Registry_addModule() called */
static Int curInit = 0;

static String libPath = NULL;
static String tmpPath = NULL;
static Int    pathLen = 0;


/*
 *  ======== Loader_getSymbol ========
 */
UInt32 Loader_getSymbol(Loader_Handle lib, String name)
{
    Void     *sym = NULL;
    String    errString = NULL;

    Log_print2(Diags_ENTRY, "[+E] Loader_getSymbol(0x%lx, %s)",
            (IArg)lib, (IArg)name);

    sym = dlsym(lib->handle, name);

    if (sym == NULL) {
        Log_print1(Diags_USER6, "[+6] Loader_getSymbol(): %s failed",
                (IArg)name);

        errString = (String)dlerror();

        if (errString != NULL) {
            Log_print1(Diags_USER7, "[+7] Loader_getSymbol> dlsym() error: %s",
                    (IArg)errString);
        }
    }

    Log_print1(Diags_EXIT, "[+X] Loader_getSymbol> Returning 0x%x", (IArg)sym);

    return ((UInt32)sym);
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
    Char           seps[] = ";";
    Char          *dir = NULL;
    String         errString = NULL;
    String         fullPath = NULL;
    Int            bufLen;

    Log_print1(Diags_ENTRY, "[+E] Loader_loadLibrary(%s)", (IArg)name);

    if ((lib = Memory_alloc(NULL, sizeof(Loader_Object), 0, NULL)) == NULL) {
        Log_print0(Diags_USER7,
                "[+7] Loader_loadLibrary> Memory_alloc failed");
        return (NULL);
    }

    /*
     *  Load the library. dlopen() will return the same handle if the library
     *  is already loaded. dlclose() must be called the same number of times
     *  as dlopen() for the library to be unloaded.
     *
     *  RTLD_LAZY: Perform lazy binding of function references (only resolve
     *  symbols when executed).
     *  RTLD_NOW: Resolve all symbols before dlopen() returns.
     *
     *  First try loading the library name as is. If this fails, try searching
     *  along the path.
     */
    lib->handle = dlopen(name, RTLD_NOW);
    if (lib->handle == NULL) {
        if (libPath == NULL) {
            Log_print0(Diags_USER7,
                    "[+7] Loader_loadLibrary> dlopen() failed");

            /* Get the last dlerror */
            errString = (String)dlerror();
            if (errString != NULL) {
                Log_print1(Diags_USER7,
                        "[+7] Loader_loadLibrary> dlopen() error: %s",
                        (IArg)errString);
            }
            Memory_free(NULL, lib, sizeof(Loader_Object));
            return (NULL);
        }

        /* strtok will mess up the path, so copy it first. */
        Assert_isTrue(tmpPath != NULL, (Assert_Id)NULL);
        strcpy(tmpPath, libPath);

        /* Allocate a big enough buffer for storing the full path name */
        bufLen = strlen(libPath) + strlen(name) + 2;
        fullPath = Memory_alloc(NULL, bufLen, 0, NULL);

        if (fullPath == NULL) {
            Log_print0(Diags_USER7, "[+7] Loader_loadLibrary> "
                    "Memory_alloc full path buffer failed");
            Memory_free(NULL, lib, sizeof(Loader_Object));
            return (NULL);
        }

        dir = strtok(tmpPath, seps);

        while (dir != NULL) {
            strcpy(fullPath, dir);
            strcat(fullPath, "/");
            strcat(fullPath, name);

            lib->handle = dlopen(fullPath, RTLD_NOW);

            if (lib->handle != NULL) {
                Log_print1(Diags_USER2, "[+2] Loader_loadLibrary> "
                        "dlopen(%s) succeeded!", (IArg)fullPath);
                break;
            }

            /*
             *  Get the last dlerror in case library was found but there was
             *  some other problem (eg, wrong format).
             */
            errString = (String)dlerror();
            if (errString != NULL) {
                Log_print2(Diags_USER2, "[+2] Loader_loadLibrary> "
                        "dlopen(%s) failed, error returned:\n     %s",
                        (IArg)fullPath, (IArg)errString);
            }

            dir = strtok(NULL, seps);
        }

        if (fullPath) {
            Memory_free(NULL, fullPath, bufLen);
        }

        if (dir == NULL) {
            Log_print2(Diags_USER7, "[+7] Loader_loadLibrary> "
                    "Failed to load library: %s with search path %s",
                    (IArg)name, (IArg)libPath);
        }
    }

    if (lib && (lib->handle == NULL)) {
        Memory_free(NULL, lib, sizeof(Loader_Object));
        lib = NULL;
    }

    Log_print1(Diags_EXIT, "[+X] Loader_loadLibrary> Exit, returning 0x%x",
            (IArg)lib);

    return (lib);
}

/*
 *  ======== Loader_setSearchPath ========
 */
Bool Loader_setSearchPath(String path)
{
    Bool    retVal = TRUE;

    Log_print1(Diags_ENTRY, "[+E] Loader_setSearchPath> Enter (%s)",
            (IArg)path);

    Assert_isTrue(((libPath != NULL) && (tmpPath != NULL) && (pathLen > 0)) ||
            ((libPath == NULL) && (tmpPath == NULL) && (pathLen == 0)),
            (Assert_Id)NULL);

    if (path == NULL) {
        /* Unsetting the library search path */
        if (libPath) {
            Memory_free(NULL, libPath, pathLen);
            Memory_free(NULL, tmpPath, pathLen);
            pathLen = 0;
        }
    }
    else if (pathLen < strlen(path) + 1) {
        /* Current path buffer is NULL or too small, free and re-allocate */
        if (libPath) {
            Memory_free(NULL, libPath, pathLen);
            Memory_free(NULL, tmpPath, pathLen);
            libPath = tmpPath  = NULL;
        }

        pathLen = strlen(path) + 1;
        libPath = Memory_alloc(NULL, pathLen, 0, NULL);

        if (libPath == NULL) {
            Log_print1(Diags_USER7, "[+7] Loader_setSearchPath> "
                    "Memory allocation of size %d failed!", (IArg)pathLen);
            retVal = FALSE;
        }
        else {
            tmpPath = Memory_alloc(NULL, pathLen, 0, NULL);
            if (tmpPath == NULL) {
                Log_print1(Diags_USER7, "[+7] Loader_setSearchPath> "
                        "Memory allocation of size %d failed!", (IArg)pathLen);
                retVal = FALSE;
            }
        }
    }

    if (!retVal) {
        /* Cleanup on failure */
        if (libPath) {
            Memory_free(NULL, libPath, pathLen);
            libPath = NULL;
        }
        if (tmpPath) {
            Memory_free(NULL, tmpPath, pathLen);
            tmpPath = NULL;
        }
        pathLen = 0;
    }
    else {
        if (path) {
            /* Copy in the new path */
            Assert_isTrue(strlen(path) + 1 <= pathLen, (Assert_Id)NULL);
            strcpy(libPath, path);
        }
    }

    Assert_isTrue(((libPath != NULL) && (tmpPath != NULL) && (pathLen > 0)) ||
            ((libPath == NULL) && (tmpPath == NULL) && (pathLen == 0)),
            (Assert_Id)NULL);

    Log_print1(Diags_EXIT, "[+X] Loader_setSearchPath> Exit, returning %s",
            (IArg)(retVal ? "TRUE" : "FALSE"));

    return (retVal);
}


/*
 *  ======== Loader_unloadLibrary ========
 */
Void Loader_unloadLibrary(Loader_Handle lib)
{
    Log_print1(Diags_ENTRY, "[+E] Loader_unloadLibrary(0x%x)", (IArg)lib);

    if (lib) {
        if (lib->handle) {
            /*
             *  Note: dlclose() will decrement the library's reference count,
             *  and only unload if the reference count goes to zero.
             */
            dlclose(lib->handle);
        }

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
        /* Free library search path buffers */
        if (libPath) {
            Memory_free(NULL, libPath, pathLen);
            libPath = NULL;
        }
        if (tmpPath) {
            Memory_free(NULL, tmpPath, pathLen);
            tmpPath = NULL;
        }
        pathLen = 0;
    }
}

/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,1; 2-24-2012 19:30:20; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


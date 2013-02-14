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
 *  ======== Engine.c ========
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_ce_Engine_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/knl/GateThread.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Registry.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/ipc/Processor.h>

#include <ti/sdo/ce/global/CESettings.h>
#include <ti/sdo/ce/alg/Algorithm.h>

#include <ti/sdo/ce/osal/Loader.h>
#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/node/node.h>

#include <ti/xdais/ialg.h>

Registry_Desc ti_sdo_ce_Engine_desc;

static Int regInit = 0;     /* Registry_addModule() called */

/*
 *  Names of functions that a dynamically loaded codec must supply.
 *
 *  TODO: These symbol names should be global somewhere (once the names are
 *  settled on) since dynamically loaded codec must have functions by these
 *  names.
 *
 *  TODO: Should we assume the dynamically loaded codec will have only
 *  one alg descriptor?
 */
#define GETNUMALGDESCFXN "GetNumEngineAlgDesc"
#define GETALGDESCFXN  "GetEngineAlgDesc"

typedef Int (*GetNumAlgDescFxn)(Void);
typedef Int (*GetAlgDescFxn)(Engine_AlgDesc *algDescTab);

typedef struct RServerObj {
    Processor_Handle  dspProc;
    String            imageName;
    Int               refCount;
} RServerObj, *RServer;

/*
 *  ======== _Engine_AlgLib ========
 *  Structure to hold information about algs added with Engine_addAlg().
 */
typedef struct _Engine_AlgLib {
    struct _Engine_AlgLib   *next;
    Loader_Handle           lib;
    Engine_AlgDesc          algDesc;

    /* Need this to support Engine_getAlgInfo() */
    String                  typeTab[2];
} _Engine_AlgLib;

/*
 *  ======== Engine_Obj ========
 */
typedef struct Engine_Obj {
    Queue_Elem      link;
    RServer         server;
    Comm_Id         toRMS;
    Comm_Handle     fromRMS;
    UInt16          rmsPoolId;
    Comm_Msg        rmsMsg;
    Engine_Desc     *desc;
    Engine_Error    lastError;
    Bool            hasServer;  /* TRUE <=> there is a server */

    /* Filled in when Engine_initFromServer() is called */
    Engine_AlgDesc *remoteAlgTab;
    Int numRemoteAlgs;

    _Engine_AlgLib *loadedLibs;    /* Algs added with Engine_addAlg() */
    Int             numLoadedLibs; /* Number of algs added */

    struct Engine_DescListElem *descElem;
    String          procId;     /* server proc name */
} Engine_Obj;

/*
 *  ======== Engine_NodeObj ========
 */
typedef struct Engine_NodeObj {
    Engine_Handle   engine;
    Comm_Id         stdIn;      /* the node's input queue */
    Comm_Handle     stdOut;     /* the node's output queue */
    String          impId;      /* algorithm implementation name */
    RMS_Word        rmsNode;    /* remote node handle */
    size_t          msgSize;    /* size of messages exchanged with node */
    RMS_Word        remoteVisa; /* Remote visa handle */
} Engine_NodeObj;

/*
 *  ======== Engine_DescListElem ========
 *  Structure for queuing up Engine_Desc objects.
 */
typedef struct Engine_DescListElem {
    Queue_Elem      link;
    Engine_Desc     desc;

    /*
     *  This is a list of algs that have been added to the engine while
     *  it is not in the 'open' state. Algs added before the engine has
     *  been opened will be accessible to all threads opening the engine.
     *  Once an engine has been opened, any algs added will be maintained
     *  in the Engine handle passed to Engine_addAlg(), and will only
     *  be accessible from the Engine handle.
     */
    _Engine_AlgLib *loadedLibs;    /* Algs that have been added */
    Int             numLoadedLibs; /* Number of algs added */

    Int             refCount;   /* Number of opened engines */

    /*
     *  Staticaly created engines will be put on the list too. For these
     *  engines, we don't need to allocate buffers for the engine name
     *  and remote name. We mark them as static, so as not to free the
     *  names.
     */
    Bool            isStatic;
} Engine_DescListElem;

/*
 *  Stub function entry that can be queued up.
 */
typedef struct Engine_StubFxnsElem {
    Queue_Elem  link;
    String      name;
    IALG_Fxns  *stubFxns;
} Engine_StubFxnsElem;

String ti_sdo_ce__versionString = "1, 0, 6";


/*
 *  ======== Engine_ALGCREATEATTRS ========
 */
Engine_AlgCreateAttrs Engine_ALGCREATEATTRS = {
    FALSE,      /* Use external heap */
    -1,         /* priority */
};

Engine_Attrs Engine_ATTRS = {
    NULL,         /* procId */
};

/* currently static internal fxn - should this be external? */
static Engine_Error Engine_getNumServerAlgs(Server_Handle server, Int *nAlgs);


static Engine_Error addEngineToList(Engine_Desc *desc, Bool isStatic);
static Engine_Node allocNode(Engine_Handle s, String impId);
static RMS_Status callServer(Engine_Handle engine, Comm_Msg *msg);
static Bool checkServer(Engine_Handle engine);
static Void cleanup(Void);
static Int copyToFile(Char *cp, Int size, String prefix, Bool *nl, FILE *out);
static Void freeNode(Engine_Node node);
static Void freeServerTab(Engine_Handle engine);
static Engine_AlgDesc *getAlgDesc(String name, Engine_Handle engine,
        String algName);
static Engine_AlgDesc *getAlgDescNum(String engName, Engine_Handle engine,
        Int index);
static Engine_DescListElem *getDescListElem(String name);
static String getServerKey(Engine_Handle engine);
static Bool isa(Engine_AlgDesc *alg, String type);
static Void name2Uuid(Engine_Obj *engine, String name, NODE_Uuid *uuid);
static Engine_Handle rmsInit(Engine_Obj *engine, Engine_Error *ec);
static Int getRpcProtocolVersion(Engine_Obj *engine, NODE_Uuid uuid);

static Void rserverClose(RServer server);
static Void rserverDetach(Engine_Handle engine);
static RServer rserverOpen(Engine_Desc * desc, Bool * startedServer,
    String procId);

extern Bool ti_sdo_ce_Engine_initFromServer;
extern Bool Server_holdingTraceToken;

/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

/* The size of this table is numProcs - it's allocated/freed at runtime */
static RServerObj *serverTab = NULL;

static Queue_Elem stubFxnsList;

/* set by CERuntime.xdt, determines if to collect DSP trace and how to set it */
Bool   Engine_alwaysCollectDspTrace = FALSE;
String Engine_ceDebugDspTraceMask   = "";

static GateThread_Handle serverLock = NULL; /* serialize access to serverTab */
static GateThread_Handle traceLock  = NULL;  /* serialize collectDspTrace */
static GateThread_Handle engineLock = NULL; /* serialize rest of Engine */

static Engine_Handle localEngine = NULL;
static Queue_Elem engineList;

static Int        numEngines = 0;
static Queue_Elem engineDescList;

/*
 *  ======== collectDspTrace ========
 */
static Void collectDspTrace(Engine_Handle engine)
{
    IArg key;
    Char prefix[32];   /* big enough? */

    sprintf(prefix, "[%s] ", engine->procId);

    key = GateThread_enter(traceLock);
    Engine_fwriteTrace( engine, prefix, stdout );
    GateThread_leave(traceLock, key);
}

/*
 *  ======== Engine_add ========
 */
Engine_Error Engine_add(Engine_Desc *pDesc)
{
    Engine_Error    status = Engine_EOK;

    Log_print1(Diags_ENTRY, "[+E] Engine_add(0x%x)", (IArg)pDesc);

    if ((pDesc == NULL) || (pDesc->name == NULL)) {
        Log_print0(Diags_USER7,
                "[+7] Engine_add> Engine desc or desc->nname is NULL!");
        status = Engine_EINVAL;
    }

    if (status == Engine_EOK) {
        /* Make sure engine name is not in already being used. */
        if (getDescListElem(pDesc->name) != NULL) {
            Log_print1(Diags_USER6, "[+6] Engine_add> Engine %s "
                    "already exists!", (IArg)pDesc->name);
            status = Engine_EINUSE;
        }
        else {
            status = addEngineToList(pDesc, FALSE);
        }
    }

    Log_print1(Diags_EXIT, "[+X] Engine_add> return (%d)", status);

    return (status);
}

/*
 *  ======== Engine_addAlg ========
 */
Engine_Error Engine_addAlg(String engName, Engine_Handle engine,
        String location, Engine_AlgDesc *pAlgDesc)
{
    Engine_DescListElem    *descElem;
    Engine_DllAlgDesc       dllAlgDesc;
    Loader_Handle           lib = NULL;
    Engine_GetAlgDescFxn    getAlgDescFxn = NULL;
    _Engine_AlgLib        **loadedLibs = NULL;
    Int                    *numLoadedLibs;
    _Engine_AlgLib         *algLib = NULL;
    Int                     size;
    String                  algName;
    String                  algTypes = NULL;
    String                  libPath = NULL;
    IArg                    key;
    Engine_Error            status = Engine_EOK;

    Log_print4(Diags_ENTRY, "[+E] Engine_addAlg('%s', 0x%lx, '%s', 0x%lx)",
            (IArg)engName, (IArg)engine, (IArg)location, (IArg)pAlgDesc);

    /* Exactly one of engName and engine must be non-NULL */
    if ((!engine && !engName) || (engine && engName)) {
        Log_print2(Diags_USER7, "[+7] Engine_addAlg> engine name = '%s', "
                "engine handle = 0x%lx. Bad input args: One and only one of "
                "these must be non-NULL!", (IArg)engName, (IArg)engine);
        return (Engine_EINVAL);
    }

    /* Check pAlgDesc and fields */
    if ((pAlgDesc == NULL) || (pAlgDesc->name == NULL)) {
        Log_print1(Diags_USER7, "[+7] Engine_addAlg> Engine_AlgDesc [0x%x] "
                "must be non-NULL, and must have a non-NULL alg name.",
                (IArg)pAlgDesc);
        return (Engine_EINVAL);
    }

    if (location == NULL) {
        /* Not a dynamic library, check more pAlgDesc params */
        if (pAlgDesc->fxns == NULL) {
            Log_print0(Diags_USER7, "[+7] Engine_addAlg> Engine_AlgDesc  "
                    "fxns must not be NULL.");
            return (Engine_EINVAL);
        }

        /*
         *  TODO:
         *  CERuntime macros for creating Engine_AlgDesc use typeTab array. If
         *  this is changed to use 'types', we can just check 'types'.
         */
        if (((pAlgDesc->typeTab == NULL) || (pAlgDesc->typeTab[0] == NULL)) &&
             (pAlgDesc->types == NULL)) {
            Log_print0(Diags_USER7, "[+7] Engine_addAlg> Engine_AlgDesc  "
                    "types must not be NULL.");
            return (Engine_EINVAL);
        }
    }

    Log_print3(Diags_ENTRY, "[+E] Engine_addAlg: alg params: name = %s, "
            "isLocal = %d, groupId = %d",
            (IArg)(pAlgDesc->name), (IArg)(pAlgDesc->isLocal),
            (IArg)(pAlgDesc->groupId));

    algName = pAlgDesc->name;

    /* Currently only adding local algs is supported. */
    if (!pAlgDesc->isLocal) {
        Log_print0(Diags_USER6,
                "[+6] Engine_addAlg> Remote algs currently not supported.");
        return (Engine_ENOTAVAIL);
    }

    key = GateThread_enter(engineLock);

    /* Check if the engine already has an alg named pAlgDesc->name. */
    if ((getAlgDesc(engName, engine, algName)) != NULL) {
        // TODO: Should we check that desc matches the one passed in
        // and bump a reference count?
        Log_print1(Diags_USER6, "[+6] Engine_addAlg> Name %s already in use "
                "by an alg", (IArg)algName);

        GateThread_leave(engineLock, key);
        return (Engine_EINUSE);
    }

    /*
     *  If an engine name was passed in, make sure it exists and is not
     *  in the "open" state.
     */
    if (engName) {
        if ((descElem = getDescListElem(engName)) == NULL) {
            Log_print1(Diags_USER7, "[+7] Engine_addAlg> Engine %s not found.",
                    (IArg)engName);

            GateThread_leave(engineLock, key);
            return (Engine_EEXIST);
        }

        if (descElem->refCount) {
            Log_print1(Diags_USER7, "[+7] Engine_addAlg> Engine %s is open. "
                    "Cannot add alg using engine name, use engine handle "
                    "instead.", (IArg)engName);
            GateThread_leave(engineLock, key);
            return (Engine_EINUSE);
        }

        /*
         *  We'll be adding the alg to the engine descriptor element, so
         *  all Engine handles that open 'engName' can access it.
         */
        loadedLibs = &(descElem->loadedLibs);
        numLoadedLibs = &(descElem->numLoadedLibs);
    }
    else {
        /*
         *  We'll be adding the alg to this engine's object, so it will
         *  only be accessible through this Engine handle.
         */
        loadedLibs = &(engine->loadedLibs);
        numLoadedLibs = &(engine->numLoadedLibs);
    }

    if (location != NULL) {
        /* Load the library containing the algs to add */
        if ((libPath = Global_getenv("CE_LIBPATH")) != NULL) {
            Loader_setSearchPath(libPath);
        }

        lib = Loader_loadLibrary(location);

        if (lib == NULL) {
            Log_print1(Diags_USER7, "[+7] Engine_addAlg-> "
                    "Loader_loadLibrary() [%s] failed", (IArg)location);

            /*
             *  Unfortunately, there's no Engine_EFAIL we can return here. We
             *  don't really no why the load failed. It could be that the
             *  library was not in the correct format, or that it was not
             *  found.  The Loader_loadLibrary() trace should indicate the
             *  reason.
             */
            GateThread_leave(engineLock, key);
            return (Engine_ENOTFOUND);
        }
        else {
            Log_print0(Diags_USER1, "[+1] Engine_addAlg> loaded library.");
        }

        if (status == Engine_EOK) {
            /* Get address of the function that fills in the alg descriptor. */
            getAlgDescFxn = (Engine_GetAlgDescFxn)Loader_getSymbol(lib,
                    Engine_GETALGDESCFXN);

            if (getAlgDescFxn == NULL) {
                Log_print1(Diags_USER7, "[+7] Engine_addAlg> "
                        "Loader_getSymbol(): %s failed", (IArg)GETALGDESCFXN);

                status = Engine_ENOTFOUND; // TODO: Add Engine_ESYMBOL?
            }
        }
    }

    /* Allocate structure to hold alg and library information */
    if (status == Engine_EOK) {
        algLib = Memory_alloc(sizeof(_Engine_AlgLib), NULL);

        if (algLib == NULL) {
            Log_print1(Diags_USER7,
                    "[+7] Engine_addAlg> Memory_alloc (%d) failed",
                    (IArg)sizeof(_Engine_AlgLib));
            status = Engine_ENOMEM;
        }
        else {
            algLib->lib = lib; /* lib will be NULL for non-dynamic case */
            algLib->typeTab[0] = algLib->typeTab[1] = NULL;
            algLib->algDesc.name = NULL;
            algLib->algDesc.types = NULL;
        }
    }

    if (status == Engine_EOK) {
        if (lib) {
            /* groupId and isLocal are not know by dynamic library */
            algLib->algDesc.groupId = pAlgDesc->groupId;
            algLib->algDesc.isLocal = pAlgDesc->isLocal;

            /* Get the rest of the alg descriptor from the library */
            (*getAlgDescFxn)(&dllAlgDesc);
            algLib->algDesc.fxns = dllAlgDesc.fxns;
            algLib->algDesc.idmaFxns = dllAlgDesc.idmaFxns;
            algLib->algDesc.iresFxns = dllAlgDesc.iresFxns;
            algTypes = dllAlgDesc.types;
        }
        else {
            algLib->algDesc = *pAlgDesc;
            algTypes = (pAlgDesc->types) ? pAlgDesc->types :
                    pAlgDesc->typeTab[0]; /* For CERuntime macros */
        }
        /* TODO: For remote something unique case, set to something unique */
        algLib->algDesc.uuid.data = 0;
    }

    /* Copy the alg name to the new alg descriptor */
    if (status == Engine_EOK) {
        size = strlen(algName) + 1;
        algLib->algDesc.name = Memory_alloc(size, NULL);
        if (algLib->algDesc.name == NULL) {
            Log_print1(Diags_USER7,
                    "[+7] Engine_addAlg> Memory_alloc(%d) alg name failed",
                    (IArg)size);
            status = Engine_ENOMEM;
        }
        else {
            strcpy(algLib->algDesc.name, algName);
        }
    }

    /* Copy the alg types to the new alg descriptor */
    if (status == Engine_EOK) {
        size = strlen(algTypes) + 1;
        algLib->algDesc.types = Memory_alloc(size, NULL);
        if (algLib->algDesc.types == NULL) {
            Log_print1(Diags_USER7,
                    "[+7] Engine_addAlg> Memory_alloc(%d) alg types failed",
                    (IArg)size);
            status = Engine_ENOMEM;
        }
        else {
            strcpy(algLib->algDesc.types, algTypes);
            algLib->typeTab[0] = algLib->algDesc.types;
            algLib->algDesc.typeTab = algLib->typeTab;
        }
    }

    /*
     *  Pass groupId to Algorithm_addGroup() to create group semaphore if it
     *  doesn't exist yet.
     */
    if (!Algorithm_addGroup(pAlgDesc->groupId)) {
        Log_print1(Diags_USER7, "[+7] Engine_addAlg> Algorithm_addGroup(%d) "
                "failed", (IArg)(pAlgDesc->groupId));

        /* Don't know why this failed, assume memory allocation. */
        status = Engine_ENOMEM;
    }

    if (status == Engine_EOK) {
        Log_print6(Diags_USER1,
                "[+1] Engine_addAlg> Adding desc [0x%x]:\n"
                "    fxns [0x%x],\n"
                "    idmaFxns [0x%x],\n"
                "    iresFxns [0x%x],\n"
                "    stub/skel config params [0x%x],\n"
                "    types [%s]",
                (IArg)(&algLib->algDesc),
                (IArg)(algLib->algDesc.fxns),
                (IArg)(algLib->algDesc.idmaFxns),
                (IArg)(algLib->algDesc.iresFxns),
                (IArg)(algLib->algDesc.codecClassConfig),
                (IArg)(algLib->algDesc.types));

        algLib->next = *loadedLibs;
        *loadedLibs = algLib;
        (*numLoadedLibs)++;
    }
    else {
        /* Clean up */
        if (lib) {
            Loader_unloadLibrary(lib);
        }
        if (algLib) {
            if (algLib->algDesc.name) {
                Memory_free(algLib->algDesc.name, strlen(algName) + 1, NULL);
            }
            if (algLib->algDesc.types) {
                Memory_free(algLib->algDesc.types, strlen(algTypes) + 1, NULL);
            }
            Memory_free(algLib, sizeof(_Engine_AlgLib), NULL);
        }
    }

    GateThread_leave(engineLock, key);
    return (status);
}

/*
 *  ======== Engine_addStubFxns ========
 */
Engine_Error Engine_addStubFxns(String fxnsName, IALG_Fxns *fxns)
{
    Engine_StubFxnsElem *stubs;
    Engine_Error         status = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine_addStubFxns('%s', 0x%x)",
            (IArg)fxnsName, (IArg)fxns);

    stubs = Memory_alloc(sizeof(Engine_StubFxnsElem), NULL);

    if (stubs == NULL) {
        Log_print0(Diags_USER7, "[+7] Engine_addStubFxns> Memory allocation "
                  "failed!");
        status = Engine_ENOMEM;
    }
    else {
        Queue_new(&stubs->link);

        stubs->name = fxnsName;
        stubs->stubFxns = fxns;

        Queue_put(&stubFxnsList, stubs);
    }

    Log_print1(Diags_EXIT, "[+X] Engine_addStubFxns> return (%d)", status);
    return (status);
}

/*
 *  ======== Engine_removeAlg ========
 */
Engine_Error Engine_removeAlg(String engName, Engine_Handle engine,
        String algName)
{
    _Engine_AlgLib    **loadedLibs = NULL;
    Int                *numLoadedLibs;
    _Engine_AlgLib     *curLib = NULL;
    _Engine_AlgLib     *prevLib = NULL;
    Engine_DescListElem *descElem = NULL;
    IArg                key;
    Engine_Error        status = Engine_ENOTFOUND;

    Log_print3(Diags_ENTRY, "[+E] Engine_removeAlg('%s', 0x%lx, '%s')",
            (IArg)engName, (IArg)engine, (IArg)algName);

    if ((engName && engine) || (!engName && !engine)) {
        Log_print2(Diags_USER7, "Engine_removeAlg> Bad input params: One of "
                   "engine name [%s] and engine handle [0x%x] must be "
                   "non-NULL, the other must be NULL",
                (IArg)engName, (IArg)engine);
        return (Engine_EINVAL);
    }

    if (algName == NULL) {
        Log_print0(Diags_USER7, "Engine_removeAlg> Bad input params: alg "
                "name must not be NULL");
        return (Engine_EINVAL);
    }

    /* Lock list of engines */
    key = GateThread_enter(engineLock);

    if (engName != NULL) {
        if ((descElem = getDescListElem(engName)) == NULL) {
            Log_print1(Diags_USER7, "[+7] Engine_removeAlg> Engine %s "
                    "not found.", (IArg)engName);

            /* Release lock */
            GateThread_leave(engineLock, key);
            return (Engine_EEXIST);
        }

        /* Remove from list of algs added before engine was opened. */
        loadedLibs = &(descElem->loadedLibs);
        numLoadedLibs = &(descElem->numLoadedLibs);
        curLib = descElem->loadedLibs;
    }
    else {
        /*
         *  Use list of algs added after the engine was opened. The engine
         *  is obviously opened, so we can only remove from this list.
         */
        descElem = engine->descElem;
        loadedLibs = &(engine->loadedLibs);
        numLoadedLibs = &(engine->numLoadedLibs);
        curLib = engine->loadedLibs;
    }

    prevLib = NULL;
    while ((curLib != NULL)) {
        if (strcmp(algName, curLib->algDesc.name) == 0) {
            status = Engine_EOK;
            break;
        }
        prevLib = curLib;
        curLib = curLib->next;
    }

    if (curLib && engName && descElem->refCount) {
        /*
         *  Alg found in pre-opened list, but the engine has been opened.
         *  We can't remove it because another thread may be using it.
         */
        Log_print1(Diags_USER7, "[+7] Engine_removeAlg> Engine %s is "
                "open. Cannot remove alg that was added before engine was "
                "opened.", (IArg)descElem->desc.name);
        status = Engine_EINUSE;
    }

    if (status == Engine_EOK) {
        Assert_isTrue(curLib != NULL, (Assert_Id)NULL);

        /* Unlink the library from the list and free resources */
        if (prevLib) {
            prevLib->next = curLib->next;
        }
        else {
            /* Removing the first in the list */
            *loadedLibs = curLib->next;
        }
        (*numLoadedLibs)--;

        if (curLib->lib) {
            Loader_unloadLibrary(curLib->lib);
        }

        if (curLib->algDesc.name) {
            Memory_free(curLib->algDesc.name, strlen(curLib->algDesc.name) + 1,
                    NULL);
        }

        if (curLib->algDesc.types) {
            Memory_free(curLib->algDesc.types,
                    strlen(curLib->algDesc.types) + 1, NULL);
        }

        Algorithm_removeGroup(curLib->algDesc.groupId);

        Memory_free(curLib, sizeof(_Engine_AlgLib), NULL);
    }

    /* Release lock */
    GateThread_leave(engineLock, key);

    Log_print1(Diags_EXIT, "[+X] Engine_removeAlg> return (%d)", status);
    return (status);
}

/*
 *  ======== Engine_call ========
 */
Int Engine_call(Engine_Node node, Comm_Msg *msg)
{
    Int status;

    /* ensure that the node simply passes message to exec/call fxn */
    NODE_Msg nodeMsg = (NODE_Msg)*msg;
    nodeMsg->cmd.id = NODE_CCALL;

    /* send the message */
    Comm_setReplyToHandle(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    /* wait for the return message with the processed result */
    if (status == Comm_EOK) {
        status = Comm_get(node->stdOut, msg, Comm_FOREVER);
    }

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    return (status);
}

/*
 *  ======== Engine_callAsync ========
 */
Int Engine_callAsync(Engine_Node node, Comm_Msg *msg)
{
    Int status;

    /* ensure that the node simply passes message to exec/call fxn */
    NODE_Msg nodeMsg = (NODE_Msg)*msg;
    nodeMsg->cmd.id = NODE_CCALL;

    /* send the message */
    Comm_setReplyToHandle(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    /* return w/o waiting for the return message with the processed result */
    return (status);
}

/*
 *  ======== Engine_callWait ========
 */
Int Engine_callWait(Engine_Node node, Comm_Msg *msg, UInt timeout)
{
    Int status;

    status = Comm_get(node->stdOut, msg, timeout);

    if (status != Comm_ETIMEOUT && Engine_alwaysCollectDspTrace) {
        collectDspTrace( node->engine );
    }

    return (status);
}

/*
 *  ======== Engine_remove ========
 */
Engine_Error Engine_remove(String engineName)
{
    Engine_DescListElem *descElem = NULL;
    Engine_Desc         *desc = NULL;
    IArg                 key;
    Engine_Error         status = Engine_EOK;

    Log_print1(Diags_ENTRY, "[+E] Engine_remove(%s)", (IArg)engineName);

    key = GateThread_enter(engineLock);

    descElem = getDescListElem(engineName);

    if (descElem == NULL) {
        Log_print0(Diags_USER6, "[+6] Engine_remove> engineName not found!");

        GateThread_leave(engineLock, key);
        return (Engine_EEXIST);
    }

    if (descElem->isStatic) {
        Log_print0(Diags_USER2, "[+2] Engine_remove> Can't remove "
                "pre-configured engine");

        GateThread_leave(engineLock, key);
        return (Engine_EEXIST);
    }

    Log_print1(Diags_USER4, "[+4] Engine_remove> engine refCount[%d]\n",
            descElem->refCount);

    if (descElem->refCount != 0) {
        Log_print1(Diags_USER6, "[+6] Engine_remove> engine refCount[%d] != 0",
                descElem->refCount);

        GateThread_leave(engineLock, key);
        return (Engine_EINUSE);
    }

    /* Remove desc from the list and free */
    Queue_extract((Queue_Elem *)descElem);

    numEngines--;
    GateThread_leave(engineLock, key);

    /* Only free names from dynamically added engines */
    Assert_isTrue(descElem->isStatic == FALSE, (Assert_Id)NULL);
    desc = &descElem->desc;
    if (desc->name) {
        Memory_free(desc->name, strlen(desc->name) + 1, NULL);
    }
    if (desc->remoteName) {
        Memory_free(desc->remoteName, strlen(desc->remoteName) + 1, NULL);
    }
    if (desc->memMap) {
        Memory_free(desc->memMap, strlen(desc->memMap) + 1, NULL);
    }

    Memory_free(descElem, sizeof(Engine_DescListElem), NULL);

    Log_print1(Diags_EXIT, "[+X] Engine_remove> returning %d", status);
    return (status);
}

/*
 *  ======== Engine_getDesc ========
 */
Engine_Error Engine_getDesc(String name, Engine_Desc *desc)
{
    Engine_DescListElem *descElem;
    IArg                 key;
    Engine_Error         status = Engine_EOK;

    if ((name == NULL) || (desc == NULL)) {
        Log_print0(Diags_USER7, "[+7] Engine_getDesc> NULL input parameter");
        return (Engine_EINVAL);
    }

    key = GateThread_enter(engineLock);

    if ((descElem = getDescListElem(name)) == NULL) {
        Log_print1(Diags_USER7, "[+7] Engine_getDesc> Engine %s not found.",
                (IArg)name);

        GateThread_leave(engineLock, key);
        return (Engine_EEXIST);
    }

    *desc = descElem->desc;

    GateThread_leave(engineLock, key);

    return (status);
}

/*
 *  ======== Engine_setDesc ========
 */
Engine_Error Engine_setDesc(String name, Engine_Desc *desc)
{
    Engine_DescListElem *descElem;
    IArg                 key;
    Engine_Error         status = Engine_EOK;


    if ((name == NULL) || (desc == NULL)) {
        Log_print0(Diags_USER7, "[+7] Engine_setDesc> NULL input parameter");
        return (Engine_EINVAL);
    }

    key = GateThread_enter(engineLock);

    if ((descElem = getDescListElem(name)) == NULL) {
        Log_print1(Diags_USER7, "[+7] Engine_setDesc> Engine %s not found.",
                (IArg)name);

        GateThread_leave(engineLock, key);
        return (Engine_EEXIST);
    }

    if (descElem->refCount) {
        Log_print1(Diags_USER7, "[+7] Engine_setDesc> Engine %s is open. "
                "Cannot change the descriptor.", (IArg)name);
        GateThread_leave(engineLock, key);
        return (Engine_EINUSE);
    }

    /* Copy the fields that are allowed to be changed. */
    descElem->desc.memMap = desc->memMap;
    descElem->desc.useExtLoader = desc->useExtLoader;
    descElem->desc.heapId = desc->heapId;

    GateThread_leave(engineLock, key);

    return (status);
}

/*
 *  ======== Engine_getMemStat ========
 */
Engine_Error Engine_getMemStat(Server_Handle server, Int segNum,
    Engine_MemStat *stat)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    Log_print3(Diags_ENTRY, "[+E] Engine_getMemStat(0x%lx, %d, 0x%lx)",
            (IArg)engine, (IArg)segNum, (IArg)stat);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_getMemStat> internal error: rms message null");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETSEGSTAT;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getSegStatIn.segId = segNum;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status == RMS_ENOTFOUND) {
        /* segNum is out of range. */
        status = engine->lastError = Engine_ENOTFOUND;
    }
    else if (msg->cmdBuf.status != RMS_EOK) {
        status = engine->lastError = Engine_ERUNTIME;
    }
    else {
        /* Copy data into stat */
        strncpy(stat->name, (Char *)msg->cmdBuf.data.getSegStatOut.name,
                Engine_MAXSEGNAMELENGTH);
        stat->name[Engine_MAXSEGNAMELENGTH] = '\0';
        stat->base = msg->cmdBuf.data.getSegStatOut.base;
        stat->size = msg->cmdBuf.data.getSegStatOut.size;
        stat->used = msg->cmdBuf.data.getSegStatOut.used;
        stat->maxBlockLen = msg->cmdBuf.data.getSegStatOut.maxBlockLen;
    }

    return (status);
}

/*
 *  ======== Engine_getNumServerAlgs ========
 */
static Engine_Error Engine_getNumServerAlgs(Server_Handle server, Int *nAlgs)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine_getNumServerAlgs(0x%lx 0x%lx)",
            (IArg)engine, (IArg)nAlgs);

    if (engine->hasServer != TRUE) {
        Log_print0(Diags_USER6,
            "[+6] Engine_getNumServerAlgs> Engine does not have a server");
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6, "[+6] Engine_getNumServerAlgs> "
                "internal error: rms message null");
        return (Engine_ERUNTIME);
    }

    /* copy command */
    msg->cmdBuf.cmd = RMS_GETNUMALGS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        status = Engine_ERUNTIME;
    }
    else {
        *nAlgs = msg->cmdBuf.data.getNumAlgsOut.numAlgs;
    }

    Log_print1(Diags_USER2, "[+2] Engine_getNumServerAlgs> number of server "
            "algs = %d", *nAlgs);

    Log_print1(Diags_EXIT, "[+X] Engine_getNumServerAlgs> Returning %d",
            (IArg)status);
    return (status);
}

/*
 *  ======== Engine_getNumMemSegs ========
 */
Engine_Error Engine_getNumMemSegs(Server_Handle server, Int *numSegs)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine_getNumMemSegs(0x%lx 0x%lx)",
            (IArg)engine, (IArg)numSegs);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_getNumMemSegs> internal error: rms message null");
        return (Engine_ERUNTIME);
    }

    /* copy command */
    msg->cmdBuf.cmd = RMS_GETNUMSEGS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        status = Engine_ERUNTIME;
    }
    else {
        *numSegs = msg->cmdBuf.data.getNumSegsOut.numSegs;
    }

    return (status);
}

/*
 *  ======== Engine_close ========
 */
Void Engine_close(Engine_Handle engine)
{
    _Engine_AlgLib *curLib;
    IArg            key;
    IArg            keyServerLock;

    Log_print1(Diags_ENTRY, "[+E] Engine_close(0x%lx)", (IArg)engine);

    if (engine != NULL) {

        if (Engine_alwaysCollectDspTrace) {
            collectDspTrace(engine);
        }

        keyServerLock = GateThread_enter(serverLock);

        if (engine->server != NULL) {
            rserverDetach(engine);
        }

        /* atomically remove engine from any list it may be on */
        Queue_extract(&engine->link);

        if (engine->rmsMsg != NULL) {
            Comm_free(engine->rmsMsg);
        }

        if (engine->fromRMS != NULL) {
            Comm_delete(engine->fromRMS);
        }

        if (engine->toRMS != Comm_INVALIDMSGQ) {
            Comm_release(engine->toRMS);
        }

        if (engine->server != NULL) {
            rserverClose(engine->server);
        }

        GateThread_leave(serverLock, keyServerLock);


        /* Clean up any dynamically loaded algs */
        while ((curLib = engine->loadedLibs) != NULL) {
            Engine_removeAlg(NULL, engine, curLib->algDesc.name);
        }

        if (engine->remoteAlgTab != NULL) {
            freeServerTab(engine);
        }

        /* Decrement count of number opened for this Engine descriptor */
        key = GateThread_enter(engineLock);
        engine->descElem->refCount--;
        GateThread_leave(engineLock, key);

        /* free Engine object */
        Memory_free(engine, sizeof(Engine_Obj), NULL);
    }
}

/*
 *  ======== Engine_createNode ========
 */
Engine_Node Engine_createNode(Engine_Handle engine, String impId,
    size_t msgSize, IALG_Params *nodeAttrs, Engine_AlgCreateAttrs *attrs)
{
    Int nodeAttrsSize;

    Log_print5(Diags_ENTRY,
            "[+E] Engine_createNode(0x%lx, '%s', %d, 0x%lx, 0x%lx)",
            (IArg)engine, (IArg)impId, (IArg)msgSize, (IArg)nodeAttrs,
            (IArg)attrs);

    nodeAttrsSize = nodeAttrs ? nodeAttrs->size : 0;

    return (Engine_createNode2(engine, impId, msgSize, nodeAttrs,
                    nodeAttrsSize, attrs));
}

/*
 *  ======== Engine_createNode2 ========
 */
Engine_Node Engine_createNode2(Engine_Handle engine, String impId,
    size_t msgSize, IALG_Params *nodeAttrs, Int nodeAttrsSize,
    Engine_AlgCreateAttrs *attrs)
{
    RMS_RmsMsg *msg;
    Engine_Node node = NULL;

    Log_print6(Diags_ENTRY,
            "[+E] Engine_createNode(0x%lx, '%s', %d, 0x%lx, 0x%lx, 0x%lx)",
            (IArg)engine, (IArg)impId, (IArg)msgSize, (IArg)nodeAttrs,
            (IArg)nodeAttrsSize, (IArg)attrs);

    if (attrs == NULL) {
        attrs = &Engine_ALGCREATEATTRS;
    }

    if (nodeAttrsSize > (sizeof(RMS_Word) * RMS_MAXARGSLENGTH)) {
        Log_print2(Diags_USER6,
                "[+6] Engine_createNode> rms message size [%d] insufficient"
                " for nodeAttrsSize [%d]",
                (IArg)(sizeof(RMS_Word) * RMS_MAXARGSLENGTH),
                (IArg)nodeAttrsSize);

        engine->lastError = Engine_EINVAL;
        goto createNodeEnd;
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_createNode> internal error: rms message null");

        engine->lastError = Engine_ERUNTIME;
        goto createNodeEnd;
    }

    if ((node = allocNode(engine, impId)) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_createNode> Node allocation failed.");

        /* engine->lastError is set in allocNode, don't override it */
        goto createNodeEnd;
    }

    node->msgSize = msgSize;

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_CREATENODE;
    msg->cmdBuf.status = RMS_EFAIL;
    name2Uuid(engine, impId, &msg->cmdBuf.data.createNodeIn.uuid);
    msg->cmdBuf.data.createNodeIn.rpcProtocolVersion =
        getRpcProtocolVersion(engine, msg->cmdBuf.data.createNodeIn.uuid);
    msg->cmdBuf.data.createNodeIn.gppQueue = Comm_getId(node->stdOut);
    msg->cmdBuf.data.createNodeIn.nodePriority = attrs->priority;
    msg->cmdBuf.data.createNodeIn.useExtHeap = attrs->useExtHeap;

    if (nodeAttrs == NULL) {
        msg->cmdBuf.data.createNodeIn.argLength = 0;
    }
    else {
        assert(nodeAttrsSize <= (sizeof (RMS_Word) * RMS_MAXARGSLENGTH));
        msg->cmdBuf.data.createNodeIn.argLength = nodeAttrsSize;
        memcpy(msg->cmdBuf.data.createNodeIn.argBuffer, nodeAttrs,
                nodeAttrsSize);
    }

    /* send create message to RMS */
    Comm_setReplyToHandle((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        assert(status == Comm_EOK);
        engine->rmsMsg = (Comm_Msg)msg;
    }
    else {
        freeNode(node);
        node = NULL;
        Log_print0(Diags_USER6,
                "[+6] Engine_createNode> FAILED to send creation msg to DSP.");

        engine->lastError = Engine_ENOCOMM;
        goto createNodeEnd;
    }

    /* check that remote create succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        freeNode(node);
        node = NULL;
        Log_print1(Diags_USER6,
                "[+6] Engine_createNode> Remote node creation FAILED (0x%x).",
                (IArg)(msg->cmdBuf.status));
        engine->lastError = Engine_ECODECCREATE;

        goto createNodeEnd;
    }

    /* get the remote node and visa handles, and remote message queue */
    node->rmsNode = msg->cmdBuf.data.createNodeOut.node;
    node->remoteVisa = msg->cmdBuf.data.createNodeOut.remoteVisa;

    /* we really should do a locate here!!! */
    node->stdIn = msg->cmdBuf.data.createNodeOut.nodeQueue;

    /* put start message to engine's RMS */
    msg->cmdBuf.cmd = RMS_STARTNODE;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.startNodeIn.node = node->rmsNode;
    Comm_setReplyToHandle((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        assert(status == Comm_EOK);
        engine->rmsMsg = (Comm_Msg)msg;
    }

    /* check that remote start succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        freeNode(node);
        node = NULL;
        Log_print1(Diags_USER6,
                "[+6] Engine_createNode> Remote start FAILED (0x%x).",
                (IArg)(msg->cmdBuf.status));

        engine->lastError = Engine_ECODECSTART;
        goto createNodeEnd;
    }

    Log_print5(Diags_USER4, "[+4] Engine_createNode> created node"
            "(stdIn=0x%x, stdOut=0x%x, algName='%s', rmsNode=0x%x, "
            "algHandle=0x%x)",
            (IArg)(node->stdIn), (IArg)(node->stdOut),
            (IArg)(node->impId), (IArg)(node->rmsNode),
            (IArg)(node->remoteVisa));
    Log_print1(Diags_USER4, "[+4]   Comm_getId(node->stdOut)=0x%x",
            (IArg)(Comm_getId(node->stdOut)));

createNodeEnd:

    if (Engine_alwaysCollectDspTrace) {
        collectDspTrace( engine );
    }

    Log_print1(Diags_USER2, "[+2] Engine_createNode> Returning 0x%x",
            (IArg)node);

    return (node);
}

/*
 *  ======== Engine_ctrlNode ========
 */
Int Engine_ctrlNode(Engine_Node node, Comm_Msg *msg, Engine_Ctrl code)
{
    Int status;
    NODE_Msg nodeMsg = (NODE_Msg)*msg;

    if (code != Engine_CEXIT) {
        return (Engine_EINVAL);
    }

    nodeMsg->cmd.id = NODE_CEXIT;

    /* send the message */
    Comm_setReplyToHandle(*msg, node->stdOut);
    status = Comm_put(node->stdIn, *msg);

    /* wait for the return message with the processed result */
    if (status == Comm_EOK) {
        status = Comm_get(node->stdOut, msg, Comm_FOREVER);
    }

    return (status);
}
/*
 *  ======== Engine_deleteNode ========
 */
Void Engine_deleteNode(Engine_Node node)
{
    Engine_Handle engine = node->engine;
    RMS_RmsMsg *msg = (RMS_RmsMsg *)engine->rmsMsg;

    Log_print1(Diags_ENTRY, "[+E] Engine_deleteNode(0x%lx)", (IArg)node);

    /* init a node delete message */
    msg->cmdBuf.cmd = RMS_DELETENODE;
    msg->cmdBuf.data.deleteNodeIn.node = node->rmsNode;

    /* put delete node message to engine's RMS */
    Comm_setReplyToHandle((Comm_Msg)msg, engine->fromRMS);
    if (Comm_put(engine->toRMS, (Comm_Msg)msg) == Comm_EOK) {
        Int status;
        status = Comm_get(engine->fromRMS, (Comm_Msg *)&msg, Comm_FOREVER);
        if (status == Comm_EOK) {
            /* check stack size to see if we are close to overrun */
            Bits16 classMask = Diags_USER5;
            UInt stacksize = msg->cmdBuf.data.deleteNodeOut.stackSize;
            UInt stackused = msg->cmdBuf.data.deleteNodeOut.stackUsed;
            Int headroom = 100;

            if (stacksize != 0) {
                headroom = (stacksize > stackused)
                    ? ((stacksize - stackused) * 100) / stacksize : 0;
            }

            if (headroom < 10) {
                classMask |= Diags_USER6; /* less than 10%, generate warning */
            }
            Log_print6(classMask, "Engine_deleteNode(0x%x): "
                    "algName = %s, algHandle = 0x%x, stack size = %d, "
                    "stack used = %d(%d%%)",
                    (IArg)node, (IArg)(node->impId), (IArg)(node->remoteVisa),
                    (IArg)stacksize, (IArg)stackused, (IArg)(100 - headroom));

            engine->rmsMsg = (Comm_Msg)msg;
        }
    }

    freeNode(node);
}

/*
 *  ======== Engine_getAlgInfo ========
 */
Engine_Error Engine_getAlgInfo(String name, Engine_AlgInfo *algInfo, Int index)
{
    Engine_AlgDesc      *alg;
    IArg                 key;
    Engine_Error         status = Engine_EOK;

    Log_print3(Diags_ENTRY, "[+E] Engine_getAlgInfo('%s', 0x%lx, 0x%x)",
            (IArg)name, (IArg)algInfo, (IArg)index);

    /* Check params */
    if ((name == NULL) || (algInfo == NULL) || (index < 0)) {
        return (Engine_EINVAL);
    }

    /* Make sure size matches with this library version's size */
    if (algInfo->algInfoSize != sizeof(Engine_AlgInfo)) {
        Log_print2(Diags_USER6,
                "[+6] Engine_getAlgInfo(): Input Engine_AlgInfo struct size "
                "[%d] does not match library Engine_AlgInfo struct size [%d]",
                (IArg)(algInfo->algInfoSize), (IArg)(sizeof(Engine_AlgInfo)));
        return (Engine_EINVAL);
    }

    /* Acquire lock to prevent algs from being added or removed */
    key = GateThread_enter(engineLock);

    alg = getAlgDescNum(name, NULL, index);

    if (alg == NULL) {
        Log_print2(Diags_USER6,
                "[+6] Engine_getAlgInfo(): Engine [%s], alg number [%d]"
                "not found.", (IArg)name, (IArg)index);
        status = Engine_EINVAL;
    }
    else {
        algInfo->name = alg->name;
        algInfo->typeTab = alg->typeTab;
        algInfo->isLocal = alg->isLocal;
    }

    GateThread_leave(engineLock, key);

    return (status);
}

/*
 *  ======== Engine_getAlgInfo2 ========
 */
Engine_Error Engine_getAlgInfo2(String name, Engine_Handle engine,
        Engine_AlgInfo2 *algInfo2, Int index)
{
    Engine_AlgDesc      *alg;
    IArg                 key;
    Engine_Error         status = Engine_EOK;

    Log_print4(Diags_ENTRY, "[+E] Engine_getAlgInfo2('%s' 0x%lx 0x%lx 0x%x)",
            (IArg)name, (IArg)engine, (IArg)algInfo2, (IArg)index);

    /* Check params */
    if ((algInfo2 == NULL) || (index < 0)) {
        Log_print2(Diags_USER7, "[+7] Engine_getAlgInfo2> Ensure that "
                "paramaters algInfo2 [0x%lx] is non-NULL and index [%d] >= 0.",
                (IArg)algInfo2, (IArg)index);
        return (Engine_EINVAL);
    }
    if ((name && engine) || (!name && !engine)) {
        Log_print2(Diags_USER7, "[+7] Engine_getAlgInfo2> engine name = '%s', "
                "engine handle = 0x%lx. Bad input args: One and only one of "
                "these must be non-NULL!", (IArg)name, (IArg)engine);
        return (Engine_EINVAL);
    }

    /* Make sure size matches with this library version's size */
    if (algInfo2->algInfoSize != sizeof(Engine_AlgInfo2)) {
        Log_print2(Diags_USER6,
            "[+6] Engine_getAlgInfo2(): Input Engine_AlgInfo2 struct size [%d]"
            "does not match library Engine_AlgInfo2 struct size [%d]",
            (IArg)algInfo2->algInfoSize, (IArg)sizeof(Engine_AlgInfo2));
        return (Engine_EINVAL);
    }

    /* Acquire lock to prevent algs from being added or removed */
    key = GateThread_enter(engineLock);

    alg = getAlgDescNum(name, engine, index);

    if (alg == NULL) {
        Log_print2(Diags_USER6,
                "[+6] Engine_getAlgInfo2(): Engine [%s], alg number [%d]"
                "not found.", (IArg)name, (IArg)index);
        status = Engine_EINVAL;
    }
    else {
        algInfo2->name = alg->name;
        algInfo2->isLocal = alg->isLocal;

        /*
         *  For auto-generated alg tables and algs obtained from the server,
         *  alg->types will not be NULL. If alg table was not generated with
         *  XDC tools (eg, for run-time config), this could be NULL. In that
         *  case, just use typeTab[0], since that will contain the complete
         *  inheritence hierarchy (assuming the it was configured correctly by
         *  the app).
         */
        algInfo2->types = alg->types;
    }

    GateThread_leave(engineLock, key);

    return (status);
}


/*
 *  ======== Engine_getAlgMemRecs ========
 */
Engine_Error Engine_getAlgMemRecs(Engine_Node node, IALG_MemRec *memTab,
        Int size, Int *numRecs)
{
    Engine_Handle    engine;
    RMS_RmsMsg      *msg;
    Int              nRecs;
    Int              i;
    IALG_MemRec     *memRecs;
    Engine_Error     status = Engine_EOK;

    Log_print4(Diags_ENTRY,
            "[+E] Engine_getAlgMemRecs(0x%lx, 0x%x, %d, 0x%lx)",
            (IArg)node, (IArg)memTab, (IArg)size, (IArg)numRecs);

    engine = node->engine;
    msg = (RMS_RmsMsg *)engine->rmsMsg;

    /* Compute maximum number of IALG_MemRecs that can be copied. */
    nRecs = (size > RMS_MAXMEMRECS) ? RMS_MAXMEMRECS : size;
    if (size > nRecs) {
        Log_print3(Diags_USER4,
                "[+4] Engine_getAlgMemRecs: memTab array size (%d) is larger"
                " then the number of records that can be copied (%d) for"
                " node (0x%x)", (IArg)size, (IArg)RMS_MAXMEMRECS, (IArg)node);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETMEMRECS;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getMemRecsIn.node = node->rmsNode;
    msg->cmdBuf.data.getMemRecsIn.numRecs = nRecs;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        // TODO: Determine what type of errors will be returned.
        if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }
    else {
        *numRecs = msg->cmdBuf.data.getMemRecsOut.numRecs;
        memRecs = (IALG_MemRec *)(msg->cmdBuf.data.getMemRecsOut.memRecs);

        for (i = 0; i < nRecs; i++) {
            memTab[i] = memRecs[i];
        }
    }

    Log_print1(Diags_EXIT, "[+X] Engine_getAlgMemRecs> Returning %d",
            (IArg)status);

    return (status);
}

/*
 *  ======== Engine_getAlgNumRecs ========
 */
Engine_Error Engine_getAlgNumRecs(Engine_Node node, Int *numRecs)
{
    Engine_Handle    engine;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine_getAlgNumRecs(0x%lx, 0x%x)",
            (IArg)node, (IArg)numRecs);

    engine = node->engine;
    msg = (RMS_RmsMsg *)engine->rmsMsg;

    /* Set up command */
    msg->cmdBuf.cmd = RMS_GETNUMMEMRECS;
    msg->cmdBuf.status = RMS_EFAIL;
    msg->cmdBuf.data.getNumRecsIn.node = node->rmsNode;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        // TODO: Determine what type of errors will be returned.
        if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }
    else {
        *numRecs = msg->cmdBuf.data.getNumRecsOut.numRecs;
    }

    Log_print1(Diags_EXIT, "[+X] Engine_getAlgNumRecs> Returning %d",
            (IArg)status);

    return (status);
}

/*
 *  ======== Engine_getNumAlgs ========
 */
Engine_Error Engine_getNumAlgs(String name, Int *numAlgs)
{
    Engine_DescListElem *descElem;

    Log_print2(Diags_ENTRY, "[+E] Engine_getNumAlgs('%s', 0x%x)",
            (IArg)name, (IArg)numAlgs);

    *numAlgs = 0;

    descElem = getDescListElem(name);
    if (descElem == NULL) {
        return (Engine_EEXIST);
    }

    /* Engine found - get number of algs */
    *numAlgs = descElem->desc.numAlgs + descElem->numLoadedLibs;

    Log_print2(Diags_EXIT, "[+X] Engine_getNumAlgs> Returning %d (0x%x algs)",
            (IArg)Engine_EOK, (IArg)*numAlgs);
    return (Engine_EOK);
}

/*
 *  ======== Engine_getNumAlgs2 ========
 */
Engine_Error Engine_getNumAlgs2(String name, Engine_Handle engine, Int *nAlgs)
{
    Engine_Desc      *desc;

    Log_print3(Diags_ENTRY, "[+E] Engine_getNumAlgs2('%s', 0x%lx, 0x%lx)",
        (IArg)name, (IArg)engine, (IArg)nAlgs);

    *nAlgs = 0;

    if (engine == NULL) {
        return (Engine_getNumAlgs(name, nAlgs));
    }
    else {
        desc = engine->desc;

        *nAlgs = desc->numAlgs + engine->numRemoteAlgs +
            engine->descElem->numLoadedLibs + engine->numLoadedLibs;
    }

    return (Engine_EOK);
}

/*
 *  ======== Engine_getConstName ========
 */
String Engine_getConstName(Engine_Handle engine, String name, String type)
{
    Engine_AlgDesc *alg;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    if ((alg = getAlgDesc(NULL, engine, name)) != NULL) {
        if (isa(alg, type)) {
            return (alg->name);
        }
    }

    Log_print2(Diags_USER6,
            "[+6] Engine_getConstName> Unable to locate alg \"%s\" (type \"%"
            "s\").", (IArg)name, (IArg)type);
    return (NULL);
}

/*
 *  ======== Engine_getFxns ========
 */
IALG_Fxns *Engine_getFxns(Engine_Handle engine, String name, String type,
        Bool *isLocal, Ptr *idmaFxns, Ptr *iresFxns, Int *groupId,
        Engine_CachedMemType *memType)
{
    Engine_AlgDesc *alg;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    alg = getAlgDesc(NULL, engine, name);

    if (alg && isa(alg, type)) {
        *isLocal = alg->isLocal;
        *idmaFxns = alg->idmaFxns;
        *iresFxns = alg->iresFxns;
        *groupId = alg->groupId;
        *memType = alg->memType;
        return (alg->fxns);
    }

    Log_print1(Diags_USER6,
            "[+6] Engine_getFxns> Unable to locate alg \"%s\".", (IArg)name);

    return (NULL);
}

/*
 *  ======== Engine_getLocalEngine ========
 */
Engine_Handle Engine_getLocalEngine(Void)
{
    if (localEngine == NULL) {
        localEngine = Engine_open(Engine_config.localEngine, NULL, NULL);
    }

    return (localEngine);
}

/*
 *  ======== Engine_getMemId ========
 */
Int Engine_getMemId(Engine_Handle engine)
{
    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    return (engine->rmsPoolId);
}

/*
 *  ======== Engine_getEngine ========
 */
Engine_Handle Engine_getEngine(Engine_Node node)
{
    return (node->engine);
}

/*
 *  ======== Engine_getCpuLoad ========
 */
Int Engine_getCpuLoad(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    Log_print1(Diags_ENTRY, "[+E] Engine_getCpuLoad(0x%lx)", (IArg)engine);

    /* This function is only valid for the Server CPU load */
    if (engine->hasServer != TRUE) {
        Log_print0(Diags_USER6,
                "[+6] Engine_getCpuLoad> Only valid if there is a server");
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    /* init a "get CPU status" message */
    msg->cmdBuf.cmd = RMS_GETCPUSTAT;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (-1);
    }

    return (msg->cmdBuf.data.getCpuStatOut.cpuLoad);
}

/*
 *  ======== Engine_getLastError ========
 */
Engine_Error Engine_getLastError(Engine_Handle engine)
{
    return (engine->lastError);
}

/*
 *  ======== Engine_getProcId ========
 */
String Engine_getProcId(Engine_Handle engine)
{
    Log_print1(Diags_ENTRY, "[+E] Engine_getProcId(0x%lx)", (IArg)engine);

    return (engine->procId);
}

/*
 *  ======== Engine_getServer ========
 */
Server_Handle Engine_getServer(Engine_Handle engine)
{
    Log_print1(Diags_ENTRY, "[+E] Engine_getServer(0x%lx)", (IArg)engine);

    if (engine->hasServer) {
        return ((Server_Handle)engine);
    }
    else {
        engine->lastError = Engine_ENOSERVER;
        return (NULL);
    }
}

/*
 *  ======== Engine_getCodecClassConfig ========
 */
Ptr Engine_getCodecClassConfig(Engine_Handle engine, String name, String type)
{
    Engine_AlgDesc *alg;
    Engine_AlgDesc *algTab;

    if (engine == NULL) {
        engine = Engine_getLocalEngine();
    }

    algTab = engine->desc->algTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(name, alg->name) == 0) {
                if (isa(alg, type)) {
                    return (alg->codecClassConfig);
                }
            }
        }
    }

    return (NULL);
}

/*
 *  ======== Engine_initFromServer ========
 */
Engine_Error Engine_initFromServer(Engine_Handle engine)
{
    RMS_RmsMsg      *msg;
    Int              index;
    Int              i;
    Int              len;
    Char            *algName;
    Char            *typeTab;
    Char            *stubsName;
    Engine_AlgDesc  *desc = NULL;
    Engine_AlgDesc  *alg = NULL;
    Int              numAlgs = 0;
    Int              numRemoteAlgs = 0;
    Engine_StubFxnsElem *stubs;
    Engine_Error     status = Engine_EOK;


    Log_print1(Diags_ENTRY, "[+E] Engine_initFromServer(0x%lx)", (IArg)engine);

    if (engine->hasServer != TRUE) {
        Log_print1(Diags_USER1, "[+1] Engine_initFromServer> Returning %d",
                (IArg)status);
        return (Engine_ENOSERVER);
    }

    /* Get the number of algs on the server */
    status = Engine_getNumServerAlgs((Server_Handle)engine, &numAlgs);

    if (status != Engine_EOK) {
        Log_print1(Diags_USER7, "[+7] Engine_initFromServer> Failed to "
                  "get number of server algs, returning %d", (IArg)status);
        return (status);
    }

    if (numAlgs <= 0) {
        /* Shouldn't happen, but just in case... */
        Log_print1(Diags_USER6, "[+6] Engine_initFromServer> Server has "
                  "no remote algs, returning %d", (IArg)status);
        return (status);
    }

    /* Count the number of remote algs that were statically configured. */
    alg = engine->desc->algTab;
    numRemoteAlgs = 0;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (alg->isLocal == FALSE) {
            numRemoteAlgs++;
        }
    }

    Log_print1(Diags_USER2, "[+2] Engine_initFromServer> Number of remote "
            "algs statically configured in engine: %d", (IArg)numRemoteAlgs);

    if (numAlgs == numRemoteAlgs) {
        /*
         *  ALl remote algs were statically configured. No need to get
         *  information from the server.
         */
        Log_print1(Diags_USER2, "[+2] Engine_initFromServer> Number of "
                "statically configured remote algs = number of server "
                "algs: %d", (IArg)numAlgs);

        Log_print1(Diags_USER1, "[+1] Engine_initFromServer> Returning %d",
                (IArg)status);
        return (status);
    }

    /*
     *  Server contains remote algs that were not statically configured
     *  into the engine. Allocate a table to hold server's alg info, and
     *  get the alg info from the server.
     */

    Log_print1(Diags_USER2, "[+2] Engine_initFromServer> Allocating "
            "descriptor array for [%d] server algs", (IArg)numAlgs);
    desc = (Engine_AlgDesc *)Memory_alloc(sizeof(Engine_AlgDesc) * numAlgs,
            NULL);
    if (desc == NULL) {
        Log_print0(Diags_USER7, "[+7] Engine_initFromServer> Failed "
                "to allocate memory for engine table");
        status = Engine_ENOMEM;
    }

    Log_print1(Diags_USER2, "[+2] Engine_initFromServer> Initializing "
            "descriptor array for [%d] server algs", (IArg)numAlgs);
    if (status == Engine_EOK) {
        for (i = 0; i < numAlgs; i++) {
            /*
             *  Initialize desc fields that will be alloc'd so we don't
             *  try to free invalid memory if something goes wrong.
             */
            desc[i].name = NULL;
            desc[i].typeTab = NULL;
        }
    }

    if (status == Engine_EOK) {
        if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
            Log_print0(Diags_USER6, "[+6] Engine_initFromServer> "
                    "internal error: rms message null");
            status = Engine_ERUNTIME;
        }
    }

    index = 0;
    while ((status == Engine_EOK) && (index < numAlgs)) {
        /* Get the info for alg 'index' */
        msg->cmdBuf.cmd = RMS_GETALG;
        msg->cmdBuf.status = RMS_EFAIL;
        msg->cmdBuf.data.getAlgIn.index = index;

        Log_print1(Diags_USER2, "[+2] Engine_initFromServer> "
                "Sending RMS_GETALG command for alg [%d]", (IArg)index);
        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check that remote cmd succeeded */
        if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            /* Index is out of range (shouldn't happen), we're done. */
            Log_print2(Diags_USER6, "[+6] Engine_initFromServer> WARNING "
                    "Cannot get info for alg [%d], numAlgs = %d",
                    (IArg)index, (IArg)numAlgs);
            break;
        }
        else if (msg->cmdBuf.status != RMS_EOK) {
            status = engine->lastError = Engine_ERUNTIME;
            Log_print2(Diags_USER7, "[+7] Engine_initFromServer> "
                    "failed to get information for alg [%d] from server. "
                    "status = 0x%x", (IArg)index, (IArg)(msg->cmdBuf.status));
        }
        else {
            /* Copy the codec name */
            algName = (Char *)msg->cmdBuf.data.getAlgOut.name;
            len = strlen(algName);
            desc[index].name = Memory_alloc(len + 1, NULL);
            if (desc[index].name == NULL) {
                Log_print1(Diags_USER7, "[+7] Engine_initFromServer> "
                        "Memory allocation for desc[%d].name failed!",
                        index);
                status = Engine_ENOMEM;
                break;
            }
            strcpy(desc[index].name, algName);
            desc[index].name[len] = '\0';

            /*
             *  Use a simplified typeTab, where strings are separated by ';'
             *  instead of having an array of strings.
             */
            desc[index].typeTab = NULL;

            typeTab = (Char *)msg->cmdBuf.data.getAlgOut.typeTab;
            len = strlen(typeTab);
            desc[index].types = Memory_alloc(len + 1, NULL);

            if (desc[index].types == NULL) {
                Log_print0(Diags_USER7, "[+7] Engine_initFromServer> "
                        "Memory allocation for types failed!");
                status = Engine_ENOMEM;
                break;
            }
            strcpy(desc[index].types, typeTab);
            desc[index].types[len] = '\0';

            /*
             *  Look up the stub functions in table. If they're not found,
             *  just leave them as NULL. In that case the alg cannot be
             *  used.
             */
            stubsName = (Char *)msg->cmdBuf.data.getAlgOut.stubFxns;
            desc[index].fxns = NULL;
            i = 0;

            stubs = (Engine_StubFxnsElem *)Queue_head(&stubFxnsList);
            while ((Queue_Elem *)stubs != &stubFxnsList) {
                if ((strcmp(stubsName, stubs->name)) == 0) {
                    /* Found match */
                    desc[index].fxns = stubs->stubFxns;
                    break;
                }
                stubs = Queue_next(stubs);
            }
            if (desc[index].fxns == NULL) {
                Log_print1(Diags_USER6, "[+6] Engine_initFromServer> "
                        "Warning: No stub functions were found for %s. "
                        "The algorithm that requires these stub functions "
                        "cannot be run remotely.", (IArg)stubsName);
            }

            desc[index].uuid = msg->cmdBuf.data.getAlgOut.uuid;

            /* Don't care about groupId since alg is remote */
            desc[index].groupId = -1;

            desc[index].rpcProtocolVersion =
                msg->cmdBuf.data.getAlgOut.rpcProtocolVersion;

            /* Fill in the rest */
            desc[index].idmaFxns = NULL;
            desc[index].isLocal = FALSE;
            desc[index].iresFxns = NULL;
            desc[index].memType = Engine_USECACHEDMEM_DEFAULT;
            desc[index].codecClassConfig = NULL;

            /*
             *  Print a warning if another alg of the same name already exists
             *  in the static engine table.
             */
            alg = engine->desc->algTab;
            algName = desc[index].name;
            for (; (alg != NULL) && (alg->name != NULL); alg++) {
                if ((strcmp(algName, alg->name) == 0) && alg->isLocal) {
                    Log_print1(Diags_USER6, "[+6] Engine_initFromServer> "
                            "WARNING: Local algorithm named \"%s\" in "
                            "static engine table matches a server alg name. "
                            "Behavior as to which algorithm will be created "
                            "when using this name is undefined.",
                            (IArg)(alg->name));
                }
            }

            index++;
        }
    }

    /*
     *  Assign these even if an error occurred so we can call freeServerTab()
     *  to clean things up.
     */
    engine->numRemoteAlgs = (desc == NULL) ? 0 : numAlgs;
    engine->remoteAlgTab = desc;

    if (status != Engine_EOK) {
        /* Free anything allocated so far */
        freeServerTab(engine);
    }

    Log_print1(Diags_USER1, "[+1] Engine_initFromServer engine->server = "
            "0x%x\n", (IArg)(engine->server));

    Log_print1(Diags_EXIT, "[+X] Engine_initFromServer> Returning %d",
            (IArg)status);

    return (status);
}

/*
 *  ======== Engine_redefineHeap ========
 */
Engine_Error Engine_redefineHeap(Server_Handle server, String name,
        Uint32 base, Uint32 size)
{
    Engine_Handle    engine = (Engine_Handle)server;
    String           heapName;
    RMS_RmsMsg      *msg;
    Engine_Error     status = Engine_EOK;

    Log_print4(Diags_ENTRY, "[+E] Engine_redefineHeap(0x%x %s 0x%x 0x%x)",
            (IArg)engine, (IArg)name, (IArg)base, (IArg)size);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_redefineHeap> internal error: rms message null");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_REDEFINEHEAP;
    msg->cmdBuf.status = RMS_EFAIL;

    heapName = (Char *)(msg->cmdBuf.data.redefineHeapIn.name);
    strncpy(heapName, name, RMS_MAXSEGNAMELENGTH);
    heapName[RMS_MAXSEGNAMELENGTH] = '\0';

    msg->cmdBuf.data.redefineHeapIn.base = base;
    msg->cmdBuf.data.redefineHeapIn.size = size;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        if (msg->cmdBuf.status == RMS_EFREE) {
            /* The heap is still in use on the DSP */
            status = engine->lastError = Engine_EINUSE;
        }
        else if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }

    return (status);
}

/*
 *  ======== Engine_releaseTraceToken ========
 */
Bool Engine_releaseTraceToken(Server_Handle server)
{
    Engine_Handle engine = (Engine_Handle)server;
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (FALSE);
    }

    /* init a "release trace token" message */
    msg->cmdBuf.cmd = RMS_RELTRACETOKEN;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        return (FALSE);
    }
    else {
        return (TRUE);
    }
}

/*
 *  ======== Engine_requestTraceToken ========
 */
Engine_Error Engine_requestTraceToken(Server_Handle server)
{
    Engine_Handle engine = (Engine_Handle)server;
    Engine_Error status = Engine_ERUNTIME;
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) != NULL) {

        /* init a "request trace token" message */
        msg->cmdBuf.cmd = RMS_REQTRACETOKEN;
        msg->cmdBuf.status = RMS_EFAIL;

        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check if remote cmd succeeded */
        if (msg->cmdBuf.status == RMS_EOK) {
            status = Engine_EOK;
        }
        else if (msg->cmdBuf.status == RMS_ERESOURCE) {
            status = Engine_EINUSE;
        }
    }

    return(status);
}

/*
 *  ======== Engine_restoreHeap ========
 */
Engine_Error Engine_restoreHeap(Server_Handle server, String name)
{
    Engine_Handle    engine = (Engine_Handle)server;
    RMS_RmsMsg      *msg;
    String           heapName;
    Engine_Error     status = Engine_EOK;

    Log_print1(Diags_ENTRY, "[+E] Engine_restoreHeap(0x%x)", (IArg)engine);

    if (engine->hasServer != TRUE) {
        return (Engine_ENOSERVER);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        Log_print0(Diags_USER6,
                "[+6] Engine_restoreHeap> internal error: rms message null");
        return (Engine_ERUNTIME);
    }

    /* Set up command */
    msg->cmdBuf.cmd = RMS_RESTOREHEAP;
    msg->cmdBuf.status = RMS_EFAIL;

    heapName = (Char *)(msg->cmdBuf.data.restoreHeapIn.name);
    strncpy(heapName, name, RMS_MAXSEGNAMELENGTH);
    heapName[RMS_MAXSEGNAMELENGTH] = '\0';

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        if (msg->cmdBuf.status == RMS_EFREE) {
            /* The heap is still in use on the DSP */
            status = engine->lastError = Engine_EINUSE;
        }
        else if (msg->cmdBuf.status == RMS_EINVAL) {
            status = engine->lastError = Engine_EINVAL;
        }
        else if (msg->cmdBuf.status == RMS_ENOTFOUND) {
            status = engine->lastError = Engine_ENOTFOUND;
        }
        else {
            status = engine->lastError = Engine_ERUNTIME;
        }
    }

    return (status);
}

/*
 *  ======== Engine_fwriteTrace ========
 */
Int Engine_fwriteTrace(Engine_Handle engine, String prefix, FILE *out)
{
    RMS_RmsMsg *msg;
    Int count = 0;
    Int readCount = 0;
    Bool newLine = TRUE;

    /* this should really be the ENTER class but it obscures the output */
    Log_print3(Diags_USER3, "[+3] Engine_fwriteTrace(0x%lx, '%s', 0x%lx)",
            (IArg)engine, (IArg)prefix, (IArg)out);

    if (engine->hasServer != TRUE) {
        Log_print0(Diags_USER3,
                "[+3] Engine_fwriteTrace> Engine has no server");
        return (0);
    }

    if (!Server_holdingTraceToken) {
        Log_print0(Diags_USER3, "[+3] Engine_fwriteTrace> Engine in use");
        engine->lastError = Engine_EINUSE;
        return (-1);
    }

    do {
        UInt32 timeKey;

        if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
            engine->lastError = Engine_ERUNTIME;
            return (-1);
        }


        timeKey = Timestamp_get32();

        /* init a "get trace" message */
        msg->cmdBuf.cmd = RMS_GETTRACE;
        msg->cmdBuf.status = RMS_EFAIL;
        msg->cmdBuf.data.getTraceIn.curTime = timeKey;
        msg->cmdBuf.data.getTraceOut.size = 0;
        msg->cmdBuf.data.getTraceOut.lost = 0;

        Log_print1(Diags_USER3,
                "[+3] Engine_fwriteTrace(): requesting DSP trace @0x%x ...",
                (IArg)timeKey);

        /* send it to the DSP and wait for results ... */
        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check that remote cmd succeeded */
        if (msg->cmdBuf.status != RMS_EOK) {
            engine->lastError = Engine_ERUNTIME;
            return (-1);
        }

        Log_print5(Diags_USER3, "[+3] Engine_fwriteTrace> "
                "got %d chars @0x%x (%d still avail, max: %d, lost: %d)",
                (IArg)(msg->cmdBuf.data.getTraceOut.size), (IArg)timeKey,
                (IArg)(msg->cmdBuf.data.getTraceOut.avail),
                (IArg)(msg->cmdBuf.data.getTraceOut.max),
                (IArg)(msg->cmdBuf.data.getTraceOut.lost));

        readCount += msg->cmdBuf.data.getTraceOut.size;

        if (msg->cmdBuf.data.getTraceOut.lost > 0) {
            fprintf(out, " [ARM] WARNING: lost %d characters of DSP server trace "
                    "due to buffer wrapping (got %d chars, %d left, max=%d; "
                    "collect trace more often, or add "
                    "Server.traceBufferSize = <largerSizeInBytes> "
                    "to DSP server's .cfg file). %s",
                    msg->cmdBuf.data.getTraceOut.lost,
                    msg->cmdBuf.data.getTraceOut.size,
                    msg->cmdBuf.data.getTraceOut.avail,
                    msg->cmdBuf.data.getTraceOut.max, prefix );
            newLine = FALSE;
        }

        /* write to file stream */
        count += copyToFile((Char *)msg->cmdBuf.data.getTraceOut.buf,
            msg->cmdBuf.data.getTraceOut.size, prefix, &newLine, out);

    } while ((msg->cmdBuf.data.getTraceOut.avail > 0)
        && (readCount < msg->cmdBuf.data.getTraceOut.max));

    /* return number of characters actually copied */
    Log_print1(Diags_EXIT, "[+X] Engine_fwriteTrace> returning count [%d]",
            (IArg)count);
    return (count);
}

/*
 *  ======== Engine_getName ========
 */
String Engine_getName(Engine_Handle engine)
{
    return (engine->desc->name);
}

/*
 *  ======== Engine_getRemoteVisa ========
 */
UInt32 Engine_getRemoteVisa(Engine_Node node)
{
    Assert_isTrue(node != NULL, (Assert_Id)NULL);

    return (node->remoteVisa);
}

/*
 *  ======== Engine_getNodeQueues ========
 */
Void Engine_getNodeQueues(Engine_Node node,
    Comm_Id *stdIn, Comm_Handle *stdOut)
{
    if (node != NULL) {
        *stdIn  = node->stdIn;
        *stdOut = node->stdOut;
    }
    else {
        *stdIn  = Comm_INVALIDMSGQ;
        *stdOut = Comm_INVALIDHANDLE;
    }
}

/*
 *  ======== Engine_getUsedMem ========
 */
UInt32 Engine_getUsedMem(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    Log_print1(Diags_ENTRY, "[+E] Engine_getUsedMem(0x%lx)", (IArg)engine);

    if (engine->hasServer != TRUE) {
        engine->lastError = Engine_ENOTAVAIL;
        return (0);
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (0);
    }

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_GETMEMSTAT;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (0);
    }

    return (msg->cmdBuf.data.getMemStatOut.used);
}

/*
 *  ======== Engine_hasServer ========
 */
Bool Engine_hasServer(Engine_Handle engine)
{
    if (engine) {
        return (engine->hasServer);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== Engine_init ========
 */
Void Engine_init(Void)
{
    Engine_Desc      *desc = NULL;
    Engine_AlgDesc   *alg = NULL;
    Engine_AlgDesc   *algTab = NULL;
    Int               numAlgs;
    GateThread_Params gateParams;
    Registry_Result   result;
    Int32             numProcs;
    int               i;
    Engine_Error      status = Engine_EOK;

    /*
     *  No need to reference count for Registry_addModule(), since there
     *  is no way to remove the module.
     */
    if (regInit == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_ce_Engine_desc, Engine_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the CE default */
            CESettings_init();
            CESettings_setDiags(Engine_MODNAME);
        }
        regInit = 1;
    }

    if (curInit != TRUE) {
        curInit = TRUE;

        if (Global_getenv("CE_DEBUG") != NULL) {
            Log_print1(Diags_USER6, "[+6] Engine_init> CE debugging on "
                    "(CE_DEBUG=%s; allowed CE_DEBUG levels: "
                    "1=min, 2=good, 3=max)",
                    (IArg)(Global_getenv("CE_DEBUG")));
        }

        Queue_new(&engineList);
        Queue_new(&stubFxnsList);
        Queue_new(&engineDescList);
        Global_atexit((Fxn)cleanup);

        GateThread_Params_init(&gateParams);
        serverLock = GateThread_create(&gateParams, NULL);
        assert(serverLock != NULL);

        GateThread_Params_init(&gateParams);
        traceLock = GateThread_create(&gateParams, NULL);
        assert(traceLock != NULL);

        GateThread_Params_init(&gateParams);
        engineLock = GateThread_create(&gateParams, NULL);
        assert(engineLock != NULL);

        /*
         *  For each engine, go through the alg table, and add the group ID
         *  of each local alg. This enables run-time config apps to not
         *  have to set up an array of group IDs that are used.
         *
         *  Also make sure the number of numAlgs in the engine desc matches the
         *  number of algs in the engine desc algTab. Correct numAlgs, if
         *  necessary (this mismatch is possible for run-time configuration,
         *  where the engine table is set up with incorrect numAlgs).
         */
        for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
            algTab = desc->algTab;

            if (algTab != NULL) {
                numAlgs = 0;
                for (alg = algTab; alg->name != NULL; alg++) {
                    numAlgs++;
                    if (alg->isLocal) {
                        Algorithm_addGroup(alg->groupId);
                    }
                }
                if (desc->numAlgs != numAlgs) {
                    Log_print3(Diags_USER5, "Engine_init> Descriptor for "
                            "engine %s configured with %d algs. Setting to "
                            "actual number of algs: %d.", (IArg)(desc->name),
                            (IArg)(desc->numAlgs), (IArg)(numAlgs));
                    desc->numAlgs = numAlgs;
                }
            }

            /*
             *  Add to the Engine descriptor list. TODO: We could statically
             *  create a table at config time and just initialize the pointers
             *  in Engine_init().
             */
            status = addEngineToList(desc, TRUE);

            if (status != Engine_EOK) {
                Log_print2(Diags_USER7,
                        "Engine_init> Failed to add engine %s to list: %d",
                        (IArg)desc->name, (IArg)status);
            }
        }

        /* Allocate and initialize the server table - one elem per core */
        numProcs = Processor_getNumProcs();
        serverTab = Memory_alloc(sizeof(*serverTab) * numProcs, NULL);

        for (i = 0; i < numProcs; i++) {
            serverTab[i].dspProc = NULL;
            serverTab[i].imageName = NULL;
            serverTab[i].refCount = 0;
        }
    }
}

/*
 *  ======== Engine_initAlgDesc ========
 */
Void Engine_initAlgDesc(Engine_AlgDesc *pAlgDesc)
{
    pAlgDesc->name = NULL;
    pAlgDesc->uuid.data = 0;
    pAlgDesc->fxns = NULL;
    pAlgDesc->idmaFxns = NULL;
    pAlgDesc->typeTab = NULL;
    pAlgDesc->isLocal = TRUE;
    pAlgDesc->groupId = 0;
    pAlgDesc->rpcProtocolVersion = 0;
    pAlgDesc->iresFxns = NULL;
    pAlgDesc->codecClassConfig = NULL;
    pAlgDesc->memType = Engine_USECACHEDMEM_DEFAULT;
    pAlgDesc->types = NULL;
}

/*
 *  ======== Engine_initAttrs ========
 */
Void Engine_initAttrs(Engine_Attrs *pAttrs)
{
    pAttrs->procId = NULL;
}

/*
 *  ======== Engine_initDesc ========
 */
Void Engine_initDesc(Engine_Desc *pDesc)
{
    pDesc->name = NULL;
    pDesc->remoteName = NULL;
    pDesc->memMap = NULL;
    pDesc->useExtLoader = FALSE;
    pDesc->heapId = 0;
}

/*
 *  ======== Engine_open ========
 */
Engine_Handle Engine_open(String name, Engine_Attrs *attrs, Engine_Error *ec)
{
    Engine_Handle engine;
    Engine_DescListElem *descElem = NULL;
    IArg          key;
    Engine_Error  dummy;

    if (ec == NULL) {
        ec = &dummy;
    }

    Log_print3(Diags_ENTRY, "[+E] Engine_open> Enter('%s', 0x%lx, 0x%x)",
            (IArg)name, (IArg)attrs, (IArg)ec);

    /* Look for engine in dynamically allocated list */
    key = GateThread_enter(engineLock);
    descElem = getDescListElem(name);
    if (descElem == NULL) {
        GateThread_leave(engineLock, key);
        *ec = Engine_EEXIST;
        return (NULL);
    }
    descElem->refCount++;

    Log_print2(Diags_USER1, "[+1] Engine_open> desc->memMap [0x%x], "
               "desc->useExtLoader [%d]", (IArg)descElem->desc.memMap,
            (IArg)descElem->desc.useExtLoader);

    GateThread_leave(engineLock, key);

    /* create Engine object */
    engine = (Engine_Obj *)Memory_alloc(sizeof (struct Engine_Obj), NULL);
    if (engine == NULL) {
        key = GateThread_enter(engineLock);
        descElem->refCount--;
        GateThread_leave(engineLock, key);
        *ec = Engine_ENOMEM;
        return (NULL);
    }

    if (attrs == NULL) {
        attrs = &Engine_ATTRS;
    }

    /* initialize Engine_Obj fields */
    Queue_new(&engine->link);
    engine->server = NULL;
    engine->toRMS = Comm_INVALIDMSGQ;
    engine->fromRMS = Comm_INVALIDHANDLE;

    /*
     * TODO:H - though assigned here, this is unconditionally
     * overridden [for Engines with Servers] in rmsInit.  Either we
     * should remove this desc->heapId field (as it's no longer used
     * - and only introduced in CE 3.x), or we should understand how
     * a user would configure it, and assign it 'good defaults'.  Maybe
     * the default says "base the poolId on procId" and
     * do what we're doing - but if the user wants to override it, they
     * can configure it at runtime (e.g. the Engine name - "myEngine:1"?).
     */
    engine->rmsPoolId = descElem->desc.heapId;
    engine->rmsMsg = NULL;
    engine->desc = &(descElem->desc);
    engine->hasServer = FALSE;
    engine->remoteAlgTab = NULL;
    engine->numRemoteAlgs = 0;
    engine->loadedLibs = NULL;
    engine->numLoadedLibs = 0;
    engine->descElem = descElem;
    engine->procId = attrs->procId;

    /* initialize RMS communications */
    engine = rmsInit(engine, ec);

    if ((engine != NULL) && Engine_alwaysCollectDspTrace) {
        collectDspTrace( engine );
    }

    /* Initialize alg table with server algs */
    if (engine && engine->hasServer && ti_sdo_ce_Engine_initFromServer) {
        *ec = Engine_initFromServer(engine);
        if (*ec != Engine_EOK) {
            Log_print1(Diags_USER6, "Engine_open> WARNING: Unable to "
                    "initialize remote enging alg table from server. "
                    "Status = %d", (IArg)*ec);
        }
    }

    if (engine == NULL) {
        key = GateThread_enter(engineLock);
        descElem->refCount--;
        GateThread_leave(engineLock, key);
    }

    Log_print1(Diags_EXIT, "[+X] Engine_open> return(0x%x)", (IArg)engine);

    return (engine);
}

/*
 *  ======== Engine_setTrace ========
 */
Int Engine_setTrace(Engine_Handle engine, String mask)
{
    RMS_RmsMsg *msg;
    int         retVal = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine_setTrace> "
            "Enter(engine=0x%x, mask='%s')", (IArg)engine, (IArg)mask);

    if (engine->hasServer != TRUE) {
        retVal = Engine_ENOSERVER;
        goto setTrace_return;
    }

    if (!Server_holdingTraceToken) {
        retVal = Engine_EINUSE;
        goto setTrace_return;
    }

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        retVal = Engine_ERUNTIME;
        goto setTrace_return;
    }

    /* init a "set trace" message */
    msg->cmdBuf.cmd = RMS_SETTRACEMASK;
    msg->cmdBuf.status = RMS_EFAIL;
    strncpy((Char *)msg->cmdBuf.data.setTraceMaskIn.traceMask, mask,
        RMS_MAXTRACEMASKSIZE);
    if (strlen(mask) > RMS_MAXTRACEMASKSIZE) {
        Log_print1(Diags_USER6, "[+6] Engine_setTrace> "
                "Warning: server trace mask too long, truncated to %d chars.",
                (IArg)RMS_MAXTRACEMASKSIZE);
    }
    Log_print0(Diags_USER1, "[+1] Engine_setTrace> "
            "Requesting DSP set trace ...");

    /* send it to the DSP and wait for results ... */
    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        retVal = Engine_ERUNTIME;
        goto setTrace_return;
    }

setTrace_return:

    Log_print1(Diags_EXIT, "[+X] Engine_setTrace> return(%d)", (IArg)retVal);
    return (retVal);
}

/*
 *  ======== addEngineToList ========
 */
static Engine_Error addEngineToList(Engine_Desc *desc, Bool isStatic)
{
    Engine_DescListElem *descElem;
    Int                 len;
    IArg                key;
    Engine_Error        status = Engine_EOK;

    Log_print2(Diags_ENTRY, "[+E] Engine addEngineToList(0x%x, %d) ",
            (IArg)desc, (IArg)isStatic);

    /* Create Engine descriptor object */
    descElem = Memory_alloc(sizeof(Engine_DescListElem), NULL);
    if (descElem == NULL) {
        Log_print0(Diags_USER7, "[+7] Engine_add> Memory_alloc() failed.");
        return (Engine_ENOMEM);
    }

    Queue_new(&descElem->link);
    descElem->refCount = 0;

    /*
     *  Initialize descriptor. For statically configured engines, we just
     *  copy the descriptor and we're done. For dynamically added engines,
     *  we allocate buffers for the engine's name and remote name and copy
     *  these.
     */
    descElem->desc = *desc;
    descElem->isStatic = isStatic;
    descElem->loadedLibs = NULL;

    if (!isStatic && (status == Engine_EOK)) {
        descElem->desc.name = NULL;
        descElem->desc.algTab = NULL;
        descElem->desc.remoteName = NULL;
        descElem->desc.memMap = NULL;
        descElem->desc.numAlgs = 0;
        /*
         *  These fields are taken from user's descriptor:
         *      descElem->desc.heapId
         *      descElem->desc.useExtLoader
         */

        /* Copy the engine name into the descriptor */
        descElem->desc.name = Memory_alloc(strlen(desc->name) + 1, NULL);
        if (descElem->desc.name == NULL) {
            Log_print0(Diags_USER7, "[+7] Engine_add> Memory_alloc() failed.");
            status = Engine_ENOMEM;
        }
        else {
            strcpy(descElem->desc.name, desc->name);
        }

        /* If the engine has a server name, copy it into the descriptor */
        if ((status == Engine_EOK) && (desc->remoteName != NULL)) {
            len = strlen(desc->remoteName) + 1;
            descElem->desc.remoteName = Memory_alloc(len, NULL);

            if (descElem->desc.remoteName == NULL) {
                Log_print0(Diags_USER7,
                        "[+7] Engine addEngineToList> Memory_alloc() failed.");
                status = Engine_ENOMEM;
            }
            else {
                strcpy(descElem->desc.remoteName, desc->remoteName);
            }
        }

        /* If the engine has a map file name, copy it into the descriptor */
        if ((status == Engine_EOK) && (desc->memMap != NULL)) {
            len = strlen(desc->memMap) + 1;
            descElem->desc.memMap = Memory_alloc(len, NULL);

            if (descElem->desc.memMap == NULL) {
                Log_print0(Diags_USER7,
                        "[+7] Engine addEngineToList> Memory_alloc() failed.");
                status = Engine_ENOMEM;
            }
            else {
                strcpy(descElem->desc.memMap, desc->memMap);
            }
        }
    }

    if (status == Engine_EOK) {
        Log_print2(Diags_USER1, "[+1] Engine addEngineToList> Adding desc: "
                "name = %s, remoteName = %s",
                (IArg)descElem->desc.name, (IArg)descElem->desc.remoteName);
    }

    if (status != Engine_EOK) {
        if (descElem) {
            if (!descElem->isStatic) {
                if (descElem->desc.name) {
                    len = strlen(descElem->desc.name) + 1;
                    Memory_free(descElem->desc.name, len, NULL);
                }

                if (descElem->desc.remoteName) {
                    len = strlen(descElem->desc.remoteName) + 1;
                    Memory_free(descElem->desc.remoteName, len, NULL);
                }

                if (descElem->desc.memMap) {
                    len = strlen(descElem->desc.memMap) + 1;
                    Memory_free(descElem->desc.memMap, len, NULL);
                }
            }

            Memory_free(descElem, sizeof(Engine_DescListElem), NULL);
        }
    }
    else {
        /* Add engine descriptor to the end of list */
        Queue_put(&engineDescList, (Ptr)descElem);

        key = GateThread_enter(engineLock);
        numEngines++;
        GateThread_leave(engineLock, key);
    }

    return (status);
}


/*
 *  ======== allocNode ========
 */
static Engine_Node allocNode(Engine_Handle engine, String impId)
{
    Engine_Node node;

    Log_print2(Diags_ENTRY, "[+E] Engine> allocNode "
            "Enter(engine=0x%x, impId='%s')", (IArg)engine, (IArg)impId);

    /* allocate local node object */
    node = (Engine_NodeObj *)Memory_alloc(sizeof (Engine_NodeObj), NULL);
    if (node == NULL) {
        engine->lastError = Engine_ENOMEM;
        return (NULL);
    }

    node->engine = engine;
    node->impId = impId;

    /* create Comm for messages from the "remote" node */
    Log_print0(Diags_ENTRY, "[+E] Engine> allocNode(). Calling Comm_create("
            "NULL, NULL)");
    node->stdOut = Comm_create(NULL, NULL);
    if (node->stdOut == NULL) {
        freeNode(node);
        engine->lastError = Engine_ENOCOMM;
        return (NULL);
    }

    return (node);
}

/*
 *  ======== callServer ========
 */
static RMS_Status callServer(Engine_Handle engine, Comm_Msg *msg)
{
    /* set reply queue to our fromRMS queue */
    Comm_setReplyToHandle(*msg, engine->fromRMS);

    /* sanity check! */
    if (engine->toRMS == Comm_INVALIDMSGQ) {
        /* Generally doesn't happen, but if Engine_open() failed,
         * it's failure handling internally calls Engine_close(), which
         * tries to get the trace off the Server via this call.  Just return
         * error.
         */
        return (RMS_ENOTFOUND);
    }

    /* send create message to RMS */
    if (Comm_put(engine->toRMS, *msg) == Comm_EOK) {
        Int status;
        /* wait for reply on fromRMS queue */
        status = Comm_get(engine->fromRMS, msg, Comm_FOREVER);
        assert(status == Comm_EOK);
    }

    return (((RMS_RmsMsg *)(*msg))->cmdBuf.status);
}

/*
 *  ======== checkServer ========
 */
static Bool checkServer(Engine_Handle engine)
{
    /* This string is defined in ti/sdo/ce/libvers.xdt */

    Log_print1(Diags_ENTRY, "[+E] checkServer(0x%lx)", (IArg)engine);

    /*
     *  TODO: Also send message to RMS to get the RPC protocol version
     *  to make sure it matches.
     */
    if (ti_sdo_ce__versionString != NULL) {
        String skey = getServerKey(engine);

        if (skey == NULL || strcmp(skey, ti_sdo_ce__versionString) != 0) {
            /* if skey == NULL, lastError has already been set */
            if (skey != NULL) {
                engine->lastError = Engine_EBADSERVER;
            }
            Log_print3(Diags_USER6, "[+6] checkServer(0x%lx) failed: "
                    "server = '%s', engine = '%s'",
                    (IArg)engine, (IArg)(skey == NULL ? "" : skey),
                    (IArg)ti_sdo_ce__versionString);
            return (FALSE);
        }
    }

    return (TRUE);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    Engine_Desc      *desc;
    Engine_AlgDesc   *algTab;
    Engine_AlgDesc   *alg;
    Engine_DescListElem *descElem;
    Int32             numProcs;

    if (curInit != FALSE) {
        curInit = FALSE;

        #if 0
        while (Queue_head(&engineList) != &engineList) {
            Engine_Handle engine = Queue_get(&engineList);
            Engine_close(engine);
        }
        #endif

        while (Queue_head(&stubFxnsList) != &stubFxnsList) {
            Engine_StubFxnsElem *stubs = Queue_get(&stubFxnsList);
            Memory_free(stubs, sizeof(Engine_StubFxnsElem), NULL);
        }

        while (Queue_head(&engineDescList) != &engineDescList) {
            descElem = (Engine_DescListElem *)Queue_get(&engineDescList);

            Log_print2(Diags_USER4, "Engine cleanup()> Num engines = %d, "
                    "removing engine %s", (IArg)numEngines,
                    (IArg)descElem->desc.name);
            numEngines--;
            if (!descElem->isStatic) {
                /* TODO: Remove any algs in descElem->loadedLibs */

                /* Free allocated 'name' and 'remoteName' */
                if (descElem->desc.name) {
                    Memory_free(descElem->desc.name,
                            strlen(descElem->desc.name) + 1, NULL);
                }
                if (descElem->desc.remoteName) {
                    Memory_free(descElem->desc.remoteName,
                            strlen(descElem->desc.remoteName) + 1, NULL);
                }
                if (descElem->desc.memMap) {
                    Memory_free(descElem->desc.memMap,
                            strlen(descElem->desc.memMap) + 1, NULL);
                }
            }
            Memory_free(descElem, sizeof(Engine_DescListElem), NULL);
        }

        for (desc = Engine_config.engineTab; desc->name != NULL; desc++) {
            algTab = desc->algTab;

            if (algTab != NULL) {
                for (alg = algTab; alg->name != NULL; alg++) {
                    if (alg->isLocal) {
                        Algorithm_removeGroup(alg->groupId);
                    }
                }
            }
        }

        if (serverLock != NULL) {
            GateThread_delete(&serverLock);
            serverLock = NULL;
        }
        if (engineLock != NULL) {
            GateThread_delete(&engineLock);
            engineLock = NULL;
        }
        if (traceLock != NULL) {
            GateThread_delete(&traceLock);
            traceLock = NULL;
        }

        if (serverTab) {
            numProcs = Processor_getNumProcs();
            Memory_free(serverTab, sizeof(*serverTab) * numProcs, NULL);
        }

        /* reinitialize static vars */
        serverTab = NULL;
        localEngine = NULL;
    }
}

/*
 *  ======== copyToFile ========
 *  copy buffer to file stream with optional prefix in front of each line
 */
static Int copyToFile(Char *cp, Int size, String prefix, Bool *newLine,
    FILE *out)
{
    Int count, i;
    Int prefixLen = 0;

    if ((prefix != NULL) && (prefix[0] != '\0')) {
        prefixLen = strlen(prefix);
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (prefixLen > 0 && *newLine) {
            fputs(prefix, out);
            count += prefixLen;
            *newLine = FALSE;
        }

        fputc(cp[i], out);
        count++;

        if (cp[i] == '\n') {
            *newLine = TRUE;
        }
    }

    return (count);
}

/*
 *  ======== freeNode ========
 */
static Void freeNode(Engine_Node node)
{
    if (node != NULL) {
        if (node->stdOut != NULL) {
            Comm_delete(node->stdOut);
        }

        Memory_free(node, sizeof(Engine_NodeObj), NULL);
    }
}

/*
 *  ======== freeServerTab ========
 *  Free the engine's remoteAlgTab.
 */
static Void freeServerTab(Engine_Handle engine)
{
    Engine_AlgDesc *desc;
    Int             i;
    Int             len;
    Int             nAlgs = engine->numRemoteAlgs;


    Log_print1(Diags_ENTRY, "[+E] Engine freeServerTab() enter(0x%x)",
            (IArg)engine);

    Log_print1(Diags_USER2, "[+2] Engine freeServerTab() engine->"
            "numRemoteAlgs = %d", (IArg)nAlgs);

    if (engine->remoteAlgTab == NULL) {
        return;
    }

    for (i = 0; i < nAlgs; i++) {
        desc = &(engine->remoteAlgTab[i]);

        if (desc->name) {
            Memory_free(desc->name, strlen(desc->name) + 1, NULL);
        }
        if (desc->types) {
            len = strlen(desc->types) + 1;
            Memory_free(desc->types, len, NULL);
        }
    }
    Memory_free(engine->remoteAlgTab, nAlgs * sizeof(Engine_AlgDesc), NULL);

    engine->numRemoteAlgs = 0;
    engine->remoteAlgTab = NULL;

    Log_print0(Diags_EXIT, "[+X] Engine freeServerTab() exit");
}

/*
 *  ======== getAlgDesc ========
 *  Find the alg descriptor with 'algName' from the many possibilities.
 *  If the engine has not been opened, use the engine name to find the alg,
 *  otherwise use the engine handle.
 */
static Engine_AlgDesc *getAlgDesc(String engName, Engine_Handle engine,
        String algName)
{
    Engine_AlgDesc      *alg = NULL;
    Engine_DescListElem *descElem;
    Engine_AlgDesc      *algTab;
    _Engine_AlgLib      *lib;


    /*
     *  First go through algs in the Engine_DescListElem object. These include
     *  all statically configured algs, and algs added to the engine while
     *  it is not in the opened state.
     */
    if (engName != NULL) {
        descElem = getDescListElem(engName);
    }
    else {
        descElem = engine->descElem;
    }

    if (descElem == NULL) {
        Log_print1(Diags_USER7, "Engine getAlgDesc> Failed to find engine "
                "discriptor in list for engine %s", (IArg)engine->desc->name);
        return (NULL);
    }

    /* Static alg table */
    algTab = descElem->desc.algTab;

    if (algTab != NULL) {
        for (alg = algTab; alg->name != NULL; alg++) {
            if (strcmp(algName, alg->name) == 0) {
                return (alg);
            }
        }
    }

    /* Algs added with Engine_addAlg() before Engine_open() */
    lib = descElem->loadedLibs;
    while (lib != NULL) {
        if (strcmp(algName, lib->algDesc.name) == 0) {
            return (&(lib->algDesc));
        }
        lib = lib->next;
    }

    if (engine) {
        /* Now go through algs obtained from server */
        algTab = engine->remoteAlgTab;

        if (algTab != NULL) {
            for (alg = algTab; alg->name != NULL; alg++) {
                if (strcmp(algName, alg->name) == 0) {
                    return (alg);
                }
            }
        }

        /* Now go through algs added after Engine_open() */
        lib = engine->loadedLibs;

        while (lib != NULL) {
            if (strcmp(algName, lib->algDesc.name) == 0) {
                return (&(lib->algDesc));
            }
            lib = lib->next;
        }
    }

    return (NULL);
}

/*
 *  ======== getAlgDescNum ========
 */
static Engine_AlgDesc *getAlgDescNum(String engName, Engine_Handle engine,
        Int index)
{
    Engine_AlgDesc      *alg = NULL;
    Int                  i, n;
    Engine_DescListElem *descElem;
    _Engine_AlgLib      *algLib;

    Log_print3(Diags_ENTRY, "[+E] getAlgDescNum('%s', 0x%lx, %d)",
            (IArg)engName, (IArg)engine, (IArg)index);

    Assert_isTrue(index >= 0, (Assert_Id)NULL);
    Assert_isTrue((engName != NULL) || (engine != NULL), (Assert_Id)NULL);
    Assert_isTrue((engName == NULL) || (engine == NULL), (Assert_Id)NULL);

    /* Assume lock acquired by caller */

    /* Get the descriptor from the list of engines */
    descElem = (engName) ? getDescListElem(engName) : engine->descElem;

    // TEST!
    if (engine) {
        descElem = getDescListElem(engine->desc->name);
    }

    if (descElem == NULL) {
        return (NULL);
    }

    /* Static alg table */
    if (index < descElem->desc.numAlgs) {
        alg = &(descElem->desc.algTab[index]);
        return (alg);
    }

    /* Engine's pre-opened added algs */
    n = index - descElem->desc.numAlgs;
    if (n < descElem->numLoadedLibs) {
        algLib = descElem->loadedLibs;

        for (i = 0; (i < n) && (algLib != NULL); i++) {
            algLib = algLib->next;
        }

        /* algLib should never be NULL but log just in case */
        if (algLib == NULL) {
            Log_print3(Diags_USER7,
                    "Engine getAlgDescNum> WARNING: Inconsistency in engine "
                    "[%s] loadedLibs[%d] and numLoadedLibs [%d]!",
                    (IArg)descElem->desc.name, (IArg)i, (IArg)n);
        }
        alg = (algLib != NULL) ? &(algLib->algDesc) : NULL;
        return (alg);
    }

    if (engine == NULL) {
        return (alg);
    }

    /* Engine opened, check remote alg table */
    n -= descElem->numLoadedLibs;

    if (n < engine->numRemoteAlgs) {
        /* Alg in remote alg table */
        alg = &(engine->remoteAlgTab[n]);
        return (alg);
    }

    n -= engine->numRemoteAlgs;

    if (n < engine->numLoadedLibs) {
        algLib = engine->loadedLibs;

        /* Check engine's post-opened added alg list */
        for (i = 0; (i < n) && (algLib != NULL); i++) {
            algLib = algLib->next;
        }

        if (algLib == NULL) {
            /* Shouldn't happen, but we'll check for this anyway */
            Log_print1(Diags_USER7, "Engine_getAlgInfo> Inconsistency "
                    "in number of loaded libs and numLoadedLibs for "
                    "engine %s", (IArg)engine->desc->name);
        }
        alg = (algLib != NULL) ? &(algLib->algDesc) : NULL;
    }

    return (alg);
}

/*
 *  ======== getDescListElem ========
 */
static Engine_DescListElem *getDescListElem(String engName)
{
    Engine_DescListElem *next;

    /* Go through list of engines looking for a match with engName */
    next = Queue_next(&engineDescList);
    while ((Queue_Elem *)next != &engineDescList) {
        if (strcmp(next->desc.name, engName) == 0) {
            /* Match found */
            return (next);
        }
        next = Queue_next(next);
    }

    return (NULL);
}


/*
 *  ======== getServerKey ========
 */
static String getServerKey(Engine_Handle engine)
{
    RMS_RmsMsg *msg;

    if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    /* init a "node create" message */
    msg->cmdBuf.cmd = RMS_GETVERS;
    msg->cmdBuf.status = RMS_EFAIL;

    callServer(engine, (Comm_Msg *)&msg);

    engine->rmsMsg = (Comm_Msg)msg;

    /* check that remote cmd succeeded */
    if (msg->cmdBuf.status != RMS_EOK) {
        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    /* Check the protocol version */
    if ((msg->cmdBuf.data.getVersOut.rpcMajor != RMS_VERSION_MAJOR) ||
            (msg->cmdBuf.data.getVersOut.rpcSource != RMS_VERSION_SOURCE) ||
            (msg->cmdBuf.data.getVersOut.rpcMinor < RMS_VERSION_MINOR)) {

        Log_print1(Diags_USER6, "[+6] getServerKey(0x%lx) protocol mismatch: ",
                (IArg)engine);
        Log_print3(Diags_USER6,
                "[+6]    server: major = %d, source key = %d, minor key = %d",
                (IArg)(msg->cmdBuf.data.getVersOut.rpcMajor),
                (IArg)(msg->cmdBuf.data.getVersOut.rpcSource),
                (IArg)(msg->cmdBuf.data.getVersOut.rpcMinor));
        Log_print3(Diags_USER6,
                "[+6]    engine: major = %d, source key = %d, minor key = %d",
                (IArg)RMS_VERSION_MAJOR, (IArg)RMS_VERSION_SOURCE,
                (IArg)RMS_VERSION_MINOR);

        engine->lastError = Engine_ERUNTIME;
        return (NULL);
    }

    return ((String)msg->cmdBuf.data.getVersOut.vers);
}

/*
 *  ======== getRpcProtocolVersion ========
 *
 *  TODO:L For performance reasons, it'd likely be quicker to look this up
 *  given a UUID rather than a name.  Then we could do "==" rather than
 *  "strcmp".
 */
static Int getRpcProtocolVersion(Engine_Handle engine, NODE_Uuid uuid)
{
    _Engine_AlgLib *lib;
    Engine_AlgDesc *alg;
    Int i;
    Int ver = -1;

    /*
     *  Note: We're assuming Engine_addAlg() cannot be used to add
     *  algs to a server before the engine has been opened (since the
     *  server would not have been loaded). Therefore, we don't need
     *  to look in the Engine_DescListElem.loadedLibs.
     */
    if (engine->desc->algTab) {
        for (alg = engine->desc->algTab; alg->name != NULL; alg++) {
            if (NODE_uuidMatch(&(alg->uuid), &uuid)) {
                /* match */
                ver = alg->rpcProtocolVersion;
                return (ver);
            }
        }
    }

    /* Check remote table, if not found in static table */
    if (engine->remoteAlgTab) {
        for (i = 0; i < engine->numRemoteAlgs; i++) {
            if (NODE_uuidMatch(&(engine->remoteAlgTab[i].uuid), &uuid)) {
                ver = engine->remoteAlgTab[i].rpcProtocolVersion;
                return (ver);
            }
        }
    }

    /*
     *  TODO: Should we always use -1 for dynamically loaded codecs? Or, do
     *  we need to add rpcProtocolVersion to Engine_DllAlgDesc?
     */
    while ((lib = engine->loadedLibs) != NULL) {
        alg = &(lib->algDesc);
        if (NODE_uuidMatch(&(alg->uuid), &uuid)) {
            /* match */
            ver = alg->rpcProtocolVersion;
            break;
        }
        lib = lib->next;
    }

    return (ver);
}

/*
 *  ======== isa ========
 */
static Bool isa(Engine_AlgDesc *alg, String type)
{
    String  tp;
    Char   *endStr = NULL;
    Char   *begStr = NULL;
    Char    sep = ';';
    Int     len;

    // TODO: Temp, until typeTab[] is removed.
    if (alg->types == NULL) {
        alg->types = alg->typeTab[0];
    }

    if ((tp = alg->types) != NULL) {
        if ((endStr = strchr(tp, sep)) == NULL) {
            /* Just one type, not multiple types separated by ';' */
            if (strcmp(tp, type) == 0) {
                return (TRUE);
            }
        }
        else {
            /* multiple types, separated by ';' */
            begStr = tp;
            while ((begStr != NULL) && (*begStr != '\0')) {
                len = (endStr != NULL) ? endStr - begStr : strlen(begStr);
                if ((strncmp(begStr, type, len) == 0) &&
                        (strlen(type) == len)) {
                    return (TRUE);
                }

                begStr = (endStr == NULL) ? NULL : endStr + 1;
                endStr = (endStr == NULL) ? NULL : strchr(begStr, sep);
            }

            if (endStr == NULL) {
                return (FALSE);
            }
        }
    }

    return (FALSE);
}

/*
 *  ======== name2Uuid ========
 *  Get the UUID of the algorithm.
 *  This id is used on the server-side to lookup the appropriate NODE_Desc;
 *  i.e., the skeleton fxns, stack size, priority, etc.
 */
static Void name2Uuid(Engine_Handle engine, String algName, NODE_Uuid *uuid)
{
    Engine_AlgDesc *alg;

    alg = getAlgDesc(NULL, engine, algName);
    if (alg) {
        *uuid = alg->uuid;
    }
}

/*
 *  ======== rmsInit ========
 */
static Engine_Handle rmsInit(Engine_Obj *engine, Engine_Error *ec)
{
    Int             status;
    Engine_AlgDesc *alg;
    String          algName = NULL;
    Bool            startedServer = FALSE;
    String          traceMask = NULL;
    char            rmsCommName[32];  /* MessageQ_max length(?) */
    UInt32          coreId;

    Log_print2(Diags_ENTRY, "[+E] rmsInit> Enter(engine=0x%x, ec=0x%x)",
            (IArg)engine, (IArg)ec);

    /*
     *  Go through the list of algorithms, checking for non-local to
     *  determine whether or not to start the server.
     */
    Log_print1(Diags_USER1, "[+E] rmsInit> engine->desc = 0x%x",
            (IArg)engine->desc);
    Log_print1(Diags_USER1, "[+E] rmsInit> engine->desc->algTab = 0x%x",
            (IArg)engine->desc->algTab);
    alg = engine->desc->algTab;
    for (; (alg != NULL) && (alg->name != NULL); alg++) {
        if (alg->isLocal != TRUE) {
            Log_print1(Diags_USER1, "[+E] rmsInit> found remote alg %s",
                    (IArg)alg->name);
            algName = alg->name;
            break;
        }
    }

    /*
     *  Connect to remote proc if there are remote algs or the name of
     *  a server program is non-NULL.
     */
    if ((algName != NULL) || (engine->desc->remoteName != NULL)) {
        engine->hasServer = TRUE;

        Log_print0(Diags_USER1, "[+E] rmsInit> engine has server!");

        /* If engine->procId isn't set, initialize it to core 0 */
        /*
         * Note, core 0 can be confusing.  On a homogeneous, BIOS-only,
         * multicore device, like 6472, core 0 is typically the app core
         * (with cores 1-5 being the slaves).  On a heterogeneous,
         * SysLink-based device, like OMAP3, core 0 is typically a slave.
         * This fundamental difference makes it difficult to decide what to do
         * in this 'default' case (an ideal default would be the 'first slave',
         * but because of these environmental differences, we don't know if
         * that's core 0 or core 1!).  So when not specified, the 'default'
         * core is core 0.
         */
        if (engine->procId == NULL) {
            engine->procId = Processor_getCoreName(0);
        }

        Log_print1(Diags_USER1, "[+E] rmsInit> engine->procId = %s",
                (IArg)engine->procId);

        /* [potentially] get the heap id for communicating with remote proc */
        coreId = Processor_getCoreId(engine->procId);

        /* Make sure engine->procId is valid */
        if (coreId == Processor_INVALIDID) {
            Log_print1(Diags_USER7, "[+7] rmsInit> Invalid procId: %s",
                (IArg)engine->procId);
            goto fail;
        }

        engine->rmsPoolId = Processor_getHeapId(coreId);

        Log_print1(Diags_USER1, "[+E] rmsInit> engine->coreId = %d",
                (IArg)coreId);

        if (engine->procId == NULL) {
            /* strange, but supported, the "remote" server is on this proc */
            engine->server = NULL;
        }
        else {
            /* connect to RMS on remote server */
            engine->server = rserverOpen(engine->desc, &startedServer,
                    engine->procId);
            if (engine->server == NULL) {
                *ec = Engine_EDSPLOAD;
                goto fail;
            }
        }

        /* create a message queue for RMS replies (pass NULL for name) */
        engine->fromRMS = Comm_create(NULL, NULL);
        if (engine->fromRMS == NULL) {
            *ec = Engine_ENOCOMM;
            goto fail;
        }

        /* allocate message to exchange with RMS */
        status = Comm_alloc(engine->rmsPoolId,
                (Comm_Msg *)&engine->rmsMsg, sizeof (RMS_RmsMsg));
        if (status != Comm_EOK) {
            *ec = Engine_ECOMALLOC;
            goto fail;
        }

        /* locate core-specific RMS's message queue */
        sprintf(rmsCommName, RMS_CMDQNAME ":%s", engine->procId);
        status = Comm_locate(rmsCommName, &engine->toRMS);
        if (status != Comm_EOK) {
            *ec = Engine_ENOSERVER;
            goto fail;
        }

        /* check server compatibility key */
        if (checkServer(engine) != TRUE) {
            *ec = engine->lastError;
            goto fail;
        }
    }

    /* put opened engine on engineList */
    Queue_put(&engineList, &engine->link);
    *ec = Engine_EOK;

    /* if started up server optionally set the DSP trace mask */
    if (startedServer == TRUE) {
        if (Engine_alwaysCollectDspTrace) {
            Log_print2(Diags_ENTRY,
                    "[+E] rmsInit> RMS initialized(0x%lx); CE_DEBUG on, "
                    "setting DSP trace mask to %s",
                    (IArg)engine, (IArg)Engine_ceDebugDspTraceMask);
            Engine_setTrace(engine, Engine_ceDebugDspTraceMask);
        }
        if ((traceMask = Global_getenv("CE_DSP0TRACE")) != NULL) {
            Log_print2(Diags_ENTRY,
                    "[+E] rmsInit(0x%lx), setting DSP trace mask to %s",
                    (IArg)engine, (IArg)traceMask);
            Engine_setTrace(engine, traceMask);
        }
    }

    return (engine);

fail:

    Engine_close(engine);

    return (NULL);
}

/*
 *  ======== rserverClose ========
 */
static Void rserverClose(RServer server)
{
    IArg key;

    key = GateThread_enter(serverLock);
    Log_print2(Diags_ENTRY, "[+E] rserverClose(0x%lx), count = %d",
            (IArg)server, (IArg)(server->refCount));

    /* decrement reference count */
    if (server->refCount-- == 1) {
        /* if no more references exist, turn off the DSP */
        Processor_delete(server->dspProc);
    }

    Log_print1(Diags_EXIT, "[+X] rserverClose(0x%lx) done.", (IArg)server);
    GateThread_leave(serverLock, key);
}

/*
 *  ======== rserverDetach ========
 */
static Void rserverDetach(Engine_Handle engine)
{
    IArg        key;
    RMS_RmsMsg *msg;
    RServer     server = engine->server;

    Log_print2(Diags_ENTRY, "[+E] rserverDetach(0x%lx), count = %d",
            (IArg)server, (IArg)(server->refCount));

    key = GateThread_enter(serverLock);

    /* Reference count will be decremented in rserverClose() */
    if (server->refCount == 1) {
        if ((msg = (RMS_RmsMsg *)engine->rmsMsg) == NULL) {
            Log_print0(Diags_USER6, "[+6] rserverDetach() NULL rmsMsg");
            engine->lastError = Engine_ERUNTIME;
            GateThread_leave(serverLock, key);
            return;
        }

        /* init a "node create" message */
        msg->cmdBuf.cmd = RMS_DETACH;
        msg->cmdBuf.status = RMS_EFAIL;

        callServer(engine, (Comm_Msg *)&msg);

        engine->rmsMsg = (Comm_Msg)msg;

        /* check that remote cmd succeeded */
        if (msg->cmdBuf.status != RMS_EOK) {
            Log_print1(Diags_USER6, "[+6] rserverDetach() remote command "
                       "failed: [%d]", (IArg)msg->cmdBuf.status);
            engine->lastError = Engine_ERUNTIME;
        }
    }

    GateThread_leave(serverLock, key);

    Log_print1(Diags_EXIT, "[+X] rserverDetach(0x%lx) done.", (IArg)server);
}

/*
 *  ======== rserverOpen ========
 */
static RServer rserverOpen(Engine_Desc * desc, Bool * startedServer,
        String procId)
{
    IArg    key;
    RServer server = &serverTab[Processor_getCoreId(procId)];

    key = GateThread_enter(serverLock);
    Log_print2(Diags_ENTRY, "[+E] rserverOpen('%s'), count = %d",
            (IArg)(desc->remoteName), (IArg)(server->refCount));

    Log_print2(Diags_ENTRY, "[+E] rserverOpen >, memMap = 0x%x, "
            "useExtLoader = %d",
            (IArg)(desc->memMap), (IArg)(desc->useExtLoader));

    if (server->refCount == 0) {
        /* if no references exist, initialize the Server */
        Processor_Attrs attrs = Processor_ATTRS;

        attrs.argv = NULL;
        attrs.argc = 0;
        attrs.cpuId = procId;
        attrs.useExtLoader = desc->useExtLoader;

        if ((server->dspProc = Processor_create(desc->remoteName,
            desc->memMap, &attrs)) != NULL) {
            server->imageName = desc->remoteName;
            *startedServer = TRUE;
        }
        else {
            /* failed to "create" the server, return NULL */
            Log_print1(Diags_USER6,
                    "[+6] rserverOpen: can't start '%s'; Processor_create "
                    "failed", (IArg)(desc->remoteName));
            server = NULL;
        }
    }
    else {
        if (strcmp(server->imageName, desc->remoteName) != 0) {
            Log_print2(Diags_USER6,
                    "[+6] rserverOpen: can't start '%s'; '%s' already running",
                    (IArg)(desc->remoteName), (IArg)(server->imageName));
            server = NULL;
        }
    }

    if (server != NULL) {
        server->refCount++;
    }

    Log_print2(Diags_EXIT, "[+X] rserverOpen('%s'): 0x%lx done.",
            (IArg)(desc->remoteName), (IArg)server);
    GateThread_leave(serverLock, key);

    return (server);
}

/*
 *  ======== Engine_getNumEngines ========
 */
Int Engine_getNumEngines()
{
    return (numEngines);
}


/*
 *  ======== _Engine_getDesc ========
 */
Engine_Desc *_Engine_getDesc(Int n)
{
    Engine_DescListElem *descElem;
    Engine_Desc         *desc = NULL;
    Int                  i;

    Log_print1(Diags_ENTRY, "[+E] _Engine_getDesc(%d)", (IArg)n);

    i = 0;
    descElem = (Engine_DescListElem *)Queue_next(&engineDescList);

    while (((Queue_Elem *)descElem != &engineDescList) && (i < n)) {
        descElem = Queue_next(descElem);
        i++;
    }

    if ((Queue_Elem *)descElem != &engineDescList) {
        desc = &(descElem->desc);
    }

    return (desc);
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:25; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


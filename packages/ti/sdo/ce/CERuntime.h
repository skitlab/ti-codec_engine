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
 *  ======== ti/sdo/ce/CERuntime.h ========
 */

/**
 *  @file       ti/sdo/ce/CERuntime.h
 *
 *  @brief      The Codec Engine Runtime init module.  Provides system
 *              wide initialization of the Codec Engine Runtime.
 */
/**
 *  @addtogroup   CODECENGINE     Codec Engine Runtime
 */

#ifndef CERuntime_
#define CERuntime_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    CODECENGINE */
/*@{*/

#include <ti/sdo/ce/Engine.h>


/* Define this symbol so alg table for an engine can be NULL */
#define CE_NULL_algs NULL

/**
 *  @brief      Macros for runtime configuration. These macros can be used to
 *              create a static table of algorithms.  However, the preferred
 *              method of building engine and alg tables, is to use the
 *              run-time APIs, Engine_add() and Engine_addAlg().
 *
 *  @sa Engine_add()
 *  @sa Engine_addAlg()
 */

/*
 *  ======== CE_DECLARE_TYPE ========
 */
/**
 *  @brief      Declare an inheritanc hierarchy for an algorithm.
 *
 *  @param[in]  name    This is a symbol that will be associated with the
 *                      @c types argument. It will be used to generate an
 *                      internal variable name, so don't use the same name
 *                      for two different calls to @c CE_DECLARE_TYPE().
 *                      @c name should be used in CE_LOCAL_ALG() to
 *                      associate an alg to @c types.
 *
 *  @param[in]  types   This is a ';' separated string of inheritance
 *                      hierarchies. It is used to identify the codec class of
 *                      an algorithm. For example, the declaration:
 *                      @c CE_DECLARE_TYPE(mydecoder,
 *                                         "ti.sdo.ce.speech1.ISPHDEC1")
 *                      indicates that mydecoder (a name that will be used
 *                      in CE_LOCAL_ALG() to declare a speech decoder),
 *                      inherits the ti.sdo.ce.speech1.ISPHDEC1 interface.
 *
 *                      Another example is the following:
 *                      CE_DECLARE_TYPE(decoder,
 *                      "ti.sdo.ce.video.IVIDDEC;ti.sdo.ce.test.xvideo.IVIDE")
 *                      This says that the decoder inherits the
 *                      ti.sdo.ce.test.xvideo.IVIDE interface, which in turn
 *                      inherits the ti.sdo.ce.video.IVIDDEC interface.
 *
 *  @deprecated No need to use this macro when using CE_LOCAL_ALG2
 *
 *  @sa CE_LOCAL_ALG2()
 */
#define CE_DECLARE_TYPE(name, types)         \
                                             \
static String typeTab_##name [] = {          \
    types,                                   \
    NULL                                     \
};                                           \
                                             \
/*
 *  ======== CE_LOCAL_ALG ========
 */
/**
 *  @brief      Generates a structure containing data for a local algorithm.
 *
 *  @param[in]  name      This symbol is used to associate the algorithm with
 *                        one of the @c types passed to @c CE_DECLARE_TYPE().
 *  @param[in]  algName   This is the string name that the applicaion will use
 *                        to create the algorithm, for example, "sphenc1_copy".
 *  @param[in]  ialgFxns  The address of the IALG_Fxns table for the algorithm.
 *  @param[in]  idma3Fxns The address of the algorithm's IDMA3_Fxns table, if
 *                        it has one, otherwise NULL.
 *  @param[in]  iresFxns  If the algorithm uses IRES, the address of its
 *                        IRES_Fxns table, otherwise NULL.
 *  @param[in]  groupId   Scratch group Id of algorithm.
 *  @param[in]  memType   The type of memory (cached, non-cached, or whatever
 *                        the default is), to allocate for the algorithm.
 *                        Choose from the following values for memType:
 *
 *                 Engine_USECACHEDMEM_DEFAULT - default memory allocation
 *                 Engine_USECACHEDMEM_NONCACHED - non-cached memory allocation
 *                 Engine_USECACHEDMEM_CACHED - cached memory allocation
 *
 *  @par Example Usage:
 *  @code
 *      CE_BEGIN_ALG_TABLE(engineName)
 *          CE_LOCAL_ALG(name_1, ...)
 *          CE_LOCAL_ALG(name_2, ...)
 *          ...
 *          CE_LOCAL_ALG(name_n, ...)
 *      CE_END_ALG_TABLE(engineName)
 *  @endcode
 *
 * @remarks     This macro must be called between the @c CE_BEGIN_ALG_TABLE()
 *              and @c CE_END_ALG_TABLE() macro calls.
 *
 *  @deprecated Use CE_LOCAL_ALG2 instaead.
 *
 *  @sa CE_DECLARE_TYPE
 *  @sa CE_BEGIN_ALG_TABLE
 */
#define CE_LOCAL_ALG(name, algName, ialgFxns, idma3Fxns, iresFxns, groupId, \
                     memType) \
                                             \
    { algName,        /* name */             \
      {0},            /* uuid */             \
      ialgFxns,       /* ialgFxns */         \
      idma3Fxns,      /* idma3Fxns */        \
      typeTab_##name, /* typeTab */          \
      TRUE,           /* isLocal */          \
      groupId,        /* groupId */          \
      0,              /* protocol */         \
      iresFxns,       /* iresFxns */         \
      NULL,           /* stub/skel params */ \
      memType,        /* cached mem type */  \
      NULL,           /* type - typeTab[0] will be used instead */ \
    },

/*
 *  ======== CE_LOCAL_ALG2 ========
 */
/**
 *  @brief      Generates a structure containing data for a local algorithm.
 *              This macro takes a 'types' string as an argument to avoid
 *              having to use the CE_DECLARE_TYPES() macro call.
 *
 *  @param[in]  algName   This is the string name that the applicaion will use
 *                        to create the algorithm, for example, "sphenc1_copy".
 *  @param[in]  ialgFxns  The address of the IALG_Fxns table for the algorithm.
 *  @param[in]  idma3Fxns The address of the algorithm's IDMA3_Fxns table, if
 *                        it has one, otherwise NULL.
 *  @param[in]  iresFxns  If the algorithm uses IRES, the address of its
 *                        IRES_Fxns table, otherwise NULL.
 *  @param[in]  groupId   Scratch group Id of algorithm.
 *  @param[in]  memType   The type of memory (cached, non-cached, or whatever
 *                        the default is), to allocate for the algorithm.
 *                        Choose from the following values for memType:
 *
 *                 Engine_USECACHEDMEM_DEFAULT - default memory allocation
 *                 Engine_USECACHEDMEM_NONCACHED - non-cached memory allocation
 *                 Engine_USECACHEDMEM_CACHED - cached memory allocation
 *  @param[in]  types     The ';' separated string of inheritance
 *                        hierarchies. This must be constant in order to
 *                        initialize the structure.
 *
 *  @par Example Usage:
 *  @code
 *      CE_BEGIN_ALG_TABLE(engineName)
 *          CE_LOCAL_ALG(name_1, ...)
 *          CE_LOCAL_ALG(name_2, ...)
 *          ...
 *          CE_LOCAL_ALG(name_n, ...)
 *      CE_END_ALG_TABLE(engineName)
 *  @endcode
 *
 * @remarks     This macro must be called between the @c CE_BEGIN_ALG_TABLE()
 *              and @c CE_END_ALG_TABLE() macro calls.
 *
 *  @sa CE_DECLARE_TYPE
 *  @sa CE_BEGIN_ALG_TABLE
 */
#define CE_LOCAL_ALG2(algName, ialgFxns, idma3Fxns, iresFxns, groupId, \
                     memType, types) \
                                             \
    { algName,        /* name */             \
      {0},            /* uuid */             \
      ialgFxns,       /* ialgFxns */         \
      idma3Fxns,      /* idma3Fxns */        \
      NULL,           /* typeTab */          \
      TRUE,           /* isLocal */          \
      groupId,        /* groupId */          \
      0,              /* protocol */         \
      iresFxns,       /* iresFxns */         \
      NULL,           /* stub/skel params */ \
      memType,        /* cached mem type */  \
      types,          /* types */            \
    },

/*
 *  ======== CE_DECLARE_LOCAL_ALG ========
 */
/**
 *  @brief      Generates a static variable of type Engine_AlgDesc.
 *              It is used in this manner:
 *
 *  @param[in]  name      The name to be given to the static Engine_AlgDesc
 *                        variable.
 *  @param[in]  algName   This is the string name that the applicaion will use
 *                        to create the algorithm, for example, "sphenc1_copy".
 *  @param[in]  ialgFxns  The address of the IALG_Fxns table for the algorithm.
 *  @param[in]  idma3Fxns The address of the algorithm's IDMA3_Fxns table, if
 *                        it has one, otherwise NULL.
 *  @param[in]  iresFxns  If the algorithm uses IRES, the address of its
 *                        IRES_Fxns table, otherwise NULL.
 *  @param[in]  groupId   Scratch group Id of algorithm.
 *  @param[in]  memType   The type of memory (cached, non-cached, or whatever
 *                        the default is), to allocate for the algorithm.
 *                        Choose from the following values for memType:
 *
 *                 Engine_USECACHEDMEM_DEFAULT - default memory allocation
 *                 Engine_USECACHEDMEM_NONCACHED - non-cached memory allocation
 *                 Engine_USECACHEDMEM_CACHED - cached memory allocation
 *  @param[in]  types     The ';' separated string of inheritance
 *                        hierarchies. This must be constant in order to
 *                        initialize the structure.
 *
 *  @par Example Usage:
 *  @code
 *      CE_DECLARE_LOCAL_ALG(algName, )
 *
 *      main()
 *      {
 *          ...
 *          status = Engine_addAlgDesc(engine, algName);
 *          ...
 *      }
 *  @endcode
 *
 */
#define CE_DECLARE_LOCAL_ALG(name, algName, ialgFxns, idma3Fxns, iresFxns, \
                     groupId, memType, types) \
static Engine_AlgDesc  name = \
                                             \
    { algName,        /* name */             \
      {0},            /* uuid */             \
      ialgFxns,       /* ialgFxns */         \
      idma3Fxns,      /* idma3Fxns */        \
      NULL,           /* typeTab */          \
      TRUE,           /* isLocal */          \
      groupId,        /* groupId */          \
      0,              /* protocol */         \
      iresFxns,       /* iresFxns */         \
      NULL,           /* stub/skel params */ \
      memType,        /* cached mem type */  \
      types,           /* type - typeTab[0] will be used instead */ \
    };


/*
 *  ======== CE_BEGIN_ALG_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_END_ALG_TABLE() macro around
 *              CE_LOCAL_ALG() to generate an algorithm table for an engine.
 *
 *  @param[in]  name  A symbol used to generate internal variable names.
 *                    Use the same name in CE_END_ALG_TABLE(), and in
 *                    the call to CE_ENGINE(), to associate an engine
 *                    with this algorithm table.
 *
 *  @par Example Usage:
 *  @code
 *      CE_BEGIN_ALG_TABLE(engineAlgTab)
 *          CE_LOCAL_ALG(name_1, ...)
 *          CE_LOCAL_ALG(name_2, ...)
 *          ...
 *          CE_LOCAL_ALG(name_n, ...)
 *      CE_END_ALG_TABLE(engineAlgTab)
 *  @endcode
 *
 *  @sa CE_END_ALG_TABLE()
 *  @sa CE_ENGINE()
 */
#define CE_BEGIN_ALG_TABLE(name)        \
static Engine_AlgDesc CE_##name##_algs[] = {


/*
 *  ======== CE_END_ALG_TABLE ========
 */
/**
 *  @brief      Use this macro after CE_BEGIN_ALG_TABLE() and CE_LOCAL_ALG()
 *              for generating an algorithm table for an engine.
 *
 *  @param[in]  name  This must be the same symbol name passed to the
 *                    previous @c CE_BEGIN_ALG_TABLE() call.
 *
 *  @par Example Usage:
 *  @code
 *      CE_BEGIN_ALG_TABLE(engineAlgTab)
 *          CE_LOCAL_ALG(name_1, ...)
 *          CE_LOCAL_ALG(name_2, ...)
 *          ...
 *          CE_LOCAL_ALG(name_n, ...)
 *      CE_END_ALG_TABLE(engineAlgTab)
 *  @endcode
 *
 *  @sa CE_BEGIN_ALG_TABLE
 *  @sa CE_ENGINE
 */
#define CE_END_ALG_TABLE(name) \
    {NULL},                    \
};

/*
 *  ======== CE_ENGINE ========
 */
/**
 *  @brief      Generates a structure containing data for an engine.
 *
 *  @param[in]  algTab      Symbol to associate an alg table to this engine.
 *                          Use the name passed to CE_BEGIN_ALG_TABLE() to
 *                          associate that alg table with this engine.
 *  @param[in]  engName     The name of the engine to open
 *  @param[in]  serverName  The name of the Server image to load (if any).
 *                          On SysLink-based systems, this is the name of a
 *                          file and is passed unchanged to ProcMgr_Load().
 *  @param[in]  memMap      The name of a memory map (if any).
 *                          On SysLink-based systems, this file is used to
 *                          map slave memory into the MMU using ProcMgr_map().
 *  @param[in]  useExtLoader  Set to TRUE if an external loader will be used
 *                          to load the server.  If set to FALSE, Codec Engine
 *                          will load the server when the Engine is opened.
 *  @param[in]  heapId      Optional heap id to be used for this Engine. This
 *                          is used internally, for example, by Comm_alloc().
 *                          Use a value of 0 for heapId as the default.
 *
 *  @remarks    This macro must be called between the @c CE_BEGIN_ENGINE_TABLE()
 *              and @c CE_END_ENGINE_TABLE() macro calls.
 *
 *  @par Example Usage:
 *  @code
 *      CE_BEGIN_ENGINE_TABLE(name)
 *          CE_ENGINE(algTab_0, "engine_0", NULL, 0)
 *          CE_ENGINE(algTab_1, "engine_1", "server.x64P", 0)
 *      CE_END_ENGINE_TABLE(name)
 *  @endcode
 *
 *  @sa CE_BEGIN_ALG_TABLE
 *  @sa CE_BEGIN_ENGINE_TABLE
 */
#define CE_ENGINE(algTab, engName, serverName, memMap, useExtLoader, heapId) \
    { engName,            /* engine name */                      \
      CE_##algTab##_algs, /* alg table */                        \
      serverName,         /* optional server name */             \
      NULL,               /* memMap */                           \
      0,                  /* useExtLoader */                     \
      0,                  /* # of algs (filled in at runtime) */ \
      heapId              /* heapId */                           \
    },


/*
 *  ======== CE_BEGIN_ENGINE_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_END_ENGINE_TABLE() macro around
 *              CE_ENGINE() to generate an engine table for the application.
 *
 *              The usage is:
 *              CE_BEGIN_ENGINE_TABLE(name)
 *                  CE_ENGINE(algTab_1, ...)
 *                  CE_ENGINE(algTab_2, ...)
 *                  ...
 *                  CE_ENGINE(algTab_n, ...)
 *              CE_END_ENGINE_TABLE(name)
 *
 *  @param[in]  name  A symbol used to generate internal variable
 *                    names. Use the same name in CE_END_ENGINE_TABLE().
 *
 *  @sa CE_END_ENGINE_TABLE
 *  @sa CE_ENGINE
 */
#define CE_BEGIN_ENGINE_TABLE(name) \
static Engine_AlgDesc _localAlgs_000[] = {    \
    {NULL},                                   \
};                                            \
                                              \
static Engine_Desc name##_000[] = {

/*
 *  ======== CE_END_ENGINE_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_BEGIN_ENGINE_TABLE() macro around
 *              CE_ENGINE() to generate an engine table for the application.
 *
 *              The usage is:
 *              CE_BEGIN_ENGINE_TABLE(name)
 *                  CE_ENGINE(algTab_1, ...)
 *                  CE_ENGINE(algTab_2, ...)
 *                  ...
 *                  CE_ENGINE(algTab_n, ...)
 *              CE_END_ENGINE_TABLE(name)
 *
 *  @param[in]  name  A symbol used to generate internal variable
 *                    names. Use the same name in CE_BEGIN_ENGINE_TABLE().
 *
 *  @sa CE_BEGIN_ENGINE_TABLE
 *  @sa CE_ENGINE
 */
#define CE_END_ENGINE_TABLE(name)             \
    {"local",                                 \
     _localAlgs_000,                          \
     NULL,                                    \
     NULL,                                    \
     0,                                       \
    },                                        \
    {NULL, NULL, NULL, NULL, 0}               \
};                                            \
                                              \
Engine_Config Engine_config = {               \
    name##_000,                               \
    "local"                                   \
};

/*
 *  ======== CERuntime_exit ========
 */
/**
 *  @brief      Exit the Codec Engine Runtime.
 *
 *  @remarks    This function finalizes the Codec Engine modules used in
 *              the current configuration.
 *
 *  @sa         CERuntime_init()
 */
extern Void CERuntime_exit(Void);


/*
 *  ======== CERuntime_init ========
 */
/**
 *  @brief      Initialize the Codec Engine Runtime.
 *
 *  @remarks    This function must be called prior to using any Codec Engine
 *              APIs; it initializes all Codec Engine modules used in the
 *              the current configuration.
 *
 *  @remarks    Note that this must be called for both applications and
 *              [if applicable] Servers.
 *
 *  @remarks    For Servers, this is typically called from main().
 *
 *  @pre        For Servers, Ipc_start() must be called prior to calling
 *              CERuntime_init().  See the examples' main() implementation for
 *              reference.
 *
 *  @sa         CERuntime_exit()
 */
extern Void CERuntime_init(Void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:25; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ce_views_CodecEngine__include
#define ti_sdo_ce_views_CodecEngine__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ce_views_CodecEngine__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ce_views_CodecEngine___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ce/views/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* NODE_Uuid */
struct ti_sdo_ce_views_CodecEngine_NODE_Uuid {
    xdc_UInt32 data;
};

/* Engine_CachedMemType */
enum ti_sdo_ce_views_CodecEngine_Engine_CachedMemType {
    ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_DEFAULT = -1,
    ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_NONCACHED = 0,
    ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_CACHED = 1
};
typedef enum ti_sdo_ce_views_CodecEngine_Engine_CachedMemType ti_sdo_ce_views_CodecEngine_Engine_CachedMemType;

/* Engine_AlgDesc */
struct ti_sdo_ce_views_CodecEngine_Engine_AlgDesc {
    xdc_String name;
    ti_sdo_ce_views_CodecEngine_NODE_Uuid uuid;
    xdc_Ptr fxns;
    xdc_Ptr idmaFxns;
    xdc_String* typeTab;
    xdc_Bool isLocal;
    xdc_Int groupId;
    xdc_Int rpcProtocolVersion;
    xdc_Ptr iresFxns;
    xdc_Ptr codecClassConfig;
    ti_sdo_ce_views_CodecEngine_Engine_CachedMemType memType;
};

/* Engine_Desc */
struct ti_sdo_ce_views_CodecEngine_Engine_Desc {
    xdc_String name;
    ti_sdo_ce_views_CodecEngine_Engine_AlgDesc* algTab;
    xdc_String remoteName;
    xdc_String linkCfg;
    xdc_Int numAlgs;
    xdc_Int heapId;
};

/* Engine_Config */
struct ti_sdo_ce_views_CodecEngine_Engine_Config {
    ti_sdo_ce_views_CodecEngine_Engine_Desc* engineTab;
    xdc_String localEngine;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ce_views_CodecEngine_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__diagsEnabled ti_sdo_ce_views_CodecEngine_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ce_views_CodecEngine_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__diagsIncluded ti_sdo_ce_views_CodecEngine_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sdo_ce_views_CodecEngine_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__diagsMask ti_sdo_ce_views_CodecEngine_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ce_views_CodecEngine_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__gateObj ti_sdo_ce_views_CodecEngine_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ce_views_CodecEngine_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__gatePrms ti_sdo_ce_views_CodecEngine_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ce_views_CodecEngine_Module__id;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__id ti_sdo_ce_views_CodecEngine_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ce_views_CodecEngine_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerDefined ti_sdo_ce_views_CodecEngine_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ce_views_CodecEngine_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerObj ti_sdo_ce_views_CodecEngine_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn0 ti_sdo_ce_views_CodecEngine_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn1 ti_sdo_ce_views_CodecEngine_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn2 ti_sdo_ce_views_CodecEngine_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn4 ti_sdo_ce_views_CodecEngine_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__loggerFxn8 ti_sdo_ce_views_CodecEngine_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ce_views_CodecEngine_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Module__startupDoneFxn ti_sdo_ce_views_CodecEngine_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ce_views_CodecEngine_Object__count;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Object__count ti_sdo_ce_views_CodecEngine_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ce_views_CodecEngine_Object__heap;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Object__heap ti_sdo_ce_views_CodecEngine_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ce_views_CodecEngine_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Object__sizeof ti_sdo_ce_views_CodecEngine_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ce_views_CodecEngine_Object__table;
__extern __FAR__ const CT__ti_sdo_ce_views_CodecEngine_Object__table ti_sdo_ce_views_CodecEngine_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ce_views_CodecEngine_Module_startup( state ) -1

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ce_views_CodecEngine_Module__startupDone__S, "ti_sdo_ce_views_CodecEngine_Module__startupDone")
__extern xdc_Bool ti_sdo_ce_views_CodecEngine_Module__startupDone__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ce_views_CodecEngine_Module_startupDone() ti_sdo_ce_views_CodecEngine_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ce_views_CodecEngine_Object_heap() ti_sdo_ce_views_CodecEngine_Object__heap__C

/* Module_heap */
#define ti_sdo_ce_views_CodecEngine_Module_heap() ti_sdo_ce_views_CodecEngine_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ce_views_CodecEngine_Module__id ti_sdo_ce_views_CodecEngine_Module_id( void ) 
{
    return ti_sdo_ce_views_CodecEngine_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ce_views_CodecEngine_Module_hasMask( void ) 
{
    return ti_sdo_ce_views_CodecEngine_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ce_views_CodecEngine_Module_getMask( void ) 
{
    return ti_sdo_ce_views_CodecEngine_Module__diagsMask__C != NULL ? *ti_sdo_ce_views_CodecEngine_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ce_views_CodecEngine_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ce_views_CodecEngine_Module__diagsMask__C != NULL) *ti_sdo_ce_views_CodecEngine_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ce_views_CodecEngine__top__
#undef __nested__
#endif

#endif /* ti_sdo_ce_views_CodecEngine__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ce_views_CodecEngine__internalaccess))

#ifndef ti_sdo_ce_views_CodecEngine__include_state
#define ti_sdo_ce_views_CodecEngine__include_state


#endif /* ti_sdo_ce_views_CodecEngine__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ce_views_CodecEngine__nolocalnames)

#ifndef ti_sdo_ce_views_CodecEngine__localnames__done
#define ti_sdo_ce_views_CodecEngine__localnames__done

/* module prefix */
#define CodecEngine_NODE_Uuid ti_sdo_ce_views_CodecEngine_NODE_Uuid
#define CodecEngine_Engine_CachedMemType ti_sdo_ce_views_CodecEngine_Engine_CachedMemType
#define CodecEngine_Engine_AlgDesc ti_sdo_ce_views_CodecEngine_Engine_AlgDesc
#define CodecEngine_Engine_Desc ti_sdo_ce_views_CodecEngine_Engine_Desc
#define CodecEngine_Engine_Config ti_sdo_ce_views_CodecEngine_Engine_Config
#define CodecEngine_Engine_USECACHEDMEM_DEFAULT ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_DEFAULT
#define CodecEngine_Engine_USECACHEDMEM_NONCACHED ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_NONCACHED
#define CodecEngine_Engine_USECACHEDMEM_CACHED ti_sdo_ce_views_CodecEngine_Engine_USECACHEDMEM_CACHED
#define CodecEngine_Module_name ti_sdo_ce_views_CodecEngine_Module_name
#define CodecEngine_Module_id ti_sdo_ce_views_CodecEngine_Module_id
#define CodecEngine_Module_startup ti_sdo_ce_views_CodecEngine_Module_startup
#define CodecEngine_Module_startupDone ti_sdo_ce_views_CodecEngine_Module_startupDone
#define CodecEngine_Module_hasMask ti_sdo_ce_views_CodecEngine_Module_hasMask
#define CodecEngine_Module_getMask ti_sdo_ce_views_CodecEngine_Module_getMask
#define CodecEngine_Module_setMask ti_sdo_ce_views_CodecEngine_Module_setMask
#define CodecEngine_Object_heap ti_sdo_ce_views_CodecEngine_Object_heap
#define CodecEngine_Module_heap ti_sdo_ce_views_CodecEngine_Module_heap

#endif /* ti_sdo_ce_views_CodecEngine__localnames__done */
#endif

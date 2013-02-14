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
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sdo_ce_utils_syscbuf_SysCBuf__include
#define ti_sdo_ce_utils_syscbuf_SysCBuf__include

#ifndef __nested__
#define __nested__
#define ti_sdo_ce_utils_syscbuf_SysCBuf__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sdo_ce_utils_syscbuf_SysCBuf___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sdo/ce/utils/syscbuf/package/package.defs.h>

#include <xdc/runtime/ISystemSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* OutputFxn */
typedef xdc_Void (*ti_sdo_ce_utils_syscbuf_SysCBuf_OutputFxn)(xdc_Char*, xdc_UInt);


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Module_State */
typedef xdc_Char __T1_ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__outbuf;
typedef xdc_Char *__ARRAY1_ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__outbuf;
typedef __ARRAY1_ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__outbuf __TA_ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__outbuf;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsEnabled ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsIncluded ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gateObj;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gateObj ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gatePrms;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gatePrms ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerDefined;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerDefined ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerObj;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerObj ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn0 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn1 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn2 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn4 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn8 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDoneFxn ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__count;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__count ti_sdo_ce_utils_syscbuf_SysCBuf_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__heap;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__heap ti_sdo_ce_utils_syscbuf_SysCBuf_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__sizeof;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__sizeof ti_sdo_ce_utils_syscbuf_SysCBuf_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__table;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Object__table ti_sdo_ce_utils_syscbuf_SysCBuf_Object__table__C;

/* bufSize */
#ifdef ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize__D
#define ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize (ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize__D)
#else
#define ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize (ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize__C)
typedef xdc_SizeT CT__ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize__C;
#endif

/* flushAtExit */
#ifdef ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit__D
#define ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit (ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit__D)
#else
#define ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit (ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit__C)
typedef xdc_Bool CT__ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit__C;
#endif

/* outputFxn */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn (ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn__C)
typedef ti_sdo_ce_utils_syscbuf_SysCBuf_OutputFxn CT__ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn__C;

/* outputFunc */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc (ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc__C)
typedef ti_sdo_ce_utils_syscbuf_SysCBuf_OutputFxn CT__ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc;
__extern __FAR__ const CT__ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sdo_ce_utils_syscbuf_SysCBuf_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*abort)(xdc_String);
    xdc_Void (*exit)(xdc_Int);
    xdc_Void (*flush)(void);
    xdc_Void (*putch)(xdc_Char);
    xdc_Bool (*ready)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_sdo_ce_utils_syscbuf_SysCBuf_Fxns__ ti_sdo_ce_utils_syscbuf_SysCBuf_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup")
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup")
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__F( xdc_Int state );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__R, "ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup")
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__R( xdc_Int state );

/* Module__startupDone__S */
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDone__S, "ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDone")
__extern xdc_Bool ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDone__S( void );

/* abort__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_abort ti_sdo_ce_utils_syscbuf_SysCBuf_abort__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_abort__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_abort")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_abort__E( xdc_String str );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_abort__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_abort")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_abort__F( xdc_String str );
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_abort__R( xdc_String str );

/* exit__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_exit ti_sdo_ce_utils_syscbuf_SysCBuf_exit__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_exit__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_exit")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_exit__E( xdc_Int stat );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_exit__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_exit")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_exit__F( xdc_Int stat );
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_exit__R( xdc_Int stat );

/* flush__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_flush ti_sdo_ce_utils_syscbuf_SysCBuf_flush__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_flush__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_flush")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_flush__E( void );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_flush__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_flush")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_flush__F( void );
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_flush__R( void );

/* putch__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_putch ti_sdo_ce_utils_syscbuf_SysCBuf_putch__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_putch__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_putch")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_putch__E( xdc_Char ch );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_putch__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_putch")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_putch__F( xdc_Char ch );
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_putch__R( xdc_Char ch );

/* ready__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_ready ti_sdo_ce_utils_syscbuf_SysCBuf_ready__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_ready__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_ready")
__extern xdc_Bool ti_sdo_ce_utils_syscbuf_SysCBuf_ready__E( void );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_ready__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_ready")
__extern xdc_Bool ti_sdo_ce_utils_syscbuf_SysCBuf_ready__F( void );
__extern xdc_Bool ti_sdo_ce_utils_syscbuf_SysCBuf_ready__R( void );

/* bind__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_bind ti_sdo_ce_utils_syscbuf_SysCBuf_bind__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_bind__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_bind")
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_bind__E( xdc_Char* buf, xdc_UInt32 size );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_bind__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_bind")
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_bind__F( xdc_Char* buf, xdc_UInt32 size );
__extern xdc_Int ti_sdo_ce_utils_syscbuf_SysCBuf_bind__R( xdc_Char* buf, xdc_UInt32 size );

/* get__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_get ti_sdo_ce_utils_syscbuf_SysCBuf_get__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_get__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_get")
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_get__E( xdc_Char* buf, xdc_UInt32 size, xdc_UInt32* avail, xdc_UInt32* lost );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_get__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_get")
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_get__F( xdc_Char* buf, xdc_UInt32 size, xdc_UInt32* avail, xdc_UInt32* lost );
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_get__R( xdc_Char* buf, xdc_UInt32 size, xdc_UInt32* avail, xdc_UInt32* lost );

/* getSize__E */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_getSize ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__E
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__E, "ti_sdo_ce_utils_syscbuf_SysCBuf_getSize")
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__E( void );
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__F, "ti_sdo_ce_utils_syscbuf_SysCBuf_getSize")
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__F( void );
__extern xdc_UInt32 ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__R( void );

/* output__I */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_output ti_sdo_ce_utils_syscbuf_SysCBuf_output__I
xdc__CODESECT(ti_sdo_ce_utils_syscbuf_SysCBuf_output__I, "ti_sdo_ce_utils_syscbuf_SysCBuf_output")
__extern xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_output__I( xdc_Char* buf, xdc_UInt size );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_ISystemSupport_Module ti_sdo_ce_utils_syscbuf_SysCBuf_Module_upCast( void )
{
    return (xdc_runtime_ISystemSupport_Module)&ti_sdo_ce_utils_syscbuf_SysCBuf_Module__FXNS__C;
}

/* Module_to_xdc_runtime_ISystemSupport */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Module_to_xdc_runtime_ISystemSupport ti_sdo_ce_utils_syscbuf_SysCBuf_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startupDone() ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDone__S()

/* Object_heap */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Object_heap() ti_sdo_ce_utils_syscbuf_SysCBuf_Object__heap__C

/* Module_heap */
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Module_heap() ti_sdo_ce_utils_syscbuf_SysCBuf_Object__heap__C

/* Module_id */
static inline CT__ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id ti_sdo_ce_utils_syscbuf_SysCBuf_Module_id( void ) 
{
    return ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sdo_ce_utils_syscbuf_SysCBuf_Module_hasMask( void ) 
{
    return ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sdo_ce_utils_syscbuf_SysCBuf_Module_getMask( void ) 
{
    return ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C != NULL ? *ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_sdo_ce_utils_syscbuf_SysCBuf_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C != NULL) *ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sdo_ce_utils_syscbuf_SysCBuf__top__
#undef __nested__
#endif

#endif /* ti_sdo_ce_utils_syscbuf_SysCBuf__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sdo_ce_utils_syscbuf_SysCBuf__internalaccess))

#ifndef ti_sdo_ce_utils_syscbuf_SysCBuf__include_state
#define ti_sdo_ce_utils_syscbuf_SysCBuf__include_state

/* Module_State */
struct ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State {
    __TA_ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__outbuf outbuf;
    xdc_UInt outidx;
    xdc_Bool wrapped;
    xdc_UInt32 bufSize;
};

/* Module__state__V */
extern struct ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State__ ti_sdo_ce_utils_syscbuf_SysCBuf_Module__state__V;

#endif /* ti_sdo_ce_utils_syscbuf_SysCBuf__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sdo_ce_utils_syscbuf_SysCBuf__nolocalnames)

#ifndef ti_sdo_ce_utils_syscbuf_SysCBuf__localnames__done
#define ti_sdo_ce_utils_syscbuf_SysCBuf__localnames__done

/* module prefix */
#define SysCBuf_OutputFxn ti_sdo_ce_utils_syscbuf_SysCBuf_OutputFxn
#define SysCBuf_Module_State ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State
#define SysCBuf_bufSize ti_sdo_ce_utils_syscbuf_SysCBuf_bufSize
#define SysCBuf_flushAtExit ti_sdo_ce_utils_syscbuf_SysCBuf_flushAtExit
#define SysCBuf_outputFxn ti_sdo_ce_utils_syscbuf_SysCBuf_outputFxn
#define SysCBuf_outputFunc ti_sdo_ce_utils_syscbuf_SysCBuf_outputFunc
#define SysCBuf_abort ti_sdo_ce_utils_syscbuf_SysCBuf_abort
#define SysCBuf_exit ti_sdo_ce_utils_syscbuf_SysCBuf_exit
#define SysCBuf_flush ti_sdo_ce_utils_syscbuf_SysCBuf_flush
#define SysCBuf_putch ti_sdo_ce_utils_syscbuf_SysCBuf_putch
#define SysCBuf_ready ti_sdo_ce_utils_syscbuf_SysCBuf_ready
#define SysCBuf_bind ti_sdo_ce_utils_syscbuf_SysCBuf_bind
#define SysCBuf_get ti_sdo_ce_utils_syscbuf_SysCBuf_get
#define SysCBuf_getSize ti_sdo_ce_utils_syscbuf_SysCBuf_getSize
#define SysCBuf_Module_name ti_sdo_ce_utils_syscbuf_SysCBuf_Module_name
#define SysCBuf_Module_id ti_sdo_ce_utils_syscbuf_SysCBuf_Module_id
#define SysCBuf_Module_startup ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup
#define SysCBuf_Module_startupDone ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startupDone
#define SysCBuf_Module_hasMask ti_sdo_ce_utils_syscbuf_SysCBuf_Module_hasMask
#define SysCBuf_Module_getMask ti_sdo_ce_utils_syscbuf_SysCBuf_Module_getMask
#define SysCBuf_Module_setMask ti_sdo_ce_utils_syscbuf_SysCBuf_Module_setMask
#define SysCBuf_Object_heap ti_sdo_ce_utils_syscbuf_SysCBuf_Object_heap
#define SysCBuf_Module_heap ti_sdo_ce_utils_syscbuf_SysCBuf_Module_heap
#define SysCBuf_Module_upCast ti_sdo_ce_utils_syscbuf_SysCBuf_Module_upCast
#define SysCBuf_Module_to_xdc_runtime_ISystemSupport ti_sdo_ce_utils_syscbuf_SysCBuf_Module_to_xdc_runtime_ISystemSupport

#endif /* ti_sdo_ce_utils_syscbuf_SysCBuf__localnames__done */
#endif

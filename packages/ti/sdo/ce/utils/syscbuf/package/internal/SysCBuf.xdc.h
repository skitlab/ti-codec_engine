/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

#ifndef ti_sdo_ce_utils_syscbuf_SysCBuf__INTERNAL__
#define ti_sdo_ce_utils_syscbuf_SysCBuf__INTERNAL__

#ifndef ti_sdo_ce_utils_syscbuf_SysCBuf__internalaccess
#define ti_sdo_ce_utils_syscbuf_SysCBuf__internalaccess
#endif

#include <ti/sdo/ce/utils/syscbuf/SysCBuf.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* abort */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_abort
#define ti_sdo_ce_utils_syscbuf_SysCBuf_abort ti_sdo_ce_utils_syscbuf_SysCBuf_abort__F

/* exit */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_exit
#define ti_sdo_ce_utils_syscbuf_SysCBuf_exit ti_sdo_ce_utils_syscbuf_SysCBuf_exit__F

/* flush */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_flush
#define ti_sdo_ce_utils_syscbuf_SysCBuf_flush ti_sdo_ce_utils_syscbuf_SysCBuf_flush__F

/* putch */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_putch
#define ti_sdo_ce_utils_syscbuf_SysCBuf_putch ti_sdo_ce_utils_syscbuf_SysCBuf_putch__F

/* ready */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_ready
#define ti_sdo_ce_utils_syscbuf_SysCBuf_ready ti_sdo_ce_utils_syscbuf_SysCBuf_ready__F

/* bind */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_bind
#define ti_sdo_ce_utils_syscbuf_SysCBuf_bind ti_sdo_ce_utils_syscbuf_SysCBuf_bind__F

/* get */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_get
#define ti_sdo_ce_utils_syscbuf_SysCBuf_get ti_sdo_ce_utils_syscbuf_SysCBuf_get__F

/* getSize */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_getSize
#define ti_sdo_ce_utils_syscbuf_SysCBuf_getSize ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__F

/* output */
#define SysCBuf_output ti_sdo_ce_utils_syscbuf_SysCBuf_output__I

/* Module_startup */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup ti_sdo_ce_utils_syscbuf_SysCBuf_Module_startup__F

/* Instance_init */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_init
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_init ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_init__F

/* Instance_finalize */
#undef ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_finalize
#define ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_finalize ti_sdo_ce_utils_syscbuf_SysCBuf_Instance_finalize__F

/* module */
#define SysCBuf_module ((ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State *)(xdc__MODOBJADDR__(ti_sdo_ce_utils_syscbuf_SysCBuf_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sdo_ce_utils_syscbuf_SysCBuf__cplusplus)
#define module ((ti_sdo_ce_utils_syscbuf_SysCBuf_Module_State *)(xdc__MODOBJADDR__(ti_sdo_ce_utils_syscbuf_SysCBuf_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_ce_utils_syscbuf_SysCBuf_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_ce_utils_syscbuf_SysCBuf_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_ce_utils_syscbuf_SysCBuf_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_ce_utils_syscbuf_SysCBuf_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_ce_utils_syscbuf_SysCBuf_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_ce_utils_syscbuf_SysCBuf_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_ce_utils_syscbuf_SysCBuf_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_ce_utils_syscbuf_SysCBuf_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_ce_utils_syscbuf_SysCBuf_Module_GateProxy_query


#endif /* ti_sdo_ce_utils_syscbuf_SysCBuf__INTERNAL____ */

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
/**
 *  @file       ti/sdo/ce/global/CESettings.h
 *
 *  @brief      Codec Engine global settings interface.
 */

/**
 *  @defgroup   ti_sdo_ce_global_CESettings
 *   
 */

#ifndef ti_sdo_ce_global_CESETTINGS_H
#define ti_sdo_ce_global_CESETTINGS_H

/** @ingroup    ti_sdo_ce_global */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Name passed to Diags_setMask() for logging. This is used
 *              internal by CE components to determine how to initialize
 *              their Diags masks. The application can use this to set
 *              default Diags mask values for CE components by adding the
 *              following code before CE comonents are initialized. For
 *              exaple:
 *
 *              #include <xdc/std.h>
 *              #include <xdc/runtime/Diags.h>
 *              #include <xdc/runtime/Registry.h>
 *
 *              #include <ti/sdo/ce/global/CESettings.h>
 *
 *              main()
 *              {
 *                  CESettings_init();
 *
 *                  // Enable all logging by default
 *                  Diags_setMask(CESETTINGS_MODNAME"+EX1234567");
 *
 *                  // Initialize after setting Diags mask for CESettings,
 *                  // so we get log output for CERuntime_init().
 *                  CERuntime_init();
 *               }
 *
 * @sa CESettings_init()
 */
#define CESETTINGS_MODNAME "ti.sdo.ce.global.CESettings"

/**
 *  @brief      De-initialize global settings
 *
 */
Void CESettings_exit();

/**
 *  @brief      Initialize global settings
 *
 */
Void CESettings_init();

/** @cond INTERNAL */
/*
 *  ======== CESettings_getDiags ========
 */
/**
 *  @brief      Get the string that corresponds to the bits set in the Diags
 *              mask of CESettings. For example, if Diags_ENTRY and Diags_USER1
 *              are enabled, this function returns "+E1"
 *
 *  @param[in]  curControl  Location to copy Diags string
 *  @param[in]  size        Length of curControl (bytes).
 *
 *  @pre        @c size must be >= 11 (For null-termintated "+EX1234567")
 */
Void CESettings_getDiags(String curControl, Int size);

/*
 *  ======== CESettings_setDiags ========
 */
/**
 *  @brief      Set the Diags mask for the module 'modName', based on the
 *              Diags mask for CESettings. For example, if CESettings has
 *              Diags_ENTRY and Diags_USER1 enabled, this function sets
 *              the Diags for modName to "+E1"
 *
 *  @param[in]  modName    Name of the module to set Diags mask for.
 *
 *  @pre        The string @c modName must not be longer than 128 characters
 */
Void CESettings_setDiags(String modName);

/** @cond INTERNAL */

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/
#endif  /* ti_sdo_ce_global_CESETTINGS_H */

/*
 *  @(#) ti.sdo.ce.global; 1, 0, 0,1; 2-24-2012 19:29:48; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


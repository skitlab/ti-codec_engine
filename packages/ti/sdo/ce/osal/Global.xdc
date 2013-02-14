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

/*!
 *  ======== Global ========
 *  Global OS Abstract Layer Configuration
 */
@Template("./Global.xdt")

metaonly module Global {

    /*!
     *  ======== os ========
     *  A specific OSAL implementations "Settings" module, for example,
     *  ti.sdo.ce.osal.bios.Settings or ti.sdo.ce.osal.linux.Settings.
     *  To set the OS of the executable to BIOS, set Global.os to:
     *  xdc.useModule('ti.sdo.ce.osal.bios.Settings').
     *
     *  When this config param is used, the {@ link ti.sdo.ce.ipc.Settings#ipc
     *  config param must also be set.
     *
     *  This should only be used to explicitly configure the OSAL to
     *  a package not provided with Codec Engine.  To use an OSAL provided
     *  by Codec Engine, it's recommended to configure the OSAL using
     *  the runtimeEnv config param instead of this one.
     *
     *  See {@ link http://wiki.davincidsp.com/index.php?title=CE_Config_Updates
     *  for more details}
     *
     *  @see runtimeEnv
     */
    config IOsal.Module os;

    /*!
     *  ======== RuntimeOS ========
     *  All runtime OSs that are abstracted by this package.
     *
     *  @see runtimeEnv
     */
    enum RuntimeEnv {
        NONE          = 0,   /*! no OS; threads are not truly supported */
        DSPBIOS       = 1,   /*! DSP/BIOS  */
        LINUX         = 2,   /*! Linux */
        DSPLINK_BIOS  = 3,   /*! DSPLINK + BIOS (DSP) */
        DSPLINK_LINUX = 4,   /*! DSPLINK + Linux (ARM) */
        WINCE         = 5,   /*! Windows CE */
        DSPLINK_WINCE = 6    /*! DSPLINK + Windows CE (ARM) */
    };

    /*!
     *  ======== runtimeEnv ========
     *  The runtime OS used to implement the abstractions provided by
     *  this package.
     *
     *  @see RuntimeEnv
     */
    config RuntimeEnv runtimeEnv;

    /*!
     *  ======== skipVirtualAddressTranslation ========
     *  If set to true, will make Memory_getBufferPhysicalAddress()
     *  skip address translation and return the given address as the
     *  physical address. Needed when the VISA calls are made with
     *  physical buffer addresses instead of virtual ones, specifically
     *  in the multi-process-via-kernel-driver case.
     *
     *  Applies only to environments where virtual memory is used (e.g. Linux)
     *  @_nodoc
     */
    config bool skipVirtualAddressTranslation = false;

    /*!
     *  ======== embedBuildInfo ========
     *  Indication whether to embed build info (packages and their directories)
     *  into the generated executable for debugging/diagnostic purposes.
     *  Setting this to 'false' may reduce the static data size by around 1K.
     *  Applies to all configurations.
     */
    config Bool embedBuildInfo = true;

    /*!
     *  ======== addObjectToProgramInfoFile ========
     *  Internal method for adding an object to an XML-like program info file
     *  created alongside the executable
     * @_nodoc
     */
    function addObjectToProgramInfoFile( objName, obj );

    /*!
     *  ======== parseInfoFile ========
     *  Internal method for parsing an XML-like server program file
     *  that lies alongside the executable
     * @_nodoc
     */
    function parseInfoFile( infoFile );

    /*!
     *  ======== validate ========
     *  Internal validate method (see package.xs)
     * @_nodoc
     */
    function validate();

}
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:12; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
//    print(this.$name + ".close() ...");
    var ipc = this.Ipc;
    var prog = Program;

    this.Processor.close();

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

//    print(this.$name + ".close(): useLinkArbiter: " + ipc.useLinkArbiter);
    //xdc.loadPackage('ti.sdo.ce.ipc');

    // This module requires ipc.Settings, osal.Global, and osal.linux
    xdc.useModule('ti.sdo.ce.ipc.Settings');
    xdc.useModule('ti.sdo.ce.osal.Global');
    xdc.useModule('ti.sdo.xdcruntime.linux.Settings');
    xdc.useModule('xdc.runtime.knl.Thread');
    xdc.useModule('xdc.runtime.knl.SemThread');
    xdc.loadPackage('ti.syslink');

    /* if unset by application config script, set default value here */
    if (ipc.usePowerManagement == undefined) {
// No LPM support yet (unclear if we'll ever restore it with SysLink)
//        if (Program.cpu.deviceName.match(/^TMS320C3430$|^OMAP[23]530$/)) {
//            ipc.usePowerManagement = true;
//        }
//        else {
            ipc.usePowerManagement = false;
//        }
    }

    /* No power mgmt supported(!) */
    if (ipc.usePowerManagement) {
        ipc.$logWarning("usePowerManagement not supported.  Disabling " +
                "user specified assignment to 'true'.", ipc,
                "usePowerManagement");
        ipc.usePowerManagement = false;
    }

    /* Optionally load and configure power management module */
    if (ipc.usePowerManagement) {
        var power = null;

        if (Program.cpu.deviceName.match(/^TMS320CDM6441$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6441GPP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320CDM6446$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6446GPP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP2530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP2530GPP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320C3430$/)) {
            power = xdc.useModule('ti.bios.power.TMS320C3430GPP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP3530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP3530GPP');
        }
        else {
            print("Warning: GPP ti.bios.power doesn't support: " +
                Program.cpu.deviceName + "\n");
        }

        if (power != null) {
            power.opersys = power.Opersys_Linux;
            power.transport = power.Transport_Link_Linux;
        }
    }

    /* optionally load the LAD communication wrapper module */
    if (ipc.useLinkArbiter) {
        var lad = xdc.loadPackage('ti.dsplink.utils.ladclient');
    }

//    print(this.$name + ".close() done!");
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    var settings = this.Ipc;
    for (var iserver = 0; iserver < settings.linkConfigs.length; iserver++ ) {
        var linkConfig = settings.linkConfigs[iserver];

        if ((linkConfig.linkCfg.doPowerControl == true) &&
            (linkConfig.linkCfg.dspManagement == settings.None)) {

            print(this.$name + ".validate() ...");
            throw "Error: invalid combination of doPowerControl=true & dspManagement=None";
        }
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        /* no matching lib found in this package, return "" */
        $trace("Unable to locate a compatible library, returning none.",
                1, ['getLibs']);
        return ("");
    }

    var lib = "lib/" + this.profile + "/ipc_syslink.a" + suffix;

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    var file = new java.io.File(this.packageBase + '/' + lib);
    if (!file.exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        lib = "lib/release/ipc_syslink.a" + suffix;
    }

    return (lib);
}


/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,1; 2-24-2012 19:30:04; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
    var prog = Program;
    var global = this.Global;

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    /*  Ensure that either .runtimeEnv or .os is set, but not both. */
    if ((global.runtimeEnv != null) && (global.os != null)) {

        throw(this.$name + ":  Setting both Global.runtimeEnv and " +
                "Global.os is not supported.  Modify your config " +
                "script to set either the .runtimeEnv (preferred) or the " +
                ".os fields.\nFor more info, see " +
                "http://tiexpressdsp.com/index.php/CE_Config_Updates\n");
    }

    /* if neither .runtimeEnv nor .os is set, choose one */
    if ((global.runtimeEnv == null) && (global.os == null)) {
        throw(this.$name + ":  Misconfigured OSAL.  Modify your config " +
                "script to set either the .runtimeEnv (preferred) or the " +
                ".os fields.\nFor more info, see " +
                "http://tiexpressdsp.com/index.php/CE_Config_Updates\n");
    }

    /*
     *  If OS has been set to DSPBIOS or DSPLINK_BIOS through Global, and
     *  Global.os has not been set, load the osal bios module and configure
     *  it. This is need for backwards compatibility.
     */
    if ((global.runtimeEnv == global.DSPBIOS) ||
            (global.runtimeEnv == global.DSPLINK_BIOS)) {

        assert(global.os == null, this.$name +
                ".Global.runtimeEnv set to BIOS, but .Global.os != null");

        var biosSettings = xdc.useModule('ti.sdo.ce.osal.bios.Settings');
        global.os = biosSettings;

// Do we need this for BIOS 6?
//        /* for other segments left undefined, use the default segment */
//        if (global.logSeg == null) {
//            global.logSeg = global.defaultMemSegId;
//        }
//
//        if (global.powerSaveMemoryBlockName == null) {
//            global.powerSaveMemoryBlockName = global.defaultMemSegId;
//        }
    }

    /*
     *  If OS is LINUX or DSPLINK_LINUX, and was set through global.runtimeEnv
     *  rather than through global.os, set global.os to linux, and pass
     *  global's linux-specific settings to linux os module.
     */
    if ((global.runtimeEnv == global.LINUX) ||
             (global.runtimeEnv == global.DSPLINK_LINUX)) {

        assert(global.os == null, this.$name +
                ".Global.runtimeEnv set to LINUX, but .Global.os != null");

        var linuxSettings = xdc.useModule('ti.sdo.ce.osal.linux.Settings');
        global.os = linuxSettings;

        if (global.runtimeEnv == global.DSPLINK_LINUX) {
            xdc.useModule('ti.sdo.ce.ipc.dsplink.Processor');
            var ipcSettings = xdc.useModule('ti.sdo.ce.ipc.Settings');
            ipcSettings.ipc = xdc.useModule('ti.sdo.ce.ipc.dsplink.Ipc');
        }
    }

    if ((global.runtimeEnv == global.WINCE) ||
            (global.runtimeEnv == global.DSPLINK_WINCE)) {

        assert(global.os == null, this.$name +
                ".Global.runtimeEnv set to WINCE, but .Global.os != null");

        var winceOS = xdc.useModule('ti.sdo.ce.osal.wince.Settings');
        global.os = winceOS;
    }

    if (global.runtimeEnv == global.NONE) {

        assert(global.os == null, this.$name +
                ".Global.runtimeEnv set to NONE, but .Global.os != null");

        var noOS = xdc.useModule('ti.sdo.ce.osal.noOS.Settings');
        global.os = noOS;
    }

    /*
     *  Establish dependency on OS package. The name of the OS package is
     *  assumed to be the full path name of the os up to the os module
     *  name (eg, for 'ti.sdo.ce.osal.bios.Settings', it is
     *  'ti.sdo.ce.osal.bios').
     */
    var osPkg = global.os.$name;
    osPkg = osPkg.substring(0, osPkg.lastIndexOf("."));
    //print("os package name: " + osPkg);
    xdc.loadPackage(osPkg);
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    /* must be called at the very end */
//    this.Global.validate();
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

    /* the location of the libraries are in lib/<profile>/* */
    var lib = "lib/" + this.profile + "/osal.a" + suffix;

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    if (!java.io.File(this.packageBase + lib).exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        lib = "lib/release/osal.a" + suffix;
    }

    return (lib);
}


/*
 *  ======== assert ========
 *  Assertion checks.
 */
function assert(fCheck, msg)
{
    if (!fCheck) {
        throw("INTERNAL ASSERTION FAILURE:  " + msg);
    }
}


/*
 *  ======== warn ========
 *  For warnings that we may not really want to print.
 */
function warn(msg)
{
    print("WARN:  " + msg);
}

/*
 *  ======== trace ========
 */
function trace(msg)
{
//    print("TRACE:  " + msg);
}
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:13; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


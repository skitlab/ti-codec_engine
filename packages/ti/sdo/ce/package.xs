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
    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Diags');
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Timestamp');
    xdc.useModule('xdc.runtime.Registry');
    xdc.useModule('xdc.runtime.Memory');

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    /* establish dependency on XDAIS and NODE since we #include their headers */
    xdc.loadPackage('ti.xdais');
    xdc.loadPackage('ti.sdo.ce.node');

    /* CERuntime.xdt [at least] requires these packages */
    xdc.loadPackage('ti.sdo.ce.global');
    xdc.loadPackage('ti.sdo.fc.global');

    /* if there's a Server in the system, we need the NODE module */
    if (this.Server.$used) {
        xdc.useModule('ti.sdo.ce.node.NODE');
    }
    this.Server.close();
    this.Engine.close();

    var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    /*
     * CE Runtime needs gates (formerly, Lock) and Thread. osal sets the Proxy
     */
    var Gate = xdc.useModule('xdc.runtime.Gate');
    xdc.useModule('xdc.runtime.knl.Thread');
    xdc.useModule('xdc.runtime.knl.GateThread');

    var os = Program.build.target.os;
    if (os == "Linux") {
        xdc.useModule('ti.sdo.xdcruntime.linux.Settings');
    }
    else if (os == undefined) {
        /* assume bios 6 */
        xdc.useModule('ti.sysbios.xdcruntime.Settings');

        // Engine.c unconditionally binds to Processor_* APIs
        xdc.useModule('ti.sdo.ce.ipc.bios.Processor');
    }
    else {
        print(this.$name + "close(): WARNING: Gate proxy was not " +
                "configured and no default was "
                + "known for the target OS");
    }

    /*
     *  Bring in this module for RMS control calls to logger. Either user
     *  will configure the proxy in the config file, or it will be set to
     *  LoggerMFPNull.
     */
    xdc.useModule('ti.sdo.utils.loggers.LogMFP');

    /*
     *  CE requires ipc to be set (CERuntime_init() calls Processor_init()
     *  and Comm_init()). If ce.ipc.Settings.ipc has not been set, try to
     *  set it here.
     */
    var ipcSettings = xdc.useModule('ti.sdo.ce.ipc.Settings');
    if (ipcSettings.ipc == undefined) {
        var ipcName = null;
        if (Program.build.target.os == "Linux") {
            // NOTE: Engine.close() would have already set ipc to dsplink if
            // there were remote algorithms, so we wouldn't be here in that
            // case.
            ipcName = "ti.sdo.ce.ipc.linux.Ipc";
        }
        else {
            // Q: what makes a DSP target? A: name starts with "C".
            // may not be true in the future, but this is just to
            // forgive those who didn't set ipc.Settings.ipc anyway.
            if (Program.build.target.os == undefined) {
//            if ((Program.build.target.name + "").match(/^C/) != null) {
                ipcName = "ti.sdo.ce.ipc.bios.Ipc";

                if (osalGlobal.runtimeEnv == osalGlobal.DSPLINK_BIOS) {
                    // Bring in this module for DSPLink
                    xdc.useModule('ti.sdo.ce.ipc.dsplink.dsp.Settings');
                }
                else if (osalGlobal.runtimeEnv == osalGlobal.DSPBIOS) {
                    // Bring in dependencies
//                    xdc.useModule('ti.sdo.ce.ipc.bios.Processor');
                }
            }
            else {
                ipcName = "ti.sdo.ce.ipc.noOS.Ipc";
            }
        }

        warn(this.$name + ".close()- " +
                "WARNING: Your application .cfg script does not specify " +
                "the ipc for this engine. Will set to *** " + ipcName +
                " ***. You should set this in your cfg file, if this is not " +
                "what you want. eg, Add the following to your .cfg script: ");
        warn("var ipcSettings = xdc.useModule(\'ti.sdo.ce.ipc.Settings\');");
        warn("ipcSettings.ipc = xdc.useModule(\'" + ipcName + "\');");

        warn("Setting ipc to " + ipcName);
        ipcSettings.ipc = xdc.useModule(ipcName);
    }

    /* unconditionally establish a dependency on 'ti.sdo.ce.alg' */
    var algSettings = xdc.useModule('ti.sdo.ce.alg.Algorithm');

    // For all local algorithms, set algSettings.groupUsed[i] = true, if the
    // alg's groupId is i.
    var engines = this.Engine.$instances;
    //print(this.$name + ".close(): Num engines = " + engines.length);
    for (var i = 0; i < engines.length; i++) {
        var eng = engines[i];
        var algs = eng.algs;

        //print(eng.name + ": Num algs = " + algs.length);
        for (var j = 0; j < algs.length; j++) {
            var alg = algs[j];
            if (alg.local) {
                if (algs[j].groupId == undefined) {
                    //print("Local alg " + alg.name + " groupId undefined.");
                }
                if ((alg.groupId >= 0) &&
                         (alg.groupId < algSettings.MAXGROUPID)) {
                    //print("Setting alg.Setting.groupUsed[" + alg.groupId +
                    //        "] to true");
                    algSettings.groupUsed[alg.groupId] = true;
                }
            }
        }
    }

    if (this.Engine.usesIDMA3()) {
        trace("THIS APP USES IDMA3 AND MUST BE BUILT WITH FC");
        algSettings.useIdma3 = true;
    }
    else {
        algSettings.useIdma3 = false;
    }

    if (this.Engine.usesIRES()) {
        trace("THIS APP USES IRES AND MUST BE BUILT WITH FC");
        algSettings.useIres = true;
    }
    else {
        algSettings.useIres = false;
    }

    xdc.loadPackage('ti.sdo.ce.utils.xdm');

    xdc.useModule('ti.sdo.ce.Settings');

    if (this.Server.traceBufferSize != 0) {
        osalGlobal.traceBufferSize = this.Server.traceBufferSize;

        print( "\nWarning: [ti.sdo.ce/package.xs] Configuring server's trace " +
               "buffer size by writing to Server's traceBufferSize field " +
               "is being deprecated; please set the server trace buffer size " +
               "by setting the traceBufferSize field in the " +
               "ti.sdo.ce.osal.Global module (e.g.: " +
               "xdc.useModule('ti.sdo.ce.osal.Global').traceBufferSize = " +
               this.Server.traceBufferSize + "; ) to avoid this warning and " +
               "a possible error with the future releases of Codec Engine. " );
    }
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    this.Server.validate();
    this.Engine.validate();
}

/*
 *  ======== Package.init ========
 *  Initialize this package.
 */
function init ()
{
    xdc.useModule('ti.sdo.ce.CERuntime');
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
    var name = "lib/" + this.profile + "/ce.a" + suffix;

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    if (!java.io.File(this.packageBase + name).exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        name = "lib/release/ce.a" + suffix;
    }

    return (name);
}


/*
 *  ======== warn ========
 *  For warnings that we may not really want to print. eg, for configurations
 *  with osal.Global.runtimeEnv set istead of osal.Global.os, or if the app
 *  .cfg has not configured ce.ipc.Settings.
 */
function warn(msg)
{
//    print(msg);
}

/*
 *  ======== trace ========
 */
function trace(msg)
{
//    print(msg);
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:26; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


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
    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Diags');
    xdc.useModule('xdc.runtime.Registry');

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    /* sanity check that we're in the config model - else we crash! */
    if (xdc.om.$name == "cfg") {
        var os = Program.build.target.os;

        if (os == "Linux") {
            xdc.useModule('ti.sdo.xdcruntime.linux.Settings');
            xdc.useModule('xdc.runtime.knl.SemProcess');
        }

        var Algorithm = this.Algorithm;

        /* establish dependency on OSAL */
        xdc.useModule('ti.sdo.ce.osal.Global');

        /* target.os is undefined for BIOS - DSKT2 is used on BIOS systems */
        if (os == undefined) {
            /* establish dependency on DSKT2 */
            xdc.useModule('ti.sdo.fc.dskt2.DSKT2');
        }

        if (Algorithm.useIdma3) {
            /* establish dependency on DMAN3, ACPY3 */
            xdc.useModule('ti.sdo.fc.dman3.DMAN3');
            xdc.useModule('ti.sdo.fc.acpy3.ACPY3');
        }

        if (Algorithm.useIres) {
            /* establish dependency on RMAN */
            xdc.useModule('ti.sdo.fc.rman.RMAN');
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

    var lib;

    /* BIOS systems have targ.os == undefined) */
    if (prog.build.target.os == undefined) {
        lib = "lib/" + this.profile + "/Algorithm_BIOS.a" + suffix;

        if (!java.io.File(this.packageBase + lib).exists()) {
            /* the suggested profile doesn't exist, try "release" */
            $trace("Unable to locate lib for requested '" + this.profile +
                    "' profile.  Using 'release' profile.", 1, ['getLibs']);
            lib = "lib/release/Algorithm_BIOS.a" + suffix;
        }
    }
    else {
        lib1 = "lib/" + this.profile + "/Algorithm_noOS.a" + suffix;
        lib2 = "lib/" + this.profile + "/alg.a" + suffix;

        /* Just test for lib 1 rather than both */
        if (!java.io.File(this.packageBase + lib1).exists()) {
            /* the suggested profile doesn't exist, try "release" */
            $trace("Unable to locate lib for requested '" + this.profile +
                    "' profile.  Using 'release' profile.", 1, ['getLibs']);

            lib1 = "lib/release/Algorithm_noOS.a" + suffix;
            lib2 = "lib/release/alg.a" + suffix;
        }

        /* return both libs */
        lib = lib1 + ";" + lib2;
    }

    return (lib);
}
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,1; 2-24-2012 19:27:09; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


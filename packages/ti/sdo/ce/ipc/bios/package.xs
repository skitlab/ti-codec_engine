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
 *  ======== createMemMapFile ========
 *  Create a text file containing the memory map, that can be used by a
 *  slave loader for mapping the slave's memory segments.
 */
function createMemMapFile(mmap)
{
}

/*
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
//    print(this.$name + ".close() ...");

    this.Processor.close();

    /* if undefined, take profile from the Settings module */
    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.ce.global.Settings').profile;
    }

    var ipc = this.Ipc;
    var prog = Program;

    // Currently, we unconditionally enable MessageQ.
    // TODO:M for local-only systems, we should support a build without an
    // IPC dependency
//    var MessageQ_enabled = true;
    var MessageQ_enabled = ipc.messageqUsed();

    // This module requires ipc.Settings, osal.bios.Settings.
    xdc.useModule('ti.sdo.ce.ipc.Settings');

    if (MessageQ_enabled) {
        // The BIOS IPC uses the following modules
        xdc.useModule('xdc.runtime.Memory');

        xdc.useModule('ti.sdo.utils.MultiProc');
        xdc.useModule('ti.sdo.ipc.MessageQ');

        xdc.useModule('ti.sysbios.syncs.SyncSem');
        xdc.useModule('ti.sdo.ipc.heaps.HeapBufMP');
    }

    // TODO:L For dependency reasons, should we declare this?
    //var osalGlobal = xdc.useModule('ti.sdo.ce.osal.Global');

    /* must use power management on 3430 */
//    if (Program.cpu.deviceName.match(/^TMS320C3430$|^OMAP3530$/)) {
//        ipc.usePowerManagement = true;
//    }

    /* Optionally load and configure power management module */
    if (ipc.dspLinkUsed() && ipc.usePowerManagement) {

        var power;

        if (ipc.powerSaveMemoryBlockName == null) {
            // Note: Since ipc depends on osal.Global, this package will
            // be closed before osal. Therefore, we cannot assume that
            // osal.Global.defaultMemSegId will be non-NULL.

            /* get the names of all instances */
            var memInsts = $$legacy.prog.module("MEM").instances();

            /* record the name of the segment "DDR" or "DDR2" if found */
            var segmentNamedLikeDdr = null;
            for (var i = 0; i < memInsts.length; i++) {
                if (memInsts[i].name == "DDR" || memInsts[i].name == "DDR2") {
                    segmentNamedLikeDdr = memInsts[i].name;
                }
            }

            print(this.$name + ".close() - setting powerSaveMemoryBlockName" +
                  " to " + segmentNamedLikeDdr);

            ipc.powerSaveMemoryBlockName = segmentNamedLikeDdr;
        }

        if (Program.cpu.deviceName.match(/^TMS320CDM6441$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6441DSP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320CDM6446$/)) {
            power = xdc.useModule('ti.bios.power.TMS320CDM6446DSP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320DM357$/)) {
            power = xdc.useModule('ti.bios.power.TMS320DM357DSP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP2530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP2530DSP');
        }
        else if (Program.cpu.deviceName.match(/^TMS320C3430$/)) {
            power = xdc.useModule('ti.bios.power.TMS320C3430DSP');
        }
        else if (Program.cpu.deviceName.match(/^OMAP3530$/)) {
            power = xdc.useModule('ti.bios.power.OMAP3530DSP');
        }
        else {
            throw "Error:  DSP ti.bios.power doesn't support: " +
                Program.cpu.deviceName;
        }

        power.opersys = power.Opersys_DSPBIOS;
        power.transport = power.Transport_Link_Linux;
        power.targetMemoryRangeName = this.Ipc.powerSaveMemoryBlockName;
    }

    if (ipc.dspLinkUsed()) {
        /* Load Link here */
//        print(this.$name + ".close(): loading dsplink.dsp");
        xdc.loadPackage('ti.sdo.ce.ipc.dsplink.dsp');
    }

//    print(this.$name + ".close() done!");
}

/*
 *  ======== Package.validate ========
 *  Verify the config params for this package; called after close()
 */
function validate()
{
    function toHex(d) {
        var hD="0123456789ABCDEF";
        var h = "";
        for (var i=0;i<8;i++) {h=hD.substr(d&15,1)+h;d=d>>4}
        return "0x" + h;
    }

    var ipc = this.Ipc;
//    print(this.$name + ".validate() ...");

//    print(this.$name + ".validate() - ipc.dspLinkUsed = " + ipc.dspLinkUsed());

    if (false && ipc.dspLinkUsed()) {
        var resetBase =
            $$legacy.prog.module("MEM").instance("RESET_VECTOR").base;

        if (Program.cpu.deviceName.match(/^OMAP[23]530$/)) {
            if ((resetBase & 0xFFF) != 0) {
                throw new Error("RESET_VECTOR segment must be aligned " +
                    "at 4KB boundary. Edit the TCF file and make sure the " +
                    "'base' property of this segment is correct.");
            }
        }
        else if ((resetBase & 0xFFFFF) != 0) {
            throw "\nError: RESET_VECTOR segment must be aligned at " +
                  "1MB boundary. Edit the TCF file and make sure the 'base' " +
                  "property of this segment is correct.\n";
        }

        /* dump memory map info into Info file */
        var osalGlobal = xdc.module('ti.sdo.ce.osal.Global');
        var os = xdc.module('ti.sdo.ce.osal.bios.Settings');
        //var dsplinkIpc = xdc.module('ti.sdo.ce.ipc.dsplink.Ipc');
        var mmap = [];
        var memInsts = $$legacy.prog.module("MEM").instances();
        var oddCount = 0;
        for (var i = 0; i < memInsts.length; i++) {
            var mi = memInsts[i];
            var type;
            var nonstandard = undefined;
            var gppAddr = undefined;

            // do this to eliminate tcf addrs 0x8xxxxxx being negative
            var baseAddr = parseInt( toHex( mi.base ) );

            if (mi.name == "DDRALGHEAP") {
                type = "other";
            }
            else if (mi.name == "POOLMEM") {
                type = "poolmem";
            }
            else if (mi.name == "DDR" || mi.name == "DDR2" ||
                     mi.name == os.defaultMemSegId ) {
                type = "main";
            }
            else if (mi.name == "DSPLINKMEM") {
                type = "link";
            }
            else if (mi.name.match(/RESET/)) {
                type = "reset";
            }
            else if (mi.name.match(/^CACHE_/i)) {
                // don't put cache sections into the memory map
                continue;
            }
            else if (Program.cpu.deviceName.match(
                    /C2430$|C3430$|^OMAP2530$|^OMAP3530$/)
                && (0x11000000 <= baseAddr) && (baseAddr < 0x80000000)) {
                // on omap3530 any address above 0x11000000 is controlled
                // by the IVA2.2 MMU and must be in the memory map, don't
                // complain about internal device addresses
                type = "other";
            }
            else if (Program.cpu.deviceName.match(
                    /C2430$|C3430$|^OMAP2530$|^OMAP3530$/)
                && (0x107F8000 <= baseAddr) && (baseAddr < 0x10F18000)) {
                // On omap device, the gpp must use L3 address to access
                // dsp internal memory. The L3 address is offset from the
                // dsp physical address by 0x4C000000. This memory range
                // covers both omap2 and omap3 (although they are not exact).
                gppAddr = parseInt(toHex(baseAddr + 0x4C000000));
                type = "code";
            }
            else {
                // complain for any other segment defined in the .tcf,
                // unless we are sure this is a system segment. We can tell if
                // a segment is system-defined (i.e. not defined in user .tcf)
                // by name or by address range for some devices

                if (Program.cpu.deviceName.match(/CDM6446$|CDM6467$|DM357$|OMAPL137$/)) {
                    // on davinci and davinci HD all external memory is above
                    // 0x80000000, and we don't record internal memory segments
                    if (baseAddr < 0x80000000) {
                        continue;
                    }
                    else if (Program.cpu.deviceName.match(/^OMAPL137$/)) {
                        if (mi.name == "L3_CBA_RAM") {
                            continue;
                        }
                    }
                }
                else if (Program.cpu.deviceName.match(
                    /C2430$|C3430$|^OMAP2530$|^OMAP3530$/)) {
                    // on omap, prune any address below internal memory
                    if (baseAddr < 0x107F8000) {
                        continue;
                    }
                }
                else {
                    print( "Warning: recording segment '" + mi.name + "' in " +
                           "info.js but don't know how to handle device '" +
                           Program.cpu.deviceName + "'." );
                }

                if (oddCount++ == 0) {
                    print( "\nWARNING: The server's .tcf file "+
                        "defines an unrecognized BIOS memory segment named \"" +
                        mi.name + "\". The Arm application may not be able to "+
                        "use Engine.createFromServer() API to configure this " +
                        "server, and you may run into a host of other " +
                        "problems. We strongly recommend that you only have " +
                        "segments \"" +
                        (osalGlobal.defaultMemSegId
                            ? osalGlobal.defaultMemSegId : "DDR[2]") + "\", " +
                        "\"DDRALGHEAP\", \"DSPLINKMEM\" and \"RESET\" defined "+
                        "in your .tcf file.\n" );
                } else {
                    print( "Warning: another non-standard BIOS memory " +
                           "segment: \"" + mi.name + "\"" );
                }
                type = "other";
                nonstandard = true;
            }
            mmap[ mmap.length ] = [ mi.name,
                { addr: baseAddr, gppAddr: gppAddr, size: mi.len,
                  type: type, nonstandard: nonstandard } ];
        }

        if (Program.cpu.deviceName.match(
                /C2430$|C3430$|^OMAP2530$|^OMAP3530$/)) {
            //print("Checking OMAP platform memory map for CMEM");
            if (!("CMEM" in mmap)) {
                // For OMAP devices, CMEM will need to be mapped to the MMU.
                // Add a place holder for CMEM that will be filled in at
                // runtime using CMEM_getBlock().
                mmap[ mmap.length ] = [ "CMEM",
                    { addr: 0, size: 0, type: "other",
                                nonstandard: undefined } ];
            }
            else {
                //print("OMAP platform memory map already has CMEM");
            }
        }
        osalGlobal.addObjectToProgramInfoFile("DSP memory map", mmap);
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

    var ipc = this.Ipc;
    var MessageQ_enabled = ipc.messageqUsed();
    var libName = (MessageQ_enabled) ? "ipc_bios.a" : "ipc_bios_nomsg.a";

    /* the location of the libraries are in lib/<profile>/* */
    var name = "lib/" + this.profile + "/" + libName + suffix;

    /*
     * If the requested profile doesn't exist, we return the 'release' library.
     */
    if (!java.io.File(this.packageBase + name).exists()) {
        $trace("Unable to locate lib for requested '" + this.profile +
                "' profile.  Using 'release' profile.", 1, ['getLibs']);
        name = "lib/release/" + libName + suffix;
    }

    return (name);
}


function trace(str)
{
//    print(str);
}
/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,1; 2-24-2012 19:29:57; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


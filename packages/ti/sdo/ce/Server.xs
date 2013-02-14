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
 *  ======== close ========
 */
function close()
{
    var Server = this;
    var Engine = xdc.useModule('ti.sdo.ce.Engine');

    if (Server.$used) {
        // print(this.$name + ".close(): using IPC");
        /* Load ipc - This causes ipc.Settings code to get generated */
        var ipcSettings = xdc.useModule('ti.sdo.ce.ipc.Settings');
    }

    /* create default groupIds based on specified thread priorities */
    var pri2id = {};
    var id = 0;

    // make this object available for our friend ServerDataSheet.html.xdt
    this.$private.pri2id = pri2id;

    // Temp var for later...
    var i = 0;

    /* Create an array of "free" groupIds, and init them all to true (free) */
    var freeGroupIds = new Array(Engine.MAXGROUPID);
    for (i = 0; i < Engine.MAXGROUPID; i++) {
        freeGroupIds[i] = true;
    }

    /*
     * Walk the alg array, marking the explicitly requested groupId's used.
     * Also, assign default priority, if necessary.
     */
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        if ((alg.groupId != undefined) && (alg.groupId != -1)) {
            freeGroupIds[alg.groupId] = false;
        }

        /* assign a default priority, if necessary */
        if (alg.threadAttrs.priority == null) {
            print ('Remark:  Alg "' + alg.name + '" threadAttrs.priority ' +
                'was not set.  Assigning default priority of ' +
                (this.MINPRI + 1) + '.');

            alg.threadAttrs.priority = this.MINPRI + 1;
        }
    }

    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        /* don't waste a free group id on algs which set it */
        if (alg.groupId == undefined) {
            /* create mapping between priority and a group id */
            if (pri2id[alg.threadAttrs.priority] == null) {
                while ((freeGroupIds[id] == false) &&
                    (id < Engine.MAXGROUPID)) {
                    id++;
                }
                pri2id[alg.threadAttrs.priority] = id;
                freeGroupIds[id] = false;
                id++;
            }
        }
    }

    /* create an array of algorithms for the default local engine */
    var engineAlgs = [];
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        var myGroupId = ((alg.groupId == undefined) ?
            pri2id[alg.threadAttrs.priority] : alg.groupId);

//        print("myGroupId:  " + myGroupId);

        engineAlgs.push({
            name: alg.name,
            mod: alg.mod,
            local: true,
            groupId: myGroupId
        });
    }

    /* create local engine and make it the default engine */
    Engine.local = Engine.create("local", engineAlgs);

    /* validate or auto-generate scratch config arrays */
    if (Program.build.target.os == undefined) {
        /* assume BIOS, and therefore DSKT2 */
        var DSKT2 = xdc.loadPackage('ti.sdo.fc.dskt2').DSKT2;

        for (i = 0; i < this.algs.length; i++) {
            var alg = this.algs[i];

            var dScr = alg.mod.getDaramScratchSize(xdc.om['xdc.cfg.Program']);
            var sScr = alg.mod.getSaramScratchSize(xdc.om['xdc.cfg.Program']);
            var groupId = ((alg.groupId == undefined) ?
                pri2id[alg.threadAttrs.priority] : alg.groupId);

            if (groupId >= 0) {
                var dCfg = DSKT2.DARAM_SCRATCH_SIZES[groupId];
                var sCfg = DSKT2.SARAM_SCRATCH_SIZES[groupId];

                if (this.autoGenScratchSizeArrays) {
                    if (dScr > dCfg) {
                        DSKT2.DARAM_SCRATCH_SIZES[groupId] = dScr;
                    }
                    if (sScr > sCfg) {
                        DSKT2.SARAM_SCRATCH_SIZES[groupId] = sScr;
                    }
                }
                else {
                    if (dCfg < dScr) {
                        this.$logWarning("Alg \"" + alg.name +
                                "\" DARAM scratch needs (" + dScr + ") " +
                                "exceeds DSKT2 config for groupId " +
                                groupId + " (" + dCfg + ")",
                                DSKT2,
                                "DARAM_SCRATCH_SIZES[" + groupId + "]");
                    }
                    if (sCfg < sScr) {
                        this.$logWarning("Alg \"" + alg.name +
                                "\" SARAM scratch needs (" + sScr + ") " +
                                "exceeds DSKT2 config for groupId " +
                                groupId + " (" + sCfg + ")",
                                DSKT2,
                                "SARAM_SCRATCH_SIZES[" + groupId + "]");
                    }
                }
            }
        }
    }

    /* establish default RMS server thread attrs */
    if (this.threadAttrs.stackMemId == null) {
        this.threadAttrs.stackMemId = 0;
    }
    if (this.threadAttrs.stackSize == null) {
        /* Apply padding to "default" stack size of 1024 */
        this.threadAttrs.stackSize = 1024 + this.stackSizePad;
    }
    if (this.threadAttrs.priority == null) {
        this.threadAttrs.priority = this.MINPRI;
    }

    /*
     *  Use the default cache policy for the skels (invalidate input buffers,
     *  writeback output buffers) if not yet set.
     */
    if (this.skelCachingPolicy == undefined) {
        this.skelCachingPolicy = this.LOCALBUFFERINVWB;
    }
}

/*
 *  ======== validate ========
 *  Validate that all the Servers are properly configured
 */
function validate()
{
    var Server = this;
    var Engine = xdc.om['ti.sdo.ce'].Engine;
    var i = 0; // temp var for later

    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];

        if ((alg.groupId < -1) || (alg.groupId > Engine.MAXGROUPID)) {
            throw ("Error:  Alg \"" + alg.name + "\" groupId out of range:  "
                    + alg.groupId);
        }

        if ((alg.threadAttrs.priority < this.MINPRI) ||
            (alg.threadAttrs.priority > this.MAXPRI)) {
            throw ("Error:  Alg \"" + alg.name + "\" priority out of range:  "
                    + alg.threadAttrs.priority);

        }
    }

    // dump the server configuration info into the program Info file
    var serverCfg = {};
    serverCfg.programName = Program.name;
    serverCfg.algs = [];
    for (i = 0; i < this.algs.length; i++) {
        var alg = this.algs[i];
        serverCfg.algs[i] = {
            name:               alg.name,
            pkg:                alg.mod.$package.$name,
            pkgVersion:         alg.mod.$package.$vers,
            mod:                alg.mod.$name,
            threadAttrs: {
                priority:       alg.threadAttrs.priority,
                stackSize:      alg.threadAttrs.stackSize
            },
            groupId:            alg.groupId,
            ialgFxns:           alg.mod.ialgFxns,
            idma3Fxns:          alg.mod.idma3Fxns,
            iresFxns:           alg.mod.iresFxns,
            serverFxns:         alg.mod.serverFxns,
            stubFxns:           alg.mod.stubFxns,
            rpcProtocolVersion: alg.mod.rpcProtocolVersion,
            uuid:               alg.mod.uuid
        };
    }
    var osalGlobal = xdc.module('ti.sdo.ce.osal.Global');
    osalGlobal.addObjectToProgramInfoFile("server algorithms", serverCfg);

    // create server data sheet, but only if there are server algs
    if ((Program.build.target.suffix.match("64|674|m3") != null) &&
        (Server.algs != undefined) &&
        (Server.algs.length > 0)) {

        /* validate that the MessageQ.maxNameLen isn't 'too small' */
        var MessageQ = xdc.module('ti.sdo.ipc.MessageQ');
        if (MessageQ.maxNameLen < 32) {
            throw ("Error:  ti.sdo.ipc.MessageQ.maxNameLen is configured to " +
                    MessageQ.maxNameLen + ".  " +
                "The ti.sdo.ce package requires it be configured >= 32 .");
        }

        var t = xdc.loadTemplate( "ti/sdo/ce/ServerDataSheet.html.xdt" );
        try {
            var outFileName = "./package/info/" + Program.name + ".DataSheet.html";
            print("\nNOTE: You can find the complete server data sheet in " +
                   outFileName);
            print(  "-----------------------------------------------------" +
                   outFileName.replace( /./g, "-" ) + "\n" );
            t.genFile(outFileName, this);
        }
        catch(e) {
            var message = "Server.xs Warning: Could not create Server data sheet"+
                " '" + outFileName + "'.\n\n" + "Details: " + e + "\n\n";
            print(message);
        }
    }
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,1; 2-24-2012 19:27:26; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

 */


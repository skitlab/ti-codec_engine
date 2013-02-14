/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sdo_ce_ipc_bios
{
    static final String VERS = "@(#) xdc-y25\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce.ipc");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.ipc.bios.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.ipc.bios", new Value.Obj("ti.sdo.ce.ipc.bios", pkgP));
    }

    void Ipc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.bios.Ipc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.bios.Ipc", new Value.Obj("ti.sdo.ce.ipc.bios.Ipc", po));
        pkgV.bind("Ipc", vo);
        // decls 
        om.bind("ti.sdo.ce.ipc.bios.Ipc.ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.bios"));
        om.bind("ti.sdo.ce.ipc.bios.Ipc.DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.bios"));
        om.bind("ti.sdo.ce.ipc.bios.Ipc.ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.bios"));
        om.bind("ti.sdo.ce.ipc.bios.Ipc.LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.bios"));
    }

    void Processor$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.bios.Processor.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.bios.Processor", new Value.Obj("ti.sdo.ce.ipc.bios.Processor", po));
        pkgV.bind("Processor", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.ipc.bios.Processor$$CommDesc", new Proto.Obj());
        om.bind("ti.sdo.ce.ipc.bios.Processor.CommDesc", new Proto.Str(spo, true));
    }

    void Ipc$$CONSTS()
    {
        // module Ipc
    }

    void Processor$$CONSTS()
    {
        // module Processor
    }

    void Ipc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Processor$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Ipc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Ipc.dspLinkUsed
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ipc.bios.Ipc$$dspLinkUsed", new Proto.Fxn(om.findStrict("ti.sdo.ce.ipc.bios.Ipc.Module", "ti.sdo.ce.ipc.bios"), $$T_Bool, 0, 0, false));
        // fxn Ipc.messageqUsed
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ipc.bios.Ipc$$messageqUsed", new Proto.Fxn(om.findStrict("ti.sdo.ce.ipc.bios.Ipc.Module", "ti.sdo.ce.ipc.bios"), $$T_Bool, 0, 0, false));
    }

    void Processor$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Processor.close
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.ipc.bios.Processor$$close", new Proto.Fxn(om.findStrict("ti.sdo.ce.ipc.bios.Processor.Module", "ti.sdo.ce.ipc.bios"), null, 0, -1, false));
    }

    void Ipc$$SIZES()
    {
    }

    void Processor$$SIZES()
    {
    }

    void Ipc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/bios/Ipc.xs");
        om.bind("ti.sdo.ce.ipc.bios.Ipc$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Ipc.Module", "ti.sdo.ce.ipc.bios");
        po.init("ti.sdo.ce.ipc.bios.Ipc.Module", om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc.bios"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("armCommMsgSize", Proto.Elm.newCNum("(xdc_UInt32)"), Global.eval("4 * 1024"), "wh");
        po.addFld("hostCommNumMsgs", Proto.Elm.newCNum("(xdc_UInt32)"), 64L, "wh");
        po.addFld("dspCommMsgSize", Proto.Elm.newCNum("(xdc_UInt32)"), 1024L, "wh");
        po.addFld("dspCommNumMsgs", Proto.Elm.newCNum("(xdc_UInt32)"), 64L, "wh");
        po.addFld("usePowerManagement", $$T_Bool, false, "wh");
        po.addFld("powerSaveMemoryBlockName", $$T_Str, null, "wh");
        po.addFld("manageIpc", $$T_Bool, true, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Ipc$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Ipc$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Ipc$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("dspLinkUsed", (Proto.Fxn)om.findStrict("ti.sdo.ce.ipc.bios.Ipc$$dspLinkUsed", "ti.sdo.ce.ipc.bios"), Global.get(cap, "dspLinkUsed"));
                po.addFxn("messageqUsed", (Proto.Fxn)om.findStrict("ti.sdo.ce.ipc.bios.Ipc$$messageqUsed", "ti.sdo.ce.ipc.bios"), Global.get(cap, "messageqUsed"));
    }

    void Processor$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/bios/Processor.xs");
        om.bind("ti.sdo.ce.ipc.bios.Processor$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Processor.Module", "ti.sdo.ce.ipc.bios");
        po.init("ti.sdo.ce.ipc.bios.Processor.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("sharedRegionId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "wh");
        po.addFld("heapId", Proto.Elm.newCNum("(xdc_UInt16)"), 0L, "wh");
        po.addFld("coreComm", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.ipc.bios.Processor.CommDesc", "ti.sdo.ce.ipc.bios"), false), $$DEFAULT, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Processor$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Processor$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ce.ipc.bios.Processor$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("close", (Proto.Fxn)om.findStrict("ti.sdo.ce.ipc.bios.Processor$$close", "ti.sdo.ce.ipc.bios"), Global.get(cap, "close"));
        // struct Processor.CommDesc
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Processor$$CommDesc", "ti.sdo.ce.ipc.bios");
        po.init("ti.sdo.ce.ipc.bios.Processor.CommDesc", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("numMsgs", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("msgSize", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("sharedRegionId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("heapId", Proto.Elm.newCNum("(xdc_UInt16)"), $$UNDEF, "w");
                po.addFld("userCreatedHeap", $$T_Bool, $$UNDEF, "w");
    }

    void Ipc$$ROV()
    {
    }

    void Processor$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.ipc.bios.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.ipc.bios"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/bios/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.ipc.bios"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.ipc.bios"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.ipc.bios"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.ipc.bios"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.ipc.bios"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.ipc.bios"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.ipc.bios", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.ipc.bios");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.ipc.bios.");
        pkgV.bind("$vers", Global.newArray("2, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.ipc.bios'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ipc_bios_nomsg.aem3',\n");
            sb.append("'lib/debug/ipc_bios.aem3',\n");
            sb.append("'lib/release/ipc_bios_nomsg.aem3',\n");
            sb.append("'lib/release/ipc_bios.aem3',\n");
            sb.append("'lib/debug/ipc_bios_nomsg.ae674',\n");
            sb.append("'lib/debug/ipc_bios.ae674',\n");
            sb.append("'lib/release/ipc_bios_nomsg.ae674',\n");
            sb.append("'lib/release/ipc_bios.ae674',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ipc_bios_nomsg.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/ipc_bios.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/ipc_bios_nomsg.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/ipc_bios.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/ipc_bios_nomsg.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/ipc_bios.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/ipc_bios_nomsg.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/ipc_bios.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Ipc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Ipc", "ti.sdo.ce.ipc.bios");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Ipc.Module", "ti.sdo.ce.ipc.bios");
        vo.init2(po, "ti.sdo.ce.ipc.bios.Ipc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.ipc.bios.Ipc$$capsule", "ti.sdo.ce.ipc.bios"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.bios", "ti.sdo.ce.ipc.bios"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.bios"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc.bios"));
        vo.bind("DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc.bios"));
        vo.bind("ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.bios"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc.bios"));
        vo.bind("LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.bios"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc.bios"));
        vo.bind("BootAndLoadDsp", om.findStrict("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", "ti.sdo.ce.ipc.bios"));
        vo.bind("BootDspAutonomously", om.findStrict("ti.sdo.ce.ipc.IIpc.BootDspAutonomously", "ti.sdo.ce.ipc.bios"));
        vo.bind("None", om.findStrict("ti.sdo.ce.ipc.IIpc.None", "ti.sdo.ce.ipc.bios"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sdo.ce.ipc");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc.bios")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.bios.Ipc$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Ipc.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Ipc.xdt");
        pkgV.bind("Ipc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Ipc");
    }

    void Processor$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Processor", "ti.sdo.ce.ipc.bios");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.bios.Processor.Module", "ti.sdo.ce.ipc.bios");
        vo.init2(po, "ti.sdo.ce.ipc.bios.Processor", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.ipc.bios.Processor$$capsule", "ti.sdo.ce.ipc.bios"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc.bios", "ti.sdo.ce.ipc.bios"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("CommDesc", om.findStrict("ti.sdo.ce.ipc.bios.Processor.CommDesc", "ti.sdo.ce.ipc.bios"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.bios.Processor.CommDesc", "ti.sdo.ce.ipc.bios"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc.bios")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.bios.Processor$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Processor.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Processor.xdt");
        pkgV.bind("Processor", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Processor");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.bios.Ipc", "ti.sdo.ce.ipc.bios"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.bios.Processor", "ti.sdo.ce.ipc.bios"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.bios.Ipc")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.bios.Processor")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.ipc.bios")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Ipc$$OBJECTS();
        Processor$$OBJECTS();
        Ipc$$CONSTS();
        Processor$$CONSTS();
        Ipc$$CREATES();
        Processor$$CREATES();
        Ipc$$FUNCTIONS();
        Processor$$FUNCTIONS();
        Ipc$$SIZES();
        Processor$$SIZES();
        Ipc$$TYPES();
        Processor$$TYPES();
        if (isROV) {
            Ipc$$ROV();
            Processor$$ROV();
        }//isROV
        $$SINGLETONS();
        Ipc$$SINGLETONS();
        Processor$$SINGLETONS();
        $$INITIALIZATION();
    }
}

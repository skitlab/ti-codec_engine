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

public class ti_sdo_ce_ipc
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
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.ipc.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.ipc", new Value.Obj("ti.sdo.ce.ipc", pkgP));
    }

    void Settings$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.Settings.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.Settings", new Value.Obj("ti.sdo.ce.ipc.Settings", po));
        pkgV.bind("Settings", vo);
        // decls 
    }

    void IIpc$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.ipc.IIpc.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.ipc.IIpc", new Value.Obj("ti.sdo.ce.ipc.IIpc", po));
        pkgV.bind("IIpc", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.ipc.IIpc$$ArmDspLinkConfigMemTableEntry", new Proto.Obj());
        om.bind("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", new Proto.Str(spo, true));
        om.bind("ti.sdo.ce.ipc.IIpc.DspManagement", new Proto.Enm("ti.sdo.ce.ipc.IIpc.DspManagement"));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.ipc.IIpc$$ArmDspLinkConfig", new Proto.Obj());
        om.bind("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.ipc.IIpc$$LinkConfigEntry", new Proto.Obj());
        om.bind("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", new Proto.Str(spo, true));
    }

    void Settings$$CONSTS()
    {
        // module Settings
    }

    void IIpc$$CONSTS()
    {
        // interface IIpc
        om.bind("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc"), "ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", 0));
        om.bind("ti.sdo.ce.ipc.IIpc.BootDspAutonomously", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc"), "ti.sdo.ce.ipc.IIpc.BootDspAutonomously", 1));
        om.bind("ti.sdo.ce.ipc.IIpc.None", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc"), "ti.sdo.ce.ipc.IIpc.None", 2));
    }

    void Settings$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IIpc$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Settings$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IIpc$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Settings$$SIZES()
    {
    }

    void IIpc$$SIZES()
    {
    }

    void Settings$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.Settings.Module", "ti.sdo.ce.ipc");
        po.init("ti.sdo.ce.ipc.Settings.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("ipc", (Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc"), $$UNDEF, "wh");
        po.addFld("debug", $$T_Bool, false, "wh");
    }

    void IIpc$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc");
        po.init("ti.sdo.ce.ipc.IIpc.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("linkConfigs", new Proto.Map((Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc")), $$DEFAULT, "wh");
        // struct IIpc.ArmDspLinkConfigMemTableEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc$$ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc");
        po.init("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("addr", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("gppAddr", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("size", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("type", $$T_Str, $$UNDEF, "w");
        // struct IIpc.ArmDspLinkConfig
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc$$ArmDspLinkConfig", "ti.sdo.ce.ipc");
        po.init("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("memTable", new Proto.Map((Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc")), $$DEFAULT, "w");
                po.addFld("doPowerControl", $$T_Bool, $$UNDEF, "w");
                po.addFld("dspManagement", (Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc"), $$UNDEF, "w");
        // struct IIpc.LinkConfigEntry
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc$$LinkConfigEntry", "ti.sdo.ce.ipc");
        po.init("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("serverName", $$T_Str, $$UNDEF, "w");
                po.addFld("linkCfg", (Proto)om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc"), $$DEFAULT, "w");
    }

    void Settings$$ROV()
    {
    }

    void IIpc$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.ipc.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.ipc"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/ipc/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.ipc"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.ipc"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.ipc"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.ipc"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.ipc"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.ipc"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.ipc", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.ipc");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.ipc.");
        pkgV.bind("$vers", Global.newArray("2, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.ipc'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Settings$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.Settings", "ti.sdo.ce.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.Settings.Module", "ti.sdo.ce.ipc");
        vo.init2(po, "ti.sdo.ce.ipc.Settings", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc", "ti.sdo.ce.ipc"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.ipc")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.ipc.Settings$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Settings.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Settings.xdt");
        pkgV.bind("Settings", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Settings");
    }

    void IIpc$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc", "ti.sdo.ce.ipc");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.ipc.IIpc.Module", "ti.sdo.ce.ipc");
        vo.init2(po, "ti.sdo.ce.ipc.IIpc", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.ipc", "ti.sdo.ce.ipc"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("ArmDspLinkConfigMemTableEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfigMemTableEntry", "ti.sdo.ce.ipc"));
        vo.bind("DspManagement", om.findStrict("ti.sdo.ce.ipc.IIpc.DspManagement", "ti.sdo.ce.ipc"));
        vo.bind("ArmDspLinkConfig", om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig", "ti.sdo.ce.ipc"));
        vo.bind("LinkConfigEntry", om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc"));
        tdefs.add(om.findStrict("ti.sdo.ce.ipc.IIpc.LinkConfigEntry", "ti.sdo.ce.ipc"));
        vo.bind("BootAndLoadDsp", om.findStrict("ti.sdo.ce.ipc.IIpc.BootAndLoadDsp", "ti.sdo.ce.ipc"));
        vo.bind("BootDspAutonomously", om.findStrict("ti.sdo.ce.ipc.IIpc.BootDspAutonomously", "ti.sdo.ce.ipc"));
        vo.bind("None", om.findStrict("ti.sdo.ce.ipc.IIpc.None", "ti.sdo.ce.ipc"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IIpc", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IIpc");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.ipc.Settings", "ti.sdo.ce.ipc"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.Settings")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.ipc.IIpc")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.ipc")).add(pkgV);
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
        Settings$$OBJECTS();
        IIpc$$OBJECTS();
        Settings$$CONSTS();
        IIpc$$CONSTS();
        Settings$$CREATES();
        IIpc$$CREATES();
        Settings$$FUNCTIONS();
        IIpc$$FUNCTIONS();
        Settings$$SIZES();
        IIpc$$SIZES();
        Settings$$TYPES();
        IIpc$$TYPES();
        if (isROV) {
            Settings$$ROV();
            IIpc$$ROV();
        }//isROV
        $$SINGLETONS();
        Settings$$SINGLETONS();
        IIpc$$SINGLETONS();
        $$INITIALIZATION();
    }
}

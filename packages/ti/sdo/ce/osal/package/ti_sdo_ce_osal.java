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

public class ti_sdo_ce_osal
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.osal.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.osal", new Value.Obj("ti.sdo.ce.osal", pkgP));
    }

    void Global$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.osal.Global.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.osal.Global", new Value.Obj("ti.sdo.ce.osal.Global", po));
        pkgV.bind("Global", vo);
        // decls 
        om.bind("ti.sdo.ce.osal.Global.RuntimeEnv", new Proto.Enm("ti.sdo.ce.osal.Global.RuntimeEnv"));
    }

    void IOsal$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.osal.IOsal.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.osal.IOsal", new Value.Obj("ti.sdo.ce.osal.IOsal", po));
        pkgV.bind("IOsal", vo);
        // decls 
    }

    void Global$$CONSTS()
    {
        // module Global
        om.bind("ti.sdo.ce.osal.Global.NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.NONE", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ce.osal.Global.DSPBIOS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.DSPBIOS", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sdo.ce.osal.Global.LINUX", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.LINUX", xdc.services.intern.xsr.Enum.intValue(2L)+0));
        om.bind("ti.sdo.ce.osal.Global.DSPLINK_BIOS", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.DSPLINK_BIOS", xdc.services.intern.xsr.Enum.intValue(3L)+0));
        om.bind("ti.sdo.ce.osal.Global.DSPLINK_LINUX", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.DSPLINK_LINUX", xdc.services.intern.xsr.Enum.intValue(4L)+0));
        om.bind("ti.sdo.ce.osal.Global.WINCE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.WINCE", xdc.services.intern.xsr.Enum.intValue(5L)+0));
        om.bind("ti.sdo.ce.osal.Global.DSPLINK_WINCE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), "ti.sdo.ce.osal.Global.DSPLINK_WINCE", xdc.services.intern.xsr.Enum.intValue(6L)+0));
    }

    void IOsal$$CONSTS()
    {
        // interface IOsal
    }

    void Global$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IOsal$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Global$$FUNCTIONS()
    {
        Proto.Fxn fxn;

        // fxn Global.addObjectToProgramInfoFile
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.osal.Global$$addObjectToProgramInfoFile", new Proto.Fxn(om.findStrict("ti.sdo.ce.osal.Global.Module", "ti.sdo.ce.osal"), null, 0, -1, false));
        // fxn Global.parseInfoFile
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.osal.Global$$parseInfoFile", new Proto.Fxn(om.findStrict("ti.sdo.ce.osal.Global.Module", "ti.sdo.ce.osal"), null, 0, -1, false));
        // fxn Global.validate
        fxn = (Proto.Fxn)om.bind("ti.sdo.ce.osal.Global$$validate", new Proto.Fxn(om.findStrict("ti.sdo.ce.osal.Global.Module", "ti.sdo.ce.osal"), null, 0, -1, false));
    }

    void IOsal$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Global$$SIZES()
    {
    }

    void IOsal$$SIZES()
    {
    }

    void Global$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/osal/Global.xs");
        om.bind("ti.sdo.ce.osal.Global$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.osal.Global.Module", "ti.sdo.ce.osal");
        po.init("ti.sdo.ce.osal.Global.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("os", (Proto)om.findStrict("ti.sdo.ce.osal.IOsal.Module", "ti.sdo.ce.osal"), $$UNDEF, "wh");
        po.addFld("runtimeEnv", (Proto)om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"), $$UNDEF, "wh");
        po.addFld("skipVirtualAddressTranslation", $$T_Bool, false, "wh");
        po.addFld("embedBuildInfo", $$T_Bool, true, "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ce.osal.Global$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ce.osal.Global$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ce.osal.Global$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                po.addFxn("addObjectToProgramInfoFile", (Proto.Fxn)om.findStrict("ti.sdo.ce.osal.Global$$addObjectToProgramInfoFile", "ti.sdo.ce.osal"), Global.get(cap, "addObjectToProgramInfoFile"));
                po.addFxn("parseInfoFile", (Proto.Fxn)om.findStrict("ti.sdo.ce.osal.Global$$parseInfoFile", "ti.sdo.ce.osal"), Global.get(cap, "parseInfoFile"));
                po.addFxn("validate", (Proto.Fxn)om.findStrict("ti.sdo.ce.osal.Global$$validate", "ti.sdo.ce.osal"), Global.get(cap, "validate"));
    }

    void IOsal$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.osal.IOsal.Module", "ti.sdo.ce.osal");
        po.init("ti.sdo.ce.osal.IOsal.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
    }

    void Global$$ROV()
    {
    }

    void IOsal$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.osal.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.osal"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/osal/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.osal"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.osal"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.osal"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.osal"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.osal"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.osal"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.osal", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.osal");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.osal.");
        pkgV.bind("$vers", Global.newArray("2, 0, 2"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.osal'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/osal.aem3',\n");
            sb.append("'lib/release/osal.aem3',\n");
            sb.append("'lib/debug/osal.ae674',\n");
            sb.append("'lib/release/osal.ae674',\n");
            sb.append("'lib/debug/osal.av5T',\n");
            sb.append("'lib/release/osal.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/osal.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/osal.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/osal.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/osal.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/osal.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/osal.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Global$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.osal.Global", "ti.sdo.ce.osal");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.osal.Global.Module", "ti.sdo.ce.osal");
        vo.init2(po, "ti.sdo.ce.osal.Global", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.osal.Global$$capsule", "ti.sdo.ce.osal"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.osal", "ti.sdo.ce.osal"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("RuntimeEnv", om.findStrict("ti.sdo.ce.osal.Global.RuntimeEnv", "ti.sdo.ce.osal"));
        vo.bind("NONE", om.findStrict("ti.sdo.ce.osal.Global.NONE", "ti.sdo.ce.osal"));
        vo.bind("DSPBIOS", om.findStrict("ti.sdo.ce.osal.Global.DSPBIOS", "ti.sdo.ce.osal"));
        vo.bind("LINUX", om.findStrict("ti.sdo.ce.osal.Global.LINUX", "ti.sdo.ce.osal"));
        vo.bind("DSPLINK_BIOS", om.findStrict("ti.sdo.ce.osal.Global.DSPLINK_BIOS", "ti.sdo.ce.osal"));
        vo.bind("DSPLINK_LINUX", om.findStrict("ti.sdo.ce.osal.Global.DSPLINK_LINUX", "ti.sdo.ce.osal"));
        vo.bind("WINCE", om.findStrict("ti.sdo.ce.osal.Global.WINCE", "ti.sdo.ce.osal"));
        vo.bind("DSPLINK_WINCE", om.findStrict("ti.sdo.ce.osal.Global.DSPLINK_WINCE", "ti.sdo.ce.osal"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.osal")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.osal.Global$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Global.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Global.xdt");
        pkgV.bind("Global", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Global");
    }

    void IOsal$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.osal.IOsal", "ti.sdo.ce.osal");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.osal.IOsal.Module", "ti.sdo.ce.osal");
        vo.init2(po, "ti.sdo.ce.osal.IOsal", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.osal", "ti.sdo.ce.osal"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IOsal", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IOsal");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.osal.Global", "ti.sdo.ce.osal"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.osal.Global")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.osal.IOsal")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.osal")).add(pkgV);
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
        Global$$OBJECTS();
        IOsal$$OBJECTS();
        Global$$CONSTS();
        IOsal$$CONSTS();
        Global$$CREATES();
        IOsal$$CREATES();
        Global$$FUNCTIONS();
        IOsal$$FUNCTIONS();
        Global$$SIZES();
        IOsal$$SIZES();
        Global$$TYPES();
        IOsal$$TYPES();
        if (isROV) {
            Global$$ROV();
            IOsal$$ROV();
        }//isROV
        $$SINGLETONS();
        Global$$SINGLETONS();
        IOsal$$SINGLETONS();
        $$INITIALIZATION();
    }
}

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

public class ti_sdo_ce_video3
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
        Global.callFxn("loadPackage", xdcO, "ti.sdo.ce");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video3.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video3", new Value.Obj("ti.sdo.ce.video3", pkgP));
    }

    void VIDDEC3Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video3.VIDDEC3Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video3.VIDDEC3Config", new Value.Obj("ti.sdo.ce.video3.VIDDEC3Config", po));
        pkgV.bind("VIDDEC3Config", vo);
        // decls 
    }

    void IVIDDEC3$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video3.IVIDDEC3.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video3.IVIDDEC3", new Value.Obj("ti.sdo.ce.video3.IVIDDEC3", po));
        pkgV.bind("IVIDDEC3", vo);
        // decls 
    }

    void VIDDEC3Config$$CONSTS()
    {
        // module VIDDEC3Config
    }

    void IVIDDEC3$$CONSTS()
    {
        // interface IVIDDEC3
    }

    void VIDDEC3Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC3$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDEC3Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC3$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDEC3Config$$SIZES()
    {
    }

    void IVIDDEC3$$SIZES()
    {
    }

    void VIDDEC3Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video3.VIDDEC3Config.Module", "ti.sdo.ce.video3");
        po.init("ti.sdo.ce.video3.VIDDEC3Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC3$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video3.IVIDDEC3.Module", "ti.sdo.ce.video3");
        po.init("ti.sdo.ce.video3.IVIDDEC3.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video3"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("serverFxns", $$T_Str, "VIDDEC3_SKEL", "wh");
        po.addFld("stubFxns", $$T_Str, "VIDDEC3_STUBS", "wh");
        po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
        po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
        po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
        po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDDEC3Config$$ROV()
    {
    }

    void IVIDDEC3$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video3.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video3"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video3/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video3"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video3"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video3"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video3"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video3"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video3"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video3", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video3");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video3.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video3'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/viddec3.aem3',\n");
            sb.append("'lib/release/viddec3.aem3',\n");
            sb.append("'lib/debug/viddec3.ae674',\n");
            sb.append("'lib/release/viddec3.ae674',\n");
            sb.append("'lib/debug/viddec3.av5T',\n");
            sb.append("'lib/release/viddec3.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/viddec3.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/viddec3.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/viddec3.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/viddec3.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/viddec3.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/viddec3.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void VIDDEC3Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video3.VIDDEC3Config", "ti.sdo.ce.video3");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video3.VIDDEC3Config.Module", "ti.sdo.ce.video3");
        vo.init2(po, "ti.sdo.ce.video3.VIDDEC3Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video3", "ti.sdo.ce.video3"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video3")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video3.VIDDEC3Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDEC3Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDEC3Config.xdt");
        pkgV.bind("VIDDEC3Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDEC3Config");
    }

    void IVIDDEC3$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video3.IVIDDEC3", "ti.sdo.ce.video3");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video3.IVIDDEC3.Module", "ti.sdo.ce.video3");
        vo.init2(po, "ti.sdo.ce.video3.IVIDDEC3", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video3", "ti.sdo.ce.video3"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ce");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC3", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC3");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video3.VIDDEC3Config", "ti.sdo.ce.video3"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video3.VIDDEC3Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video3.IVIDDEC3")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video3")).add(pkgV);
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
        VIDDEC3Config$$OBJECTS();
        IVIDDEC3$$OBJECTS();
        VIDDEC3Config$$CONSTS();
        IVIDDEC3$$CONSTS();
        VIDDEC3Config$$CREATES();
        IVIDDEC3$$CREATES();
        VIDDEC3Config$$FUNCTIONS();
        IVIDDEC3$$FUNCTIONS();
        VIDDEC3Config$$SIZES();
        IVIDDEC3$$SIZES();
        VIDDEC3Config$$TYPES();
        IVIDDEC3$$TYPES();
        if (isROV) {
            VIDDEC3Config$$ROV();
            IVIDDEC3$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDDEC3Config$$SINGLETONS();
        IVIDDEC3$$SINGLETONS();
        $$INITIALIZATION();
    }
}

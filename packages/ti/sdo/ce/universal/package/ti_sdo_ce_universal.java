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

public class ti_sdo_ce_universal
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.universal.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.universal", new Value.Obj("ti.sdo.ce.universal", pkgP));
    }

    void UNIVERSALConfig$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.universal.UNIVERSALConfig.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.universal.UNIVERSALConfig", new Value.Obj("ti.sdo.ce.universal.UNIVERSALConfig", po));
        pkgV.bind("UNIVERSALConfig", vo);
        // decls 
    }

    void IUNIVERSAL$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.universal.IUNIVERSAL.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.universal.IUNIVERSAL", new Value.Obj("ti.sdo.ce.universal.IUNIVERSAL", po));
        pkgV.bind("IUNIVERSAL", vo);
        // decls 
    }

    void UNIVERSALConfig$$CONSTS()
    {
        // module UNIVERSALConfig
    }

    void IUNIVERSAL$$CONSTS()
    {
        // interface IUNIVERSAL
    }

    void UNIVERSALConfig$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IUNIVERSAL$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void UNIVERSALConfig$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IUNIVERSAL$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void UNIVERSALConfig$$SIZES()
    {
    }

    void IUNIVERSAL$$SIZES()
    {
    }

    void UNIVERSALConfig$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.universal.UNIVERSALConfig.Module", "ti.sdo.ce.universal");
        po.init("ti.sdo.ce.universal.UNIVERSALConfig.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IUNIVERSAL$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.universal.IUNIVERSAL.Module", "ti.sdo.ce.universal");
        po.init("ti.sdo.ce.universal.IUNIVERSAL.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.universal"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("serverFxns", $$T_Str, "UNIVERSAL_SKEL", "wh");
        po.addFld("stubFxns", $$T_Str, "UNIVERSAL_STUBS", "wh");
        po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
        po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
        po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
        po.addFld("manageInOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
        po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void UNIVERSALConfig$$ROV()
    {
    }

    void IUNIVERSAL$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.universal.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.universal"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/universal/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.universal"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.universal"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.universal"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.universal"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.universal"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.universal"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.universal", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.universal");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.universal.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.universal'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/universal.aem3',\n");
            sb.append("'lib/release/universal.aem3',\n");
            sb.append("'lib/debug/universal.ae674',\n");
            sb.append("'lib/release/universal.ae674',\n");
            sb.append("'lib/debug/universal.av5T',\n");
            sb.append("'lib/release/universal.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/universal.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/universal.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/universal.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/universal.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/universal.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/universal.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void UNIVERSALConfig$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.universal.UNIVERSALConfig", "ti.sdo.ce.universal");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.universal.UNIVERSALConfig.Module", "ti.sdo.ce.universal");
        vo.init2(po, "ti.sdo.ce.universal.UNIVERSALConfig", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.universal", "ti.sdo.ce.universal"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.universal")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.universal.UNIVERSALConfig$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./UNIVERSALConfig.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./UNIVERSALConfig.xdt");
        pkgV.bind("UNIVERSALConfig", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("UNIVERSALConfig");
    }

    void IUNIVERSAL$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.universal.IUNIVERSAL", "ti.sdo.ce.universal");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.universal.IUNIVERSAL.Module", "ti.sdo.ce.universal");
        vo.init2(po, "ti.sdo.ce.universal.IUNIVERSAL", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.universal", "ti.sdo.ce.universal"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ce");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IUNIVERSAL", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IUNIVERSAL");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.universal.UNIVERSALConfig", "ti.sdo.ce.universal"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.universal.UNIVERSALConfig")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.universal.IUNIVERSAL")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.universal")).add(pkgV);
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
        UNIVERSALConfig$$OBJECTS();
        IUNIVERSAL$$OBJECTS();
        UNIVERSALConfig$$CONSTS();
        IUNIVERSAL$$CONSTS();
        UNIVERSALConfig$$CREATES();
        IUNIVERSAL$$CREATES();
        UNIVERSALConfig$$FUNCTIONS();
        IUNIVERSAL$$FUNCTIONS();
        UNIVERSALConfig$$SIZES();
        IUNIVERSAL$$SIZES();
        UNIVERSALConfig$$TYPES();
        IUNIVERSAL$$TYPES();
        if (isROV) {
            UNIVERSALConfig$$ROV();
            IUNIVERSAL$$ROV();
        }//isROV
        $$SINGLETONS();
        UNIVERSALConfig$$SINGLETONS();
        IUNIVERSAL$$SINGLETONS();
        $$INITIALIZATION();
    }
}

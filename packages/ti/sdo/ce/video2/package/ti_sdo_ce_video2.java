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

public class ti_sdo_ce_video2
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.video2.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.video2", new Value.Obj("ti.sdo.ce.video2", pkgP));
    }

    void VIDENC2Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.VIDENC2Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.VIDENC2Config", new Value.Obj("ti.sdo.ce.video2.VIDENC2Config", po));
        pkgV.bind("VIDENC2Config", vo);
        // decls 
    }

    void VIDDEC2Config$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.VIDDEC2Config.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.VIDDEC2Config", new Value.Obj("ti.sdo.ce.video2.VIDDEC2Config", po));
        pkgV.bind("VIDDEC2Config", vo);
        // decls 
    }

    void IVIDDEC2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.IVIDDEC2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.IVIDDEC2", new Value.Obj("ti.sdo.ce.video2.IVIDDEC2", po));
        pkgV.bind("IVIDDEC2", vo);
        // decls 
    }

    void IVIDENC2$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.video2.IVIDENC2.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.video2.IVIDENC2", new Value.Obj("ti.sdo.ce.video2.IVIDENC2", po));
        pkgV.bind("IVIDENC2", vo);
        // decls 
    }

    void VIDENC2Config$$CONSTS()
    {
        // module VIDENC2Config
    }

    void VIDDEC2Config$$CONSTS()
    {
        // module VIDDEC2Config
    }

    void IVIDDEC2$$CONSTS()
    {
        // interface IVIDDEC2
    }

    void IVIDENC2$$CONSTS()
    {
        // interface IVIDENC2
    }

    void VIDENC2Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDDEC2Config$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDDEC2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void IVIDENC2$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void VIDENC2Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDDEC2Config$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDDEC2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void IVIDENC2$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void VIDENC2Config$$SIZES()
    {
    }

    void VIDDEC2Config$$SIZES()
    {
    }

    void IVIDDEC2$$SIZES()
    {
    }

    void IVIDENC2$$SIZES()
    {
    }

    void VIDENC2Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDENC2Config.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.VIDENC2Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void VIDDEC2Config$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.VIDDEC2Config.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codecsList", $$T_Obj, $$UNDEF, "wh");
    }

    void IVIDDEC2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.IVIDDEC2.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video2"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("serverFxns", $$T_Str, "VIDDEC2_SKEL", "wh");
        po.addFld("stubFxns", $$T_Str, "VIDDEC2_STUBS", "wh");
        po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
        po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
        po.addFld("manageInBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
        po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void IVIDENC2$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDENC2.Module", "ti.sdo.ce.video2");
        po.init("ti.sdo.ce.video2.IVIDENC2.Module", om.findStrict("ti.sdo.ce.ICodec.Module", "ti.sdo.ce.video2"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("serverFxns", $$T_Str, "VIDENC2_SKEL", "wh");
        po.addFld("stubFxns", $$T_Str, "VIDENC2_STUBS", "wh");
        po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), 0L, "rh");
        po.addFld("codecClassConfigurable", $$T_Bool, true, "rh");
        po.addFld("manageInBufsPlaneDescCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(3L)), Global.newArray(new Object[]{true, true, true}), "wh");
        po.addFld("manageInBufsMetaPlaneDescCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(3L)), Global.newArray(new Object[]{true, true, true}), "wh");
        po.addFld("manageOutBufsCache", new Proto.Arr($$T_Bool, false, xdc.services.intern.xsr.Enum.intValue(16L)), Global.newArray(new Object[]{true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true}), "wh");
    }

    void VIDENC2Config$$ROV()
    {
    }

    void VIDDEC2Config$$ROV()
    {
    }

    void IVIDDEC2$$ROV()
    {
    }

    void IVIDENC2$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.video2.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.video2"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/video2/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.video2"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.video2"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.video2", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.video2");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.video2.");
        pkgV.bind("$vers", Global.newArray("1, 0, 3"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.video2'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/viddec2.aem3',\n");
            sb.append("'lib/debug/videnc2.aem3',\n");
            sb.append("'lib/release/viddec2.aem3',\n");
            sb.append("'lib/release/videnc2.aem3',\n");
            sb.append("'lib/debug/viddec2.ae674',\n");
            sb.append("'lib/debug/videnc2.ae674',\n");
            sb.append("'lib/release/viddec2.ae674',\n");
            sb.append("'lib/release/videnc2.ae674',\n");
            sb.append("'lib/debug/viddec2.av5T',\n");
            sb.append("'lib/debug/videnc2.av5T',\n");
            sb.append("'lib/release/viddec2.av5T',\n");
            sb.append("'lib/release/videnc2.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/viddec2.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/videnc2.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/viddec2.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/videnc2.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/viddec2.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/videnc2.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/viddec2.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/videnc2.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/viddec2.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/debug/videnc2.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/viddec2.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/videnc2.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void VIDENC2Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.VIDENC2Config", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDENC2Config.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.VIDENC2Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video2")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video2.VIDENC2Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDENC2Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDENC2Config.xdt");
        pkgV.bind("VIDENC2Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDENC2Config");
    }

    void VIDDEC2Config$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.VIDDEC2Config", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
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
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.video2")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.video2.VIDDEC2Config$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./VIDDEC2Config.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./VIDDEC2Config.xdt");
        pkgV.bind("VIDDEC2Config", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("VIDDEC2Config");
    }

    void IVIDDEC2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDDEC2.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.IVIDDEC2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ce");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDDEC2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDDEC2");
        vo.seal(null);
    }

    void IVIDENC2$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.video2.IVIDENC2", "ti.sdo.ce.video2");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.video2.IVIDENC2.Module", "ti.sdo.ce.video2");
        vo.init2(po, "ti.sdo.ce.video2.IVIDENC2", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Interface");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.video2", "ti.sdo.ce.video2"));
        tdefs.clear();
        proxies.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("ti.sdo.ce");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$interfaces")).add(vo);
        pkgV.bind("IVIDENC2", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("IVIDENC2");
        vo.seal(null);
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video2.VIDENC2Config", "ti.sdo.ce.video2"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.video2.VIDDEC2Config", "ti.sdo.ce.video2"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.video2.VIDENC2Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.VIDDEC2Config")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.IVIDDEC2")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.video2.IVIDENC2")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.video2")).add(pkgV);
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
        VIDENC2Config$$OBJECTS();
        VIDDEC2Config$$OBJECTS();
        IVIDDEC2$$OBJECTS();
        IVIDENC2$$OBJECTS();
        VIDENC2Config$$CONSTS();
        VIDDEC2Config$$CONSTS();
        IVIDDEC2$$CONSTS();
        IVIDENC2$$CONSTS();
        VIDENC2Config$$CREATES();
        VIDDEC2Config$$CREATES();
        IVIDDEC2$$CREATES();
        IVIDENC2$$CREATES();
        VIDENC2Config$$FUNCTIONS();
        VIDDEC2Config$$FUNCTIONS();
        IVIDDEC2$$FUNCTIONS();
        IVIDENC2$$FUNCTIONS();
        VIDENC2Config$$SIZES();
        VIDDEC2Config$$SIZES();
        IVIDDEC2$$SIZES();
        IVIDENC2$$SIZES();
        VIDENC2Config$$TYPES();
        VIDDEC2Config$$TYPES();
        IVIDDEC2$$TYPES();
        IVIDENC2$$TYPES();
        if (isROV) {
            VIDENC2Config$$ROV();
            VIDDEC2Config$$ROV();
            IVIDDEC2$$ROV();
            IVIDENC2$$ROV();
        }//isROV
        $$SINGLETONS();
        VIDENC2Config$$SINGLETONS();
        VIDDEC2Config$$SINGLETONS();
        IVIDDEC2$$SINGLETONS();
        IVIDENC2$$SINGLETONS();
        $$INITIALIZATION();
    }
}

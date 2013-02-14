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

public class ti_sdo_ce_utils_syscbuf
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
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.utils.syscbuf.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.utils.syscbuf", new Value.Obj("ti.sdo.ce.utils.syscbuf", pkgP));
    }

    void SysCBuf$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf", new Value.Obj("ti.sdo.ce.utils.syscbuf.SysCBuf", po));
        pkgV.bind("SysCBuf", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$Module_State", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", new Proto.Str(spo, false));
    }

    void SysCBuf$$CONSTS()
    {
        // module SysCBuf
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.abort", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_abort__E", "xdc_Void(*)(xdc_String)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.exit", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_exit__E", "xdc_Void(*)(xdc_Int)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.flush", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_flush__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.putch", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_putch__E", "xdc_Void(*)(xdc_Char)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.ready", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_ready__E", "xdc_Bool(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.bind", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_bind__E", "xdc_Int(*)(xdc_Char*,xdc_UInt32)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.get", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_get__E", "xdc_UInt32(*)(xdc_Char*,xdc_UInt32,xdc_UInt32*,xdc_UInt32*)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.getSize", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__E", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.output", new Extern("ti_sdo_ce_utils_syscbuf_SysCBuf_output__I", "xdc_Void(*)(xdc_Char*,xdc_UInt)", true, false));
    }

    void SysCBuf$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void SysCBuf$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void SysCBuf$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", "ti.sdo.ce.utils.syscbuf");
        sizes.clear();
        sizes.add(Global.newArray("outbuf", "UPtr"));
        sizes.add(Global.newArray("outidx", "UInt"));
        sizes.add(Global.newArray("wrapped", "UShort"));
        sizes.add(Global.newArray("bufSize", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void SysCBuf$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/utils/syscbuf/SysCBuf.xs");
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.Module", "ti.sdo.ce.utils.syscbuf");
        po.init("ti.sdo.ce.utils.syscbuf.SysCBuf.Module", om.findStrict("xdc.runtime.ISystemSupport.Module", "ti.sdo.ce.utils.syscbuf"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("bufSize", Proto.Elm.newCNum("(xdc_SizeT)"), 0L, "w");
            po.addFld("flushAtExit", $$T_Bool, true, "w");
            po.addFld("sectionName", $$T_Str, null, "wh");
            po.addFld("outputFxn", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"), null, "w");
            po.addFld("outputFunc", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"), "&ti_sdo_ce_utils_syscbuf_SysCBuf_output__I", "r");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef SysCBuf.OutputFxn
        om.bind("ti.sdo.ce.utils.syscbuf.SysCBuf.OutputFxn", new Proto.Adr("xdc_Void(*)(xdc_Char*,xdc_UInt)", "PFv"));
        // struct SysCBuf.Module_State
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf$$Module_State", "ti.sdo.ce.utils.syscbuf");
        po.init("ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("outbuf", new Proto.Arr(Proto.Elm.newCNum("(xdc_Char)"), false), $$DEFAULT, "w");
                po.addFld("outidx", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("wrapped", $$T_Bool, $$UNDEF, "w");
                po.addFld("bufSize", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
    }

    void SysCBuf$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf", "ti.sdo.ce.utils.syscbuf");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf$$Module_State", "ti.sdo.ce.utils.syscbuf");
        po.bind("outbuf$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Char", "isScalar", true));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.utils.syscbuf.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.utils.syscbuf"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/utils/syscbuf/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.utils.syscbuf"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.utils.syscbuf"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.utils.syscbuf"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.utils.syscbuf"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.utils.syscbuf"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.utils.syscbuf"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.utils.syscbuf", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.utils.syscbuf");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.utils.syscbuf.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.utils.syscbuf'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/syscbuf.aem3',\n");
            sb.append("'lib/release/syscbuf.aem3',\n");
            sb.append("'lib/debug/syscbuf.ae674',\n");
            sb.append("'lib/release/syscbuf.ae674',\n");
            sb.append("'lib/debug/syscbuf.av5T',\n");
            sb.append("'lib/release/syscbuf.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/syscbuf.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/release/syscbuf.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/debug/syscbuf.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/release/syscbuf.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/debug/syscbuf.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/release/syscbuf.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void SysCBuf$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf", "ti.sdo.ce.utils.syscbuf");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.Module", "ti.sdo.ce.utils.syscbuf");
        vo.init2(po, "ti.sdo.ce.utils.syscbuf.SysCBuf", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf$$capsule", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.utils.syscbuf", "ti.sdo.ce.utils.syscbuf"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        mcfgs.add("bufSize");
        mcfgs.add("flushAtExit");
        vo.bind("OutputFxn", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.OutputFxn", "ti.sdo.ce.utils.syscbuf"));
        mcfgs.add("outputFxn");
        mcfgs.add("outputFunc");
        icfgs.add("outputFunc");
        vo.bind("Module_State", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", "ti.sdo.ce.utils.syscbuf"));
        tdefs.add(om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.Module_State", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.utils.syscbuf")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("abort", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.abort", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("exit", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.exit", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("flush", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.flush", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("putch", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.putch", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("ready", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.ready", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("bind", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.bind", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("get", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.get", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("getSize", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.getSize", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("output", om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf.output", "ti.sdo.ce.utils.syscbuf"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ce_utils_syscbuf_SysCBuf_Module__startupDone__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_abort__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_exit__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_flush__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_putch__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_ready__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_bind__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_get__E", "ti_sdo_ce_utils_syscbuf_SysCBuf_getSize__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", "./SysCBuf.xdt");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        loggables.add(Global.newObject("name", "abort", "entry", "\"%s\"", "exit", ""));
        loggables.add(Global.newObject("name", "exit", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "flush", "entry", "", "exit", ""));
        loggables.add(Global.newObject("name", "putch", "entry", "%d", "exit", ""));
        loggables.add(Global.newObject("name", "ready", "entry", "", "exit", "%d"));
        loggables.add(Global.newObject("name", "bind", "entry", "%p, 0x%x", "exit", "%d"));
        loggables.add(Global.newObject("name", "get", "entry", "%p, 0x%x, %p, %p", "exit", "0x%x"));
        loggables.add(Global.newObject("name", "getSize", "entry", "", "exit", "0x%x"));
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./SysCBuf.xdt");
        pkgV.bind("SysCBuf", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("SysCBuf");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.utils.syscbuf.SysCBuf", "ti.sdo.ce.utils.syscbuf"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.utils.syscbuf.SysCBuf")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.utils.syscbuf")).add(pkgV);
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
        SysCBuf$$OBJECTS();
        SysCBuf$$CONSTS();
        SysCBuf$$CREATES();
        SysCBuf$$FUNCTIONS();
        SysCBuf$$SIZES();
        SysCBuf$$TYPES();
        if (isROV) {
            SysCBuf$$ROV();
        }//isROV
        $$SINGLETONS();
        SysCBuf$$SINGLETONS();
        $$INITIALIZATION();
    }
}

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

public class ti_sdo_ce_views
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
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.views.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.views", new Value.Obj("ti.sdo.ce.views", pkgP));
    }

    void CodecEngine$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.views.CodecEngine", new Value.Obj("ti.sdo.ce.views.CodecEngine", po));
        pkgV.bind("CodecEngine", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine$$NODE_Uuid", new Proto.Obj());
        om.bind("ti.sdo.ce.views.CodecEngine.NODE_Uuid", new Proto.Str(spo, false));
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", new Proto.Enm("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType"));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine$$Engine_AlgDesc", new Proto.Obj());
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine$$Engine_Desc", new Proto.Obj());
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_Desc", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine$$Engine_Config", new Proto.Obj());
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_Config", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.views.CodecEngine$$Engine_Meta", new Proto.Obj());
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_Meta", new Proto.Str(spo, false));
    }

    void CodecEngine$$CONSTS()
    {
        // module CodecEngine
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_DEFAULT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", "ti.sdo.ce.views"), "ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_DEFAULT", xdc.services.intern.xsr.Enum.intValue(Global.eval("-1"))+0));
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_NONCACHED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", "ti.sdo.ce.views"), "ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_NONCACHED", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_CACHED", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", "ti.sdo.ce.views"), "ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_CACHED", xdc.services.intern.xsr.Enum.intValue(1L)+0));
    }

    void CodecEngine$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void CodecEngine$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void CodecEngine$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sdo.ce.views.CodecEngine.NODE_Uuid", "ti.sdo.ce.views");
        sizes.clear();
        sizes.add(Global.newArray("data", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ce.views.CodecEngine.NODE_Uuid']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ce.views.CodecEngine.NODE_Uuid']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ce.views.CodecEngine.NODE_Uuid'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", "ti.sdo.ce.views");
        sizes.clear();
        sizes.add(Global.newArray("name", "UPtr"));
        sizes.add(Global.newArray("uuid", "Sti.sdo.ce.views.CodecEngine;NODE_Uuid"));
        sizes.add(Global.newArray("fxns", "UPtr"));
        sizes.add(Global.newArray("idmaFxns", "UPtr"));
        sizes.add(Global.newArray("typeTab", "UPtr"));
        sizes.add(Global.newArray("isLocal", "UShort"));
        sizes.add(Global.newArray("groupId", "TInt"));
        sizes.add(Global.newArray("rpcProtocolVersion", "TInt"));
        sizes.add(Global.newArray("iresFxns", "UPtr"));
        sizes.add(Global.newArray("codecClassConfig", "UPtr"));
        sizes.add(Global.newArray("memType", "Nti.sdo.ce.views.CodecEngine.Engine_CachedMemType;;-1;0;1"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_AlgDesc']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_AlgDesc']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_AlgDesc'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Desc", "ti.sdo.ce.views");
        sizes.clear();
        sizes.add(Global.newArray("name", "UPtr"));
        sizes.add(Global.newArray("algTab", "UPtr"));
        sizes.add(Global.newArray("remoteName", "UPtr"));
        sizes.add(Global.newArray("linkCfg", "UPtr"));
        sizes.add(Global.newArray("numAlgs", "TInt"));
        sizes.add(Global.newArray("heapId", "TInt"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Desc']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Desc']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Desc'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Config", "ti.sdo.ce.views");
        sizes.clear();
        sizes.add(Global.newArray("engineTab", "UPtr"));
        sizes.add(Global.newArray("localEngine", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Config']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Config']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sdo.ce.views.CodecEngine.Engine_Config'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void CodecEngine$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/views/CodecEngine.xs");
        om.bind("ti.sdo.ce.views.CodecEngine$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine.Module", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sdo.ce.views"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sdo.ce.views"), $$UNDEF, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sdo.ce.views.CodecEngine$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sdo.ce.views.CodecEngine$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sdo.ce.views.CodecEngine$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sdo.ce.views.CodecEngine$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct CodecEngine.NODE_Uuid
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$NODE_Uuid", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.NODE_Uuid", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("data", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
        // struct CodecEngine.Engine_AlgDesc
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_AlgDesc", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("uuid", (Proto)om.findStrict("ti.sdo.ce.views.CodecEngine.NODE_Uuid", "ti.sdo.ce.views"), $$DEFAULT, "w");
                po.addFld("fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("idmaFxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("typeTab", new Proto.Adr("xdc_String*", "Ps"), $$UNDEF, "w");
                po.addFld("isLocal", $$T_Bool, $$UNDEF, "w");
                po.addFld("groupId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("rpcProtocolVersion", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("iresFxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("codecClassConfig", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("memType", (Proto)om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", "ti.sdo.ce.views"), $$UNDEF, "w");
        // struct CodecEngine.Engine_Desc
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_Desc", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.Engine_Desc", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("name", $$T_Str, $$UNDEF, "w");
                po.addFld("algTab", new Proto.Adr("ti_sdo_ce_views_CodecEngine_Engine_AlgDesc*", "PS"), $$UNDEF, "w");
                po.addFld("remoteName", $$T_Str, $$UNDEF, "w");
                po.addFld("linkCfg", $$T_Str, $$UNDEF, "w");
                po.addFld("numAlgs", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("heapId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
        // struct CodecEngine.Engine_Config
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_Config", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.Engine_Config", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("engineTab", new Proto.Adr("ti_sdo_ce_views_CodecEngine_Engine_Desc*", "PS"), $$UNDEF, "w");
                po.addFld("localEngine", $$T_Str, $$UNDEF, "w");
        // struct CodecEngine.Engine_Meta
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_Meta", "ti.sdo.ce.views");
        po.init("ti.sdo.ce.views.CodecEngine.Engine_Meta", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("algName", $$T_Str, $$UNDEF, "w");
                po.addFld("isLocal", $$T_Bool, $$UNDEF, "w");
                po.addFld("heapId", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
    }

    void CodecEngine$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine", "ti.sdo.ce.views");
        vo.bind("NODE_Uuid$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.NODE_Uuid", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$NODE_Uuid", "ti.sdo.ce.views");
        vo.bind("Engine_AlgDesc$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_AlgDesc", "ti.sdo.ce.views");
        vo.bind("Engine_Desc$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.Engine_Desc", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_Desc", "ti.sdo.ce.views");
        po.bind("algTab$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", "isScalar", false));
        vo.bind("Engine_Config$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.Engine_Config", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine$$Engine_Config", "ti.sdo.ce.views");
        po.bind("engineTab$fetchDesc", Global.newObject("type", "ti.sdo.ce.views.CodecEngine.Engine_Desc", "isScalar", false));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.views.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.views"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.sdo.ce.views", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.views");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.views.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.views'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void CodecEngine$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine", "ti.sdo.ce.views");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine.Module", "ti.sdo.ce.views");
        vo.init2(po, "ti.sdo.ce.views.CodecEngine", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sdo.ce.views.CodecEngine$$capsule", "ti.sdo.ce.views"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.views", "ti.sdo.ce.views"));
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
        vo.bind("NODE_Uuid", om.findStrict("ti.sdo.ce.views.CodecEngine.NODE_Uuid", "ti.sdo.ce.views"));
        tdefs.add(om.findStrict("ti.sdo.ce.views.CodecEngine.NODE_Uuid", "ti.sdo.ce.views"));
        vo.bind("Engine_CachedMemType", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_CachedMemType", "ti.sdo.ce.views"));
        vo.bind("Engine_AlgDesc", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", "ti.sdo.ce.views"));
        tdefs.add(om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_AlgDesc", "ti.sdo.ce.views"));
        vo.bind("Engine_Desc", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Desc", "ti.sdo.ce.views"));
        tdefs.add(om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Desc", "ti.sdo.ce.views"));
        vo.bind("Engine_Config", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Config", "ti.sdo.ce.views"));
        tdefs.add(om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Config", "ti.sdo.ce.views"));
        vo.bind("Engine_Meta", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Meta", "ti.sdo.ce.views"));
        tdefs.add(om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_Meta", "ti.sdo.ce.views"));
        vo.bind("Engine_USECACHEDMEM_DEFAULT", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_DEFAULT", "ti.sdo.ce.views"));
        vo.bind("Engine_USECACHEDMEM_NONCACHED", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_NONCACHED", "ti.sdo.ce.views"));
        vo.bind("Engine_USECACHEDMEM_CACHED", om.findStrict("ti.sdo.ce.views.CodecEngine.Engine_USECACHEDMEM_CACHED", "ti.sdo.ce.views"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.views")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ce_views_CodecEngine_Module__startupDone__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("CodecEngine", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("CodecEngine");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.views.CodecEngine", "ti.sdo.ce.views"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sdo.ce.views.CodecEngine", "ti.sdo.ce.views");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitBasic", "structName", "Engine_Meta")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.views.CodecEngine")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.views")).add(pkgV);
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
        CodecEngine$$OBJECTS();
        CodecEngine$$CONSTS();
        CodecEngine$$CREATES();
        CodecEngine$$FUNCTIONS();
        CodecEngine$$SIZES();
        CodecEngine$$TYPES();
        if (isROV) {
            CodecEngine$$ROV();
        }//isROV
        $$SINGLETONS();
        CodecEngine$$SINGLETONS();
        $$INITIALIZATION();
    }
}

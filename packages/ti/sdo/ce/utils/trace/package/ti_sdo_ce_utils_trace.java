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

public class ti_sdo_ce_utils_trace
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
        pkgP = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sdo.ce.utils.trace", new Value.Obj("ti.sdo.ce.utils.trace", pkgP));
    }

    void TraceUtil$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil", new Value.Obj("ti.sdo.ce.utils.trace.TraceUtil", po));
        pkgV.bind("TraceUtil", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil$$PipeCmdAlias", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", new Proto.Str(spo, true));
        spo = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil$$Attrs", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.Attrs", new Proto.Str(spo, true));
    }

    void TraceUtil_Module_GateProxy$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", new Value.Obj("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", po));
        pkgV.bind("TraceUtil_Module_GateProxy", vo);
        // decls 
        // insts 
        Object insP = om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Object", new Proto.Obj());
        Object objP = om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Params", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Params", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Instance_State", new Proto.Obj());
        om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance_State", new Proto.Str(po, false));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Handle", insP);
        if (isROV) {
            om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Object", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance_State", "ti.sdo.ce.utils.trace"));
        }//isROV
    }

    void TraceUtil$$CONSTS()
    {
        // module TraceUtil
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.NO_TRACING", Global.newObject("localTraceMask", "*=", "localTraceFile", null, "dsp0TraceMask", "*=", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.DEFAULT_TRACING", Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.SOCRATES_TRACING", Global.newObject("localTraceMask", "*=67", "localTraceFile", "/tmp/cearmlog.txt", "dsp0TraceMask", "*=67", "dsp0TraceFile", "/tmp/cedsp0log.txt", "dsp0BiosFile", "/tmp/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{Global.newObject("alias", "socrates=on", "cmds", Global.newArray(new Object[]{"tracemask=*+5", "dsp0tracemask=*+5,ti.bios+3", "refreshperiod=200"})), Global.newObject("alias", "socrates=off", "cmds", Global.newArray(new Object[]{"tracemask=*-5", "refreshperiod=0", "dsp0tracemask=*-5,ti.bios-3"}))})));
        om.bind("ti.sdo.ce.utils.trace.TraceUtil.FULL_TRACING", Global.newObject("localTraceMask", "*=01234567", "localTraceFile", "trace/cearmlog.txt", "dsp0TraceMask", "*=01234567,ti.bios=01324567", "dsp0TraceFile", "trace/cedsp0log.txt", "dsp0BiosFile", "trace/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 100L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})));
    }

    void TraceUtil_Module_GateProxy$$CONSTS()
    {
        // module TraceUtil_Module_GateProxy
        om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.query", new Extern("ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_query__E", "xdc_Bool(*)(xdc_Int)", true, false));
    }

    void TraceUtil$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TraceUtil_Module_GateProxy$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sdo$ce$utils$trace$TraceUtil_Module_GateProxy$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.create() called before xdc.useModule('ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy')\");\n");
                sb.append("}\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$create", new Proto.Fxn(om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Module", "ti.sdo.ce.utils.trace"), om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", "ti.sdo.ce.utils.trace"), 1, 0, false));
                        fxn.addArg(0, "__params", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Params", "ti.sdo.ce.utils.trace"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sdo$ce$utils$trace$TraceUtil_Module_GateProxy$$create = function( __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy'];\n");
                sb.append("var __inst = xdc.om['ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sdo.ce.utils.trace']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy'].Instance_State);\n");
                sb.append("if (!__mod.delegate$) {\n");
                    sb.append("throw new Error(\"Unbound proxy module: ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy\");\n");
                sb.append("}\n");
                sb.append("var __dmod = __mod.delegate$.$orig;\n");
                sb.append("var __dinst = __dmod.create(__params);\n");
                sb.append("__inst.$$bind('delegate$', __dinst);\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, []);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TraceUtil$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TraceUtil_Module_GateProxy$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TraceUtil$$SIZES()
    {
    }

    void TraceUtil_Module_GateProxy$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void TraceUtil$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Module", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("NO_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=", "localTraceFile", null, "dsp0TraceMask", "*=", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
                po.addFld("DEFAULT_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
                po.addFld("SOCRATES_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", "/tmp/cearmlog.txt", "dsp0TraceMask", "*=67", "dsp0TraceFile", "/tmp/cedsp0log.txt", "dsp0BiosFile", "/tmp/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 0L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{Global.newObject("alias", "socrates=on", "cmds", Global.newArray(new Object[]{"tracemask=*+5", "dsp0tracemask=*+5,ti.bios+3", "refreshperiod=200"})), Global.newObject("alias", "socrates=off", "cmds", Global.newArray(new Object[]{"tracemask=*-5", "refreshperiod=0", "dsp0tracemask=*-5,ti.bios-3"}))})), "rh");
                po.addFld("FULL_TRACING", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=01234567", "localTraceFile", "trace/cearmlog.txt", "dsp0TraceMask", "*=01234567,ti.bios=01324567", "dsp0TraceFile", "trace/cedsp0log.txt", "dsp0BiosFile", "trace/bioslog.dat", "traceFileFlags", "w", "refreshPeriod", 100L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "rh");
        po.addFld("attrs", (Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"), Global.newObject("localTraceMask", "*=67", "localTraceFile", null, "dsp0TraceMask", "*=67", "dsp0TraceFile", null, "dsp0BiosFile", null, "traceFileFlags", null, "refreshPeriod", 300L, "cmdPipeFile", "/tmp/cecmdpipe", "cmdAliases", Global.newArray(new Object[]{})), "wh");
        po.addFldV("Module_GateProxy", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ce.utils.trace"), null, "wh", $$delegGet, $$delegSet);
        // struct TraceUtil.PipeCmdAlias
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil$$PipeCmdAlias", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("alias", $$T_Str, $$UNDEF, "w");
                po.addFld("cmds", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
        // struct TraceUtil.Attrs
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil$$Attrs", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil.Attrs", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("localTraceMask", $$T_Str, $$UNDEF, "w");
                po.addFld("localTraceFile", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0TraceMask", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0TraceFile", $$T_Str, $$UNDEF, "w");
                po.addFld("dsp0BiosFile", $$T_Str, $$UNDEF, "w");
                po.addFld("traceFileFlags", $$T_Str, $$UNDEF, "w");
                po.addFld("refreshPeriod", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("cmdPipeFile", $$T_Str, $$UNDEF, "w");
                po.addFld("cmdAliases", new Proto.Arr((Proto)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"), false), $$DEFAULT, "w");
    }

    void TraceUtil_Module_GateProxy$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Module", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Module", om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ce.utils.trace"));
                po.addFld("delegate$", (Proto)om.findStrict("xdc.runtime.IGateProvider.Module", "ti.sdo.ce.utils.trace"), null, "wh");
                po.addFld("abstractInstances$", $$T_Bool, false, "wh");
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$create", "ti.sdo.ce.utils.trace"), Global.get("ti$sdo$ce$utils$trace$TraceUtil_Module_GateProxy$$create"));
        }//isCFG
                po.addFxn("queryMeta", (Proto.Fxn)om.findStrict("xdc.runtime.IGateProvider$$queryMeta", "ti.sdo.ce.utils.trace"), $$UNDEF);
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", om.findStrict("xdc.runtime.IGateProvider.Instance", "ti.sdo.ce.utils.trace"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ce.utils.trace"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Params", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Params", om.findStrict("xdc.runtime.IGateProvider$$Params", "ti.sdo.ce.utils.trace"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("Q_BLOCKING", Proto.Elm.newCNum("(xdc_Int)"), 1L, "rh");
                po.addFld("Q_PREEMPTING", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sdo.ce.utils.trace"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Object", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Object", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", "ti.sdo.ce.utils.trace"));
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Instance_State", "ti.sdo.ce.utils.trace");
        po.init("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance_State", null);
        po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void TraceUtil$$ROV()
    {
    }

    void TraceUtil_Module_GateProxy$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", "ti.sdo.ce.utils.trace");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy$$Instance_State", "ti.sdo.ce.utils.trace");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sdo.ce.utils.trace.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sdo.ce.utils.trace"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sdo/ce/utils/trace/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sdo.ce.utils.trace"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sdo.ce.utils.trace"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sdo.ce.utils.trace", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sdo.ce.utils.trace");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sdo.ce.utils.trace.");
        pkgV.bind("$vers", Global.newArray("1, 0, 1"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sdo.ce.utils.trace'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/release/TraceUtil.av5T',\n");
            sb.append("'lib/debug/TraceUtil.av5T',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/release/TraceUtil.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
            sb.append("['lib/debug/TraceUtil.av5T', {target: 'gnu.targets.arm.GCArmv5T', suffix: 'v5T'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void TraceUtil$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil", "ti.sdo.ce.utils.trace");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Module", "ti.sdo.ce.utils.trace");
        vo.init2(po, "ti.sdo.ce.utils.trace.TraceUtil", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.sdo.ce.utils.trace", "ti.sdo.ce.utils.trace"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("PipeCmdAlias", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"));
        tdefs.add(om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.PipeCmdAlias", "ti.sdo.ce.utils.trace"));
        vo.bind("Attrs", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"));
        tdefs.add(om.findStrict("ti.sdo.ce.utils.trace.TraceUtil.Attrs", "ti.sdo.ce.utils.trace"));
        vo.bind("Module_GateProxy$proxy", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", "ti.sdo.ce.utils.trace"));
        proxies.add("Module_GateProxy");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.utils.trace")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.sdo.ce.utils.trace.TraceUtil$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", "./TraceUtil.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./TraceUtil.xdt");
        pkgV.bind("TraceUtil", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TraceUtil");
    }

    void TraceUtil_Module_GateProxy$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", "ti.sdo.ce.utils.trace");
        po = (Proto.Obj)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Module", "ti.sdo.ce.utils.trace");
        vo.init2(po, "ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("Instance", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance", "ti.sdo.ce.utils.trace"));
        vo.bind("Params", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Params", "ti.sdo.ce.utils.trace"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Params", "ti.sdo.ce.utils.trace")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Handle", "ti.sdo.ce.utils.trace"));
        vo.bind("$package", om.findStrict("ti.sdo.ce.utils.trace", "ti.sdo.ce.utils.trace"));
        tdefs.clear();
        proxies.clear();
        proxies.add("delegate$");
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sdo.ce.utils.trace")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 0);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
            vo.bind("__initObject", Global.get("ti$sdo$ce$utils$trace$TraceUtil_Module_GateProxy$$__initObject"));
        }//isCFG
        vo.bind("query", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.query", "ti.sdo.ce.utils.trace"));
        vo.bind("$$fxntab", Global.newArray("ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Handle__label", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Module__startupDone", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__create", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__delete", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__destruct", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__get", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__first", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Object__next", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Params__init", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Proxy__abstract", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__Proxy__delegate", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__queryMeta", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__query", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__enter", "ti_sdo_ce_utils_trace_TraceUtil_Module_GateProxy_DELEGATE__leave"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Object", "ti.sdo.ce.utils.trace"));
        vo.bind("Instance_State", om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy.Instance_State", "ti.sdo.ce.utils.trace"));
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 1);
        loggables.clear();
        loggables.add(Global.newObject("name", "query", "entry", "%d", "exit", "%d"));
        loggables.add(Global.newObject("name", "enter", "entry", "%p", "exit", "%p"));
        loggables.add(Global.newObject("name", "leave", "entry", "%p, %p", "exit", ""));
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TraceUtil_Module_GateProxy", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TraceUtil_Module_GateProxy");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sdo.ce.utils.trace")).findStrict("PARAMS", "ti.sdo.ce.utils.trace");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", "ti.sdo.ce.utils.trace")).findStrict("PARAMS", "ti.sdo.ce.utils.trace");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil", "ti.sdo.ce.utils.trace"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy", "ti.sdo.ce.utils.trace"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sdo.ce.utils.trace.TraceUtil")).bless();
        ((Value.Obj)om.getv("ti.sdo.ce.utils.trace.TraceUtil_Module_GateProxy")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sdo.ce.utils.trace")).add(pkgV);
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
        TraceUtil$$OBJECTS();
        TraceUtil_Module_GateProxy$$OBJECTS();
        TraceUtil$$CONSTS();
        TraceUtil_Module_GateProxy$$CONSTS();
        TraceUtil$$CREATES();
        TraceUtil_Module_GateProxy$$CREATES();
        TraceUtil$$FUNCTIONS();
        TraceUtil_Module_GateProxy$$FUNCTIONS();
        TraceUtil$$SIZES();
        TraceUtil_Module_GateProxy$$SIZES();
        TraceUtil$$TYPES();
        TraceUtil_Module_GateProxy$$TYPES();
        if (isROV) {
            TraceUtil$$ROV();
            TraceUtil_Module_GateProxy$$ROV();
        }//isROV
        $$SINGLETONS();
        TraceUtil$$SINGLETONS();
        TraceUtil_Module_GateProxy$$SINGLETONS();
        $$INITIALIZATION();
    }
}

#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = ti/sdo/ce/alg
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/include/utils.tci:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/include/utils.tci
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xdc.tci:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xdc.tci
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/template.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/template.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/om2.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/om2.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen2.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen2.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/IPackage.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/IPackage.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Clock.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Clock.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Trace.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Trace.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/bld.js:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/bld.js
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/BuildEnvironment.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/PackageContents.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/PackageContents.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/_gen.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/_gen.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Library.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Library.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Executable.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Executable.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Repository.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Repository.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Configuration.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Configuration.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Script.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Script.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Manifest.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Manifest.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Utils.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Utils.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget2.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget2.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITargetFilter.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITargetFilter.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/xdc/bld/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/codec_engine.bld:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/codec_engine.bld
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/ITarget.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/ITarget.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/C28_large.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/C28_large.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/C28_float.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/C28_float.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/IArm.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/IArm.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/elf/IArm.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/elf/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/elf/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/ITarget.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/ITarget.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/TMS470.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/TMS470.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/ITarget.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/ITarget.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Linux86.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Linux86.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Mingw.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Mingw.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/MVArm9.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/MVArm9.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/UCArm9.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/UCArm9.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/package.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv6.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv6.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv7A.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv7A.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M3.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M3.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4F.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4F.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/MVArm9.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/MVArm9.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/UCArm9.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/UCArm9.xs
/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/package.xs:
package.mak: /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/package.xs
package.mak: package.bld
endif

ti.targets.arm.elf.M3.rootDir ?= /proj/productization/tools/cgt470/cgt470_4_9_2/
ti.targets.arm.elf.packageBase ?= /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/arm/elf/
ti.targets.elf.C674.rootDir ?= /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/dsp-devkit/cgt6x_7_3_1
ti.targets.elf.packageBase ?= /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/ti/targets/elf/
gnu.targets.arm.GCArmv5T.rootDir ?= /codesourcery/arm-2009q1/
gnu.targets.arm.packageBase ?= /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/
.PRECIOUS: $(XDCCFGDIR)/%.oem3
.PHONY: all,em3 .dlls,em3 .executables,em3 test,em3
all,em3: .executables,em3
.executables,em3: .libraries,em3
.executables,em3: .dlls,em3
.dlls,em3: .libraries,em3
.libraries,em3: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,em3
	@$(ECHO) xdc .executables,em3
	@$(ECHO) xdc .libraries,em3
	@$(ECHO) xdc .dlls,em3

.PRECIOUS: $(XDCCFGDIR)/%.oe674
.PHONY: all,e674 .dlls,e674 .executables,e674 test,e674
all,e674: .executables,e674
.executables,e674: .libraries,e674
.executables,e674: .dlls,e674
.dlls,e674: .libraries,e674
.libraries,e674: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,e674
	@$(ECHO) xdc .executables,e674
	@$(ECHO) xdc .libraries,e674
	@$(ECHO) xdc .dlls,e674

.PRECIOUS: $(XDCCFGDIR)/%.ov5T
.PHONY: all,v5T .dlls,v5T .executables,v5T test,v5T
all,v5T: .executables,v5T
.executables,v5T: .libraries,v5T
.executables,v5T: .dlls,v5T
.dlls,v5T: .libraries,v5T
.libraries,v5T: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,v5T
	@$(ECHO) xdc .executables,v5T
	@$(ECHO) xdc .libraries,v5T
	@$(ECHO) xdc .dlls,v5T


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_ti.sdo.ce.alg.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package ti.sdo.ce.alg" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

ifeq (,$(MK_NOGENDEPS))
-include package/package.cfg.dep
endif

package/package.ext.xml: package/package.cfg.xdc.inc
package/package.cfg.xdc.inc: $(XDCROOT)/packages/xdc/cfg/cfginc.js package.xdc
	@$(MSG) generating schema include file list ...
	$(CONFIG) -f $(XDCROOT)/packages/xdc/cfg/cfginc.js ti.sdo.ce.alg $@

.libraries,em3 .libraries: lib/debug/Algorithm_BIOS.aem3

-include lib/debug/Algorithm_BIOS.aem3.mak
lib/debug/Algorithm_BIOS.aem3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3 package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oem3  into $@ ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/ar470  rq $@   package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3 package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oem3 
lib/debug/Algorithm_BIOS.aem3: export C_DIR=
lib/debug/Algorithm_BIOS.aem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 clean::
	-$(RM) lib/debug/Algorithm_BIOS.aem3
.libraries,em3 .libraries: lib/release/Algorithm_BIOS.aem3

-include lib/release/Algorithm_BIOS.aem3.mak
lib/release/Algorithm_BIOS.aem3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3 package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oem3  into $@ ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/ar470  rq $@   package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3 package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oem3 
lib/release/Algorithm_BIOS.aem3: export C_DIR=
lib/release/Algorithm_BIOS.aem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 clean::
	-$(RM) lib/release/Algorithm_BIOS.aem3
.libraries,e674 .libraries: lib/debug/Algorithm_BIOS.ae674

-include lib/debug/Algorithm_BIOS.ae674.mak
lib/debug/Algorithm_BIOS.ae674: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674 package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oe674  into $@ ...
	$(ti.targets.elf.C674.rootDir)/bin/ar6x  rq $@   package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674 package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oe674 
lib/debug/Algorithm_BIOS.ae674: export C_DIR=
lib/debug/Algorithm_BIOS.ae674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 clean::
	-$(RM) lib/debug/Algorithm_BIOS.ae674
.libraries,e674 .libraries: lib/release/Algorithm_BIOS.ae674

-include lib/release/Algorithm_BIOS.ae674.mak
lib/release/Algorithm_BIOS.ae674: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674 package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oe674  into $@ ...
	$(ti.targets.elf.C674.rootDir)/bin/ar6x  rq $@   package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674 package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oe674 
lib/release/Algorithm_BIOS.ae674: export C_DIR=
lib/release/Algorithm_BIOS.ae674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 clean::
	-$(RM) lib/release/Algorithm_BIOS.ae674
.libraries,v5T .libraries: lib/debug/Algorithm_noOS.av5T

-include lib/debug/Algorithm_noOS.av5T.mak
lib/debug/Algorithm_noOS.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/debug/Algorithm_noOS/Algorithm_noOS.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/debug/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/debug/Algorithm_noOS/Algorithm_noOS.ov5T 
lib/debug/Algorithm_noOS.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/debug/Algorithm_noOS.av5T
.libraries,v5T .libraries: lib/debug/alg.av5T

-include lib/debug/alg.av5T.mak
lib/debug/alg.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/debug/alg/alg_control.ov5T package/lib/lib/debug/alg/alg_create.ov5T package/lib/lib/debug/alg/alg_malloc.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/debug/alg/alg_control.ov5T package/lib/lib/debug/alg/alg_create.ov5T package/lib/lib/debug/alg/alg_malloc.ov5T 
lib/debug/alg.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/debug/alg.av5T
.libraries,v5T .libraries: lib/release/Algorithm_noOS.av5T

-include lib/release/Algorithm_noOS.av5T.mak
lib/release/Algorithm_noOS.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/release/Algorithm_noOS/Algorithm_noOS.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/release/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/release/Algorithm_noOS/Algorithm_noOS.ov5T 
lib/release/Algorithm_noOS.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/release/Algorithm_noOS.av5T
.libraries,v5T .libraries: lib/release/alg.av5T

-include lib/release/alg.av5T.mak
lib/release/alg.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/alg/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/release/alg/alg_control.ov5T package/lib/lib/release/alg/alg_create.ov5T package/lib/lib/release/alg/alg_malloc.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/release/alg/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/release/alg/alg_control.ov5T package/lib/lib/release/alg/alg_create.ov5T package/lib/lib/release/alg/alg_malloc.ov5T 
lib/release/alg.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/release/alg.av5T
test:;
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
.PHONY: package_ti.sdo.ce.alg.oem3,copy
package_ti.sdo.ce.alg.oem3,copy : package_ti.sdo.ce.alg.oem3,0,copy package_ti.sdo.ce.alg.oem3,1,copy 
	@

package_ti.sdo.ce.alg.oem3,0,copy : package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3
package_ti.sdo.ce.alg.oem3,1,copy : package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oem3
.PHONY: package_ti.sdo.ce.alg.sem3,copy
package_ti.sdo.ce.alg.sem3,copy : package_ti.sdo.ce.alg.sem3,0,copy package_ti.sdo.ce.alg.sem3,1,copy 
	@

package_ti.sdo.ce.alg.sem3,0,copy : package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.sem3
package_ti.sdo.ce.alg.sem3,1,copy : package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.sem3
.PHONY: Algorithm_BIOS.oem3,copy
Algorithm_BIOS.oem3,copy : Algorithm_BIOS.oem3,0,copy Algorithm_BIOS.oem3,1,copy 
	@

Algorithm_BIOS.oem3,0,copy : package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oem3
Algorithm_BIOS.oem3,1,copy : package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oem3
.PHONY: Algorithm_BIOS.sem3,copy
Algorithm_BIOS.sem3,copy : Algorithm_BIOS.sem3,0,copy Algorithm_BIOS.sem3,1,copy 
	@

Algorithm_BIOS.sem3,0,copy : package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.sem3
Algorithm_BIOS.sem3,1,copy : package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.sem3
.PHONY: package_ti.sdo.ce.alg.oe674,copy
package_ti.sdo.ce.alg.oe674,copy : package_ti.sdo.ce.alg.oe674,0,copy package_ti.sdo.ce.alg.oe674,1,copy 
	@

package_ti.sdo.ce.alg.oe674,0,copy : package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674
package_ti.sdo.ce.alg.oe674,1,copy : package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.oe674
.PHONY: package_ti.sdo.ce.alg.se674,copy
package_ti.sdo.ce.alg.se674,copy : package_ti.sdo.ce.alg.se674,0,copy package_ti.sdo.ce.alg.se674,1,copy 
	@

package_ti.sdo.ce.alg.se674,0,copy : package/lib/lib/debug/Algorithm_BIOS/package/package_ti.sdo.ce.alg.se674
package_ti.sdo.ce.alg.se674,1,copy : package/lib/lib/release/Algorithm_BIOS/package/package_ti.sdo.ce.alg.se674
.PHONY: Algorithm_BIOS.oe674,copy
Algorithm_BIOS.oe674,copy : Algorithm_BIOS.oe674,0,copy Algorithm_BIOS.oe674,1,copy 
	@

Algorithm_BIOS.oe674,0,copy : package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.oe674
Algorithm_BIOS.oe674,1,copy : package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.oe674
.PHONY: Algorithm_BIOS.se674,copy
Algorithm_BIOS.se674,copy : Algorithm_BIOS.se674,0,copy Algorithm_BIOS.se674,1,copy 
	@

Algorithm_BIOS.se674,0,copy : package/lib/lib/debug/Algorithm_BIOS/Algorithm_BIOS.se674
Algorithm_BIOS.se674,1,copy : package/lib/lib/release/Algorithm_BIOS/Algorithm_BIOS.se674
.PHONY: package_ti.sdo.ce.alg.ov5T,copy
package_ti.sdo.ce.alg.ov5T,copy : package_ti.sdo.ce.alg.ov5T,0,copy package_ti.sdo.ce.alg.ov5T,1,copy package_ti.sdo.ce.alg.ov5T,2,copy package_ti.sdo.ce.alg.ov5T,3,copy 
	@

package_ti.sdo.ce.alg.ov5T,0,copy : package/lib/lib/debug/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T
package_ti.sdo.ce.alg.ov5T,1,copy : package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T
package_ti.sdo.ce.alg.ov5T,2,copy : package/lib/lib/release/Algorithm_noOS/package/package_ti.sdo.ce.alg.ov5T
package_ti.sdo.ce.alg.ov5T,3,copy : package/lib/lib/release/alg/package/package_ti.sdo.ce.alg.ov5T
.PHONY: package_ti.sdo.ce.alg.sv5T,copy
package_ti.sdo.ce.alg.sv5T,copy : package_ti.sdo.ce.alg.sv5T,0,copy package_ti.sdo.ce.alg.sv5T,1,copy package_ti.sdo.ce.alg.sv5T,2,copy package_ti.sdo.ce.alg.sv5T,3,copy 
	@

package_ti.sdo.ce.alg.sv5T,0,copy : package/lib/lib/debug/Algorithm_noOS/package/package_ti.sdo.ce.alg.sv5T
package_ti.sdo.ce.alg.sv5T,1,copy : package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.sv5T
package_ti.sdo.ce.alg.sv5T,2,copy : package/lib/lib/release/Algorithm_noOS/package/package_ti.sdo.ce.alg.sv5T
package_ti.sdo.ce.alg.sv5T,3,copy : package/lib/lib/release/alg/package/package_ti.sdo.ce.alg.sv5T
.PHONY: Algorithm_noOS.ov5T,copy
Algorithm_noOS.ov5T,copy : Algorithm_noOS.ov5T,0,copy Algorithm_noOS.ov5T,1,copy 
	@

Algorithm_noOS.ov5T,0,copy : package/lib/lib/debug/Algorithm_noOS/Algorithm_noOS.ov5T
Algorithm_noOS.ov5T,1,copy : package/lib/lib/release/Algorithm_noOS/Algorithm_noOS.ov5T
.PHONY: Algorithm_noOS.sv5T,copy
Algorithm_noOS.sv5T,copy : Algorithm_noOS.sv5T,0,copy Algorithm_noOS.sv5T,1,copy 
	@

Algorithm_noOS.sv5T,0,copy : package/lib/lib/debug/Algorithm_noOS/Algorithm_noOS.sv5T
Algorithm_noOS.sv5T,1,copy : package/lib/lib/release/Algorithm_noOS/Algorithm_noOS.sv5T
.PHONY: alg_control.ov5T,copy
alg_control.ov5T,copy : alg_control.ov5T,0,copy alg_control.ov5T,1,copy 
	@

alg_control.ov5T,0,copy : package/lib/lib/debug/alg/alg_control.ov5T
alg_control.ov5T,1,copy : package/lib/lib/release/alg/alg_control.ov5T
.PHONY: alg_control.sv5T,copy
alg_control.sv5T,copy : alg_control.sv5T,0,copy alg_control.sv5T,1,copy 
	@

alg_control.sv5T,0,copy : package/lib/lib/debug/alg/alg_control.sv5T
alg_control.sv5T,1,copy : package/lib/lib/release/alg/alg_control.sv5T
.PHONY: alg_create.ov5T,copy
alg_create.ov5T,copy : alg_create.ov5T,0,copy alg_create.ov5T,1,copy 
	@

alg_create.ov5T,0,copy : package/lib/lib/debug/alg/alg_create.ov5T
alg_create.ov5T,1,copy : package/lib/lib/release/alg/alg_create.ov5T
.PHONY: alg_create.sv5T,copy
alg_create.sv5T,copy : alg_create.sv5T,0,copy alg_create.sv5T,1,copy 
	@

alg_create.sv5T,0,copy : package/lib/lib/debug/alg/alg_create.sv5T
alg_create.sv5T,1,copy : package/lib/lib/release/alg/alg_create.sv5T
.PHONY: alg_malloc.ov5T,copy
alg_malloc.ov5T,copy : alg_malloc.ov5T,0,copy alg_malloc.ov5T,1,copy 
	@

alg_malloc.ov5T,0,copy : package/lib/lib/debug/alg/alg_malloc.ov5T
alg_malloc.ov5T,1,copy : package/lib/lib/release/alg/alg_malloc.ov5T
.PHONY: alg_malloc.sv5T,copy
alg_malloc.sv5T,copy : alg_malloc.sv5T,0,copy alg_malloc.sv5T,1,copy 
	@

alg_malloc.sv5T,0,copy : package/lib/lib/debug/alg/alg_malloc.sv5T
alg_malloc.sv5T,1,copy : package/lib/lib/release/alg/alg_malloc.sv5T

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,ti_sdo_ce_alg
ti_sdo_ce_alg.tar: package/package.bld.xml
ti_sdo_ce_alg.tar: package/package.ext.xml
ti_sdo_ce_alg.tar: package/package.rel.dot
ti_sdo_ce_alg.tar: package/build.cfg
ti_sdo_ce_alg.tar: package/package.xdc.inc
ti_sdo_ce_alg.tar: alg.h
ti_sdo_ce_alg.tar: Algorithm.h
ti_sdo_ce_alg.tar: _alg.h
ti_sdo_ce_alg.tar: package.bld
ti_sdo_ce_alg.tar: _Algorithm.h
ti_sdo_ce_alg.tar: simple_GCArmv5T.mak
ti_sdo_ce_alg.tar: alg_control.c
ti_sdo_ce_alg.tar: alg_create.c
ti_sdo_ce_alg.tar: alg_malloc.c
ti_sdo_ce_alg.tar: Algorithm_BIOS.c
ti_sdo_ce_alg.tar: Algorithm_noOS.c
ti_sdo_ce_alg.tar: package/package.cfg.xdc.inc
ti_sdo_ce_alg.tar: lib/debug/Algorithm_BIOS.aem3
ti_sdo_ce_alg.tar: package/package_ti.sdo.ce.alg.c
ti_sdo_ce_alg.tar: lib/release/Algorithm_BIOS.aem3
ti_sdo_ce_alg.tar: lib/debug/Algorithm_BIOS.ae674
ti_sdo_ce_alg.tar: lib/release/Algorithm_BIOS.ae674
ti_sdo_ce_alg.tar: lib/debug/Algorithm_noOS.av5T
ti_sdo_ce_alg.tar: lib/debug/alg.av5T
ti_sdo_ce_alg.tar: lib/release/Algorithm_noOS.av5T
ti_sdo_ce_alg.tar: lib/release/alg.av5T
ifeq (,$(MK_NOGENDEPS))
-include package/rel/ti_sdo_ce_alg.tar.dep
endif
package/rel/ti_sdo_ce_alg/ti/sdo/ce/alg/package/package.rel.xml:

ti_sdo_ce_alg.tar: package/rel/ti_sdo_ce_alg.xdc.inc package/rel/ti_sdo_ce_alg/ti/sdo/ce/alg/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/ti_sdo_ce_alg.xdc.inc,package/rel/ti_sdo_ce_alg.tar.dep)


release release,ti_sdo_ce_alg: all ti_sdo_ce_alg.tar
clean:: .clean
	-$(RM) ti_sdo_ce_alg.tar
	-$(RM) package/rel/ti_sdo_ce_alg.xdc.inc
	-$(RM) package/rel/ti_sdo_ce_alg.tar.dep

clean:: .clean
	-$(RM) .libraries .libraries,*
clean:: 
	-$(RM) .dlls .dlls,*
#
# The following clean rule removes user specified
# generated files or directories.
#
	-$(RMDIR) lib/

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard lib))
    $(shell $(MKDIR) lib)
endif
ifeq (,$(wildcard lib/debug))
    $(shell $(MKDIR) lib/debug)
endif
ifeq (,$(wildcard lib/release))
    $(shell $(MKDIR) lib/release)
endif
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
ifeq (,$(wildcard package/external))
    $(shell $(MKDIR) package/external)
endif
ifeq (,$(wildcard package/lib/lib))
    $(shell $(MKDIR) package/lib/lib)
endif
ifeq (,$(wildcard package/lib/lib/debug))
    $(shell $(MKDIR) package/lib/lib/debug)
endif
ifeq (,$(wildcard package/lib/lib/debug/Algorithm_BIOS))
    $(shell $(MKDIR) package/lib/lib/debug/Algorithm_BIOS)
endif
ifeq (,$(wildcard package/lib/lib/debug/Algorithm_BIOS/package))
    $(shell $(MKDIR) package/lib/lib/debug/Algorithm_BIOS/package)
endif
ifeq (,$(wildcard package/lib/lib/release))
    $(shell $(MKDIR) package/lib/lib/release)
endif
ifeq (,$(wildcard package/lib/lib/release/Algorithm_BIOS))
    $(shell $(MKDIR) package/lib/lib/release/Algorithm_BIOS)
endif
ifeq (,$(wildcard package/lib/lib/release/Algorithm_BIOS/package))
    $(shell $(MKDIR) package/lib/lib/release/Algorithm_BIOS/package)
endif
ifeq (,$(wildcard package/lib/lib/debug/Algorithm_noOS))
    $(shell $(MKDIR) package/lib/lib/debug/Algorithm_noOS)
endif
ifeq (,$(wildcard package/lib/lib/debug/Algorithm_noOS/package))
    $(shell $(MKDIR) package/lib/lib/debug/Algorithm_noOS/package)
endif
ifeq (,$(wildcard package/lib/lib/debug/alg))
    $(shell $(MKDIR) package/lib/lib/debug/alg)
endif
ifeq (,$(wildcard package/lib/lib/debug/alg/package))
    $(shell $(MKDIR) package/lib/lib/debug/alg/package)
endif
ifeq (,$(wildcard package/lib/lib/release/Algorithm_noOS))
    $(shell $(MKDIR) package/lib/lib/release/Algorithm_noOS)
endif
ifeq (,$(wildcard package/lib/lib/release/Algorithm_noOS/package))
    $(shell $(MKDIR) package/lib/lib/release/Algorithm_noOS/package)
endif
ifeq (,$(wildcard package/lib/lib/release/alg))
    $(shell $(MKDIR) package/lib/lib/release/alg)
endif
ifeq (,$(wildcard package/lib/lib/release/alg/package))
    $(shell $(MKDIR) package/lib/lib/release/alg/package)
endif
endif
clean::
	-$(RMDIR) package


clean:: 
	-$(RM) package/ti.sdo.ce.alg.pjt
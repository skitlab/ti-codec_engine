#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = ti/sdo/ce/image
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
package/%.xdc.inc package/%_ti.sdo.ce.image.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package ti.sdo.ce.image" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

ifeq (,$(MK_NOGENDEPS))
-include package/package.cfg.dep
endif

package/package.ext.xml: package/package.cfg.xdc.inc
package/package.cfg.xdc.inc: $(XDCROOT)/packages/xdc/cfg/cfginc.js package.xdc
	@$(MSG) generating schema include file list ...
	$(CONFIG) -f $(XDCROOT)/packages/xdc/cfg/cfginc.js ti.sdo.ce.image $@

.libraries,em3 .libraries: lib/release/image.aem3

-include lib/release/image.aem3.mak
lib/release/image.aem3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/image/package/package_ti.sdo.ce.image.oem3 package/lib/lib/release/image/imgdec.oem3 package/lib/lib/release/image/imgdec_skel.oem3 package/lib/lib/release/image/imgdec_stubs.oem3 package/lib/lib/release/image/imgenc.oem3 package/lib/lib/release/image/imgenc_skel.oem3 package/lib/lib/release/image/imgenc_stubs.oem3  into $@ ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/ar470  rq $@   package/lib/lib/release/image/package/package_ti.sdo.ce.image.oem3 package/lib/lib/release/image/imgdec.oem3 package/lib/lib/release/image/imgdec_skel.oem3 package/lib/lib/release/image/imgdec_stubs.oem3 package/lib/lib/release/image/imgenc.oem3 package/lib/lib/release/image/imgenc_skel.oem3 package/lib/lib/release/image/imgenc_stubs.oem3 
lib/release/image.aem3: export C_DIR=
lib/release/image.aem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 clean::
	-$(RM) lib/release/image.aem3
.libraries,em3 .libraries: lib/debug/image.aem3

-include lib/debug/image.aem3.mak
lib/debug/image.aem3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oem3 package/lib/lib/debug/image/imgdec.oem3 package/lib/lib/debug/image/imgdec_skel.oem3 package/lib/lib/debug/image/imgdec_stubs.oem3 package/lib/lib/debug/image/imgenc.oem3 package/lib/lib/debug/image/imgenc_skel.oem3 package/lib/lib/debug/image/imgenc_stubs.oem3  into $@ ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/ar470  rq $@   package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oem3 package/lib/lib/debug/image/imgdec.oem3 package/lib/lib/debug/image/imgdec_skel.oem3 package/lib/lib/debug/image/imgdec_stubs.oem3 package/lib/lib/debug/image/imgenc.oem3 package/lib/lib/debug/image/imgenc_skel.oem3 package/lib/lib/debug/image/imgenc_stubs.oem3 
lib/debug/image.aem3: export C_DIR=
lib/debug/image.aem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 clean::
	-$(RM) lib/debug/image.aem3
.libraries,e674 .libraries: lib/release/image.ae674

-include lib/release/image.ae674.mak
lib/release/image.ae674: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674 package/lib/lib/release/image/imgdec.oe674 package/lib/lib/release/image/imgdec_skel.oe674 package/lib/lib/release/image/imgdec_stubs.oe674 package/lib/lib/release/image/imgenc.oe674 package/lib/lib/release/image/imgenc_skel.oe674 package/lib/lib/release/image/imgenc_stubs.oe674  into $@ ...
	$(ti.targets.elf.C674.rootDir)/bin/ar6x  rq $@   package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674 package/lib/lib/release/image/imgdec.oe674 package/lib/lib/release/image/imgdec_skel.oe674 package/lib/lib/release/image/imgdec_stubs.oe674 package/lib/lib/release/image/imgenc.oe674 package/lib/lib/release/image/imgenc_skel.oe674 package/lib/lib/release/image/imgenc_stubs.oe674 
lib/release/image.ae674: export C_DIR=
lib/release/image.ae674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 clean::
	-$(RM) lib/release/image.ae674
.libraries,e674 .libraries: lib/debug/image.ae674

-include lib/debug/image.ae674.mak
lib/debug/image.ae674: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oe674 package/lib/lib/debug/image/imgdec.oe674 package/lib/lib/debug/image/imgdec_skel.oe674 package/lib/lib/debug/image/imgdec_stubs.oe674 package/lib/lib/debug/image/imgenc.oe674 package/lib/lib/debug/image/imgenc_skel.oe674 package/lib/lib/debug/image/imgenc_stubs.oe674  into $@ ...
	$(ti.targets.elf.C674.rootDir)/bin/ar6x  rq $@   package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oe674 package/lib/lib/debug/image/imgdec.oe674 package/lib/lib/debug/image/imgdec_skel.oe674 package/lib/lib/debug/image/imgdec_stubs.oe674 package/lib/lib/debug/image/imgenc.oe674 package/lib/lib/debug/image/imgenc_skel.oe674 package/lib/lib/debug/image/imgenc_stubs.oe674 
lib/debug/image.ae674: export C_DIR=
lib/debug/image.ae674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 clean::
	-$(RM) lib/debug/image.ae674
.libraries,v5T .libraries: lib/release/image.av5T

-include lib/release/image.av5T.mak
lib/release/image.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/release/image/package/package_ti.sdo.ce.image.ov5T package/lib/lib/release/image/imgdec.ov5T package/lib/lib/release/image/imgdec_skel.ov5T package/lib/lib/release/image/imgdec_stubs.ov5T package/lib/lib/release/image/imgenc.ov5T package/lib/lib/release/image/imgenc_skel.ov5T package/lib/lib/release/image/imgenc_stubs.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/release/image/package/package_ti.sdo.ce.image.ov5T package/lib/lib/release/image/imgdec.ov5T package/lib/lib/release/image/imgdec_skel.ov5T package/lib/lib/release/image/imgdec_stubs.ov5T package/lib/lib/release/image/imgenc.ov5T package/lib/lib/release/image/imgenc_skel.ov5T package/lib/lib/release/image/imgenc_stubs.ov5T 
lib/release/image.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/release/image.av5T
.libraries,v5T .libraries: lib/debug/image.av5T

-include lib/debug/image.av5T.mak
lib/debug/image.av5T: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T package/lib/lib/debug/image/imgdec.ov5T package/lib/lib/debug/image/imgdec_skel.ov5T package/lib/lib/debug/image/imgdec_stubs.ov5T package/lib/lib/debug/image/imgenc.ov5T package/lib/lib/debug/image/imgenc_skel.ov5T package/lib/lib/debug/image/imgenc_stubs.ov5T  into $@ ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/arm-none-linux-gnueabi/bin/ar  cr $@   package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T package/lib/lib/debug/image/imgdec.ov5T package/lib/lib/debug/image/imgdec_skel.ov5T package/lib/lib/debug/image/imgdec_stubs.ov5T package/lib/lib/debug/image/imgenc.ov5T package/lib/lib/debug/image/imgenc_skel.ov5T package/lib/lib/debug/image/imgenc_stubs.ov5T 
lib/debug/image.av5T: export LD_LIBRARY_PATH=

clean,v5T clean::
	-$(RM) lib/debug/image.av5T
test:;
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
.PHONY: package_ti.sdo.ce.image.oem3,copy
package_ti.sdo.ce.image.oem3,copy : package_ti.sdo.ce.image.oem3,0,copy package_ti.sdo.ce.image.oem3,1,copy 
	@

package_ti.sdo.ce.image.oem3,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oem3
package_ti.sdo.ce.image.oem3,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.oem3
.PHONY: package_ti.sdo.ce.image.sem3,copy
package_ti.sdo.ce.image.sem3,copy : package_ti.sdo.ce.image.sem3,0,copy package_ti.sdo.ce.image.sem3,1,copy 
	@

package_ti.sdo.ce.image.sem3,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sem3
package_ti.sdo.ce.image.sem3,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.sem3
.PHONY: imgdec.oem3,copy
imgdec.oem3,copy : imgdec.oem3,0,copy imgdec.oem3,1,copy 
	@

imgdec.oem3,0,copy : package/lib/lib/debug/image/imgdec.oem3
imgdec.oem3,1,copy : package/lib/lib/release/image/imgdec.oem3
.PHONY: imgdec.sem3,copy
imgdec.sem3,copy : imgdec.sem3,0,copy imgdec.sem3,1,copy 
	@

imgdec.sem3,0,copy : package/lib/lib/debug/image/imgdec.sem3
imgdec.sem3,1,copy : package/lib/lib/release/image/imgdec.sem3
.PHONY: imgdec_skel.oem3,copy
imgdec_skel.oem3,copy : imgdec_skel.oem3,0,copy imgdec_skel.oem3,1,copy 
	@

imgdec_skel.oem3,0,copy : package/lib/lib/debug/image/imgdec_skel.oem3
imgdec_skel.oem3,1,copy : package/lib/lib/release/image/imgdec_skel.oem3
.PHONY: imgdec_skel.sem3,copy
imgdec_skel.sem3,copy : imgdec_skel.sem3,0,copy imgdec_skel.sem3,1,copy 
	@

imgdec_skel.sem3,0,copy : package/lib/lib/debug/image/imgdec_skel.sem3
imgdec_skel.sem3,1,copy : package/lib/lib/release/image/imgdec_skel.sem3
.PHONY: imgdec_stubs.oem3,copy
imgdec_stubs.oem3,copy : imgdec_stubs.oem3,0,copy imgdec_stubs.oem3,1,copy 
	@

imgdec_stubs.oem3,0,copy : package/lib/lib/debug/image/imgdec_stubs.oem3
imgdec_stubs.oem3,1,copy : package/lib/lib/release/image/imgdec_stubs.oem3
.PHONY: imgdec_stubs.sem3,copy
imgdec_stubs.sem3,copy : imgdec_stubs.sem3,0,copy imgdec_stubs.sem3,1,copy 
	@

imgdec_stubs.sem3,0,copy : package/lib/lib/debug/image/imgdec_stubs.sem3
imgdec_stubs.sem3,1,copy : package/lib/lib/release/image/imgdec_stubs.sem3
.PHONY: imgenc.oem3,copy
imgenc.oem3,copy : imgenc.oem3,0,copy imgenc.oem3,1,copy 
	@

imgenc.oem3,0,copy : package/lib/lib/debug/image/imgenc.oem3
imgenc.oem3,1,copy : package/lib/lib/release/image/imgenc.oem3
.PHONY: imgenc.sem3,copy
imgenc.sem3,copy : imgenc.sem3,0,copy imgenc.sem3,1,copy 
	@

imgenc.sem3,0,copy : package/lib/lib/debug/image/imgenc.sem3
imgenc.sem3,1,copy : package/lib/lib/release/image/imgenc.sem3
.PHONY: imgenc_skel.oem3,copy
imgenc_skel.oem3,copy : imgenc_skel.oem3,0,copy imgenc_skel.oem3,1,copy 
	@

imgenc_skel.oem3,0,copy : package/lib/lib/debug/image/imgenc_skel.oem3
imgenc_skel.oem3,1,copy : package/lib/lib/release/image/imgenc_skel.oem3
.PHONY: imgenc_skel.sem3,copy
imgenc_skel.sem3,copy : imgenc_skel.sem3,0,copy imgenc_skel.sem3,1,copy 
	@

imgenc_skel.sem3,0,copy : package/lib/lib/debug/image/imgenc_skel.sem3
imgenc_skel.sem3,1,copy : package/lib/lib/release/image/imgenc_skel.sem3
.PHONY: imgenc_stubs.oem3,copy
imgenc_stubs.oem3,copy : imgenc_stubs.oem3,0,copy imgenc_stubs.oem3,1,copy 
	@

imgenc_stubs.oem3,0,copy : package/lib/lib/debug/image/imgenc_stubs.oem3
imgenc_stubs.oem3,1,copy : package/lib/lib/release/image/imgenc_stubs.oem3
.PHONY: imgenc_stubs.sem3,copy
imgenc_stubs.sem3,copy : imgenc_stubs.sem3,0,copy imgenc_stubs.sem3,1,copy 
	@

imgenc_stubs.sem3,0,copy : package/lib/lib/debug/image/imgenc_stubs.sem3
imgenc_stubs.sem3,1,copy : package/lib/lib/release/image/imgenc_stubs.sem3
.PHONY: package_ti.sdo.ce.image.oe674,copy
package_ti.sdo.ce.image.oe674,copy : package_ti.sdo.ce.image.oe674,0,copy package_ti.sdo.ce.image.oe674,1,copy 
	@

package_ti.sdo.ce.image.oe674,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.oe674
package_ti.sdo.ce.image.oe674,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674
.PHONY: package_ti.sdo.ce.image.se674,copy
package_ti.sdo.ce.image.se674,copy : package_ti.sdo.ce.image.se674,0,copy package_ti.sdo.ce.image.se674,1,copy 
	@

package_ti.sdo.ce.image.se674,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.se674
package_ti.sdo.ce.image.se674,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674
.PHONY: imgdec.oe674,copy
imgdec.oe674,copy : imgdec.oe674,0,copy imgdec.oe674,1,copy 
	@

imgdec.oe674,0,copy : package/lib/lib/debug/image/imgdec.oe674
imgdec.oe674,1,copy : package/lib/lib/release/image/imgdec.oe674
.PHONY: imgdec.se674,copy
imgdec.se674,copy : imgdec.se674,0,copy imgdec.se674,1,copy 
	@

imgdec.se674,0,copy : package/lib/lib/debug/image/imgdec.se674
imgdec.se674,1,copy : package/lib/lib/release/image/imgdec.se674
.PHONY: imgdec_skel.oe674,copy
imgdec_skel.oe674,copy : imgdec_skel.oe674,0,copy imgdec_skel.oe674,1,copy 
	@

imgdec_skel.oe674,0,copy : package/lib/lib/debug/image/imgdec_skel.oe674
imgdec_skel.oe674,1,copy : package/lib/lib/release/image/imgdec_skel.oe674
.PHONY: imgdec_skel.se674,copy
imgdec_skel.se674,copy : imgdec_skel.se674,0,copy imgdec_skel.se674,1,copy 
	@

imgdec_skel.se674,0,copy : package/lib/lib/debug/image/imgdec_skel.se674
imgdec_skel.se674,1,copy : package/lib/lib/release/image/imgdec_skel.se674
.PHONY: imgdec_stubs.oe674,copy
imgdec_stubs.oe674,copy : imgdec_stubs.oe674,0,copy imgdec_stubs.oe674,1,copy 
	@

imgdec_stubs.oe674,0,copy : package/lib/lib/debug/image/imgdec_stubs.oe674
imgdec_stubs.oe674,1,copy : package/lib/lib/release/image/imgdec_stubs.oe674
.PHONY: imgdec_stubs.se674,copy
imgdec_stubs.se674,copy : imgdec_stubs.se674,0,copy imgdec_stubs.se674,1,copy 
	@

imgdec_stubs.se674,0,copy : package/lib/lib/debug/image/imgdec_stubs.se674
imgdec_stubs.se674,1,copy : package/lib/lib/release/image/imgdec_stubs.se674
.PHONY: imgenc.oe674,copy
imgenc.oe674,copy : imgenc.oe674,0,copy imgenc.oe674,1,copy 
	@

imgenc.oe674,0,copy : package/lib/lib/debug/image/imgenc.oe674
imgenc.oe674,1,copy : package/lib/lib/release/image/imgenc.oe674
.PHONY: imgenc.se674,copy
imgenc.se674,copy : imgenc.se674,0,copy imgenc.se674,1,copy 
	@

imgenc.se674,0,copy : package/lib/lib/debug/image/imgenc.se674
imgenc.se674,1,copy : package/lib/lib/release/image/imgenc.se674
.PHONY: imgenc_skel.oe674,copy
imgenc_skel.oe674,copy : imgenc_skel.oe674,0,copy imgenc_skel.oe674,1,copy 
	@

imgenc_skel.oe674,0,copy : package/lib/lib/debug/image/imgenc_skel.oe674
imgenc_skel.oe674,1,copy : package/lib/lib/release/image/imgenc_skel.oe674
.PHONY: imgenc_skel.se674,copy
imgenc_skel.se674,copy : imgenc_skel.se674,0,copy imgenc_skel.se674,1,copy 
	@

imgenc_skel.se674,0,copy : package/lib/lib/debug/image/imgenc_skel.se674
imgenc_skel.se674,1,copy : package/lib/lib/release/image/imgenc_skel.se674
.PHONY: imgenc_stubs.oe674,copy
imgenc_stubs.oe674,copy : imgenc_stubs.oe674,0,copy imgenc_stubs.oe674,1,copy 
	@

imgenc_stubs.oe674,0,copy : package/lib/lib/debug/image/imgenc_stubs.oe674
imgenc_stubs.oe674,1,copy : package/lib/lib/release/image/imgenc_stubs.oe674
.PHONY: imgenc_stubs.se674,copy
imgenc_stubs.se674,copy : imgenc_stubs.se674,0,copy imgenc_stubs.se674,1,copy 
	@

imgenc_stubs.se674,0,copy : package/lib/lib/debug/image/imgenc_stubs.se674
imgenc_stubs.se674,1,copy : package/lib/lib/release/image/imgenc_stubs.se674
.PHONY: package_ti.sdo.ce.image.ov5T,copy
package_ti.sdo.ce.image.ov5T,copy : package_ti.sdo.ce.image.ov5T,0,copy package_ti.sdo.ce.image.ov5T,1,copy 
	@

package_ti.sdo.ce.image.ov5T,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T
package_ti.sdo.ce.image.ov5T,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.ov5T
.PHONY: package_ti.sdo.ce.image.sv5T,copy
package_ti.sdo.ce.image.sv5T,copy : package_ti.sdo.ce.image.sv5T,0,copy package_ti.sdo.ce.image.sv5T,1,copy 
	@

package_ti.sdo.ce.image.sv5T,0,copy : package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sv5T
package_ti.sdo.ce.image.sv5T,1,copy : package/lib/lib/release/image/package/package_ti.sdo.ce.image.sv5T
.PHONY: imgdec.ov5T,copy
imgdec.ov5T,copy : imgdec.ov5T,0,copy imgdec.ov5T,1,copy 
	@

imgdec.ov5T,0,copy : package/lib/lib/debug/image/imgdec.ov5T
imgdec.ov5T,1,copy : package/lib/lib/release/image/imgdec.ov5T
.PHONY: imgdec.sv5T,copy
imgdec.sv5T,copy : imgdec.sv5T,0,copy imgdec.sv5T,1,copy 
	@

imgdec.sv5T,0,copy : package/lib/lib/debug/image/imgdec.sv5T
imgdec.sv5T,1,copy : package/lib/lib/release/image/imgdec.sv5T
.PHONY: imgdec_skel.ov5T,copy
imgdec_skel.ov5T,copy : imgdec_skel.ov5T,0,copy imgdec_skel.ov5T,1,copy 
	@

imgdec_skel.ov5T,0,copy : package/lib/lib/debug/image/imgdec_skel.ov5T
imgdec_skel.ov5T,1,copy : package/lib/lib/release/image/imgdec_skel.ov5T
.PHONY: imgdec_skel.sv5T,copy
imgdec_skel.sv5T,copy : imgdec_skel.sv5T,0,copy imgdec_skel.sv5T,1,copy 
	@

imgdec_skel.sv5T,0,copy : package/lib/lib/debug/image/imgdec_skel.sv5T
imgdec_skel.sv5T,1,copy : package/lib/lib/release/image/imgdec_skel.sv5T
.PHONY: imgdec_stubs.ov5T,copy
imgdec_stubs.ov5T,copy : imgdec_stubs.ov5T,0,copy imgdec_stubs.ov5T,1,copy 
	@

imgdec_stubs.ov5T,0,copy : package/lib/lib/debug/image/imgdec_stubs.ov5T
imgdec_stubs.ov5T,1,copy : package/lib/lib/release/image/imgdec_stubs.ov5T
.PHONY: imgdec_stubs.sv5T,copy
imgdec_stubs.sv5T,copy : imgdec_stubs.sv5T,0,copy imgdec_stubs.sv5T,1,copy 
	@

imgdec_stubs.sv5T,0,copy : package/lib/lib/debug/image/imgdec_stubs.sv5T
imgdec_stubs.sv5T,1,copy : package/lib/lib/release/image/imgdec_stubs.sv5T
.PHONY: imgenc.ov5T,copy
imgenc.ov5T,copy : imgenc.ov5T,0,copy imgenc.ov5T,1,copy 
	@

imgenc.ov5T,0,copy : package/lib/lib/debug/image/imgenc.ov5T
imgenc.ov5T,1,copy : package/lib/lib/release/image/imgenc.ov5T
.PHONY: imgenc.sv5T,copy
imgenc.sv5T,copy : imgenc.sv5T,0,copy imgenc.sv5T,1,copy 
	@

imgenc.sv5T,0,copy : package/lib/lib/debug/image/imgenc.sv5T
imgenc.sv5T,1,copy : package/lib/lib/release/image/imgenc.sv5T
.PHONY: imgenc_skel.ov5T,copy
imgenc_skel.ov5T,copy : imgenc_skel.ov5T,0,copy imgenc_skel.ov5T,1,copy 
	@

imgenc_skel.ov5T,0,copy : package/lib/lib/debug/image/imgenc_skel.ov5T
imgenc_skel.ov5T,1,copy : package/lib/lib/release/image/imgenc_skel.ov5T
.PHONY: imgenc_skel.sv5T,copy
imgenc_skel.sv5T,copy : imgenc_skel.sv5T,0,copy imgenc_skel.sv5T,1,copy 
	@

imgenc_skel.sv5T,0,copy : package/lib/lib/debug/image/imgenc_skel.sv5T
imgenc_skel.sv5T,1,copy : package/lib/lib/release/image/imgenc_skel.sv5T
.PHONY: imgenc_stubs.ov5T,copy
imgenc_stubs.ov5T,copy : imgenc_stubs.ov5T,0,copy imgenc_stubs.ov5T,1,copy 
	@

imgenc_stubs.ov5T,0,copy : package/lib/lib/debug/image/imgenc_stubs.ov5T
imgenc_stubs.ov5T,1,copy : package/lib/lib/release/image/imgenc_stubs.ov5T
.PHONY: imgenc_stubs.sv5T,copy
imgenc_stubs.sv5T,copy : imgenc_stubs.sv5T,0,copy imgenc_stubs.sv5T,1,copy 
	@

imgenc_stubs.sv5T,0,copy : package/lib/lib/debug/image/imgenc_stubs.sv5T
imgenc_stubs.sv5T,1,copy : package/lib/lib/release/image/imgenc_stubs.sv5T

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,ti_sdo_ce_image
ti_sdo_ce_image.tar: package/package.bld.xml
ti_sdo_ce_image.tar: package/package.ext.xml
ti_sdo_ce_image.tar: package/package.rel.dot
ti_sdo_ce_image.tar: package/build.cfg
ti_sdo_ce_image.tar: package/package.xdc.inc
ti_sdo_ce_image.tar: imgdec.h
ti_sdo_ce_image.tar: imgenc.h
ti_sdo_ce_image.tar: _imgdec.h
ti_sdo_ce_image.tar: _imgenc.h
ti_sdo_ce_image.tar: package.bld
ti_sdo_ce_image.tar: IIMGDEC_dsutils.xs
ti_sdo_ce_image.tar: IIMGENC_dsutils.xs
ti_sdo_ce_image.tar: simple_GCArmv5T.mak
ti_sdo_ce_image.tar: package/package.cfg.xdc.inc
ti_sdo_ce_image.tar: lib/release/image.aem3
ti_sdo_ce_image.tar: package/package_ti.sdo.ce.image.c
ti_sdo_ce_image.tar: imgdec.c
ti_sdo_ce_image.tar: imgdec_skel.c
ti_sdo_ce_image.tar: imgdec_stubs.c
ti_sdo_ce_image.tar: imgenc.c
ti_sdo_ce_image.tar: imgenc_skel.c
ti_sdo_ce_image.tar: imgenc_stubs.c
ti_sdo_ce_image.tar: lib/debug/image.aem3
ti_sdo_ce_image.tar: lib/release/image.ae674
ti_sdo_ce_image.tar: lib/debug/image.ae674
ti_sdo_ce_image.tar: lib/release/image.av5T
ti_sdo_ce_image.tar: lib/debug/image.av5T
ifeq (,$(MK_NOGENDEPS))
-include package/rel/ti_sdo_ce_image.tar.dep
endif
package/rel/ti_sdo_ce_image/ti/sdo/ce/image/package/package.rel.xml:

ti_sdo_ce_image.tar: package/rel/ti_sdo_ce_image.xdc.inc package/rel/ti_sdo_ce_image/ti/sdo/ce/image/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/ti_sdo_ce_image.xdc.inc,package/rel/ti_sdo_ce_image.tar.dep)


release release,ti_sdo_ce_image: all ti_sdo_ce_image.tar
clean:: .clean
	-$(RM) ti_sdo_ce_image.tar
	-$(RM) package/rel/ti_sdo_ce_image.xdc.inc
	-$(RM) package/rel/ti_sdo_ce_image.tar.dep

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
ifeq (,$(wildcard lib/release))
    $(shell $(MKDIR) lib/release)
endif
ifeq (,$(wildcard lib/debug))
    $(shell $(MKDIR) lib/debug)
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
ifeq (,$(wildcard package/lib/lib/release))
    $(shell $(MKDIR) package/lib/lib/release)
endif
ifeq (,$(wildcard package/lib/lib/release/image))
    $(shell $(MKDIR) package/lib/lib/release/image)
endif
ifeq (,$(wildcard package/lib/lib/release/image/package))
    $(shell $(MKDIR) package/lib/lib/release/image/package)
endif
ifeq (,$(wildcard package/lib/lib/debug))
    $(shell $(MKDIR) package/lib/lib/debug)
endif
ifeq (,$(wildcard package/lib/lib/debug/image))
    $(shell $(MKDIR) package/lib/lib/debug/image)
endif
ifeq (,$(wildcard package/lib/lib/debug/image/package))
    $(shell $(MKDIR) package/lib/lib/debug/image/package)
endif
endif
clean::
	-$(RMDIR) package


clean:: 
	-$(RM) package/ti.sdo.ce.image.pjt

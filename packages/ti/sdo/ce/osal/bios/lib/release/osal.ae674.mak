#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.elf.C674{1,0,7.3,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674.dep
endif

package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674: | .interfaces
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674: package/package_ti.sdo.ce.osal.bios.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal/package -fr=./package/lib/lib/release/osal/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal/package -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal/package -fr=./package/lib/lib/release/osal/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674: export C_DIR=
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.se674: | .interfaces
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.se674: package/package_ti.sdo.ce.osal.bios.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal/package -fr=./package/lib/lib/release/osal/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal/package -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal/package -fr=./package/lib/lib/release/osal/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.se674: export C_DIR=
package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/Global_BIOS.oe674.dep
endif

package/lib/lib/release/osal/Global_BIOS.oe674: | .interfaces
package/lib/lib/release/osal/Global_BIOS.oe674: Global_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Global_BIOS.oe674: export C_DIR=
package/lib/lib/release/osal/Global_BIOS.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/Global_BIOS.se674: | .interfaces
package/lib/lib/release/osal/Global_BIOS.se674: Global_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Global_BIOS.se674: export C_DIR=
package/lib/lib/release/osal/Global_BIOS.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/Loader_noOS.oe674.dep
endif

package/lib/lib/release/osal/Loader_noOS.oe674: | .interfaces
package/lib/lib/release/osal/Loader_noOS.oe674: Loader_noOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Loader_noOS.oe674: export C_DIR=
package/lib/lib/release/osal/Loader_noOS.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/Loader_noOS.se674: | .interfaces
package/lib/lib/release/osal/Loader_noOS.se674: Loader_noOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Loader_noOS.se674: export C_DIR=
package/lib/lib/release/osal/Loader_noOS.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/Memory_BIOS.oe674.dep
endif

package/lib/lib/release/osal/Memory_BIOS.oe674: | .interfaces
package/lib/lib/release/osal/Memory_BIOS.oe674: Memory_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Memory_BIOS.oe674: export C_DIR=
package/lib/lib/release/osal/Memory_BIOS.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/Memory_BIOS.se674: | .interfaces
package/lib/lib/release/osal/Memory_BIOS.se674: Memory_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Memory_BIOS.se674: export C_DIR=
package/lib/lib/release/osal/Memory_BIOS.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/File_BIOS.oe674.dep
endif

package/lib/lib/release/osal/File_BIOS.oe674: | .interfaces
package/lib/lib/release/osal/File_BIOS.oe674: File_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/File_BIOS.oe674: export C_DIR=
package/lib/lib/release/osal/File_BIOS.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/File_BIOS.se674: | .interfaces
package/lib/lib/release/osal/File_BIOS.se674: File_BIOS.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/File_BIOS.se674: export C_DIR=
package/lib/lib/release/osal/File_BIOS.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/osal/Trace_SysCBuf.oe674.dep
endif

package/lib/lib/release/osal/Trace_SysCBuf.oe674: | .interfaces
package/lib/lib/release/osal/Trace_SysCBuf.oe674: Trace_SysCBuf.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Trace_SysCBuf.oe674: export C_DIR=
package/lib/lib/release/osal/Trace_SysCBuf.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/osal/Trace_SysCBuf.se674: | .interfaces
package/lib/lib/release/osal/Trace_SysCBuf.se674: Trace_SysCBuf.c lib/release/osal.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/osal -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/osal -fr=./package/lib/lib/release/osal
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/osal/Trace_SysCBuf.se674: export C_DIR=
package/lib/lib/release/osal/Trace_SysCBuf.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 ::
	-$(RM) package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674
	-$(RM) package/lib/lib/release/osal/Global_BIOS.oe674
	-$(RM) package/lib/lib/release/osal/Loader_noOS.oe674
	-$(RM) package/lib/lib/release/osal/Memory_BIOS.oe674
	-$(RM) package/lib/lib/release/osal/File_BIOS.oe674
	-$(RM) package/lib/lib/release/osal/Trace_SysCBuf.oe674
	-$(RM) package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.se674
	-$(RM) package/lib/lib/release/osal/Global_BIOS.se674
	-$(RM) package/lib/lib/release/osal/Loader_noOS.se674
	-$(RM) package/lib/lib/release/osal/Memory_BIOS.se674
	-$(RM) package/lib/lib/release/osal/File_BIOS.se674
	-$(RM) package/lib/lib/release/osal/Trace_SysCBuf.se674

lib/release/osal.ae674: package/lib/lib/release/osal/package/package_ti.sdo.ce.osal.bios.oe674 package/lib/lib/release/osal/Global_BIOS.oe674 package/lib/lib/release/osal/Loader_noOS.oe674 package/lib/lib/release/osal/Memory_BIOS.oe674 package/lib/lib/release/osal/File_BIOS.oe674 package/lib/lib/release/osal/Trace_SysCBuf.oe674 lib/release/osal.ae674.mak

clean::
	-$(RM) lib/release/osal.ae674.mak

#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M3{1,0,4.9,2
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3.dep
endif

package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3: | .interfaces
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3: package/package_ti.sdo.ce.image1.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c  -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1/package -fr=./package/lib/lib/debug/imgenc1/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1/package -s oem3 $< -C   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1/package -fr=./package/lib/lib/debug/imgenc1/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3: export C_DIR=
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.sem3: | .interfaces
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.sem3: package/package_ti.sdo.ce.image1.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 -n $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1/package -fr=./package/lib/lib/debug/imgenc1/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1/package -s oem3 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1/package -fr=./package/lib/lib/debug/imgenc1/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.sem3: export C_DIR=
package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.sem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/imgenc1/imgenc1.oem3.dep
endif

package/lib/lib/debug/imgenc1/imgenc1.oem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1.oem3: imgenc1.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c  -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1.oem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1.oem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

package/lib/lib/debug/imgenc1/imgenc1.sem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1.sem3: imgenc1.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 -n $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1.sem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1.sem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/imgenc1/imgenc1_skel.oem3.dep
endif

package/lib/lib/debug/imgenc1/imgenc1_skel.oem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1_skel.oem3: imgenc1_skel.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c  -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1_skel.oem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1_skel.oem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

package/lib/lib/debug/imgenc1/imgenc1_skel.sem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1_skel.sem3: imgenc1_skel.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 -n $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1_skel.sem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1_skel.sem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3.dep
endif

package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3: imgenc1_stubs.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c  -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C   -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

package/lib/lib/debug/imgenc1/imgenc1_stubs.sem3: | .interfaces
package/lib/lib/debug/imgenc1/imgenc1_stubs.sem3: imgenc1_stubs.c lib/debug/imgenc1.aem3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem3 -n $< ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/cl470 -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/imgenc1 -s oem3 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M3 --abi=eabi -eo.oem3 -ea.sem3  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M3 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_9_2 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M3.rootDir)/include/rts -I$(ti.targets.arm.elf.M3.rootDir)/include  -fs=./package/lib/lib/debug/imgenc1 -fr=./package/lib/lib/debug/imgenc1
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/imgenc1/imgenc1_stubs.sem3: export C_DIR=
package/lib/lib/debug/imgenc1/imgenc1_stubs.sem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 ::
	-$(RM) package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1.oem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1_skel.oem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3
	-$(RM) package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.sem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1.sem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1_skel.sem3
	-$(RM) package/lib/lib/debug/imgenc1/imgenc1_stubs.sem3

lib/debug/imgenc1.aem3: package/lib/lib/debug/imgenc1/package/package_ti.sdo.ce.image1.oem3 package/lib/lib/debug/imgenc1/imgenc1.oem3 package/lib/lib/debug/imgenc1/imgenc1_skel.oem3 package/lib/lib/debug/imgenc1/imgenc1_stubs.oem3 lib/debug/imgenc1.aem3.mak

clean::
	-$(RM) lib/debug/imgenc1.aem3.mak

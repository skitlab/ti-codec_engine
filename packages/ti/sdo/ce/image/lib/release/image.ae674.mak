#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.elf.C674{1,0,7.3,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674.dep
endif

package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674: | .interfaces
package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674: package/package_ti.sdo.ce.image.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image/package -fr=./package/lib/lib/release/image/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image/package -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image/package -fr=./package/lib/lib/release/image/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674: export C_DIR=
package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674: | .interfaces
package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674: package/package_ti.sdo.ce.image.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image/package -fr=./package/lib/lib/release/image/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image/package -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image/package -fr=./package/lib/lib/release/image/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674: export C_DIR=
package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgdec.oe674.dep
endif

package/lib/lib/release/image/imgdec.oe674: | .interfaces
package/lib/lib/release/image/imgdec.oe674: imgdec.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec.oe674: export C_DIR=
package/lib/lib/release/image/imgdec.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgdec.se674: | .interfaces
package/lib/lib/release/image/imgdec.se674: imgdec.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec.se674: export C_DIR=
package/lib/lib/release/image/imgdec.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgdec_skel.oe674.dep
endif

package/lib/lib/release/image/imgdec_skel.oe674: | .interfaces
package/lib/lib/release/image/imgdec_skel.oe674: imgdec_skel.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec_skel.oe674: export C_DIR=
package/lib/lib/release/image/imgdec_skel.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgdec_skel.se674: | .interfaces
package/lib/lib/release/image/imgdec_skel.se674: imgdec_skel.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec_skel.se674: export C_DIR=
package/lib/lib/release/image/imgdec_skel.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgdec_stubs.oe674.dep
endif

package/lib/lib/release/image/imgdec_stubs.oe674: | .interfaces
package/lib/lib/release/image/imgdec_stubs.oe674: imgdec_stubs.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec_stubs.oe674: export C_DIR=
package/lib/lib/release/image/imgdec_stubs.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgdec_stubs.se674: | .interfaces
package/lib/lib/release/image/imgdec_stubs.se674: imgdec_stubs.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgdec_stubs.se674: export C_DIR=
package/lib/lib/release/image/imgdec_stubs.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgenc.oe674.dep
endif

package/lib/lib/release/image/imgenc.oe674: | .interfaces
package/lib/lib/release/image/imgenc.oe674: imgenc.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc.oe674: export C_DIR=
package/lib/lib/release/image/imgenc.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgenc.se674: | .interfaces
package/lib/lib/release/image/imgenc.se674: imgenc.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc.se674: export C_DIR=
package/lib/lib/release/image/imgenc.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgenc_skel.oe674.dep
endif

package/lib/lib/release/image/imgenc_skel.oe674: | .interfaces
package/lib/lib/release/image/imgenc_skel.oe674: imgenc_skel.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc_skel.oe674: export C_DIR=
package/lib/lib/release/image/imgenc_skel.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgenc_skel.se674: | .interfaces
package/lib/lib/release/image/imgenc_skel.se674: imgenc_skel.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc_skel.se674: export C_DIR=
package/lib/lib/release/image/imgenc_skel.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/image/imgenc_stubs.oe674.dep
endif

package/lib/lib/release/image/imgenc_stubs.oe674: | .interfaces
package/lib/lib/release/image/imgenc_stubs.oe674: imgenc_stubs.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C   -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc_stubs.oe674: export C_DIR=
package/lib/lib/release/image/imgenc_stubs.oe674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

package/lib/lib/release/image/imgenc_stubs.se674: | .interfaces
package/lib/lib/release/image/imgenc_stubs.se674: imgenc_stubs.c lib/release/image.ae674.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle674 -n $< ...
	$(ti.targets.elf.C674.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/release/image -s oe674 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6740 --abi=eabi -eo.oe674 -ea.se674  -pdr -pden -pds=880 -pds=238 -pds452 -pds195 -mi10 -mo -g  -Dxdc_target_name__=C674 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_3_1 -O2 -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS) -I$(ti.targets.elf.C674.rootDir)/include -fs=./package/lib/lib/release/image -fr=./package/lib/lib/release/image
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/image/imgenc_stubs.se674: export C_DIR=
package/lib/lib/release/image/imgenc_stubs.se674: PATH:=$(ti.targets.elf.C674.rootDir)/bin/:$(PATH)

clean,e674 ::
	-$(RM) package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674
	-$(RM) package/lib/lib/release/image/imgdec.oe674
	-$(RM) package/lib/lib/release/image/imgdec_skel.oe674
	-$(RM) package/lib/lib/release/image/imgdec_stubs.oe674
	-$(RM) package/lib/lib/release/image/imgenc.oe674
	-$(RM) package/lib/lib/release/image/imgenc_skel.oe674
	-$(RM) package/lib/lib/release/image/imgenc_stubs.oe674
	-$(RM) package/lib/lib/release/image/package/package_ti.sdo.ce.image.se674
	-$(RM) package/lib/lib/release/image/imgdec.se674
	-$(RM) package/lib/lib/release/image/imgdec_skel.se674
	-$(RM) package/lib/lib/release/image/imgdec_stubs.se674
	-$(RM) package/lib/lib/release/image/imgenc.se674
	-$(RM) package/lib/lib/release/image/imgenc_skel.se674
	-$(RM) package/lib/lib/release/image/imgenc_stubs.se674

lib/release/image.ae674: package/lib/lib/release/image/package/package_ti.sdo.ce.image.oe674 package/lib/lib/release/image/imgdec.oe674 package/lib/lib/release/image/imgdec_skel.oe674 package/lib/lib/release/image/imgdec_stubs.oe674 package/lib/lib/release/image/imgenc.oe674 package/lib/lib/release/image/imgenc_skel.oe674 package/lib/lib/release/image/imgenc_stubs.oe674 lib/release/image.ae674.mak

clean::
	-$(RM) lib/release/image.ae674.mak
#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.GCArmv5T{1,0,4.3,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T.dep
endif

package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T: | .interfaces
package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T: package/package_ti.sdo.ce.image.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sv5T: | .interfaces
package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sv5T: package/package_ti.sdo.ce.image.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgdec.ov5T.dep
endif

package/lib/lib/debug/image/imgdec.ov5T: | .interfaces
package/lib/lib/debug/image/imgdec.ov5T: imgdec.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgdec.sv5T: | .interfaces
package/lib/lib/debug/image/imgdec.sv5T: imgdec.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgdec_skel.ov5T.dep
endif

package/lib/lib/debug/image/imgdec_skel.ov5T: | .interfaces
package/lib/lib/debug/image/imgdec_skel.ov5T: imgdec_skel.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec_skel.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgdec_skel.sv5T: | .interfaces
package/lib/lib/debug/image/imgdec_skel.sv5T: imgdec_skel.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec_skel.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgdec_stubs.ov5T.dep
endif

package/lib/lib/debug/image/imgdec_stubs.ov5T: | .interfaces
package/lib/lib/debug/image/imgdec_stubs.ov5T: imgdec_stubs.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec_stubs.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgdec_stubs.sv5T: | .interfaces
package/lib/lib/debug/image/imgdec_stubs.sv5T: imgdec_stubs.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgdec_stubs.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgenc.ov5T.dep
endif

package/lib/lib/debug/image/imgenc.ov5T: | .interfaces
package/lib/lib/debug/image/imgenc.ov5T: imgenc.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgenc.sv5T: | .interfaces
package/lib/lib/debug/image/imgenc.sv5T: imgenc.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgenc_skel.ov5T.dep
endif

package/lib/lib/debug/image/imgenc_skel.ov5T: | .interfaces
package/lib/lib/debug/image/imgenc_skel.ov5T: imgenc_skel.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc_skel.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgenc_skel.sv5T: | .interfaces
package/lib/lib/debug/image/imgenc_skel.sv5T: imgenc_skel.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc_skel.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/image/imgenc_stubs.ov5T.dep
endif

package/lib/lib/debug/image/imgenc_stubs.ov5T: | .interfaces
package/lib/lib/debug/image/imgenc_stubs.ov5T: imgenc_stubs.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc_stubs.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/image/imgenc_stubs.sv5T: | .interfaces
package/lib/lib/debug/image/imgenc_stubs.sv5T: imgenc_stubs.c lib/debug/image.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g -DXDM_INCLUDE_DOT9_SUPPORT  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/image/imgenc_stubs.sv5T: export LD_LIBRARY_PATH=

clean,v5T ::
	-$(RM) package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T
	-$(RM) package/lib/lib/debug/image/imgdec.ov5T
	-$(RM) package/lib/lib/debug/image/imgdec_skel.ov5T
	-$(RM) package/lib/lib/debug/image/imgdec_stubs.ov5T
	-$(RM) package/lib/lib/debug/image/imgenc.ov5T
	-$(RM) package/lib/lib/debug/image/imgenc_skel.ov5T
	-$(RM) package/lib/lib/debug/image/imgenc_stubs.ov5T
	-$(RM) package/lib/lib/debug/image/package/package_ti.sdo.ce.image.sv5T
	-$(RM) package/lib/lib/debug/image/imgdec.sv5T
	-$(RM) package/lib/lib/debug/image/imgdec_skel.sv5T
	-$(RM) package/lib/lib/debug/image/imgdec_stubs.sv5T
	-$(RM) package/lib/lib/debug/image/imgenc.sv5T
	-$(RM) package/lib/lib/debug/image/imgenc_skel.sv5T
	-$(RM) package/lib/lib/debug/image/imgenc_stubs.sv5T

lib/debug/image.av5T: package/lib/lib/debug/image/package/package_ti.sdo.ce.image.ov5T package/lib/lib/debug/image/imgdec.ov5T package/lib/lib/debug/image/imgdec_skel.ov5T package/lib/lib/debug/image/imgdec_stubs.ov5T package/lib/lib/debug/image/imgenc.ov5T package/lib/lib/debug/image/imgenc_skel.ov5T package/lib/lib/debug/image/imgenc_stubs.ov5T lib/debug/image.av5T.mak

clean::
	-$(RM) lib/debug/image.av5T.mak

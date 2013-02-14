#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.GCArmv5T{1,0,4.3,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T.dep
endif

package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T: | .interfaces
package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T: package/package_ti.sdo.ce.vidtranscode.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.sv5T: | .interfaces
package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.sv5T: package/package_ti.sdo.ce.vidtranscode.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/vidtranscode/vidtranscode.ov5T.dep
endif

package/lib/lib/release/vidtranscode/vidtranscode.ov5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode.ov5T: vidtranscode.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/release/vidtranscode/vidtranscode.sv5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode.sv5T: vidtranscode.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T.dep
endif

package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T: vidtranscode_skel.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/release/vidtranscode/vidtranscode_skel.sv5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode_skel.sv5T: vidtranscode_skel.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode_skel.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T.dep
endif

package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T: vidtranscode_stubs.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/release/vidtranscode/vidtranscode_stubs.sv5T: | .interfaces
package/lib/lib/release/vidtranscode/vidtranscode_stubs.sv5T: vidtranscode_stubs.c lib/release/vidtranscode.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/vidtranscode/vidtranscode_stubs.sv5T: export LD_LIBRARY_PATH=

clean,v5T ::
	-$(RM) package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode.ov5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T
	-$(RM) package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.sv5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode.sv5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode_skel.sv5T
	-$(RM) package/lib/lib/release/vidtranscode/vidtranscode_stubs.sv5T

lib/release/vidtranscode.av5T: package/lib/lib/release/vidtranscode/package/package_ti.sdo.ce.vidtranscode.ov5T package/lib/lib/release/vidtranscode/vidtranscode.ov5T package/lib/lib/release/vidtranscode/vidtranscode_skel.ov5T package/lib/lib/release/vidtranscode/vidtranscode_stubs.ov5T lib/release/vidtranscode.av5T.mak

clean::
	-$(RM) lib/release/vidtranscode.av5T.mak

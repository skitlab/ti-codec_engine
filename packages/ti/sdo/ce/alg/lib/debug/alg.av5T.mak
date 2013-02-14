#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.GCArmv5T{1,0,4.3,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T.dep
endif

package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T: | .interfaces
package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T: package/package_ti.sdo.ce.alg.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.sv5T: | .interfaces
package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.sv5T: package/package_ti.sdo.ce.alg.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/alg/alg_control.ov5T.dep
endif

package/lib/lib/debug/alg/alg_control.ov5T: | .interfaces
package/lib/lib/debug/alg/alg_control.ov5T: alg_control.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_control.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/alg/alg_control.sv5T: | .interfaces
package/lib/lib/debug/alg/alg_control.sv5T: alg_control.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_control.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/alg/alg_create.ov5T.dep
endif

package/lib/lib/debug/alg/alg_create.ov5T: | .interfaces
package/lib/lib/debug/alg/alg_create.ov5T: alg_create.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_create.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/alg/alg_create.sv5T: | .interfaces
package/lib/lib/debug/alg/alg_create.sv5T: alg_create.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_create.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/alg/alg_malloc.ov5T.dep
endif

package/lib/lib/debug/alg/alg_malloc.ov5T: | .interfaces
package/lib/lib/debug/alg/alg_malloc.ov5T: alg_malloc.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_malloc.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/alg/alg_malloc.sv5T: | .interfaces
package/lib/lib/debug/alg/alg_malloc.sv5T: alg_malloc.c lib/debug/alg.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/alg/alg_malloc.sv5T: export LD_LIBRARY_PATH=

clean,v5T ::
	-$(RM) package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T
	-$(RM) package/lib/lib/debug/alg/alg_control.ov5T
	-$(RM) package/lib/lib/debug/alg/alg_create.ov5T
	-$(RM) package/lib/lib/debug/alg/alg_malloc.ov5T
	-$(RM) package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.sv5T
	-$(RM) package/lib/lib/debug/alg/alg_control.sv5T
	-$(RM) package/lib/lib/debug/alg/alg_create.sv5T
	-$(RM) package/lib/lib/debug/alg/alg_malloc.sv5T

lib/debug/alg.av5T: package/lib/lib/debug/alg/package/package_ti.sdo.ce.alg.ov5T package/lib/lib/debug/alg/alg_control.ov5T package/lib/lib/debug/alg/alg_create.ov5T package/lib/lib/debug/alg/alg_malloc.ov5T lib/debug/alg.av5T.mak

clean::
	-$(RM) lib/debug/alg.av5T.mak

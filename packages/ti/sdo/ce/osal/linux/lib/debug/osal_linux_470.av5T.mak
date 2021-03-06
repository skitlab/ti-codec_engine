#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.GCArmv5T{1,0,4.3,3
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T: package/package_ti.sdo.ce.osal.linux.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.sv5T: package/package_ti.sdo.ce.osal.linux.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T: Global_noOS.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/Global_noOS.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Global_noOS.sv5T: Global_noOS.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Global_noOS.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T: Loader_linux.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/Loader_linux.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Loader_linux.sv5T: Loader_linux.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Loader_linux.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/File_posix.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/File_posix.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/File_posix.ov5T: File_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/File_posix.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/File_posix.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/File_posix.sv5T: File_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/File_posix.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T: Lock_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/Lock_posix.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Lock_posix.sv5T: Lock_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Lock_posix.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T: LockMP_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/LockMP_posix.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/LockMP_posix.sv5T: LockMP_posix.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/LockMP_posix.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/Trace.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/Trace.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Trace.ov5T: Trace.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Trace.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/Trace.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Trace.sv5T: Trace.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Trace.sv5T: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T.dep
endif

package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T: Memory_cmem.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T: export LD_LIBRARY_PATH=

package/lib/lib/debug/osal_linux_470/Memory_cmem.sv5T: | .interfaces
package/lib/lib/debug/osal_linux_470/Memory_cmem.sv5T: Memory_cmem.c lib/debug/osal_linux_470.av5T.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv5T -S $< ...
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv5t -Dfar=  -Wall -fno-strict-aliasing  -D_DEBUG_=1 -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_3_3 -g  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/osal_linux_470/Memory_cmem.sv5T: export LD_LIBRARY_PATH=

clean,v5T ::
	-$(RM) package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/File_posix.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Trace.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T
	-$(RM) package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Global_noOS.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Loader_linux.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/File_posix.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Lock_posix.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/LockMP_posix.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Trace.sv5T
	-$(RM) package/lib/lib/debug/osal_linux_470/Memory_cmem.sv5T

lib/debug/osal_linux_470.av5T: package/lib/lib/debug/osal_linux_470/package/package_ti.sdo.ce.osal.linux.ov5T package/lib/lib/debug/osal_linux_470/Global_noOS.ov5T package/lib/lib/debug/osal_linux_470/Loader_linux.ov5T package/lib/lib/debug/osal_linux_470/File_posix.ov5T package/lib/lib/debug/osal_linux_470/Lock_posix.ov5T package/lib/lib/debug/osal_linux_470/LockMP_posix.ov5T package/lib/lib/debug/osal_linux_470/Trace.ov5T package/lib/lib/debug/osal_linux_470/Memory_cmem.ov5T lib/debug/osal_linux_470.av5T.mak

clean::
	-$(RM) lib/debug/osal_linux_470.av5T.mak

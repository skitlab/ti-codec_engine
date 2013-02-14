#
#  Copyright 2012 by Texas Instruments Incorporated.
#  
#

# Generated by build.filter.Make on Thu Feb 23 2012 17:50:37 GMT-0800 (PST)
#
# SEARCHPATH is a semicolon-delimited directory list of dependencies
#
SEARCHPATH ?= $(PKG_PATH)

#
# Set LIBDIR to the directory where libraries are created
#
LIBDIR ?= .objs

#
# Macro definitions referenced below
#
empty =
space =$(empty) $(empty)
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(SEARCHPATH))))
RM = rm -f
MKDIR = mkdir -p
RMDIR = rm -rf

.PHONY: all clean initialize

all: initialize
initialize:
	-@$(MKDIR) .objs
ifneq (.objs,$(LIBDIR))
	-@$(MKDIR) $(LIBDIR)
endif

clean::
	-$(RMDIR) .objs
clean::
	-$(RMDIR) $(LIBDIR)
gnu.targets.arm.GCArmv5T.rootDir ?= $(CGT_ARM_INSTALL_DIR)

.objs/speech_sphdec.ov5T: sphdec.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphdec.ov5T
clean::
	-$(RM) .objs/speech_sphdec.ov5T

.objs/speech_sphdec_skel.ov5T: sphdec_skel.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphdec_skel.ov5T
clean::
	-$(RM) .objs/speech_sphdec_skel.ov5T

.objs/speech_sphdec_stubs.ov5T: sphdec_stubs.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphdec_stubs.ov5T
clean::
	-$(RM) .objs/speech_sphdec_stubs.ov5T

.objs/speech_sphenc.ov5T: sphenc.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphenc.ov5T
clean::
	-$(RM) .objs/speech_sphenc.ov5T

.objs/speech_sphenc_skel.ov5T: sphenc_skel.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphenc_skel.ov5T
clean::
	-$(RM) .objs/speech_sphenc_skel.ov5T

.objs/speech_sphenc_stubs.ov5T: sphenc_stubs.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/speech_sphenc_stubs.ov5T
clean::
	-$(RM) .objs/speech_sphenc_stubs.ov5T

$(LIBDIR)/speech.av5T: .objs/speech_sphdec.ov5T .objs/speech_sphdec_skel.ov5T .objs/speech_sphdec_stubs.ov5T .objs/speech_sphenc.ov5T .objs/speech_sphenc_skel.ov5T .objs/speech_sphenc_stubs.ov5T 
	 $(CGTOOLS_V5T)/$(AR_V5T) cr $@ $^
all: $(LIBDIR)/speech.av5T
clean::
	-$(RM) $(LIBDIR)/speech.av5T
#
#  @(#) ti.sdo.ce.speech; 1, 0, 2,1; 2-24-2012 19:30:32; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


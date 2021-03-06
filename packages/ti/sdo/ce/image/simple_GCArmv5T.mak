#
#  Copyright 2012 by Texas Instruments Incorporated.
#  
#

# Generated by build.filter.Make on Thu Feb 23 2012 17:50:17 GMT-0800 (PST)
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

.objs/image_imgdec.ov5T: imgdec.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgdec.ov5T
clean::
	-$(RM) .objs/image_imgdec.ov5T

.objs/image_imgdec_skel.ov5T: imgdec_skel.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgdec_skel.ov5T
clean::
	-$(RM) .objs/image_imgdec_skel.ov5T

.objs/image_imgdec_stubs.ov5T: imgdec_stubs.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgdec_stubs.ov5T
clean::
	-$(RM) .objs/image_imgdec_stubs.ov5T

.objs/image_imgenc.ov5T: imgenc.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgenc.ov5T
clean::
	-$(RM) .objs/image_imgenc.ov5T

.objs/image_imgenc_skel.ov5T: imgenc_skel.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgenc_skel.ov5T
clean::
	-$(RM) .objs/image_imgenc_skel.ov5T

.objs/image_imgenc_stubs.ov5T: imgenc_stubs.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections -DXDM_INCLUDE_DOT9_SUPPORT  $(INCS)  -o $@ $<
	 
all: .objs/image_imgenc_stubs.ov5T
clean::
	-$(RM) .objs/image_imgenc_stubs.ov5T

$(LIBDIR)/image.av5T: .objs/image_imgdec.ov5T .objs/image_imgdec_skel.ov5T .objs/image_imgdec_stubs.ov5T .objs/image_imgenc.ov5T .objs/image_imgenc_skel.ov5T .objs/image_imgenc_stubs.ov5T 
	 $(CGTOOLS_V5T)/$(AR_V5T) cr $@ $^
all: $(LIBDIR)/image.av5T
clean::
	-$(RM) $(LIBDIR)/image.av5T
#
#  @(#) ti.sdo.ce.image; 1, 0, 3,1; 2-24-2012 19:29:54; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


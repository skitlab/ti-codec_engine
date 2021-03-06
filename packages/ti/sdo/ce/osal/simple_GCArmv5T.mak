#
#  Copyright 2012 by Texas Instruments Incorporated.
#  
#

# Generated by build.filter.Make on Thu Feb 23 2012 17:50:28 GMT-0800 (PST)
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

.objs/osal_Queue.ov5T: Queue.c
	 $(CGTOOLS_V5T)/$(CC_V5T) -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing  -march=armv5t -Dfar=  -Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_2_1 -O2 -ffunction-sections  $(INCS)  -o $@ $<
	 
all: .objs/osal_Queue.ov5T
clean::
	-$(RM) .objs/osal_Queue.ov5T

$(LIBDIR)/osal.av5T: .objs/osal_Queue.ov5T 
	 $(CGTOOLS_V5T)/$(AR_V5T) cr $@ $^
all: $(LIBDIR)/osal.av5T
clean::
	-$(RM) $(LIBDIR)/osal.av5T
#
#  @(#) ti.sdo.ce.osal; 2, 0, 2,1; 2-24-2012 19:30:13; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


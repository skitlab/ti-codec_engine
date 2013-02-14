# 
#  Copyright (c) 2012, Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
#
#  ======== video1_copy.rtcfg_remote_evm3530_linux/makefile ========
#  GNUmake-based makefile
#

#
# EXAMPLES_ROOTDIR should be set to the examples directory under your
# CE_INSTALL_DIR.
#
EXAMPLES_ROOTDIR ?= $(CURDIR)/../../../../../../../..

#
#  Include xdcpaths.mak if it exists. This file defines package paths and
#  build rules.  If xdcpaths.mak does not exist the variables must be set on
#  the command line.
#
-include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

#
#  ======== define all the repositories needed by this example ========
#
XDCTOOLS_REPO   ?= $(XDC_INSTALL_DIR)/packages
CE_REPO         ?= $(CE_INSTALL_DIR)/packages
SUFFIX          ?= v5T

#
#  Make sure CE_INSTALL_DIR was set properly. By using "-include" to include
#  xdcpaths.mak, no error message will be given if xdcpaths.mak is not found,
#  and in that case, the user must have set the environment variables, for
#  example, on the command line.
# 
ERRMSG = which is invalid (could not find file "$(TEST_FILE)"). Set this in <codec engine examples>/xdcpaths.mak! If you intended to use xdcpaths.mak, also please make sure that EXAMPLES_ROOTDIR is set correctly in this makefile. See the build documentation to correct this error.
TEST_FILE := $(CE_REPO)/ti/sdo/ce/package.xdc
ifeq ($(wildcard $(TEST_FILE)),)
    $(error CE_INSTALL_DIR is set to "$(CE_INSTALL_DIR)", $(ERRMSG))
endif


REPO_PATH = \
	$(XDCTOOLS_REPO) \
	$(CE_REPO) \
	$(LINK_INSTALL_DIR)/packages \
	$(XDAIS_INSTALL_DIR)/packages \
	$(FC_INSTALL_DIR)/packages \
	$(CMEM_INSTALL_DIR)/packages \
	$(EXAMPLES_ROOTDIR)


CE_APPS_DIR ?= $(EXAMPLES_ROOTDIR)/ti/sdo/ce/examples/apps

#
#  ======== common defines ========
#
ALL.defs =
ALL.incs = -I. $(addprefix -I,$(REPO_PATH))
ALL.libs = $(addprefix -L,$(REPO_PATH))

EXTLIBS_$(PROFILE) = \
	$(CE_APPS_DIR)/rtcfg/osal/$(DEV)/lib/osal.a \
	$(CE_APPS_DIR)/rtcfg/osal/$(DEV)/lib/cstubs.a

#
#  ======== standard macros ========
#
ECHO    ?= echo
MKDIR   ?= mkdir
RM      ?= rm -f
RMDIR   ?= rm -rf

ifneq (clean,$(MAKECMDGOALS))
ifneq (,$(PROFILE))
ifeq (,$(wildcard bin/$(PLAT)/$(PROFILE)))
    $(shell $(MKDIR) -p bin/$(PLAT)/$(PROFILE))
endif
endif
endif

.PHONY: nothing

#
#  ======== toolchain macros ========
#  Note: You do not need to set CGTOOLS_V5T and CC_V5T if they have been
#  set in xdcpaths.mak.
#
CGTOOLS_V5T ?= <__your_CGTOOLS_V5T__>
CC_V5T ?= <__your_CC_V5T__>
CC = $(CGTOOLS_V5T)/$(CC_V5T)

CCPROFILE.debug = -g -D_DEBUG_=1 
CCPROFILE.release = -O2
CFLAGS = -fPIC -Wall -fno-strict-aliasing $(CCPROFILE.$(PROFILE)) \
    -I. $(addprefix -I,$(REPO_PATH))
CPPFLAGS = -Dxdc_target_name__=GCArmv5T \
    -Dxdc_target_types__=gnu/targets/arm/std.h

LNKPROFILE.debug = -g
LNKPROFILE.release =
LDFLAGS = $(LNKPROFILE.$(PROFILE))
LDLIBS = -lpthread -lrt -ldl

#
#  ======== example sources ========
#
#  This example is built with the following source files:
#
#  $(CE_REPO)/ti/sdo/ce/utils/rtcfg/
#      rtcfg.c
#      rtcfg_fcinit.c	
#
#      The source files in $(CE_REPO)/ti/sdo/ce/utils/rtcfg are run-time
#      configuration files.  These files do not need to be modified to run this
#      example. If you want to modify the configuration in any of these files,
#      copy it to this directory and modify as needed.
#
#  $(EXAMPLES_ROOTDIR)/ti/sdo/ce/examples/apps/video1_copy/
#      app.c
#      main_hlos_remote.c
#
#      These are the same source files used to build the XDC configurable
#      version of this app. They do not need to be modified for the run-time
#      configuration example.
#
#  $(CURDIR)/
#      app_config.c
#      evm3530_config_all.c
#
#      The file, app_config.c, contains algorithm and engine tables needed
#      by the app. The file, evm3530_config_all.c, contains platform specific
#      configuration.
#
#  The vpath variable below sets the search path for the source files.
#
APP.srcs =                      \
	rtcfg.c                 \
	rtcfg_fcinit.c		\
        app_config.c            \
        evmTI816X_config_all.c  \
        app.c                   \
        main_hlos_remote.c

APP.objs = $(addprefix bin/$(PLAT)/$(PROFILE)/, \
    $(patsubst %.c,%.o$(SUFFIX),$(APP.srcs)))

#
#  The vpath variable lets us maintain some of the same sources for both XDC
#  build and gmake build, and use default run-time configuration files.
#
vpath %.c $(CE_APPS_DIR)/video1_copy $(CE_REPO)/ti/sdo/ce/utils/rtcfg

#
#  ======== linker command files ========
#
#  Set up path to find linker command files, and which linker command
#  files will be used (eg, debug or release).
#

#  Path for linker command files. We use several linker command files,
#  keeping those containing Codec Engine and Framework Components libraries
#  in a common area where they can be used by multiple apps. The linker
#  command files in this directory just contain the codec libraries needed
#  by this app.
#
#  The common linker command files, in ti/sdo/ce/utils/rtcfg/linux/<platform>,
#  shouldn't need modification, but in the chance that they did, they could be
#  copied to this directory and modified as needed. The vpath will cause
#  any modified linker command files to be found first.
#
vpath %.cmd $(CE_REPO)/ti/sdo/ce/utils/rtcfg/linux/evmTI816X

LINKER_FILE = # linker_$(PROFILE).cmd - No local codecs, so we don't use this.
CE_LINKER_FILE = ce_remote_$(PROFILE).cmd
FC_LINKER_FILE = fc_$(PROFILE).cmd

#
#  ======== compute build goals from DEVICE and PROGRAMS ========
#  Don't attempt to build unless DEVICE = OMAP3530, PROGRAMS = APP_CLIENT,
#  and GPPOS is Linux.
#
ifneq (,$(findstring TI816X,$(DEVICE)))
ifneq (,$(findstring APP_CLIENT,$(PROGRAMS)))
ifneq (,$(findstring LINUX,$(GPPOS)))
GOALS := $(GOALS) TI816X_APP_CLIENT
endif
endif
endif

ifeq (,$(GOALS))
GOALS = nothing
endif

#
#  ======== make commands ========
#
all:
	$(MAKE) $(GOALS)
PROGRAM = video1_copy

TI816X_APP_CLIENT:
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	@$(MAKE) PLAT=ti_platforms_evmTI816X DEV=debug\
            PROFILE=debug TARGET=GCArmv5T \
            bin/ti_platforms_evmTI816X/debug/$(PROGRAM).xv5T
	@$(MAKE) PLAT=ti_platforms_evmTI816X DEV=release\
            PROFILE=release TARGET=GCArmv5T \
            bin/ti_platforms_evmTI816X/release/$(PROGRAM).xv5T


nothing:
	@$(ECHO) "Nothing to build for the given devices and programs"
	@$(ECHO) "    DEVICE=\"$(DEVICE)\""
	@$(ECHO) "    PROGRAMS=\"$(PROGRAMS)\""

#
#  ======== build rules ========
#
bin/$(PLAT)/$(PROFILE)/$(PROGRAM).x$(SUFFIX): $(APP.objs) $(EXTLIBS_$(PROFILE)) $(CE_LINKER_FILE) $(LINKER_FILE) $(FC_LINKER_FILE)
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(CC) -o $@ $^ $(EXTLIBS_$(PROFILE)) $(LDLIBS) $(ALL.defs) $(ALL.libs)

.SECONDARY:
bin/$(PLAT)/$(PROFILE)/%.o$(SUFFIX): %.h
bin/$(PLAT)/$(PROFILE)/%.o$(SUFFIX): %.c
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(CE_APPS_DIR)/rtcfg/osal/$(DEV)/lib/osal.a:
$(CE_APPS_DIR)/rtcfg/osal/$(DEV)/lib/cstubs.a:
	@echo "Making osal..."
	$(MAKE) -C $(CE_APPS_DIR)/rtcfg/osal \
		OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) all


#
#  ======== clean ========
#
clean::
	$(RMDIR) bin
#
#  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,1; 2-24-2012 19:27:23; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


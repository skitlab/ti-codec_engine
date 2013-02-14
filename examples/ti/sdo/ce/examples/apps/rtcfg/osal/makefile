#
#  Copyright 2012 by Texas Instruments Incorporated.
#  
#

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
#  ======== ti.sdo.ce.examples.apss.rtcfg.osal/makefile ========
#

#
# EXAMPLES_ROOTDIR should be set to the examples directory under your
# CE_INSTALL_DIR.
#
EXAMPLES_ROOTDIR ?= $(CURDIR)/../../../../../../..

#
#  Include xdcpaths.mak if it exists. This file defines package paths and
#  build rules.  If xdcpaths.mak does not exist the variables must be set on
#  the command line.
#
-include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

# take the tool chain from xdcpaths.mak
CROSS_COMPILE = $(subst -gcc,-,$(CGTOOLS_V5T)/$(CC_V5T))

#
#  ======== standard macros ========
#
ECHO    ?= echo
MKDIR   ?= mkdir
RM      ?= rm -f
RMDIR   ?= rm -rf

ifneq (clean,$(MAKECMDGOALS))
ifneq (,$(PROFILE))
ifeq (,$(wildcard $(PROFILE)))
    $(shell $(MKDIR) -p $(PROFILE))
endif
endif
endif

ifneq (,$(findstring LINUX,$(GPPOS)))
GOALS := $(GOALS) debug release
endif


ifeq (,$(GOALS))
GOALS = nothing
endif

#
#  ======== make commands ========
#
.PHONY: debug release

all:
	$(MAKE) $(GOALS)

debug:
	@$(ECHO) "#"
	@$(ECHO) "# osal makefile: Making $@ ..."
	$(MAKE) PROFILE=$@ .outdir
	$(MAKE) -C $@ \
            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/build/Makefile \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            PRECONFIG=$(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/development \
            CFLAGS=-g
	$(MAKE) -C $@ \
            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs/Makefile \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            CFLAGS=-g

release:
	@$(ECHO) "#"
	@$(ECHO) "# osal makefile: Making $@ ..."
	$(MAKE) PROFILE=$@ .outdir
	$(MAKE) -C $@ \
            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/build/Makefile \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            PRECONFIG=$(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/production \
            CFLAGS=-O2
	$(MAKE) -C $@ \
            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs/Makefile \
            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
            CROSS_COMPILE=$(CROSS_COMPILE) \
            CFLAGS=-O2

nothing:
	@$(ECHO) "Nothing to build for the given devices and programs"
	@$(ECHO) "    DEVICE=\"$(DEVICE)\""
	@$(ECHO) "    PROGRAMS=\"$(PROGRAMS)\""


.outdir: ;


#
#  ======== clean ========
#
clean::
	$(RMDIR) debug release
#
#  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,1; 2-17-2012 23:58:40; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#

#
#  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,1; 2-24-2012 19:27:22; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


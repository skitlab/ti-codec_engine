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


TARGETS := ""

#
#  Figure out what targets to build for
#
ifneq (,$(findstring X86,$(DEVICES)))
TARGETS := X86
endif

TEST_FILE := $(CGTOOLS_V5T)/$(CC_V5T)
ifneq ($(wildcard $(TEST_FILE)),)
    TARGETS := V5T $(TARGETS)
endif

ifeq ($(USING_CETOOLS),1)

# rtcfg/osal makefiles use OSAL_INSTALL_DIR
OSAL_PROD = $(CE_INSTALL_DIR)/cetools

else

OSAL_PROD = $(OSAL_INSTALL_DIR)

endif

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

all:
	@$(ECHO) "# Making all... TARGETS = $(TARGETS)"
ifneq (,$(findstring X86,$(TARGETS)))
	$(MAKE) OSAL_INSTALL_DIR=$(OSAL_PROD) -f make86U.mk all
endif
ifneq (,$(findstring V5T,$(TARGETS)))
	$(MAKE) OSAL_INSTALL_DIR=$(OSAL_PROD) -f makev5T.mk all
endif

#
#  ======== clean ========
#
clean::
	$(RMDIR) osal_dev osal_rel


.outdir: ;
#
#  @(#) ti.sdo.ce.utils.rtcfg.osal; 1, 0, 0,1; 2-24-2012 19:31:38; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


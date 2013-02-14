# --COPYRIGHT--,BSD
#  Copyright (c) $(CPYYEAR), Texas Instruments Incorporated
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
# --/COPYRIGHT--
#
#  ======== paths.mk ========
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
CE_REPO         ?= $(CE_INSTALL_DIR)/packages

# Root dir for codecs used in this server
CODECS_REPO       ?= $(FC_INSTALL_DIR)/examples

PROFILE = debug

SUFFIX          ?= 64P
PLAT=ti_platforms_evm3530

#
#  ======== standard macros ========
#
ECHO    ?= echo
MKDIR   ?= mkdir
RM      ?= rm -f
RMDIR   ?= rm -rf

ifneq (clean,$(MAKECMDGOALS))
ifneq (,$(PROFILE))
ifeq (,$(wildcard bin/$(PLAT)))
    $(shell $(MKDIR) -p bin/$(PLAT))
endif
endif
endif


REPO_PATH = \
	$(XDC_INSTALL_DIR)/packages \
	$(XDAIS_INSTALL_DIR)/packages \
	$(OSAL_INSTALL_DIR)/packages \
	$(IPC_INSTALL_DIR)/packages \
	$(FC_INSTALL_DIR)/packages \
	$(BIOS_INSTALL_DIR)/packages \
	$(CE_REPO) \
	$(CETOOLS_REPO) \
	$(CODECS_REPO) \
	$(LINK_INSTALL_DIR)/packages \
	$(EXAMPLES_ROOTDIR)

XDC_PATH := $(XDC_INSTALL_DIR)/packages;$(CE_REPO);$(BIOS_INSTALL_DIR)/packages;$(IPC_INSTALL_DIR)/packages;$(XDAIS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(OSAL_INSTALL_DIR)/packages;$(EXAMPLES_ROOTDIR);$(LINK_INSTALL_DIR)/packages;$(XDC_PATH)


# Configuro settings.  CONFIGPKG is the basename of your application's
# config script
CONFIGPKG = rtcfg_all
CONFIG_BLD := ./_config.bld

# Name the xdc target and platform
XDCTARGET = ti.targets.C64P

XDCPLATFORM = ti.platforms.evm3530:DSP

# configuro-generated files
COMPILER_FILE = $(CONFIGPKG)/compiler.opt
LINKER_FILE = $(CONFIGPKG)/linker.cmd

# The path to the configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro


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

#
# ==== Standard Variables ====
#

# These vars are used when installing CE content
DESTDIR ?= <UNDEFINED>
packagesdir ?= /packages
libdir ?= /lib
includedir ?= /include
ifeq ($(docdir),)
    docdir := /share/ti/codec_engine/doc
    xdcdocdir := /docs/codec_engine
else
    xdcdocdir := $(docdir)
endif

ifeq ($(prefix),)
    prefix := /usr
    xdcprefix := /
else
    xdcprefix := $(prefix)
endif

include ./products.mak

#
# Set XDCOPTIONS.  Use -v for a verbose build.
#
#XDCOPTIONS=v
export XDCOPTIONS

# JOBS is the max number of parallel build commands to run concurrently.
# You can often get a build performance lift by setting JOBS to a value > 1,
# however debugging build errors is tough(!), so the default setting is 1.
JOBS=1

#######################################################
## Shouldn't have to modify anything below this line ##
#######################################################

#
# Set XDCARGS to some of the variables above.  XDCARGS are passed
# to the XDC build engine, which loads codec_engine.bld, which
# extracts these variables and use them to determine what to build and
# which toolchains to use.
#
# Note that not all of these variables need to be set to something valid.
# Unfortunately, since these vars are unconditionally assigned, your build line
# will be longer and more noisy than necessary (e.g., it will include CC_V5T
# assignment even if you're just building for C64P).
#
# Some background is here:
#     http://rtsc.eclipse.org/docs-tip/Command_-_xdc#Environment_Variables
#
XDCARGS= \
    ti.targets.C64P=\"$(ti.targets.C64P)\" \
    ti.targets.C674=\"$(ti.targets.C674)\" \
    ti.targets.arm.elf.M3=\"$(ti.targets.arm.elf.M3)\" \
    ti.targets.elf.C64P=\"$(ti.targets.elf.C64P)\" \
    ti.targets.elf.C64T=\"$(ti.targets.elf.C64T)\" \
    ti.targets.elf.C66=\"$(ti.targets.elf.C66)\" \
    ti.targets.elf.C674=\"$(ti.targets.elf.C674)\" \
    gnu.targets.arm.GCArmv5T=\"$(gnu.targets.arm.GCArmv5T)\" \
    google.targets.arm.Bionic=\"$(google.targets.arm.Bionic)\"


# Set XDCPATH to contain necessary repositories.
XDCPATH = $(XDAIS_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR)/packages;$(OSAL_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(EDMA3_LLD_INSTALL_DIR)/packages;$(IPC_INSTALL_DIR)/packages

# Set your XDC executable command
XDC = $(XDC_INSTALL_DIR)/xdc XDCARGS="$(XDCARGS)" XDCBUILDCFG=./codec_engine.bld

# Conditionally set XDCOPTIONS=v for verbose builds
#XDCOPTIONS=v
export XDCOPTIONS
export XDCPATH


# Helper variables
PRODUCTS=$(subst packages/,,$(wildcard packages/ti/sdo/*))
LIBS = $(shell cd packages && find . -name '*.av5T' -or -name '*.av7A' -type f)
HEADERS = $(shell cd packages && find . -name '*.h' -type f -not \( -name "package.defs.h" -o -name "_*.h" \))
DOCS = $(wildcard *.html) docs

LIBDIR = $(DESTDIR)/$(prefix)/$(libdir)
INCDIR = $(DESTDIR)/$(prefix)/$(includedir)
DOCDIR = $(DESTDIR)/$(prefix)/$(docdir)
PACKAGESDIR = $(DESTDIR)/$(xdcprefix)/$(packagesdir)
XDCDOCDIR = $(DESTDIR)/$(xdcprefix)/$(xdcdocdir)


# Helper functions
define purge
	@find $(PACKAGESDIR)/$(1) -name $(2) -exec rm -rf {} \;

endef


# Targets
all: .all-packages

# This builds all packages rooted in ./packages
.all-packages:
	$(XDC) --jobs=$(JOBS) -Pr ./packages

# This cleans all packages rooted in ./packages
clean:
	$(XDC) --jobs=$(JOBS) clean -Pr ./packages

install-packages:
	@echo "Installing packages into $(PACKAGESDIR)..."
	@mkdir -p $(PACKAGESDIR)
	@cd packages && cp --parents -rf $(PRODUCTS) $(PACKAGESDIR)
#	$(foreach prod,$(PRODUCTS),$(call purge,$(prod),'*.c'))
#	$(foreach prod,$(PRODUCTS),$(call purge,$(prod),'*.bld'))
	@echo "Installing documentation into $(XDCDOCDIR)..."
	@mkdir -p $(XDCDOCDIR)
	@cp -rf $(DOCS) xdoc $(XDCDOCDIR)

install:
	@echo "Installing libraries into $(LIBDIR)..."
	@mkdir -p $(LIBDIR)
	@cd packages && cp --parents -f $(LIBS) $(LIBDIR)
	@echo "Installing header files into $(INCDIR)..."
	@mkdir -p $(INCDIR)
	@cd packages && cp --parents -f $(HEADERS) $(INCDIR)
	@echo "Installing documentation into $(DOCDIR)..."
	@mkdir -p $(DOCDIR)
	@cp -rf $(DOCS) $(DOCDIR)

help:
	@echo
	@echo "Available build targets are:"
	@echo
	@echo "  install-packages"
	@echo "      Install CE packages and docs"
	@echo
	@echo "  install"
	@echo "      Install CE headers, libraries and docs"
	@echo
#
#  @(#) codec_engine_3_22_01_06; 1, 0, 0,1; 2-24-2012 19:49:44; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


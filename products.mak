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
#  ======== products.mak ========
#

# Optional, but useful when many/all dependent components are in one folder
#
DEPOT = _your_depot_folder_

# Define the product variables for the device you will be using.
IPC_INSTALL_DIR         = $(DEPOT)/ipc_1_24_02_27
FC_INSTALL_DIR          = $(DEPOT)/framework_components_3_22_01_07
LINK_INSTALL_DIR        = $(DEPOT)/syslink_2_10_03_20
OSAL_INSTALL_DIR        = $(DEPOT)/osal_1_22_01_09
XDAIS_INSTALL_DIR       = $(DEPOT)/xdais_7_22_00_03
CMEM_INSTALL_DIR        = $(DEPOT)/linuxutils_3_22_00_02
EDMA3_LLD_INSTALL_DIR   = $(DEPOT)/edma3_lld_02_11_02_04
XDC_INSTALL_DIR         = $(DEPOT)/xdctools_3_23_01_43
BIOS_INSTALL_DIR        = $(DEPOT)/bios_6_33_02_31

# Set location of various cgtools
ti.targets.C64P ?=
ti.targets.C674 ?=

ti.targets.elf.C64P ?=
ti.targets.elf.C64T ?=
ti.targets.elf.C66 ?=
ti.targets.elf.C674 ?=

ti.targets.arm.elf.M3 ?=

# Note that GCC targets are 'special' and require more than one var to be set.
#
# The CGTOOLS_* var points at the base of the toolchain.
# The CC_* var points at the gcc binary (e.g. bin/arm-none-linux-gnueabi-gcc)
#
# Note, the *_V5T vars are for Linux GCC tools, the *_BNC are for Android
CGTOOLS_V5T ?=
CC_V5T      ?=

CGTOOLS_BNC ?=
CC_BNC      ?=
LIBCDIR_BNC ?=
FSDIR_BNC   ?=

# The AR_* var points at the ar binary (e.g. bin/arm-none-linux-gnueabi-ar)
# We can often auto-determine this based on the value of CC_V5T.
# The magic make cmd replaces the "-gcc" at the end of CC_V5T var with "-ar".
AR_V5T      ?= $(CC_V5T:-gcc=-ar)

# don't modify this, it's derived from the GCC vars above
gnu.targets.arm.GCArmv5T ?= $(CGTOOLS_V5T);LONGNAME=$(CC_V5T);profiles.release.compileOpts.copts=-O2 -ffunction-sections
google.targets.arm.Bionic ?= $(CGTOOLS_BNC);LONGNAME=$(CC_BNC);libcDir=$(LIBCDIR_BNC);fsDir=$(FSDIR_BNC)

# Use this goal to print your product variables.
.show-products::
#	@echo "DEPOT                       = $(DEPOT)"
	@echo "LINK_INSTALL_DIR            = $(LINK_INSTALL_DIR)"
	@echo "CMEM_INSTALL_DIR            = $(CMEM_INSTALL_DIR)"
	@echo "XDAIS_INSTALL_DIR           = $(XDAIS_INSTALL_DIR)"
	@echo "IPC_INSTALL_DIR             = $(IPC_INSTALL_DIR)"
	@echo "EDMA3_LLD_INSTALL_DIR       = $(EDMA3_LLD_INSTALL_DIR)"
	@echo "FC_INSTALL_DIR              = $(FC_INSTALL_DIR)"
	@echo "OSAL_INSTALL_DIR            = $(OSAL_INSTALL_DIR)"
	@echo "CGTOOLS_V5T                 = $(CGTOOLS_V5T)"
	@echo "CC_V5T                      = $(CC_V5T)"
	@echo "AR_V5T                      = $(AR_V5T)"
	@echo "ti.targets.C64P      (COFF) = $(ti.targets.C64P)"
	@echo "ti.targets.C674      (COFF) = $(ti.targets.C674)"
	@echo "ti.targets.elf.C64T   (ELF) = $(ti.targets.elf.C64T)"
	@echo "ti.targets.elf.C64P   (ELF) = $(ti.targets.elf.C64P)"
	@echo "ti.targets.elf.C674   (ELF) = $(ti.targets.elf.C674)"
	@echo "ti.targets.elf.C66    (ELF) = $(ti.targets.elf.C66)"
	@echo "ti.targets.arm.elf.M3 (ELF) = $(ti.targets.arm.elf.M3)"
	@echo "gnu.targets.arm.GCArmv5T    = $(gnu.targets.arm.GCArmv5T)"
	@echo "google.targets.arm.Bionic   = $(google.targets.arm.Bionic)"

#
#  @(#) codec_engine_3_22_01_06; 1, 0, 0,1; 2-24-2012 19:49:44; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


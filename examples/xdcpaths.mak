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
#  ======== xdcpaths.mak ========
#  definition of XDC paths and commands
#
#  This makefile constructs the "search path" for the XDCtools where it finds
#  numerous components and packages needed to build examples and
#  programs.  See examples/build_instructions.html for general details about
#  this file.
#
#  USER NOTE:
#  1) you can remove some of the devices from the "DEVICE" list and/or remove
#     some of the types of binaries from the "PROGRAMS" list and/or remove
#     some of the OS runtime environments from the "GPPOS" list to reduce
#     the build time (and possibly avoid checking for presence of a component
#     you don't need)

# (Optional) remove from this list the GPP OS's you're not interested in
# building.
#
# Note, this is only used when DEVICES contains a device that runs a GPP running
# a High Level OS (HLOS) like Linux, WinCE, etc.
#
# In most cases, you'll likely set this to empty (e.g. BIOS-running 6472 users)
# or one HLOS entry (e.g. Linux GCC using OMAP3 users).
#
# Note, this is a space-delimited list.
#GPPOS := LINUX_GCC ANDROID
GPPOS := LINUX_GCC

# (Optional) Remove from the list the types of programs you're not
# interested in building:
#
# APP_CLIENT -- build client apps for algs running remotely, on multicore systems
# DSP_SERVER -- build servers containing algs, for use by client apps on other processors
# APP_LOCAL  -- build apps with local algs in a single executable
#
# Note, this is a space-delimited list.
PROGRAMS := APP_CLIENT DSP_SERVER APP_LOCAL

#
# Note, this is a space-delimited list.
#
#DEVICE := OMAP3530 OMAPL138 OMAP4430 C6472 C6474 TI816X TI814X TI813X
DEVICE := TI814X

# Set this to your CE installation dir
CE_INSTALL_DIR :=

# Pre-pend these vars to what products.mak's .show-products prints
.show-products::
	@echo "DEVICE                      = $(DEVICE)"
	@echo "GPPOS                       = $(GPPOS)"
	@echo "PROGRAMS                    = $(PROGRAMS)"
	@echo "CE_INSTALL_DIR              = $(CE_INSTALL_DIR)"

include $(CE_INSTALL_DIR)/products.mak

# The appropriate dependencies will be used to generate the XDC_PATH.
# Any other components your example requires can be added to thsi variable
# MY_XDC_PATH := <your component>/packages;
MY_XDC_PATH :=

# check above settings for correctness
include $(EXAMPLES_ROOTDIR)/buildutils/xdcpathcheck.mak

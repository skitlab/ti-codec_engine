#
#  Copyright (c) 2010, Texas Instruments Incorporated
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
#  ======== linuxdist/build/Makefile ========
#


ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard lib))
    $(shell mkdir -p lib)
endif
endif

OSAL_INSTALL_DIR ?= ../../..
XDCSOURCES ?= $(OSAL_INSTALL_DIR)/sources
LINUXOSAL ?= $(OSAL_INSTALL_DIR)/packages
PRECONFIG ?= $(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/production

SRCDIRS = $(XDCSOURCES) $(LINUXOSAL) $(PRECONFIG)

# include source files specified by preconfig. Defines CSRCS and CPPSRCS
-include $(PRECONFIG)/sources.inc

XDC_TARGET ?= GCArmv5T
XDC_TYPES ?= gnu/targets/arm/std.h
SUFFIX ?= v5T

CPPFLAGS = -Dxdc_target_name__=$(XDC_TARGET) -Dxdc_target_types__=$(XDC_TYPES) -I. $(addprefix -I,$(SRCDIRS))

CXX = $(CC)
CXXFLAGS = $(CFLAGS)

OUTPUT_OPTION = -o lib/$(notdir $@)


VPATH = $(XDCSOURCES):$(LINUXOSAL):$(PRECONFIG)

all: lib/osal.a$(SUFFIX)

ALL.objs = $(addprefix lib/, $(patsubst %.c,%.o$(SUFFIX),$(CSRCS)))

ALL.cppobjs = $(addprefix lib/,	$(patsubst %.cpp,%.o$(SUFFIX),$(CPPSRCS)))

lib/osal.a$(SUFFIX): $(ALL.objs) lib/preConfig_p$(SUFFIX).o$(SUFFIX)
lib/osal.a$(SUFFIX): $(ALL.cppobjs)
	@echo "#"
	@echo "# Making $@ ..."
	$(AR) -cr $@ $(addprefix lib/,$(notdir $^))

$(PRECONFIG)/preConfig_p$(SUFFIX).c:

.SECONDARY:
lib/%.o$(SUFFIX): %.c
	@echo "#"
	@echo "# Making $@ ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) -o lib/$(notdir $@) -c $<

lib/%.o$(SUFFIX): %.cpp
	@echo "#"
	@echo "# Making $@ ..."
	$(CC) $(CPPFLAGS) $(CFLAGS) -o lib/$(notdir $@) -c $<

clean::
	rm -f lib/*


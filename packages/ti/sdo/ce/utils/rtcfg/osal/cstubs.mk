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
#  ======== linuxdist.cstubs/Makefile ========
#

include ../defs.mk

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard lib))
    $(shell mkdir -p lib)
endif
endif

OSAL_INSTALL_DIR ?= ../../..
XDCSOURCES ?= $(OSAL_INSTALL_DIR)/sources
LINUXOSAL ?= $(OSAL_INSTALL_DIR)/packages
CSTUBSSOURCES ?= $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs

SRCDIRS = $(XDCSOURCES) $(LINUXOSAL)

XDC_TARGET ?= GCArmv5T
XDC_TYPES ?= gnu/targets/arm/std.h

CPPFLAGS = -Dxdc_target_name__=$(XDC_TARGET) -Dxdc_target_types__=$(XDC_TYPES) -I. $(addprefix -I,$(SRCDIRS))

OUTPUT_OPTION = -o lib/$@


ALL_srcs = LoggerPosix.c
ALL_objs :=  $(addprefix lib/, $(patsubst %.c,%.o$(SUFFIX),$(ALL_srcs)))

VPATH = $(CSTUBSSOURCES)

all: lib/cstubs.a$(SUFFIX)

lib/cstubs.a$(SUFFIX): $(ALL_objs)
	@echo "#"
	@echo "# Making $@ ..."
	$(AR) -cr $@ $^

.SECONDARY:
lib/%.o$(SUFFIX): %.c
	@echo "#"
	@echo "# Making $@ ... XDC_TARGET = $(XDC_TARGET)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean::
	rm -f lib/*


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
#  ======== makeapp.mk ========
#  GNUmake-based makefile
#

include paths.mk

#
#  ======== toolchain macros ========
#
CC_C64P ?= bin/cl6x
LNK_C64P ?= bin/lnk6x

CC = $(ti.targets.C64P)/$(CC_C64P)
LNK = $(ti.targets.C64P)/$(LNK_C64P)

CCPROFILE.debug = -g -D_DEBUG_=1
CCPROFILE.release = -O2
CPPFLAGS = -Dxdc_target_name__=64P \
    -Dxdc_target_types__=ti/targets/std.h

LNKPROFILE.debug = -q
LNKPROFILE.release = -q
LDFLAGS = $(LNKPROFILE.$(PROFILE)) -w -q -u _c_int00 -c  $(addprefix -I,$(REPO_PATH))

LDLIBS = -l $(ti.targets.C64P)/lib/rts64plus.lib

PROGRAM = bin/$(PLAT)/rtcfgapp.x$(SUFFIX)

# Augment the standard $(CPPFLAGS) variable, adding the
# Configuro-generated compiler file.
CPPFLAGS +=  $(shell cat $(COMPILER_FILE)) -g

APP.srcs =                      \
	rtcfg.c                 \
	rtcfg_bios_fcinit.c     \
	rtcfg_bios_ceinit.c     \
	app_config.c            \
	svr_config.c            \
	main.c

APP.objs = $(addprefix bin/$(PLAT)/, \
    $(patsubst %.c,%.o$(SUFFIX),$(APP.srcs)))

vpath %.c $(CE_REPO)/ti/sdo/ce/utils/rtcfg

.PHONY: nothing

#
#  ======== compute build goals from DEVICE and PROGRAMS ========
#  Don't attempt to build unless DEVICE = OMAP3530, PROGRAMS = DSP_SERVER,
#  and COFF toolchain is selected.
#
#  Note that we support more than that combination, but to keep this makefile
#  simple we limit the build to just that combo.
#
ifneq (,$(findstring OMAP3530,$(DEVICE)))
ifneq (,$(findstring DSP_SERVER,$(PROGRAMS)))
ifneq (,$(ti.targets.C64P))
GOALS := $(PROGRAM)
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
	$(MAKE) -f makeapp.mk $(GOALS)

#all: bin/$(PLAT)/rtcfgapp.x$(SUFFIX)

# The generated linker and compiler files depend on the generated
# config package
$(LINKER_FILE) $(COMPILER_FILE) : $(CONFIGPKG)

# Compile
bin/$(PLAT)/%.o$(SUFFIX) : %.c $(COMPILER_FILE)
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -eo.o$(SUFFIX) -fr=bin/$(PLAT) $<

# Link
#bin/$(PLAT)/rtcfgapp.x$(SUFFIX): $(APP.objs)
$(PROGRAM):  $(APP.objs)
	@$(ECHO) "#"
	@$(ECHO) "# Making $@ ..."
	$(LNK) -o $@ $(LDFLAGS) $^ mylink.cmd $(LINKER_FILE) $(LDLIBS) -m $@.map

nothing:
	@$(ECHO) "Nothing to build for the given devices and programs"
	@$(ECHO) "    DEVICE=\"$(DEVICE)\""
	@$(ECHO) "    PROGRAMS=\"$(PROGRAMS)\""

#
#  ======== clean ========
#
clean::
	@$(ECHO) "# Removing bin directory..."
	$(RMDIR) bin


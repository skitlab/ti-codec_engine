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
#  ======== makefile ========
#

all:
%::
#	echo DEVICE=$(DEVICE)
	$(MAKE) -C speech $@
	$(MAKE) -C speech_copy $@
	$(MAKE) -C image_copy $@
	$(MAKE) -C video_copy $@
	$(MAKE) -C audio_copy $@
	$(MAKE) -C scale $@
	$(MAKE) -C server_api_example $@
	$(MAKE) -C video3_copy $@
	$(MAKE) -C video2_copy $@
	$(MAKE) -C video1_copy $@
	$(MAKE) -C image1_copy $@
	$(MAKE) -C audio1_copy/sync $@
#	$(MAKE) -C audio1_copy/async $@
	$(MAKE) -C audio1_ires $@
	$(MAKE) -C speech1_copy $@
	$(MAKE) -C rtcfg/osal $@
#	$(MAKE) -C rtcfg/audio1_ires/rtcfg_local_evm3530_linux $@
	$(MAKE) -C rtcfg/speech1_copy/rtcfg_DM365 $@
	$(MAKE) -C rtcfg/speech1_copy/rtcfg_local_evm3530_linux $@
	$(MAKE) -C rtcfg/speech1_copy/rtcfg_remote_evm3530_linux $@
	$(MAKE) -C rtcfg/video1_copy/rtcfg_local_evm3530_linux $@
	$(MAKE) -C rtcfg/video1_copy/rtcfg_remote_evm3530_linux $@
	$(MAKE) -C rtcfg/video1_copy/rtcfg_remote_evmTI816X_linux $@
#	$(MAKE) -C video2split_copy $@
	$(MAKE) -C vidtranscode $@
	$(MAKE) -C vidanalytics $@
	$(MAKE) -C universal_copy $@
#	$(MAKE) -C edmacodec1_copy $@

#
#  @(#) ti.sdo.ce.examples.apps; 1, 0, 0,1; 2-24-2012 19:27:22; /db/atree/library/trees/ce/ce-t06/src/ xlibrary

#


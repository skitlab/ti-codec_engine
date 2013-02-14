#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/examples/ti/sdo/ce/examples/codecs/audenc_copy/../../../../../..;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdais_7_22_00_03/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/bios_6_33_05_46/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/linuxutils_3_22_00_02/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/syslink_2_20_00_14/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/osal_1_22_01_09/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/framework_components_3_22_01_07/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/edma3lld_02_11_05_02/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/ipc_1_24_03_32/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/packages
override XDCROOT = /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53
override XDCBUILDCFG = /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/codec_engine.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = DEVICE="TI814X" PROGRAMS="APP_CLIENT DSP_SERVER APP_LOCAL" GPPOS="LINUX_GCC" ti.targets.C64P="" ti.targets.C674="" ti.targets.arm.elf.M3="" ti.targets.elf.C64P="" ti.targets.elf.C64T="" ti.targets.elf.C66="" ti.targets.elf.C674="" gnu.targets.arm.GCArmv5T="/codesourcery/arm-2009q1/;LONGNAME=bin/arm-none-linux-gnueabi-gcc;profiles.release.compileOpts.copts=-O2 -ffunction-sections" google.targets.arm.Bionic=";LONGNAME=;libcDir=;fsDir="
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/examples/ti/sdo/ce/examples/codecs/audenc_copy/../../../../../..;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdais_7_22_00_03/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/bios_6_33_05_46/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/linuxutils_3_22_00_02/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/syslink_2_20_00_14/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/osal_1_22_01_09/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/framework_components_3_22_01_07/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/edma3lld_02_11_05_02/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/ipc_1_24_03_32/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/codec_engine_3_22_01_06/packages;/swcoe/sdk/cm/netra/ti-ezsdk_dm816x-evm_5_05_01_04/component-sources/xdctools_3_23_03_53/packages;../../../../../..
HOSTOS = Linux
endif

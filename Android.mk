LOCAL_PATH:= $(call my-dir)
include $(LOCAL_PATH)/../config/mm_config.mk

# Library suffix name
SUFFIX := bnc

###############################################################################
# CE.A
###############################################################################
include $(CLEAR_VARS)

LOCAL_MODULE                := timm_ce
LOCAL_MODULE_SUFFIX         := .a
LOCAL_MODULE_CLASS          := STATIC_LIBRARIES
LOCAL_MODULE_TAGS           := optional

LOCAL_SRC_FILES := android_binaries/$(LOCAL_MODULE)$(LOCAL_MODULE_SUFFIX)

# Specify variables to be exported to the sub-build
define $(LOCAL_MODULE)_set_config_vars
    $(call timm_set_config_var1,XDCPATH) \
    $(call timm_set_config_var2,XDCBUILDCFG,CONFIG_BLD) \
    $(call timm_set_config_var1,XDCOPTIONS) \
    $(call timm_set_config_var1,TOOLCHAIN_DIR) \
    $(call timm_set_config_var1,TOOLCHAIN_CC) \
    $(call timm_set_config_var2,ANDROID_CFLAGS,CFLAGS) \
    $(call timm_set_config_var2,CROSS_COMPILE,TOOLCHAIN_DIR) \
    $(call timm_set_config_var2,ANDROID_LDFLAGS,LDFLAGS)
endef


# Build against the Android stack
define $(LOCAL_MODULE)_rebuild
$(LOCAL_PATH)/$(LOCAL_SRC_FILES) :
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/packages/
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc -PR $(LOCAL_PATH)/packages/
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/examples/ti/xdais/dm/examples
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/codecs
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/extensions
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc -PR $(LOCAL_PATH)/examples/ti/xdais/dm/examples
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/codecs
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/extensions
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/servers
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc clean -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/apps
	$(call $(LOCAL_MODULE)_set_config_vars) \
	XDCBUILDCFG=$(LOCAL_PATH)/examples/ti/sdo/ce/examples/servers/all_codecs/android_config.bld \
	$(timm_XDC_INSTALL_DIR)/xdc -PR \
	$(LOCAL_PATH)/examples/ti/sdo/ce/examples/servers
	$(call $(LOCAL_MODULE)_set_config_vars) \
	$(timm_XDC_INSTALL_DIR)/xdc -PR $(LOCAL_PATH)/examples/ti/sdo/ce/examples/apps
	mkdir -p $$(dir $$@)
	cp -fp $(LOCAL_PATH)/packages/ti/sdo/ce/lib/release/ce.a$(SUFFIX) $$@
endef
$(eval $(call $(LOCAL_MODULE)_rebuild))

include $(BUILD_PREBUILT)

# Cleanup
$(LOCAL_MODULE)_set_config_vars  :=
$(LOCAL_MODULE)_rebuild          :=

###############################################################################
# UNIVERSAL.A
###############################################################################
include $(CLEAR_VARS)

LOCAL_MODULE                := timm_universal
LOCAL_MODULE_SUFFIX         := .a
LOCAL_MODULE_CLASS          := STATIC_LIBRARIES
LOCAL_MODULE_TAGS           := optional

LOCAL_SRC_FILES := android_binaries/$(LOCAL_MODULE)$(LOCAL_MODULE_SUFFIX)

define $(LOCAL_MODULE)_rebuild
$(LOCAL_PATH)/$(LOCAL_SRC_FILES) : $(LOCAL_PATH)/android_binaries/timm_ce.a
	cp -fp $(LOCAL_PATH)/packages/ti/sdo/ce/universal/lib/release/universal.a$(SUFFIX) $$@
endef
$(eval $(call $(LOCAL_MODULE)_rebuild))

include $(BUILD_PREBUILT)

include $(LOCAL_PATH)/../config/mm_config_cleanup.mk


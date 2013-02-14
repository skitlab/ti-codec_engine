#
#  ======== makefile ========
#

PROFILE = release

ce: $(LIBDIR)/ti/sdo/ce/lib/$(PROFILE)/ce.av5T
ce: $(LIBDIR)/ti/sdo/ce/node/lib/$(PROFILE)/node.av5T
ce: $(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)/alg.av5T
ce: $(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)/Algorithm_noOS.av5T
ce: $(LIBDIR)/ti/sdo/ce/audio/lib/$(PROFILE)/audio.av5T
ce: $(LIBDIR)/ti/sdo/ce/audio1/lib/$(PROFILE)/auddec1.av5T
ce: $(LIBDIR)/ti/sdo/ce/audio1/lib/$(PROFILE)/audenc1.av5T
ce: $(LIBDIR)/ti/sdo/ce/global/lib/$(PROFILE)/cesettings.av5T
ce: $(LIBDIR)/ti/sdo/ce/image/lib/$(PROFILE)/image.av5T
ce: $(LIBDIR)/ti/sdo/ce/image1/lib/$(PROFILE)/imgdec1.av5T
ce: $(LIBDIR)/ti/sdo/ce/image1/lib/$(PROFILE)/imgenc1.av5T
ce: $(LIBDIR)/ti/sdo/ce/ipc/dsplink/lib/$(PROFILE)/ipc_syslink.av5T
ce: $(LIBDIR)/ti/sdo/ce/ipc/linux/lib/$(PROFILE)/ipc_linux.av5T
ce: $(LIBDIR)/ti/sdo/ce/osal/lib/$(PROFILE)/osal.av5T
ce: $(LIBDIR)/ti/sdo/ce/osal/linux/lib/$(PROFILE)/osal_linux_470.av5T
ce: $(LIBDIR)/ti/sdo/ce/speech/lib/$(PROFILE)/speech.av5T
ce: $(LIBDIR)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphdec1.av5T
ce: $(LIBDIR)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphenc1.av5T
ce: $(LIBDIR)/ti/sdo/ce/universal/lib/$(PROFILE)/universal.av5T
ce: $(LIBDIR)/ti/sdo/ce/xdm/lib/$(PROFILE)/XdmUtils.av5T
ce: $(LIBDIR)/ti/sdo/ce/vidanalytics/lib/$(PROFILE)/vidanalytics.av5T
ce: $(LIBDIR)/ti/sdo/ce/video/lib/$(PROFILE)/video.av5T
ce: $(LIBDIR)/ti/sdo/ce/video1/lib/$(PROFILE)/viddec1.av5T
ce: $(LIBDIR)/ti/sdo/ce/video1/lib/$(PROFILE)/videnc1.av5T
ce: $(LIBDIR)/ti/sdo/ce/video2/lib/$(PROFILE)/viddec2.av5T
ce: $(LIBDIR)/ti/sdo/ce/video2/lib/$(PROFILE)/videnc2.av5T
ce: $(LIBDIR)/ti/sdo/ce/video3/lib/$(PROFILE)/viddec3.av5T
ce: $(LIBDIR)/ti/sdo/ce/vidtranscode/lib/$(PROFILE)/vidtranscode.av5T
ce: $(LIBDIR)/ti/sdo/ce/video2/split/lib/$(PROFILE)/viddec2front.av5T
ce: $(LIBDIR)/ti/sdo/ce/video2/split/lib/$(PROFILE)/viddec2back.av5T

PKGPATH = $(IPC_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(OSAL_INSTALL_DIR)/sources;$(OSAL_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR)/packages;$(XDAIS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages
#
#  ======== makefile.GCArmv5T ========
#
$(LIBDIR)/ti/sdo/ce/lib/$(PROFILE)/ce.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)/alg.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/alg -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)/Algorithm_noOS.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/alg -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/alg/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/audio/lib/$(PROFILE)/audio.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/audio -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/audio/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/audio1/lib/$(PROFILE)/auddec1.av5T $(LIBDIR)/ti/sdo/ce/audio1/lib/$(PROFILE)/audenc1.av5T :
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/audio1 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/audio1/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/global/lib/$(PROFILE)/cesettings.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/global -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/global/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/image/lib/$(PROFILE)/image.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/image -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/image/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/image1/lib/$(PROFILE)/imgdec1.av5T $(LIBDIR)/ti/sdo/ce/image1/lib/$(PROFILE)/imgenc1.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/image1 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/image1/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/ipc/dsplink/lib/$(PROFILE)/ipc_syslink.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/ipc/dsplink -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/ipc/dsplink/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/ipc/linux/lib/$(PROFILE)/ipc_linux.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/ipc/linux -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/ipc/linux/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/node/lib/$(PROFILE)/node.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/node -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/node/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/osal/lib/$(PROFILE)/osal.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/osal -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/osal/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/osal/linux/lib/$(PROFILE)/osal_linux_470.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/osal/linux -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/osal/linux/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/speech/lib/$(PROFILE)/speech.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/speech -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/speech/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphdec1.av5T $(LIBDIR)/ti/sdo/ce/speech1/lib/$(PROFILE)/sphenc1.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/speech1 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/speech1/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/universal/lib/$(PROFILE)/universal.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/universal -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/universal/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/xdm/lib/$(PROFILE)/XdmUtils.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/utils/xdm -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/xdm/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/vidanalytics/lib/$(PROFILE)/vidanalytics.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/vidanalytics -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/vidanalytics/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/video/lib/$(PROFILE)/video.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/video -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/video/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/video1/lib/$(PROFILE)/viddec1.av5T $(LIBDIR)/ti/sdo/ce/video1/lib/$(PROFILE)/videnc1.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/video1 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/video1/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/video2/lib/$(PROFILE)/viddec2.av5T $(LIBDIR)/ti/sdo/ce/video2/lib/$(PROFILE)/videnc2.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/video2 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/video2/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/video2/split/lib/$(PROFILE)/viddec2front.av5T $(LIBDIR)/ti/sdo/ce/video2/split/lib/$(PROFILE)/viddec2back.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/video2/split -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/video2/split/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/video3/lib/$(PROFILE)/viddec3.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/video3 -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/video3/lib/$(PROFILE)
            $@

$(LIBDIR)/ti/sdo/ce/vidtranscode/lib/$(PROFILE)/vidtranscode.av5T:
	@echo "#"
	@echo "# Making $@..."
	$(MAKE) -C ti/sdo/ce/vidtranscode -f simple_GCArmv5T.mak \
            PKG_PATH="$(PKGPATH)" \
            CGTOOLS_V5T=$(CGTOOLS_V5T) \
            CC_V5T=$(CC_V5T) \
            AR_V5T=$(AR_V5T) \
	    LIBDIR=$(LIBDIR)/ti/sdo/ce/vidtranscode/lib/$(PROFILE)
            $@

#
#  ======== clean ========
#
clean::
	@echo "#"
	@echo "# Cleaning packages..."
	$(MAKE) -C ti/sdo/ce -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/alg -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/audio -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/audio1 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/global -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/image1 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/ipc/dsplink -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/ipc/linux -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/node -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/osal -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/osal/linux -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/speech -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/speech1 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/universal -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/utils/xdm -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/vidanalytics -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/video -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/video1 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/video2 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/video2/split -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/video3 -f simple_GCArmv5T.mak clean
	$(MAKE) -C ti/sdo/ce/vidtranscode -f simple_GCArmv5T.mak clean

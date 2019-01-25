define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -type f) \
 )
endef
# $(1): module name
# $(2): source file
# $(3): destination directory
define include-prebuilt-with-destination-directory
include $$(CLEAR_VARS)
LOCAL_MODULE := $(1)
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/redbend.mk
LOCAL_MODULE_STEM := $(notdir $(2))
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(3)
LOCAL_SRC_FILES := $(2)
include $$(BUILD_PREBUILT)
endef
redbends := $(call all-files-under, cfg_files)

redbends_target_directory := $(TARGET_OUT)/etc
$(foreach omadm, $(redbends), $(eval $(call include-prebuilt-with-destination-directory,target-redbends-$(notdir $(omadm)),$(omadm),$(redbends_target_directory))))
redbends_target := $(addprefix $(redbends_target_directory)/,$(foreach omadm,$(redbends),$(notdir $(omadm))))
.PHONY: redbends_target
cacerts: $(redbends_target)

# This is so that build/target/product/core.mk can use redbend in PRODUCT_PACKAGES
ALL_MODULES.cacerts.INSTALLED := $(redbends_target)

redbends_host_directory := $(HOST_OUT)/etc
$(foreach omadm, $(redbends), $(eval $(call include-prebuilt-with-destination-directory,host-redbends-$(notdir $(omadm)),$(omadm),$(redbends_host_directory))))

redbends_host := $(addprefix $(redbends_host_directory)/,$(foreach omadm,$(redbends),$(notdir $(omadm))))
.PHONY: redbends-host
redbends-host: $(redbends_host)



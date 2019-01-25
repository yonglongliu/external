LOCAL_PATH:= $(call my-dir)
#Enable Samsung NFC
BOARD_USES_SAMSUNG_NFC := 1
ifeq ($(BOARD_USES_SAMSUNG_NFC), 1)
    LOCAL_PATH:= $(call my-dir)
    include $(LOCAL_PATH)/Android-sec.mk
endif
ifeq (0,1)
include $(CLEAR_VARS)
NFA := src/nfa
NFC := src/nfc
HAL := src/hal
UDRV := src/udrv

D_CFLAGS := -DANDROID -DBUILDCFG=1 \
    -Wno-deprecated-register \
    -Wno-unused-parameter \

######################################
# Build shared library system/lib/libnfc-nci.so for stack code.

LOCAL_ARM_MODE := arm
ifeq (true,$(TARGET_IS_64_BIT))
LOCAL_MULTILIB := 64
else
LOCAL_MULTILIB := 32
endif
LOCAL_MODULE := libnfc-nci
LOCAL_SHARED_LIBRARIES := libhardware_legacy libcutils liblog libdl libhardware
LOCAL_CFLAGS += $(D_CFLAGS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/include \
    $(LOCAL_PATH)/src/gki/ulinux \
    $(LOCAL_PATH)/src/gki/common \
    $(LOCAL_PATH)/$(NFA)/include \
    $(LOCAL_PATH)/$(NFA)/int \
    $(LOCAL_PATH)/$(NFC)/include \
    $(LOCAL_PATH)/$(NFC)/int \
    $(LOCAL_PATH)/src/hal/include \
    $(LOCAL_PATH)/src/hal/int \
    $(LOCAL_PATH)/$(HALIMPL)/include
LOCAL_SRC_FILES := \
    $(call all-c-files-under, $(NFA)/ce $(NFA)/dm $(NFA)/ee) \
    $(call all-c-files-under, $(NFA)/hci $(NFA)/int $(NFA)/p2p $(NFA)/rw $(NFA)/sys) \
    $(call all-c-files-under, $(NFC)/int $(NFC)/llcp $(NFC)/nci $(NFC)/ndef $(NFC)/nfc $(NFC)/tags) \
    $(call all-c-files-under, src/adaptation) \
    $(call all-cpp-files-under, src/adaptation) \
    $(call all-c-files-under, src/gki) \
    src/nfca_version.c
include $(BUILD_SHARED_LIBRARY)


######################################
include $(call all-makefiles-under,$(LOCAL_PATH))
endif
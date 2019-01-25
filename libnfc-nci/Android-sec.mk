######################################
# function to find all *.cpp files under a directory
$(warning *** [S.LSI] libnfc-nci ***)

LOCAL_PATH:= $(call my-dir)
NFA := src/nfa
NFC := src/nfc
HAL := src/hal
UDRV := src/udrv
HALIMPL := halimpl/samsung
D_CFLAGS := -DANDROID -DBUILDCFG=1 \
    -Wno-deprecated-register \
    -Wno-unused-parameter 

D_CFLAGS += -DNFC_SEC_NOT_OPEN_INCLUDED=TRUE
D_CFLAGS += -DNFA_EE_MAX_AID_CFG_LEN=230
D_CFLAGS += -DSEC_HCI_CONNECTIVITY_WR

######################################
# Build shared library system/lib/libnfc-nci.so for stack code.

include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_MODULE := libnfc-nci
LOCAL_SHARED_LIBRARIES := libhardware_legacy libcutils liblog libdl libhardware
LOCAL_CFLAGS := $(D_CFLAGS)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/src/include \
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
# Build shared library system/lib/hw/nfc_nci.*.so for Hardware Abstraction Layer.
# Android's generic HAL (libhardware.so) dynamically loads this shared library.

include $(CLEAR_VARS)
LOCAL_MODULE := nfc_nci.sec
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_SRC_FILES := \
    $(call all-c-files-under, $(HALIMPL)) \
    $(call all-cpp-files-under, $(HALIMPL))

LOCAL_SHARED_LIBRARIES := liblog libcutils libhardware_legacy libcrypto libssl

#LOCAL_C_INCLUDES := external/stlport/stlport bionic/ bionic/libstdc++/include \
    external/openssl/include \

LOCAL_C_INCLUDES := external/openssl/include \
    $(LOCAL_PATH)/$(HALIMPL)/osi \
    $(LOCAL_PATH)/$(HALIMPL)/include \
    hardware/libhardware/include/hardware

LOCAL_CFLAGS := -DANDROID \
    -DBUILDCFG=1 -DNFC_SEC_NOT_OPEN_INCLUDED=TRUE -DNFC_HAL_TARGET=TRUE -DNFC_RW_ONLY=TRUE -DNFC_HAL_USE_FIRMPIN -DNFC_HAL_DO_NOT_UPDATE_BL5000

include $(BUILD_SHARED_LIBRARY)

######################################
include $(call all-makefiles-under,$(LOCAL_PATH))

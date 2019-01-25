LOCAL_PATH:= $(call my-dir)

COMMON := src/common
LOG := src/log
MIFARE := src/mifare
UTILS := src/utils

#NXP PN547 Enable
D_CFLAGS += -DNFCC_PN547

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_ARM_MODE := arm
LOCAL_MODULE := libnfc-mifare
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := $(D_CFLAGS)

LOCAL_SHARED_LIBRARIES := libcutils libnfc-nci

LOCAL_C_INCLUDES := external/libnfc-mifare/inc \
    $(LOCAL_PATH)/$(COMMON) \
    $(LOCAL_PATH)/$(LOG) \
    $(LOCAL_PATH)/$(MIFARE) \
    $(LOCAL_PATH)/$(UTILS) \
    external/stlport/stlport \
    bionic

LOCAL_SRC_FILES := \
    $(call all-c-files-under, $(LOG)) \
    $(call all-c-files-under, $(MIFARE)) \
    $(call all-cpp-files-under, $(UTILS)) \
m   src/phNxpExtns.c

######################################
# depend on libnfc-nci library.

VOB_COMPONENTS := external/libnfc-nci/src
NFA := $(VOB_COMPONENTS)/nfa
NFC := $(VOB_COMPONENTS)/nfc

LOCAL_C_INCLUDES += \
    $(NFA)/include \
    $(NFA)/brcm \
    $(NFC)/include \
    $(NFC)/brcm \
    $(NFC)/int \
    $(VOB_COMPONENTS)/hal/include \
    $(VOB_COMPONENTS)/hal/int \
    $(VOB_COMPONENTS)/include \
    $(VOB_COMPONENTS)/gki/ulinux \
    $(VOB_COMPONENTS)/gki/common

include $(BUILD_SHARED_LIBRARY)

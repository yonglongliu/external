LOCAL_PATH:= $(call my-dir)
ifeq ($(BOARD_ENABLE_OMADM_REDBEND),true)
	include $(call all-subdir-makefiles)
endif


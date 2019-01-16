LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libnx_deinterlacer

ifeq ($(BUILD_ID), PI)
LOCAL_VENDOR_MODULE := true
endif

LOCAL_SRC_FILES := \
	nx-deinterlacer.c
LOCAL_SHARED_LIBRARIES := \
	liblog \
	libcutils \
	libhardware
LOCAL_C_INCLUDES += \
	system/core/include/utils \
	frameworks/native/include \
	$(call include-path-for)

include $(BUILD_SHARED_LIBRARY)

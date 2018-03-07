
ifdef CONFIG_SPIRAM_CACHE_WORKAROUND
LIBC_PATH := $(COMPONENT_PATH)/lib/libc-psram-workaround.a
LIBM_PATH := $(COMPONENT_PATH)/lib/libm-psram-workaround.a

else

ifdef CONFIG_NEWLIB_NANO_FORMAT
ifdef CONFIG_CHIP_IS_ESP32
LIBC_PATH := $(COMPONENT_PATH)/lib/libc_nano.a
else # esp32c do not have a nano lib by now
LIBC_PATH := $(COMPONENT_PATH)/lib/libc_esp32c.a
endif
else
ifdef CONFIG_CHIP_IS_ESP32
LIBC_PATH := $(COMPONENT_PATH)/lib/libc.a
else
LIBC_PATH := $(COMPONENT_PATH)/lib/libc_esp32c.a
endif
endif  # CONFIG_NEWLIB_NANO_FORMAT

LIBM_PATH := $(COMPONENT_PATH)/lib/libm.a

endif  # CONFIG_SPIRAM_CACHE_WORKAROUND

COMPONENT_ADD_LDFLAGS := $(LIBC_PATH) $(LIBM_PATH) -lnewlib

COMPONENT_ADD_LINKER_DEPS := $(LIBC_PATH) $(LIBM_PATH)

COMPONENT_ADD_INCLUDEDIRS := platform_include include

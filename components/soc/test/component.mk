# currently the only SoC supported; to be moved into Kconfig
ifdef CONFIG_CHIP_IS_ESP32
SOC_NAME := esp32
endif

ifdef CONFIG_CHIP_IS_ESP32C
SOC_NAME := esp32c
endif


COMPONENT_SRCDIRS := ../$(SOC_NAME)/test

COMPONENT_ADD_LDFLAGS = -Wl,--whole-archive -l$(COMPONENT_NAME) -Wl,--no-whole-archive



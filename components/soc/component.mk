# currently the only SoC supported; to be moved into Kconfig
ifdef CONFIG_CHIP_IS_ESP32
SOC_NAME := esp32
endif

ifdef CONFIG_CHIP_IS_ESP32C
SOC_NAME := esp32c
endif

COMPONENT_SRCDIRS := $(SOC_NAME)
COMPONENT_ADD_INCLUDEDIRS := $(SOC_NAME)/include include

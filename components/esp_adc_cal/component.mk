#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS := include

ifndef CONFIG_CHIP_IS_ESP32
COMPONENT_OBJEXCLUDE = esp_adc_cal_esp32.o
endif

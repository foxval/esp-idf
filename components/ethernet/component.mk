#
# Component Makefile
#

ifdef CONFIG_CHIP_IS_ESP32
COMPONENT_SRCDIRS := . eth_phy
else
COMPONENT_CONFIG_ONLY := 1
endif


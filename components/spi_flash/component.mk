COMPONENT_ADD_INCLUDEDIRS := include

COMPONENT_SRCDIRS := . $(SOC_NAME)

COMPONENT_PRIV_INCLUDEDIRS := .

ifdef IS_BOOTLOADER_BUILD
# Bootloader needs updated SPIUnlock from this file
COMPONENT_OBJS := spi_flash_rom_patch.o
endif


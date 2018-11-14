COMPONENT_ADD_INCLUDEDIRS := include
COMPONENT_PRIV_INCLUDEDIRS := include_priv

ifdef IS_BOOTLOADER_BUILD
# share "private" headers with the bootloader component
# eventual goal: all functionality that needs this lives in bootloader_support
COMPONENT_ADD_INCLUDEDIRS += include_priv
endif

COMPONENT_SRCDIRS := src

ifndef IS_BOOTLOADER_BUILD
COMPONENT_SRCDIRS += src/idf  # idf sub-directory contains platform agnostic IDF versions
else
COMPONENT_SRCDIRS += src/$(CHIP_NAME)  # one sub-dir per chip
endif

#
# Secure boot signing key support
#
ifdef CONFIG_SECURE_BOOT_ENABLED

ifdef CONFIG_CHIP_IS_ESP32C
ifdef CONFIG_SECURE_BOOT_BUILD_SIGNED_BINARIES
$(error Build system does not support signing ESP32C binaries. Disable 'Build Signed Binaries' and sign by hand.)
endif
endif # ESP32C

ifdef CONFIG_CHIP_IS_ESP32
# this path is created relative to the component build directory
SECURE_BOOT_VERIFICATION_KEY := $(abspath signature_verification_key.bin)

ifdef CONFIG_SECURE_BOOT_BUILD_SIGNED_BINARIES
# verification key derived from signing key.
$(SECURE_BOOT_VERIFICATION_KEY): $(SECURE_BOOT_SIGNING_KEY) $(SDKCONFIG_MAKEFILE)
	$(ESPSECUREPY) extract_public_key --keyfile $< $@
else
# find the configured public key file
ORIG_SECURE_BOOT_VERIFICATION_KEY := $(call resolvepath,$(call dequote,$(CONFIG_SECURE_BOOT_VERIFICATION_KEY)),$(PROJECT_PATH))

$(ORIG_SECURE_BOOT_VERIFICATION_KEY):
	@echo "Secure boot verification public key '$@' missing."
	@echo "This can be extracted from the private signing key, see"
	@echo "docs/security/secure-boot.rst for details."
	exit 1

# copy it into the build dir, so the secure boot verification key has
# a predictable file name
$(SECURE_BOOT_VERIFICATION_KEY): $(ORIG_SECURE_BOOT_VERIFICATION_KEY) $(SDKCONFIG_MAKEFILE)
	$(summary) CP $< $@
	cp $< $@
endif

COMPONENT_EXTRA_CLEAN += $(SECURE_BOOT_VERIFICATION_KEY)

COMPONENT_EMBED_FILES := $(SECURE_BOOT_VERIFICATION_KEY)

endif # ESP32
endif # SECURE BOOT


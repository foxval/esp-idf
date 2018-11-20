// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "sdkconfig.h"

#include "bootloader_flash.h"
#include "bootloader_sha.h"
#include "esp_log.h"
#include "esp_image_format.h"
#include "esp_secure_boot.h"
#include "rom/secure_boot.h"

static const char* TAG = "secure_boot";

#define DIGEST_LEN 32

// TODO: This function is basically the same as its ESP32 equivalent
esp_err_t esp_secure_boot_verify_signature(uint32_t src_addr, uint32_t length)
{
    uint8_t digest[DIGEST_LEN];
    const uint8_t *data;

    ESP_LOGD(TAG, "verifying signature src_addr 0x%x length 0x%x", src_addr, length);

    data = bootloader_mmap(src_addr, length + sizeof(esp_secure_boot_sig_block_t));
    if(data == NULL) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", src_addr, length+sizeof(esp_secure_boot_sig_block_t));
        return ESP_FAIL;
    }

    // Calculate digest of main image
#ifdef BOOTLOADER_BUILD
    bootloader_sha256_handle_t handle = bootloader_sha256_start();
    bootloader_sha256_data(handle, data, length);
    bootloader_sha256_finish(handle, digest);
#else
    /* Use thread-safe esp-idf SHA function */
    esp_sha(SHA2_256, data, length, digest);
#endif

    // Map the signature block and verify the signature
    bootloader_munmap(data);
    return esp_secure_boot_verify_signature_block(src_addr + length, digest);
}

esp_err_t esp_secure_boot_verify_signature_block(uint32_t sig_block_flash_offs, const uint8_t *image_digest)
{
    ets_secure_boot_key_digests_t trusted_keys;

    assert(sig_block_flash_offs % 4096 == 0); // TODO: enforce this in a better way

    const ets_secure_boot_signature_t *sig = bootloader_mmap(sig_block_flash_offs, sizeof(ets_secure_boot_signature_t));

    if (sig == NULL) {
        ESP_LOGE(TAG, "Failed to mmap data at offset 0x%x", sig_block_flash_offs);
        return ESP_FAIL;
    }

    int r = ets_secure_boot_read_key_digests(&trusted_keys);
    if (r != 0) {
        ESP_LOGE(TAG, "No trusted key digests were found in efuse!");
    } else {
        ESP_LOGD(TAG, "Verifying with RSA-PSS...");
        r = ets_secure_boot_verify_signature(sig, image_digest, &trusted_keys);
    }

    bootloader_munmap(sig);

    return (r == 0) ? ESP_OK : ESP_ERR_IMAGE_INVALID;
}

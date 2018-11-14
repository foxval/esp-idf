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

// TODO: This is just for testing, needs replacing with a proper
// workflow for secure boot key digest loading
void temp_load_keys_efuse()
{
    // digest of secure_boot_signing_key0.pem
    const unsigned char digest0_bin[] = {
        0x91, 0x90, 0xb7, 0xf9, 0x47, 0x3c, 0x11, 0x80, 0x76, 0x89, 0x69, 0x92,
        0x2f, 0xcf, 0xba, 0xc0, 0x38, 0x92, 0xe2, 0x77, 0x86, 0x52, 0x65, 0xd6,
        0xad, 0x96, 0xba, 0xef, 0x28, 0xcc, 0x89, 0xcf
    };

    if(!ets_efuse_find_purpose(ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0, NULL) && ets_efuse_key_block_unused(ETS_EFUSE_BLOCK_KEY0)) {
        ESP_LOGI(TAG, "Writing digest of secure_boot_signing_key0.pem to key slot 0...");
        ets_efuse_write_key(ETS_EFUSE_BLOCK_KEY0,
                            ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0,
                            digest0_bin,
                            sizeof(digest0_bin));
    } else {
        ESP_LOGI(TAG, "Efuse already written");
    }
}


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
    temp_load_keys_efuse();

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

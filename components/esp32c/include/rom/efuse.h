// Copyright 2015-2018 Espressif Systems (Shanghai) PTE LTD
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

#ifndef _ROM_EFUSE_H_
#define _ROM_EFUSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/** \defgroup efuse_APIs efuse APIs
  * @brief     ESP32 efuse read/write APIs
  * @attention
  *
  */

/** @addtogroup efuse_APIs
  * @{
  */

typedef enum {
    ETS_EFUSE_KEY_PURPOSE_USER = 0,
    ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT = 1,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_1 = 2,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_2 = 3,
    ETS_EFUSE_KEY_PURPOSE_XTS_AES_128_KEY = 4,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL = 5,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG = 6,
    ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_DIGITAL_SIGNATURE = 7,
    ETS_EFUSE_KEY_PURPOSE_HMAC_UP = 8,
    ETS_EFUSE_KEY_PURPOSE_MAX,
} ets_efuse_purpose_t;

typedef enum {
    ETS_EFUSE_BLOCK0 = 0,
    ETS_EFUSE_MAC_SPI_8M_0 = 1,
    ETS_EFUSE_BLOCK_SYS_DATA = 2,
    ETS_EFUSE_BLOCK_USR_DATA = 3,
    ETS_EFUSE_BLOCK_KEY0 = 4,
    ETS_EFUSE_BLOCK_KEY1 = 5,
    ETS_EFUSE_BLOCK_KEY2 = 6,
    ETS_EFUSE_BLOCK_KEY3 = 7,
    ETS_EFUSE_BLOCK_KEY4 = 8,
    ETS_EFUSE_BLOCK_KEY5 = 9,
    ETS_EFUSE_BLOCK_KEY6 = 10,
    ETS_EFUSE_BLOCK_MAX,
} ets_efuse_block_t;

/**
 * @brief Enable efuse subsystem. Called after reset. Doesn't need to be called again.
 */
void ets_efuse_start(void);

/**
  * @brief  Efuse read operation: copies data from physical efuses to efuse read registers.
  *
  * @param  null
  *
  * @return null
  */
void ets_efuse_read(void);

/**
  * @brief  Efuse write operation: Copies data from efuse write registers to efuse. Operates on a single block of efuses at a time.
  *
  * @note This function does not update read efuses, call ets_efuse_read() once all programming is complete.
  *
  * @return null
  */
void ets_efuse_program(ets_efuse_block_t block);

/**
 * @brief Set all Efuse program registers to zero.
 *
 * Call this before writing new data to the program registers.
 */
void ets_efuse_clear_program_registers(void);

/**
 * @brief Program a block of key data to an efuse block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6.
 * @param purpose Purpose to set for this key. Purpose must be already unset.
 * @param data Pointer to data to write.
 * @param data_len Length of data to write.
 *
 * @note This function also calls ets_efuse_program() for the specified block, and for block 0 (setting the purpose)
 */
int ets_efuse_write_key(ets_efuse_block_t key_block, ets_efuse_purpose_t purpose, const void *data, size_t data_len);


/**
 * @brief Return the current purpose set for an efuse key block
 *
 * @param key_block Block to read purpose for. Must be in range ETS_EFUSE_BLOCK_KEY0 to ETS_EFUSE_BLOCK_KEY6.
 */
ets_efuse_purpose_t ets_efuse_get_key_purpose(ets_efuse_block_t key_block);

/**
 * @brief Calculate Reed-Solomon Encoding values for a block of efuse data.
 *
 * @param data Pointer to data buffer (length 32 bytes)
 * @param rs_values Pointer to write encoded data to (length 12 bytes)
 */
void ets_efuse_rs_calculate(const void *data, void *rs_values);

/**
  * @brief  Read 8M Analog Clock value(8 bit) in efuse, the analog clock will not change with temperature.
  *         It can be used to test the external xtal frequency, do not touch this efuse field.
  *
  * @param  null
  *
  * @return u32: 1 for 100KHZ, range is 0 to 255.
  */
uint32_t ets_efuse_get_8M_clock(void);

/**
  * @brief  Read spi flash pin configuration from Efuse
  *
  * @return
  * - 0 for default SPI pins.
  * - 1 for default HSPI pins.
  * - Other values define a custom pin configuration mask. Pins are encoded as per the EFUSE_SPICONFIG_RET_SPICLK,
  *   EFUSE_SPICONFIG_RET_SPIQ, EFUSE_SPICONFIG_RET_SPID, EFUSE_SPICONFIG_RET_SPICS0, EFUSE_SPICONFIG_RET_SPIHD macros.
  *   WP pin (for quad I/O modes) is not saved in efuse and not returned by this function.
  */
uint32_t ets_efuse_get_spiconfig(void);

#define EFUSE_SPICONFIG_SPI_DEFAULTS 0
#define EFUSE_SPICONFIG_HSPI_DEFAULTS 1

#define EFUSE_SPICONFIG_RET_SPICLK_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICLK_SHIFT        0
#define EFUSE_SPICONFIG_RET_SPICLK(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICLK_SHIFT) & EFUSE_SPICONFIG_RET_SPICLK_MASK)

#define EFUSE_SPICONFIG_RET_SPIQ_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPIQ_SHIFT          6
#define EFUSE_SPICONFIG_RET_SPIQ(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPIQ_SHIFT) & EFUSE_SPICONFIG_RET_SPIQ_MASK)

#define EFUSE_SPICONFIG_RET_SPID_MASK           0x3f
#define EFUSE_SPICONFIG_RET_SPID_SHIFT          12
#define EFUSE_SPICONFIG_RET_SPID(ret)           (((ret) >> EFUSE_SPICONFIG_RET_SPID_SHIFT) & EFUSE_SPICONFIG_RET_SPID_MASK)

#define EFUSE_SPICONFIG_RET_SPICS0_MASK         0x3f
#define EFUSE_SPICONFIG_RET_SPICS0_SHIFT        18
#define EFUSE_SPICONFIG_RET_SPICS0(ret)         (((ret) >> EFUSE_SPICONFIG_RET_SPICS0_SHIFT) & EFUSE_SPICONFIG_RET_SPICS0_MASK)


#define EFUSE_SPICONFIG_RET_SPIHD_MASK          0x3f
#define EFUSE_SPICONFIG_RET_SPIHD_SHIFT         24
#define EFUSE_SPICONFIG_RET_SPIHD(ret)          (((ret) >> EFUSE_SPICONFIG_RET_SPIHD_SHIFT) & EFUSE_SPICONFIG_RET_SPIHD_MASK)

/**
  * @brief  A crc8 algorithm used for MAC addresses in efuse
  *
  * @param  unsigned char const *p : Pointer to original data.
  *
  * @param  unsigned int len : Data length in byte.
  *
  * @return unsigned char: Crc value.
  */
unsigned char esp_crc8(unsigned char const *p, unsigned int len);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* _ROM_EFUSE_H_ */

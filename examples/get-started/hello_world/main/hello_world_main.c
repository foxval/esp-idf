/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "soc/efuse_reg.h"
#include "rom/efuse.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/boot_mode.h"
#include <string.h>


void write_xtal_freq_40M()
{
	REG_SET_BIT(EFUSE_PGM_DATA3_REG, (0x28 << EFUSE_XTAL_FREQ_S)); //[27,29] is useful best 28
	ets_efuse_program(0);
}

void write_clock_freq_8M()
{
	uint8_t block_data[32] = { 0 };
	block_data[11] = 0x32;  //[0x320, 0x360] is usful best 0x320
	block_data[10] = 0x00;
	uint8_t block_rs[12];
	ets_efuse_rs_calculate(block_data, block_rs);
	for(int i = 24; i < 32; i++) {
		block_data[i] ^= block_rs[i - 24];
		block_rs[i - 24] ^= block_data[i];
		block_data[i] ^= block_rs[i - 24];
	}
	memcpy((void *)EFUSE_PGM_DATA0_REG, block_data, sizeof(block_data));
	memcpy((void *)EFUSE_PGM_CHECK_VALUE0_REG, block_rs, sizeof(block_rs));

	ets_efuse_program(1);
}

void write_clock_store_5()
{
	uint32_t high = REG_READ(RTC_CNTL_STORE5_REG) >> 16;
    uint32_t low = REG_READ(RTC_CNTL_STORE5_REG) & 0xffff;
    printf("high:               %x, low:        %x\n", high, low);
    printf("rtc freq:           %d\n", high << 12);

	uint32_t clock = 41000000;
	clock = clock >> 12;
	REG_SET_BIT(RTC_CNTL_STORE5_REG, clock);
	REG_SET_BIT(RTC_CNTL_STORE5_REG, (clock << 16));
}

void write_print_channel_1()
{
	REG_SET_BIT(EFUSE_PGM_DATA4_REG, EFUSE_UART_PRINT_CHANNEL);
	ets_efuse_program(0);
}

void write_print_control(uint8_t model)
{
	REG_SET_BIT(EFUSE_PGM_DATA4_REG, (model << EFUSE_UART_PRINT_CONTROL_S));
	ets_efuse_program(0);
}

void download_dis()
{
	REG_SET_BIT(EFUSE_PGM_DATA4_REG, EFUSE_DIS_DOWNLOAD_MODE);
	ets_efuse_program(0);
}

void secure_download_en()
{
	REG_SET_BIT(EFUSE_PGM_DATA4_REG, EFUSE_ENABLE_SECURITY_DOWNLOAD);
	ets_efuse_program(0);
}

void usb_dis()
{
	REG_SET_BIT(EFUSE_PGM_DATA1_REG, EFUSE_DIS_USB);
	ets_efuse_program(0);
}

void usb_download_dis()
{
	REG_SET_BIT(EFUSE_PGM_DATA4_REG, EFUSE_DIS_USB_DOWNLOAD_MODE);
	ets_efuse_program(0);
}

void delay_flash()
{
	REG_SET_BIT(EFUSE_PGM_DATA3_REG,  (0xf << EFUSE_FLASH_TPUW_S));
	ets_efuse_program(0);
}

void secure_boot_en()
{
	REG_SET_BIT(EFUSE_PGM_DATA3_REG, EFUSE_SECURE_BOOT_EN);
	ets_efuse_program(0);
}

void usb_ext_phy()
{
        REG_SET_BIT(EFUSE_PGM_DATA1_REG, BIT(25));
        ets_efuse_program(0);
}

void secure_boot_key0_write()
{
	unsigned char rsakey_digest_bin[] = {
  		0x82, 0xfc, 0xf7, 0xff, 0x72, 0x14, 0xc4, 0x34, 0x22, 0x32, 0x64, 0xe8,
  		0x13, 0x6c, 0xcc, 0x12, 0xe8, 0xa2, 0xd4, 0xf9, 0xba, 0x17, 0xd0, 0x85,
  		0xcb, 0x88, 0x3d, 0x39, 0xcd, 0xdd, 0xee, 0x14
	};
	unsigned int rsakey_digest_bin_len = 32;

	ets_efuse_write_key(4, 9, rsakey_digest_bin, rsakey_digest_bin_len);
}

void secure_boot_key1_write()
{
	unsigned char rsakey_digest_bin[] = {
  		0x0a, 0x8a, 0xca, 0xf7, 0xb7, 0x79, 0xf8, 0x67, 0xe4, 0xe1, 0x46, 0x9a,
  		0x58, 0xb4, 0x97, 0xe0, 0x23, 0x73, 0x5a, 0xcc, 0x15, 0xcd, 0xb7, 0xbd,
  		0x5e, 0xad, 0xe1, 0xe1, 0x4d, 0xbf, 0xca, 0x1b
	};
	unsigned int rsakey_digest_bin_len = 32;

	ets_efuse_write_key(5, 10, rsakey_digest_bin, rsakey_digest_bin_len);
}

void secure_boot_key2_write()
{
	unsigned char rsakey_digest_bin[] = {
  		0x97, 0x8b, 0x95, 0xa4, 0xd8, 0x72, 0x3b, 0xd2, 0x00, 0xbc, 0x13, 0x0d,
  		0x19, 0x36, 0x48, 0x89, 0x66, 0x7a, 0x37, 0x95, 0x33, 0xa4, 0x06, 0xef,
  		0xb4, 0xaa, 0x42, 0xfa, 0x3e, 0x18, 0x8e, 0x36
	};
	unsigned int rsakey_digest_bin_len = 32;

	ets_efuse_write_key(6, 11, rsakey_digest_bin, rsakey_digest_bin_len);
}

void msg_print()
{
	printf("spi freq:			%x\n", REG_GET_FIELD(EFUSE_RD_MAC_SPI_8M_2_REG, EFUSE_CLK8M_FREQ));
	printf("xtal freq 			%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA2_REG, EFUSE_XTAL_FREQ));
	printf("print chanel:		%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA3_REG, EFUSE_UART_PRINT_CHANNEL));
	printf("print control:		%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA3_REG, EFUSE_UART_PRINT_CONTROL));
	printf("store4:				%x\n", REG_READ(RTC_CNTL_STORE4_REG) & 0x1);
	printf("download dis:		%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA3_REG, EFUSE_DIS_DOWNLOAD_MODE));
	printf("secure download en:	%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA3_REG, EFUSE_ENABLE_SECURITY_DOWNLOAD));
	printf("usb dis:			%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA0_REG, EFUSE_DIS_USB));
	printf("usb download dis:	%x\n", REG_GET_FIELD(EFUSE_RD_REPEAT_DATA3_REG, EFUSE_DIS_USB_DOWNLOAD_MODE));
	uint32_t high = REG_READ(RTC_CNTL_STORE5_REG) >> 16;
	uint32_t low = REG_READ(RTC_CNTL_STORE5_REG) & 0xffff;
	printf("high:				%x, low:		%x\n", high, low);
	printf("rtc freq:			%d\n", high << 12);
	printf("spi boot model 		%x\n", ETS_IS_FLASH_BOOT());
	printf("delay flash:		%d\n", ets_efuse_get_flash_delay_us());
}

void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    //secure_download_en();
    //usb_download_dis();
    usb_dis();
    usb_ext_phy();
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}

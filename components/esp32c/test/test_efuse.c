/* Note: These tests run on FPGA only, not on real silicon */
#include <sdkconfig.h>
#ifdef CONFIG_HARDWARE_IS_FPGA
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <rom/efuse.h>
#include <soc/efuse_reg.h>
#include "unity.h"

static void dump_efuse_block(int n, uint32_t addr, const char *label)
{
    uint32_t block[8];
    printf("Block %d (%s)\n", n, label);
    memcpy(block, (void *)addr, 32);
    for (int i = 0; i < 8; i++) {
        printf("%08x%c", block[i], (i == 3 || i == 7) ? '\n' : ' ');
    }
}

static void dump_efuse_blocks()
{
    dump_efuse_block(0,  EFUSE_RD_REPEAT_DATA0_REG, "EFUSE_RD_REPEAT_DATAx_REG");
    dump_efuse_block(1,  EFUSE_RD_MAC_SPI_8M_0_REG, "EFUSE_RD_RD_MAC_SPI_8M_x_REG");
    dump_efuse_block(2,  EFUSE_RD_SYS_DATA0_REG, "EFUSE_RD_SYS_DATAx_REG");
    dump_efuse_block(3,  EFUSE_RD_USR_DATA0_REG, "EFUSE_RD_USR_DATAx_REG");

    dump_efuse_block(4,  EFUSE_RD_KEY0_DATA0_REG, "EFUSE_RD_KEY0_DATAx_REG");
    dump_efuse_block(5,  EFUSE_RD_KEY1_DATA0_REG, "EFUSE_RD_KEY1_DATAx_REG");
    dump_efuse_block(6,  EFUSE_RD_KEY2_DATA0_REG, "EFUSE_RD_KEY2_DATAx_REG");
    dump_efuse_block(7,  EFUSE_RD_KEY3_DATA0_REG, "EFUSE_RD_KEY3_DATAx_REG");
    dump_efuse_block(8,  EFUSE_RD_KEY4_DATA0_REG, "EFUSE_RD_KEY4_DATAx_REG");
    dump_efuse_block(9,  EFUSE_RD_KEY5_DATA0_REG, "EFUSE_RD_KEY5_DATAx_REG");
    dump_efuse_block(10, EFUSE_RD_KEY6_DATA0_REG, "EFUSE_RD_KEY6_DATAx_REG");
}

TEST_CASE("efuse write key block", "[esp32c]")
{
    const ets_efuse_block_t BLOCK = ETS_EFUSE_BLOCK_KEY0;
    const uint32_t BLOCK_READ0_REG = EFUSE_RD_KEY0_DATA0_REG;

    printf("Before:\n");
    dump_efuse_blocks();

    /* Check if the block is already in use */
    TEST_ASSERT_EQUAL(ETS_EFUSE_KEY_PURPOSE_USER,
                      ets_efuse_get_key_purpose(BLOCK));
    for (int i = 0; i < (32 / 4); i += 4) {
        TEST_ASSERT_EQUAL_HEX32(0, REG_READ(BLOCK_READ0_REG));
    }
    // TODO: also check not read/write protected

    const uint8_t key_data[32] = {
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
        25,26,27,28,29,30,31,32
    };
    const uint32_t *key_words = (const uint32_t *)key_data;

    printf("Calling ets_efuse_write_key...\n");
    int r = ets_efuse_write_key(BLOCK, ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT, key_data, sizeof(key_data));
    TEST_ASSERT_EQUAL(0, r);

    printf("After:\n");
    dump_efuse_blocks();

    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_HEX32(key_words[i], REG_READ(BLOCK_READ0_REG + (4*i)));
    }
    // TODO: check no error bits are set
}



#endif /* CONFIG_HARDWARE_IS_FPGA */

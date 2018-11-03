/* Note: These tests run on FPGA only, not on real silicon */
#include <sdkconfig.h>
#ifdef CONFIG_HARDWARE_IS_FPGA
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <rom/efuse.h>
#include <rom/hmac.h>
#include <soc/efuse_reg.h>
#include <esp_log.h>
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

    // TODO: use a ROM API for this
    TEST_ASSERT_EQUAL(ETS_EFUSE_BLOCK_KEY0, BLOCK);
    unsigned err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY0_ERR_NUM);
    unsigned fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY0_FAIL);

    TEST_ASSERT_EQUAL(0, err);
    TEST_ASSERT_EQUAL(0, fail);
}

TEST_CASE("Soft-disable JTAG", "[esp32c][ignore]")
{
    ets_efuse_clear_program_registers();
    REG_SET_BIT(EFUSE_PGM_DATA1_REG, EFUSE_SOFT_DIS_JTAG);
    ets_efuse_program(ETS_EFUSE_BLOCK0);
    printf("JTAG soft-disabled (needs manual confirmation)...\n");
}

TEST_CASE("Temporarily enable JTAG", "[esp32c][ignore]")
{
    const ets_efuse_block_t key_block = ETS_EFUSE_BLOCK_KEY3;
    const ets_efuse_purpose_t purpose = ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL;
    const uint8_t key_data[32] = { "Hello world!" }; // padded with lots of zeroes

    /* The JTAG HMAC of the key_data. Produced by the following Python:

       import hmac, hashlib, binascii
       binascii.hexlify(hmac.HMAC(b"Hello world!", b"\x00" * 32, hashlib.sha256).digest())
    */
    const uint8_t key_hmac[32] = {
        0xda, 0x28, 0x7c, 0xf7, 0xab, 0x5b, 0x59, 0x02, 0x94, 0x04, 0x28, 0x4d, 0x8b, 0x5e, 0x97, 0x68,
        0x22, 0xb5, 0x98, 0x50, 0xde, 0x6f, 0x81, 0x4c, 0xe9, 0x09, 0x9d, 0x9c, 0x69, 0x2b, 0x60, 0x62,
    };

    int r = ets_efuse_write_key(key_block, purpose,
                        key_data, sizeof(key_data));

    TEST_ASSERT_EQUAL(r, 0);

    r = ets_jtag_enable_temporarily(key_hmac, key_block);
    TEST_ASSERT_EQUAL(r, 0);

    printf("JTAG temporarily enabled? (Need manual confirmation)\n");
}

TEST_CASE("HMAC re-disable JTAG", "[esp32c][ignore]")
{
    int r = ets_hmac_invalidate_downstream(ETS_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG);
    TEST_ASSERT_EQUAL(r, 0);

    ets_hmac_disable();

    printf("JTAG re-disabled? (Need manual confirmation)\n");
}

TEST_CASE("efuse key blocks test read/write disable", "[esp32c]")
{
        printf("ERR0 0x%08x ERR1 0x%08x\n",
               REG_READ(EFUSE_RD_RS_ERR0_REG),
               REG_READ(EFUSE_RD_RS_ERR1_REG));

    for (ets_efuse_block_t block = ETS_EFUSE_BLOCK_KEY0; block <= ETS_EFUSE_BLOCK_KEY6; block++) {
        uint32_t key_data[8] = { };
        memset(key_data, (char)block, sizeof(key_data));

        printf("Testing block %d...\n", block);

        // Write key block
        int r = ets_efuse_write_key(block, ETS_EFUSE_KEY_PURPOSE_SECURE_BOOT, key_data, sizeof(key_data));
        TEST_ASSERT_EQUAL(0, r);

        // Check it's all there
        uint32_t rd = ets_efuse_get_read_register_address(block);
        for(int i = 0; i < 8; i++) {
            TEST_ASSERT_EQUAL(key_data[i], REG_READ(rd + i * 4));
        }

        // Corrupt it
        ets_efuse_clear_program_registers();
        REG_WRITE(EFUSE_PGM_DATA0_REG, 0xCCCCCCCC);
        REG_WRITE(EFUSE_PGM_DATA1_REG, 0xCCCCCCCC);
        //REG_WRITE(EFUSE_PGM_CHECK_VALUE0_REG, 0xFFFFFFFF);
        ets_efuse_program(block);

        uint32_t new_word1 = REG_READ(rd);
        printf("before 0x%08x after 0x%08x\n", key_data[0], new_word1);
        TEST_ASSERT_NOT_EQUAL(key_data[0], new_word1);

        // Write protect it
        ets_efuse_clear_program_registers();
        // TODO: ROM function for this
        REG_WRITE(EFUSE_PGM_DATA0_REG, 1<<(block+19));
        ets_efuse_program(ETS_EFUSE_BLOCK0);

        // Try to corrupt it some more
        ets_efuse_clear_program_registers();
        REG_WRITE(EFUSE_PGM_DATA0_REG, 0x11111111);
        ets_efuse_program(block);

        // But it hasn't changed
        uint32_t new_word2 = REG_READ(rd);
        TEST_ASSERT_EQUAL(new_word1, new_word2);

        // Now read protect it
        ets_efuse_clear_program_registers();
        // TODO: ROM function for this
        REG_WRITE(EFUSE_PGM_DATA1_REG, 1<<(block-4));
        ets_efuse_program(ETS_EFUSE_BLOCK0);

        for(int i = 0; i < 8; i++) {
            TEST_ASSERT_EQUAL(0, REG_READ(rd + i * 4));
        }

        printf("ERR0 0x%08x ERR1 0x%08x\n",
               REG_READ(EFUSE_RD_RS_ERR0_REG),
               REG_READ(EFUSE_RD_RS_ERR1_REG));

    // TODO: use a ROM API for this
    unsigned err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY0_ERR_NUM);
    unsigned fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY0_FAIL);
    printf("key0 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY1_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY1_FAIL);
    printf("key1 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY2_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY2_FAIL);
    printf("key2 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY3_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY3_FAIL);
    printf("key3 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY4_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR0_REG, EFUSE_RD_KEY4_FAIL);
    printf("key4 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR1_REG, EFUSE_RD_KEY5_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR1_REG, EFUSE_RD_KEY5_FAIL);
    printf("key5 err %d fail %d\n", err, fail);

    err = REG_GET_FIELD(EFUSE_RD_RS_ERR1_REG, EFUSE_RD_KEY6_ERR_NUM);
    fail = REG_GET_BIT(EFUSE_RD_RS_ERR1_REG, EFUSE_RD_KEY6_FAIL);
    printf("key6 err %d fail %d\n", err, fail);

    }
}

#endif /* CONFIG_HARDWARE_IS_FPGA */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <esp_system.h>
#include "unity.h"
#include "sdkconfig.h"
#include "hwcrypto/sha.h"

static const uint8_t sha256_thousand_as[32] = {
    0x41, 0xed, 0xec, 0xe4, 0x2d, 0x63, 0xe8, 0xd9, 0xbf, 0x51, 0x5a, 0x9b, 0xa6, 0x93, 0x2e, 0x1c,
    0x20, 0xcb, 0xc9, 0xf5, 0xa5, 0xd1, 0x34, 0x64, 0x5a, 0xdb, 0x5d, 0xb1, 0xb9, 0x73, 0x7e, 0xa3 };

static const uint8_t sha256_thousand_bs[32] = {
    0xf6, 0xf1, 0x18, 0xe1, 0x20, 0xe5, 0x2b, 0xe0, 0xbd, 0x0c, 0xfd, 0xf2, 0x79, 0x4c, 0xd1, 0x2c, 0x07, 0x68, 0x6c, 0xc8, 0x71, 0x23, 0x5a, 0xc2, 0xf1, 0x14, 0x59, 0x37, 0x8e, 0x6d, 0x23, 0x5b
};

static const uint8_t sha512_thousand_bs[64] = {
    0xa6, 0x68, 0x68, 0xa3, 0x73, 0x53, 0x2a, 0x5c, 0xc3, 0x3f, 0xbf, 0x43, 0x4e, 0xba, 0x10, 0x86, 0xb3, 0x87, 0x09, 0xe9, 0x14, 0x3f, 0xbf, 0x37, 0x67, 0x8d, 0x43, 0xd9, 0x9b, 0x95, 0x08, 0xd5, 0x80, 0x2d, 0xbe, 0x9d, 0xe9, 0x1a, 0x54, 0xab, 0x9e, 0xbc, 0x8a, 0x08, 0xa0, 0x1a, 0x89, 0xd8, 0x72, 0x68, 0xdf, 0x52, 0x69, 0x7f, 0x1c, 0x70, 0xda, 0xe8, 0x3f, 0xe5, 0xae, 0x5a, 0xfc, 0x9d
};

static const uint8_t sha384_thousand_bs[48] = {
    0x6d, 0xe5, 0xf5, 0x88, 0x57, 0x60, 0x83, 0xff, 0x7c, 0x94, 0x61, 0x5f, 0x8d, 0x96, 0xf2, 0x76, 0xd5, 0x3f, 0x77, 0x0c, 0x8e, 0xc1, 0xbf, 0xb6, 0x04, 0x27, 0xa4, 0xba, 0xea, 0x6c, 0x68, 0x44, 0xbd, 0xb0, 0x9c, 0xef, 0x6a, 0x09, 0x28, 0xe8, 0x1f, 0xfc, 0x95, 0x03, 0x69, 0x99, 0xab, 0x1a
};

static const uint8_t sha1_thousand_as[20] = {
    0x29, 0x1e, 0x9a, 0x6c, 0x66, 0x99, 0x49, 0x49, 0xb5, 0x7b, 0xa5,
    0xe6, 0x50, 0x36, 0x1e, 0x98, 0xfc, 0x36, 0xb1, 0xba };

TEST_CASE("esp_sha simple SHA function", "[esp32c]")
{
    size_t len_input = 1000;
    uint8_t *input = malloc(len_input);
    uint8_t digest[64] = {};

    memset(input, 'a', len_input);
    esp_sha(SHA1, input, len_input, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha1_thousand_as, digest, sizeof(sha1_thousand_as));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    esp_sha(SHA2_256, input, len_input, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha256_thousand_bs, digest, sizeof(sha256_thousand_bs));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    esp_sha(SHA2_384, input, len_input, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha384_thousand_bs, digest, sizeof(sha384_thousand_bs));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    esp_sha(SHA2_512, input, len_input, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha512_thousand_bs, digest, sizeof(sha512_thousand_bs));

    free(input);
}

TEST_CASE("simple SHA ROM functions", "[esp32c]")
{
    SHA_CTX ctx;
    size_t len_input = 1000;
    uint8_t *input = malloc(len_input);
    uint8_t digest[64] = {};

    ets_sha_enable();

    memset(input, 'a', len_input);

    ets_sha_init(&ctx, SHA1);
    ets_sha_update(&ctx, input, len_input, false);
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha1_thousand_as, digest, sizeof(sha1_thousand_as));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    ets_sha_init(&ctx, SHA2_256);
    ets_sha_update(&ctx, input, len_input, false);
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha256_thousand_bs, digest, sizeof(sha256_thousand_bs));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    ets_sha_init(&ctx, SHA2_384);
    ets_sha_update(&ctx, input, len_input, false);
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha384_thousand_bs, digest, sizeof(sha384_thousand_bs));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    ets_sha_init(&ctx, SHA2_512);
    ets_sha_update(&ctx, input, len_input, false);
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha512_thousand_bs, digest, sizeof(sha512_thousand_bs));

    free(input);
}

TEST_CASE("multi update SHA ROM function", "[esp32c]")
{
    SHA_CTX ctx;
    const size_t len_input = 1000;
    uint8_t *input = malloc(len_input);
    uint8_t digest[64] = {};

    ets_sha_enable();

    memset(input, 'a', len_input);

    ets_sha_init(&ctx, SHA1);
    assert(len_input % 10 == 0);
    for (int i = 0; i < len_input; i += 10) {
        ets_sha_update(&ctx, &input[i], 10, false);
    }
    TEST_ASSERT(ctx.in_hardware); // at least one SHA finished
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha1_thousand_as, digest, sizeof(sha1_thousand_as));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);

    ets_sha_init(&ctx, SHA2_256);
    for (int i = 0; i < len_input; i += 10) {
        ets_sha_update(&ctx, &input[i], 10, true);
    }
    TEST_ASSERT(ctx.in_hardware); // at least one SHA block finished
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha256_thousand_bs, digest, sizeof(sha256_thousand_bs));

    bzero(digest, sizeof(digest));
    memset(input, 'b', len_input);
    ets_sha_init(&ctx, SHA2_384);
    assert(len_input % 4 == 0);
    for (int i = 0; i < len_input; i += 4) {
        ets_sha_update(&ctx, &input[i], 4, true);
    }
    TEST_ASSERT(ctx.in_hardware); // at least one SHA block finished
    ets_sha_finish(&ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha384_thousand_bs, digest, sizeof(sha384_thousand_bs));

    free(input);
}


TEST_CASE("interleaved SHA ROM functions", "[esp32c]")
{
    SHA_CTX sha1_ctx, sha256_ctx, sha384_ctx, sha512_ctx;
    size_t len_input = 1000;
    uint8_t *input_as = malloc(len_input);
    uint8_t *input_bs = malloc(len_input);
    uint8_t digest[64] = {};

    memset(input_as, 'a', len_input);
    memset(input_bs, 'b', len_input);

    ets_sha_enable();

    ets_sha_init(&sha1_ctx, SHA1);
    ets_sha_init(&sha256_ctx, SHA2_256);
    ets_sha_init(&sha384_ctx, SHA2_384);
    ets_sha_init(&sha512_ctx, SHA2_512);

    assert(len_input % 8 == 0);
    for (int i = 0; i < len_input; i += 8) {
        sha1_ctx.in_hardware = false;
        ets_sha_update(&sha1_ctx, &input_as[i], 4, false);
        ets_sha_update(&sha1_ctx, &input_as[i+4], 4, true);

        sha256_ctx.in_hardware = false;
        ets_sha_update(&sha256_ctx, &input_bs[i], 8, true);

        sha384_ctx.in_hardware = false;
        ets_sha_update(&sha384_ctx, &input_bs[i], 4, true);

        sha512_ctx.in_hardware = false;
        ets_sha_update(&sha512_ctx, &input_bs[i], 8, true);

        sha384_ctx.in_hardware = false;
        ets_sha_update(&sha384_ctx, &input_bs[i+4], 4, true);
    }

    ets_sha_finish(&sha384_ctx, digest); // state_in_hardware matches last update
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha384_thousand_bs, digest, sizeof(sha384_thousand_bs));

    ets_sha_finish(&sha1_ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha1_thousand_as, digest, sizeof(sha1_thousand_as));

    ets_sha_finish(&sha256_ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha256_thousand_bs, digest, sizeof(sha256_thousand_bs));

    ets_sha_finish(&sha512_ctx, digest);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(sha512_thousand_bs, digest, sizeof(sha512_thousand_bs));

    free(input_as);
    free(input_bs);

    ets_sha_disable();
}

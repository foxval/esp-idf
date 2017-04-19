#include <math.h>
#include "unity.h"
#include "driver/adc.h"
#include "driver/dac.h"

// Connect GPIO25 (DAC1) to GPIO36 (SENSOR_VP), GPIO26 (DAC2) to GPIO39 (SENSOR_VN)
TEST_CASE("can sample using LNA", "[adc][ignore]")
{
    const size_t sample_count = 128;
    int16_t sample_buf[sample_count];

    int dac_voltages[][4] = {
            {20, 20, 0, 0},
            {20, 21, 0, 0},
            {20, 22, 0, 0},
            {20, 23, 0, 0},
            {20, 24, 0, 0},
            {20, 25, 0, 0},
            {20, 26, 0, 0},
            {20, 20, 1, 0},
            {21, 20, 1, 0},
            {22, 20, 1, 0},
            {23, 20, 1, 0},
            {24, 20, 1, 0},
            {25, 20, 1, 0},
            {26, 20, 1, 0},
            {60, 60, 2, 0},
            {60, 61, 2, 0},
            {60, 62, 2, 0},
            {60, 63, 2, 0},
            {60, 64, 2, 0},
            {60, 65, 2, 0},
            {60, 66, 2, 0},
            {60, 60, 3, 0},
            {61, 60, 3, 0},
            {62, 60, 3, 0},
            {63, 60, 3, 0},
            {64, 60, 3, 0},
            {65, 60, 3, 0},
            {66, 60, 3, 0},
            {0, 0, 4, 0}
    };

    adc1_config_channel_atten(0, ADC_ATTEN_0db);
    adc1_config_channel_atten(3, ADC_ATTEN_0db);
    adc1_config_width(ADC_WIDTH_12Bit);

    const size_t tests_count = sizeof(dac_voltages)/sizeof(dac_voltages[0]);
    printf("\n Vp  Vn   Out  +/- di  do   slope\n\n");

    int test_grp = 0;
    size_t test_grp_start = 0;
    for (size_t it = 0; it < tests_count - 1; ++it) {
        dac_out_voltage(DAC_CHANNEL_1, dac_voltages[it][0]);
        dac_out_voltage(DAC_CHANNEL_2, dac_voltages[it][1]);

        int result = 0;
        int result_c0 = 0;
        int result_c3 = 0;
        for (size_t is = 0; is < sample_count; ++is) {
            int val = adc1_get_lna_voltage();
            sample_buf[is] = val;
            result += val;

            val = adc1_get_voltage(0);
            result_c0 += val;

            val = adc1_get_voltage(3);
            result_c3 += val;
        }
        int result_div = result / sample_count;
        int result_c0_div = result_c0 / sample_count;
        int result_c3_div = result_c3 / sample_count;

        int stddev = 0;
        for (size_t is = 0; is < sample_count; ++is) {
            int diff = sample_buf[is] - result_div;
            stddev += diff * diff;
        }
        dac_voltages[it][3] = result;

        float slope = 0;
        int diff = 0;
        float res_diff = 0;
        if (it != test_grp_start) {
            int ref_res_val = dac_voltages[test_grp_start][3];
            int diff_vp = dac_voltages[it][0] - dac_voltages[test_grp_start][0];
            int diff_vn = dac_voltages[it][1] - dac_voltages[test_grp_start][1];
            diff = diff_vp - diff_vn;
            res_diff = (result - ref_res_val) / (float) sample_count;
            slope = res_diff / diff;
        }

        printf("%3d %3d %5d %.2f %+2d %05.1f %+05.1f %5d %5d %5d\n",
                dac_voltages[it][0],
                dac_voltages[it][1],
                result_div,
                sqrtf(stddev / (float) (result - 1)),
                diff, res_diff, slope,
                result_c0_div, result_c3_div, result_c0_div - result_c3_div);


        int next_test_grp = dac_voltages[it + 1][2];
        if (next_test_grp != test_grp) {
            test_grp = next_test_grp;
            test_grp_start = it + 1;
            printf("\n");
        }

    }
}

// Connect GPIO25 (DAC1) to GPIO36 and GPIO39
TEST_CASE("LNA common mode test", "[adc][ignore]")
{
    adc1_config_channel_atten(0, ADC_ATTEN_0db);
    adc1_config_channel_atten(3, ADC_ATTEN_0db);
    adc1_config_width(ADC_WIDTH_12Bit);


    const size_t sample_count = 128;
    int16_t sample_buf[sample_count];

    for (int dac_v = 0; dac_v < 256; ++dac_v) {
        dac_out_voltage(DAC_CHANNEL_1, dac_v);
        int result = 0;
        for (size_t is = 0; is < sample_count; ++is) {
            int val = adc1_get_lna_voltage();
            sample_buf[is] = val;
            result += val;

        }
        int result_div = result / sample_count;

        int stddev = 0;
        for (size_t is = 0; is < sample_count; ++is) {
            int diff = sample_buf[is] - result_div;
            stddev += diff * diff;
        }

        printf("%3d %5d %.2f\n", dac_v, result_div, sqrtf(stddev / (float) (result - 1)));
    }
}

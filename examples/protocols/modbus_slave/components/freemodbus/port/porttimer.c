/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "driver/timer.h"
//#include "esp_timer.h"              // for timer functions
//#include "soc/timer_group_struct.h" // for group timer structure

#define MB_US50_FREQ        (20000) // 20kHz  fox: 1/20000 = 50mks
#define MB_DISCR_TIME_US    (50)    // 50uS = one discreet for timer

//#define TIMER_DIVIDER     (16)  //  Hardware timer clock divider
#define MB_TIMER_PRESCALLER ((TIMER_BASE_CLK / MB_US50_FREQ) - 1);
#define MB_TIMER_SCALE      (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
#define MB_TIMER_DIVIDER    ((TIMER_BASE_CLK / 1000000UL) * MB_DISCR_TIME_US - 1) // divider for 50uS
#define MB_TIMER_WITHOUT_RELOAD   (0)        // testing will be done without auto reload
#define MB_TIMER_WITH_RELOAD      (1)        // testing will be done with auto reload
#define MB_TIMER_IO_LED           (19)

const USHORT timer_idx = TIMER_0;


/* ----------------------- Start implementation -----------------------------*/

void IRAM_ATTR timer_group0_isr(void *param)
{
    int timer_idx = (int) param;
    static uint8_t pin_level = 0;

    // Retrieve the interrupt status and the counter value
    // from the timer that reported the interrupt
    uint32_t intr_status = TIMERG0.int_st_timers.val;
    vMBPortSetWithinException( TRUE );
    if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {
        TIMERG0.int_clr_timers.t0 = 1;
        TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN; // reenable alarm
        (void) pxMBPortCBTimerExpired(); // xMBRTUTimerT35Expired();
        // Todo: remove later these lines that are for debugging
        gpio_pad_select_gpio(MB_TIMER_IO_LED);
        /* Set the GPIO as a push/pull output */
        gpio_set_direction(MB_TIMER_IO_LED, GPIO_MODE_OUTPUT);
        gpio_set_level(MB_TIMER_IO_LED, pin_level);
        pin_level ^= 0x01;
    }
    vMBPortSetWithinException( FALSE );
}

BOOL xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    timer_config_t config;
    //uint64_t alarm_val = (TIME3_5_PERIOD * (TIMER_BASE_CLK / 1000000UL)) / TIMER_DIVIDER;
    printf("xMBPortTimersInit.\r\n");
    config.alarm_en = TIMER_ALARM_EN;
    config.auto_reload = MB_TIMER_WITH_RELOAD;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = MB_TIMER_PRESCALLER;     //Range is 2 to 65536
    config.intr_type = TIMER_INTR_LEVEL;
    config.counter_en = TIMER_PAUSE;
    // Configure timer
    timer_init(TIMER_GROUP_0, timer_idx, &config);
    // Stop timer counter
    timer_pause(TIMER_GROUP_0, timer_idx);
    // Reset counter value
    timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0x00000000ULL);
    //wait3T5_us = 35*11*100000/baud;
    // Set alarm value for usTim1Timerout50us * 50uS
    timer_set_alarm_value(TIMER_GROUP_0, timer_idx, (uint32_t)(usTim1Timerout50us)); //alarm_val
    // Register isr for timer
    timer_isr_register(TIMER_GROUP_0, timer_idx, timer_group0_isr,
                    (void *) timer_idx, ESP_INTR_FLAG_IRAM, NULL);
    // Enable timer interrupt
    //timer_enable_intr(TIMER_GROUP_0, timer_idx);
    //timer_start(TIMER_GROUP_0, timer_idx);
    return TRUE;
}

void vMBPortTimersEnable()
{
    timer_pause(TIMER_GROUP_0, timer_idx);
    //static uint64_t timer_value = 0;
    timer_pause(TIMER_GROUP_0, timer_idx);
    //timer_get_counter_value(TIMER_GROUP_0, timer_idx, &timer_value);
    timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0ULL);
    timer_enable_intr(TIMER_GROUP_0, timer_idx);
    timer_start(TIMER_GROUP_0, timer_idx);
}

void vMBPortTimersDisable()
{
    timer_pause(TIMER_GROUP_0, timer_idx);
    timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0x00000000ULL);
    // Disable timer interrupt
    timer_disable_intr(TIMER_GROUP_0, timer_idx);
}

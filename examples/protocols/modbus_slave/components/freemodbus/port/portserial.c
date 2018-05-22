#include "port.h"
#include "driver/uart.h"
#include "freertos/queue.h" // for queue support
#include "soc/uart_reg.h"
#include "driver/gpio.h"
#include "esp_log.h"        // for esp_log
#include "esp_err.h"        // for ESP_ERROR_CHECK macro
   
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#define MB_UART_RXD   (22)
#define MB_UART_TXD   (23)
#define MB_UART_RTS   (18)

// Set buffer size for transmission
#define MB_BUF_SIZE   (255)

// Wait timeout for uart driver
#define MB_PACKET_READ_TICS     (1000 / portTICK_RATE_MS)
#define MB_BAUD_RATE_DEFAULT    (115200)
#define MB_QUEUE_LENGTH         (20)
#define MB_GPIO_LED             (19)
#define MB_GPIO_RTS             (5)
#define MB_SERIAL_TASK_PRIO     (configMAX_PRIORITIES - 3) //(2 | portPRIVILEGE_BIT) //(configMAX_PRIORITIES - 3)
#define MB_SERIAL_STACK_SIZE    (2048)
#define MB_SERIAL_TXDONE_TOUT   (500)
#define MB_SERIAL_TOUT          (3) // 3.5*8 = 28 ticks, TOUT=3 -> ~24..33 ticks

// Note: This code uses mixed coding standard due to legacy IDF code and used freemodbus stack

// A queue to handle UART event.
static QueueHandle_t   mb_uart_queue;
static TaskHandle_t    mb_task_handle;
static const char *TAG = "MB_SERIAL";

// The UART hardware port number is used
static int uart_number = UART_NUM_2;
//uint8_t* mb_local_uart_buffer = NULL;
//static uint16_t mb_local_uart_buffer_size = 0;

static BOOL bRxEnabled = FALSE;
static BOOL bTxEnabled = FALSE;

static UCHAR ucBuffer[MB_BUF_SIZE];
static USHORT uiRxBufferPos = 0;

// Todo: Remove later, used for debugging
void vMBPortSerialSetPin(CHAR ucGpioNum, CHAR ucLevel)
{
    gpio_pad_select_gpio((uint8_t)ucGpioNum);
    // Set the GPIO as a push/pull output
    gpio_set_direction((uint8_t)ucGpioNum, GPIO_MODE_OUTPUT);
    gpio_set_level((uint8_t)ucGpioNum, (uint8_t)ucLevel);
}

// Todo: for debugging, remove later
void vMBPortSerialSetRts(CHAR ucLevel)
{
    uart_set_rts(uart_number, (uint8_t)(ucLevel ^ 0x01));
}

void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    // It may be called from xMBRTUTransmitFSM() of different task
    ENTER_CRITICAL_SECTION();
    if (xRxEnable) {
        //uart_enable_rx_intr(uart_number);
        bRxEnabled = TRUE;
        vTaskResume(mb_task_handle);
    } else {
        vTaskSuspend(mb_task_handle);
        bRxEnabled = FALSE;
    }
    if (xTxEnable) {
        bTxEnabled = TRUE;
        //vMBPortSerialSetRts(1);
    } else {
        bTxEnabled = FALSE;
        //vMBPortSerialSetRts(0);
    }
    EXIT_CRITICAL_SECTION();
}

BOOL xMBPortSerialRxPoll(size_t event_size)
{
    BOOL        bStatus = TRUE;
    uint16_t    length;

    if (bRxEnabled) {
        // Set pin for debugging
        vMBPortSerialSetPin(26, 0);
        if (event_size > 0) {
            event_size = (event_size > MB_BUF_SIZE) ?  MB_BUF_SIZE : event_size;
            uiRxBufferPos = ((uiRxBufferPos + event_size) >= MB_BUF_SIZE) ? 0 : uiRxBufferPos;
            // Get received packet into Rx buffer
            length = uart_read_bytes(uart_number, &ucBuffer[uiRxBufferPos], event_size, portMAX_DELAY);
            for(uint16_t i = 0; i < length; i++ ) {
                // Call the modbus stack callback function and let it fill the buffers.
                ( void )pxMBFrameCBByteReceived(); // calls callback xMBRTUReceiveFSM() to execute MB state machine
            }
            // The buffer is transferred into mb stack and is not needed
            uart_flush_input(uart_number);
            // Send event EV_FRAME_RECEIVED to allow stack process packet
            (void) pxMBPortCBTimerExpired(); // xMBRTUTimerT35Expired();
            vMBPortSerialSetPin(26, 1);
            ESP_LOGI(TAG, "RX_T35_timeout: %d(bytes in buffer)\n", length);
        }
    }
    return bStatus;
}

BOOL xMBPortSerialTxPoll()
{
    BOOL        bStatus = FALSE;
    //uint16_t    bytes_written;
    USHORT      count = 0;
    BOOL        xNeedPoll = FALSE;

    if( bTxEnabled ) {
        vMBPortSerialSetPin(19, 0);
        // Continue while all response bytes put in buffer or out of buffer
        while((xNeedPoll == FALSE) && (count++ < MB_BUF_SIZE) ) {
            // Calls the modbus stack callback function to let it fill the UART transmit buffer.
            xNeedPoll = pxMBFrameCBTransmitterEmpty( ); // calls callback xMBRTUTransmitFSM();
        }
        vMBPortSerialSetPin(19, 1); // Todo: for debugging
        ESP_LOGI(TAG, "MB_TX_buffer sent: (%d) bytes\n", (uint16_t)count);
        bStatus = TRUE;
    }
    return bStatus;
}

static void uart_task(void *pvParameters)
{
    uart_event_t event;

    for(;;) {
        if (pdTRUE == xQueueReceive(mb_uart_queue, (void*)&event, portMAX_DELAY)) {
            ESP_LOGI(TAG, "MB_uart[%d] event:", uart_number);
            //vMBPortTimersEnable();
            switch(event.type) {
                //Event of UART receving data
                case UART_DATA:
                    ESP_LOGI(TAG,"data, len: %d", event.size);
                    // Read received data and send it to modbus stack
                    (void)xMBPortSerialRxPoll(event.size);
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow\n");
                    xQueueReset(mb_uart_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full\n");
                    xQueueReset(mb_uart_queue);
                    uart_flush_input(uart_number);
                    break;
                    //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break\n");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error\n");
                    break;
                    //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error\n");
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d\n", event.type);
                    break;
            }
        }
    }
    vTaskDelete(NULL);
}

BOOL xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate,
                        UCHAR ucDataBits, eMBParity eParity )
{
    // Set communication port number
    uart_number = ucPORT;
    // Configure serial communication parameters
    int parity = UART_PARITY_DISABLE;
    int data_bits = UART_DATA_8_BITS;
    switch(eParity){
        case MB_PAR_NONE:
            //data_bits = DATA_BITS_8;
            parity = UART_PARITY_DISABLE;
            break;
        case MB_PAR_ODD:
            //data_bits = DATA_BITS_9;
            parity = UART_PARITY_ODD;
            break;
        case MB_PAR_EVEN:
            //data_bits = DATA_BITS_9;
            parity = UART_PARITY_EVEN;
            break;
    }
    switch(ucDataBits){
        case 5:
            data_bits = UART_DATA_5_BITS;
            break;
        case 6:
            data_bits = UART_DATA_6_BITS;
            break;
        case 7:
            data_bits = UART_DATA_7_BITS;
            break;
        case 8:
            data_bits = UART_DATA_8_BITS;
            break;
        default:
            data_bits = UART_DATA_8_BITS;
            break;
    }
    uart_config_t uart_config = {
        .baud_rate = ulBaudRate,
        .data_bits = data_bits,
        .parity = parity,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 2,
    };
    esp_log_level_set(TAG, ESP_LOG_INFO);
    ESP_LOGI(TAG, "xMBPortSerialInit.\n");
    //Set UART parameters
    uart_param_config(uart_number, &uart_config);
    //Set UART pins,(-1: default pin, no change.)
    uart_set_pin(uart_number, MB_UART_TXD, MB_UART_RXD, MB_UART_RTS, UART_PIN_NO_CHANGE);
    //Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);
    //Install UART driver, and get the queue.
    uart_driver_install(uart_number, MB_BUF_SIZE, MB_BUF_SIZE, MB_QUEUE_LENGTH, &mb_uart_queue, ESP_INTR_FLAG_LOWMED);
    // Set driver mode to Half Duplex
    uart_set_mode(uart_number, UART_MODE_RS485_HALF_DUPLEX);
    //uart_set_mode(uart_number, UART_MODE_RS485_A);
    uart_set_rx_timeout(uart_number, MB_SERIAL_TOUT); // Set timeout for TOUT interrupt
    // Create task to handle UART events
    if (pdPASS != xTaskCreate(uart_task, "uart_queue_task", \
            MB_SERIAL_STACK_SIZE, (void*)uart_number, MB_SERIAL_TASK_PRIO, &mb_task_handle)) {
        ESP_LOGI(TAG, "Modbus stack serial task creation error.\n");
    } else {
        vTaskSuspend(mb_task_handle); // suspend task while stack is not started
    }
    uiRxBufferPos = 0;
    return TRUE;
}

static void xMBPortSerialWaitTransmission( )
{
    uart_wait_tx_done(uart_number, MB_SERIAL_TXDONE_TOUT);
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    // Send one byte to UART transmission buffer
    // This function is called by modbus stack
    uart_write_bytes(uart_number, &ucByte, 1);
    uint8_t coll_det = 0;
    uart_get_collision_flag(uart_number, &coll_det);
    return TRUE;
}

// Get one byte from RX buffer
BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
    assert( uiRxBufferPos < MB_BUF_SIZE );
    *pucByte = ucBuffer[uiRxBufferPos];
    uiRxBufferPos++;
    return TRUE;
}





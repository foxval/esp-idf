#ifndef _PORT_H
#define _PORT_H
/* ----------------------- Platform includes --------------------------------*/
#include "driver/uart.h"
#include "driver/timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/xtensa_api.h"
#include "freertos/portmacro.h"

/* ----------------------- Defines ------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define MB_ENTER_CRITICAL_ISR(mux)    portENTER_CRITICAL_ISR(mux)
#define MB_EXIT_CRITICAL_ISR(mux)     portEXIT_CRITICAL_ISR(mux)
#define MB_ENTER_CRITICAL(mux)    portENTER_CRITICAL(mux)
#define MB_EXIT_CRITICAL(mux)     portEXIT_CRITICAL(mux)

#define ENTER_CRITICAL_SECTION( )   ( vMBPortEnterCritical() )
#define EXIT_CRITICAL_SECTION( )    ( vMBPortExitCritical() )

typedef char    BOOL;

typedef unsigned char UCHAR;
typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

void vMBPortSetWithinException( BOOL bInException );

void vMBPortEnterCritical(void);

void vMBPortExitCritical(void);

// Todo: The functions below are left here for debugging of port
BOOL xMBPortSerialRxPoll(size_t size);

BOOL xMBPortSerialTxPoll();

void vMBPortSerialSetPin(CHAR gpio_num, CHAR level);

void vMBPortSerialSetRts(CHAR level);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

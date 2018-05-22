/*
 * FreeModbus Libary: ESP32 Demo Application
 * Copyright (C) 2010 Christian Walter <cwalter@embedded-solutions.at>
 *
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * IF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: portevent.c,v 1.1 2010/06/06 13:07:20 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "port/port.h"
/* ----------------------- Variables ----------------------------------------*/
static xQueueHandle xQueueHdl;

#define EVENT_QUEUE_SIZE        (5)
#define QUEUE_TIMEOUT           ((TickType_t)20)

BOOL bMBPortIsWithinException( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortEventInit( void )
{
    //fox:
    printf("xMBPortEventInit.\r\n");
    BOOL bStatus = FALSE;
    if( NULL != ( xQueueHdl = xQueueCreate( EVENT_QUEUE_SIZE, sizeof( eMBEventType ) ) ) )
    {
      vQueueAddToRegistry( xQueueHdl, "MbPortEventQueue" );  
      bStatus = TRUE;
    }
    return bStatus;
}

void
vMBPortEventClose( void )
{
    if( NULL != xQueueHdl )
    {
        vQueueDelete( xQueueHdl );
        xQueueHdl = NULL;
    }
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
    BOOL bStatus = TRUE;
    assert(xQueueHdl != NULL);
    
    if( bMBPortIsWithinException(  ) )
    {
        xQueueSendFromISR( xQueueHdl, ( const void * )&eEvent, pdFALSE );
    }
    else
    {
        xQueueSend( xQueueHdl, ( const void * )&eEvent, QUEUE_TIMEOUT );
    }
    return bStatus;
}

BOOL
xMBPortEventGet( eMBEventType * peEvent )
{
    assert(NULL != xQueueHdl);
    BOOL xEventHappened = FALSE;

    if (pdTRUE == xQueueReceive(xQueueHdl, peEvent, portMAX_DELAY)) { // (10 / portTICK_RATE_MS)portMAX_DELAY
        xEventHappened = TRUE;
    }
    if ((*peEvent == EV_EXECUTE) && (xEventHappened == TRUE)) {
        // If timeout is over we need to poll serial data
        //(void)xMBPortSerialTxPoll();
    }
    return xEventHappened;
}

xQueueHandle
xMBPortEventGetHandle( void )
{
    if(NULL != xQueueHdl) //
    {
        return xQueueHdl;
    }
    return NULL;
}


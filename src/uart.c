#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"

#include "uart.h"

#define UART_TIMEOUT_COUNTS 168000000 / 115200

static uint8_t received_buf[256];

void
uart_init( void )
{
    USART_InitTypeDef usart_init1;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    usart_init1.USART_BaudRate = 115200;
    usart_init1.USART_WordLength = USART_WordLength_8b;
    usart_init1.USART_StopBits = USART_StopBits_1;
    usart_init1.USART_Parity = USART_Parity_No; // might change this
    usart_init1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init( USART1, &usart_init1 );
    USART_ITConfig( USART1, USART_IT_RXNE, ENABLE ); // interrupt when read ready
    USART_Cmd( USART1, ENABLE );
}

/******************************************************************************
 * Put string over uart (not sure why volatile keyword needs to be used)
 */
int
uart_puts( USART_TypeDef *USARTx, volatile uint8_t *s )
{
    int timeout_counts;
    while ( *s )
    {
        timeout_counts = UART_TIMEOUT_COUNTS;
        // check if transmit register is empty and no timeout
        while ( !(USARTx->SR & USART_SR_TC ) && timeout_counts > 0)
            /* timeout_counts--; */
        /* if ( timeout_counts == 0 ) */
        /*     return 1; */
        USART_SendData( USARTx, *s );
        s++ ;
    }
    return 0;
}

void
USART1_IRQHandler( void )
{
    // check if USART1 receive interrupt flag is set
    if ( USART_GetITStatus( USART1, USART_IT_RXNE ) )
    {
        static uint32_t count = 0;
        uint8_t t = USART1->DR; // XXX Use USART_ReceiveData() if using parity bit

        if ( t != '\n' && count < 256 )
        {
            received_buf[count] = t;
            count++;
        }
        else
        {
            received_buf[count] = '\0';
            count = 0;
            uart_puts( USART1, received_buf );
        }
    }
}

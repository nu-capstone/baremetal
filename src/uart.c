#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"

#include "uart.h"

// #define UART_TIMEOUT_COUNTS 168000000 / 19200
#define UART_TIMEOUT_COUNTS 168000000

static uint8_t received_buf[256];

void
uart_init( void )
{
    USART_InitTypeDef usart_init1;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    usart_init1.USART_BaudRate = 19200;
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
 */
void
uart_buf_init( uart_buf_t *buf )
{
    buf->head = 0;
    buf->tail = 0;
}

/******************************************************************************
 */
static int
uart_buf_next( uart_buf_t *buf )
{
    if ( buf->tail + 1 == UART_BUF_LEN )
        return 0;
    else
        return buf->tail + 1;
}

/******************************************************************************
 */
int
uart_data_avail( uart_buf_t *buf )
{
    if ( buf->tail == buf->head )
        return 0;
    return 1;
}

/******************************************************************************
 */
int
uart_space_avail( uart_buf_t *buf )
{
    if ( uart_buf_next( buf ) == buf->head )
        return 0;
    return 1;
}

/******************************************************************************
 */
int
uart_push( uart_buf_t *buf,
           uint8_t c )
{
    buf->buf[buf->tail] = c;
    buf->tail = uart_buf_next( buf );

    return 0;
}

/******************************************************************************
 */
uint8_t
uart_pop( uart_buf_t *buf )
{
    uint8_t data = buf->buf[buf->head];
    buf->head = uart_buf_next( buf );
    
    return data;
}

/*******************************************************************************
 * XXX Pretty bad code here
 */
int
uart_send( int length )
{
    for ( int i = 0; i < length; i++ )
    {
        while ( !(USART1->SR & 0x00000040) )
            ;
        USART_SendData(USART1, tx_buf.buf[tx_buf.head]);
        tx_buf.head++; 
    }
    return 0;
}

void
USART1_IRQHandler( void )
{
    // check if USART1 receive interrupt flag is set
    if ( USART_GetITStatus( USART1, USART_IT_RXNE ) )
    {
        uint8_t t = USART1->DR;
        uart_push( &rx_buf, t );
#if 0
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
#endif
    }
}

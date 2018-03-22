#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_BUF_LEN 256

typedef struct _uart_buf_t
{
    uint8_t buf[UART_BUF_LEN];
    int head;
    int tail;
} uart_buf_t;

uart_buf_t rx_buf;
uart_buf_t tx_buf;

void uart_init( void );

void uart_buf_init( uart_buf_t *buf );
int uart_data_avail( uart_buf_t *buf );
int uart_space_avail( uart_buf_t *buf );
uint8_t uart_pop( uart_buf_t *buf );
int uart_push( uart_buf_t *buf, uint8_t c );

#endif // UART_H

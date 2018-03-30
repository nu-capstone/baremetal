#include "stm32f4xx.h"

#include "adpd.h"
#include "uart.h"
#include "i2c.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"

/******************************************************************************
 */
int
main( void )
{
    int dumb = 12;
    tx_buf.buf[0] = 't';
    tx_buf.buf[1] = 'e';
    tx_buf.buf[2] = 's';
    tx_buf.buf[3] = 't';
    tx_buf.buf[4] = '\n';
    tx_buf.buf[5] = '\0';

    dumb = 13;
    
    gpio_init();
    dumb = 14;
    // uart_init();
    i2c_init();
    dumb = 15;
    // adpd_init();

    // interrupt_init();

    uint16_t test = adpd_read_1word( 0x0 );
    dumb = 16;
    // adpd_read_words( 0, test_data, 64 );

    return 0;
    while ( 1 )
    {
        // read command from uart
        // if ( command received )
        //  process command
        //  respond over uart
        // else
        //  read adpd0
        //  read adpd1
        //  do dsp shit
        //  send stuff back over uart
    }
    return 0;
}

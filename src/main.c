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
    // initialization here
    gpio_init();
    uart_init();
    i2c_init();
    adpd_init();

    uart_puts( USART1, "Stuff is initialized\n" );

    interrupt_init();
    while ( 1 )
    {
        // do the shit 
    }
    return 0;
}

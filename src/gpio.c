#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "gpio.h"

void
gpio_init( void )
{
    GPIO_InitTypeDef gpio_init;

    // enable clock for GPIOA and SYSCFG
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE );

    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Pin = GPIO_Pin_0; // PA0
    gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &gpio_init );
}

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "gpio.h"

void
gpio_init( void )
{
    GPIO_InitTypeDef gpio_initA;
    GPIO_InitTypeDef gpio_initB;

    // enable clock for GPIOA, GPIOB, and SYSCFG
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE );

    // Interrupt pin
    gpio_initA.GPIO_Mode = GPIO_Mode_IN;
    gpio_initA.GPIO_OType = GPIO_OType_PP;
    gpio_initA.GPIO_Pin = GPIO_Pin_0; // PA0
    gpio_initA.GPIO_PuPd = GPIO_PuPd_DOWN;
    gpio_initA.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &gpio_initA );

    // I2C1 pins for SDA and SCL
    gpio_initB.GPIO_Mode = GPIO_Mode_AF;
    gpio_initB.GPIO_OType = GPIO_OType_OD;
    gpio_initB.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; // PB8 and PB9
    gpio_initB.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_initB.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &gpio_initB );

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1); // SCL
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1); // SDA
}

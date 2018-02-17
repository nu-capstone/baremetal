#include "stm32f4xx_exti.h"
#include "misc.h"

#include "interrupt.h"

void
interrupt_init( void )
{
    EXTI_InitTypeDef exti_init;
    NVIC_InitTypeDef nvic_init;

    // using PA0 for EXTI_Line0
    SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA, EXTI_PinSource0 );

    exti_init.EXTI_Line = EXTI_Line0;
    exti_init.EXTI_LineCmd = ENABLE;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init( &exti_init );

    // add IRQ for ADPD to NVIC
    nvic_init.NVIC_IRQChannel = EXTI0_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 0x0;
    nvic_init.NVIC_IRQChannelSubPriority = 0x0; // can't be preempted
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &nvic_init );

    nvic_init.NVIC_IRQChannel = USART1_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 0x1;
    nvic_init.NVIC_IRQChannelSubPriority = 0x1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &nvic_init );
}

#include "stm32f4xx_tim.h"

#include "timer.h"

void
timer_init( void )
{
    TIM_TimeBaseInitTypeDef advtimer_init;

    // enable rcc for TIMER1
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );

    advtimer_init.TIM_Prescaler = 10000;
    advtimer_init.TIM_CounterMode = 65565;
    advtimer_init.TIM_Period = TIM_CounterMode_Down;
    advtimer_init.TIM_ClockDivision = 0;
    advtimer_init.TIM_RepetitionCounter = 1;
    TIM_Cmd( TIM1, ENABLE );
    TIM_TimeBaseInit( TIM1, &advtimer_init );
}

#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"

#define I2C_CLOCKSPEED          100000
#define I2C_MODE                I2C_MODE_I2C

#define ADVTIMER_PRESCALER      10000
#define ADVTIMER_PERIOD         65565
#define ADVTIMER_COUNTMODE      TIM_CounterMode_Down
#define ADVTIMER_CLOCKDIV       0
#define ADVTIMER_REPCOUNT       1

/******************************************************************************
 * Configure peripherals
 */
void
config_periphs( void )
{
    I2C_InitTypedef i2c_init;
    I2C_TypeDef i2c;
    TIM_TimeBaseInitTypeDef advtimer_init;
    TIM_TypeDef advtimer;

    // initializing timer
    advtimer_init.TIM_Prescaler = ADVTIMER_PRESCALER;
    advtimer_init.TIM_CounterMode = ADVTIMER_COUNTMODE;
    advtimer_init.TIM_Period = ADVTIMER_PERIOD;
    advtimer_init.TIM_ClockDivision = ADVTIMER_CLOCKDIV;
    advtimer_init.TIM_RepetitionCounter = ADVTIMER_REPCOUNT;
    TIM_TimeBaseInit( &advtimer, &advtimer_init );
    TIM_Cmd( advtimer, ENABLE );


}

/******************************************************************************
 */
int
main( void )
{
    return 0;
}

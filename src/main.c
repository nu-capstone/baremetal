#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_tim.h"

#define I2C_CLOCKSPEED          100000
#define I2C_MODE                I2C_MODE_I2C
#define I2C_DUTYCYCLE           I2C_DutyCycle_2
#define I2C_MASTERADDR          0x0
#define I2C_ACK                 I2C_Ack_Enable
#define I2C_ACKADDR             I2C_AcknowledgedAddress_7bit

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
    I2C_InitTypeDef i2c_init;
    TIM_TimeBaseInitTypeDef advtimer_init;

    // initializing timer
    advtimer_init.TIM_Prescaler = ADVTIMER_PRESCALER;
    advtimer_init.TIM_CounterMode = ADVTIMER_COUNTMODE;
    advtimer_init.TIM_Period = ADVTIMER_PERIOD;
    advtimer_init.TIM_ClockDivision = ADVTIMER_CLOCKDIV;
    advtimer_init.TIM_RepetitionCounter = ADVTIMER_REPCOUNT;
    TIM_Cmd( TIM1, ENABLE );
    TIM_TimeBaseInit( TIM1, &advtimer_init );
    
    // initialize i2c
    i2c_init.I2C_ClockSpeed = I2C_CLOCKSPEED;
    i2c_init.I2C_Mode = I2C_MODE;
    i2c_init.I2C_DutyCycle = I2C_DUTYCYCLE;
    i2c_init.I2C_OwnAddress1 = I2C_MASTERADDR;
    i2c_init.I2C_Ack = I2C_ACK;
    i2c_init.I2C_AcknowledgedAddress = I2C_ACKADDR;
    I2C_Cmd( I2C1, ENABLE );
    I2C_Init( I2C1, &i2c_init );

}

/******************************************************************************
 */
int
main( void )
{
    config_periphs();
    return 0;
}

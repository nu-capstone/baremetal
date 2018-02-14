#include "stm32f4xx_i2c.h"

#include "i2c.h"

void
i2c_init( void )
{
    I2C_InitTypeDef i2c_init;

    i2c_init.I2C_ClockSpeed = 100000;
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_OwnAddress1 = 0x0;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Cmd( I2C1, ENABLE );
    I2C_Init( I2C1, &i2c_init );
}

void
EXTI0_IRQHandler( void )
{
    if ( EXTI_GetITStatus( EXTI_Line0 ) != RESET )
    {
        // do the shit 

        EXTI_ClearITPendingBit( EXTI_Line0 );
    }
}

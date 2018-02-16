#include "stm32f4xx_i2c.h"

#include "i2c.h"

void
i2c_init( void )
{
    I2C_InitTypeDef i2c_init;

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    i2c_init.I2C_ClockSpeed = 100000;
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_OwnAddress1 = 0x0;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Cmd( I2C1, ENABLE );
    I2C_Init( I2C1, &i2c_init );
    I2C_ITConfig( I2C1, I2C_IT_ERR, ENABLE ); // enable error interrupt
}

/******************************************************************************
 */
void I2C1_ER_IRQHandler( void )
{
}

int
i2c_send_start( I2C_TypeDef *I2Cx )
{
    while ( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ))
        ;
    I2C_GenerateSTART( I2Cx, ENABLE );
    while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ))
        ;
}

int
i2c_start( I2C_TypeDef *I2Cx,
           uint8_t slave_addr,
           uint8_t direction )
{
    // wait until not busy
    while ( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
        ;

    I2C_GenerateSTART( I2Cx, ENABLE );
    // wait for SDA to be released (slave is ready)
    while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ))
        ;

    I2C_Send7bitAddress( I2Cx, slave_addr, direction );

    // wait for slave to 
    if ( direction == I2C_Direction_Transmitter )
        while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
            ;
    else if ( direction == I2C_Direction_Receiver )
        while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) )
            ;

    return 0;
}

/******************************************************************************
 * Send one byte and wait for ack
 */
int 
i2c_send( I2C_TypeDef *I2Cx,
          uint8_t data )
{
    I2C_SendData( I2Cx, data );
    
    // wait for ack
    while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
        ;

    return 0;
}

/******************************************************************************
 * Receive byte and send ack
 */
uint8_t
i2c_receive_ack( I2C_TypeDef *I2Cx )
{
    I2C_AcknowledgeConfig( I2Cx, ENABLE );

    while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED ))
        ;

    return I2C_ReceiveData( I2Cx );
}

/******************************************************************************
 * Receive byte and send nack
 */
uint8_t
i2c_receive_nack( I2C_TypeDef *I2Cx )
{
    I2C_AcknowledgeConfig( I2Cx, DISABLE );
    I2C_GenerateSTOP( I2Cx, ENABLE );

    while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED ) )
        ;
    
    return I2C_ReceiveData( I2Cx );
}

/******************************************************************************
 */
int
i2c_stop( I2C_TypeDef *I2Cx )
{
    I2C_GenerateSTOP( I2Cx, ENABLE );
}

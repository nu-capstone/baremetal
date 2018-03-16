#include "stm32f4xx_i2c.h"

#include "adpd.h"
#include "i2c.h"

#define ADPD_SLAVE_ADDR     0x64

/******************************************************************************
 * FIFO data ready interrupt
 */
void
EXTI0_IRQHandler( void )
{
}

/******************************************************************************
 */
int
adpd_init( void )
{
}

/******************************************************************************
 */
int
adpd_start( void )
{
    uint16_t status = adpd_read_1word( 0x4b );
    adpd_write_reg( 0x4b, status | (1 << 7) ); // Enable 32kHz clock for FSM transitions
    adpd_write_reg( 0x10, 0x1 ); // change device to program mode
    // XXX Program configuration registers here
    adpd_write_reg( 0x10, 0x2 ); // start in sampling mode

    return 0;
}

/******************************************************************************
 */
int
adpd_write_reg( uint8_t reg_addr,
                uint16_t data )
{
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Transmitter );
    i2c_send( I2C1, reg_addr );
    i2c_send( I2C1, (uint8_t) (data >> 8) );
    i2c_send( I2C1, (uint8_t) (data & 0xff) );
    i2c_stop( I2C1 );

    return 0;
}

/******************************************************************************
 */
uint16_t
adpd_read_1word( uint8_t reg_addr )
{
    uint16_t word;
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Transmitter );
    i2c_send( I2C1, reg_addr );
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Receiver );
    word = i2c_receive_ack( I2C1 ) << 8;
    word |= i2c_receive_nack( I2C1 );
    i2c_stop( I2C1 );

    return word;
}

/******************************************************************************
 * Length is number of 16-bit words being read
 */
int
adpd_read_words( uint8_t reg_addr,
                 uint16_t *buf,
                 int length )
{ 
    int i = 0;
    uint8_t temp;
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Transmitter );
    i2c_send( I2C1, reg_addr );
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Receiver );
    
    while ( i < length )
    {
        // XXX Do shit here
        buf[i] = i2c_receive_ack( I2C1 ) << 8;

        // if last half-word return nack otherwise return ack
        if ( i == length - 1 )
            buf[i] |= i2c_receive_nack( I2C1 );
        else
            buf[i] |= i2c_receive_ack( I2C1 );

        i++;
    }

    return 0;
}

/******************************************************************************
 */
int
adpd_read_all_regs( uint16_t *buf )
{

}

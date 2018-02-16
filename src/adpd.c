#include "stm32f4xx_i2c.h"

#include "adpd.h"

#define ADPD_SLAVE_ADDR     0x64

int
adpd_write_reg( uint8_t reg_addr,
                uint16_t data )
{
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Transmitter );
    i2c_send( I2C1, reg_addr );
    i2c_send( I2C1, (uint8_t) (data >> 8) );
    i2c_send( I2C1, (uint8_t) (data & 0xff) );
    i2c_stop( I2C1 );
}

uint16_t
adpd_read_1word( uint8_t reg_addr )
{
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Transmitter );
    i2c_send( I2C1, reg_addr );
    i2c_start( I2C1, ADPD_SLAVE_ADDR, I2C_Direction_Receiver );
    i2c_receive_ack( I2C1 );
    i2c_receive_nack( I2C1 );
    i2c_stop( I2C1 );
}

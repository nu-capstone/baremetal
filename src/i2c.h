#ifndef I2C_H
#define I2C_H

#include "stm32f4xx_i2c.h"

void i2c_init( void );
int i2c_send_start( I2C_TypeDef *I2Cx );
int i2c_start( I2C_TypeDef *I2Cx, uint8_t slave_address, uint8_t direction );
int i2c_send( I2C_TypeDef *I2Cx, uint8_t data );
uint8_t i2c_receive_ack( I2C_TypeDef *I2Cx );
uint8_t i2c_receive_nack( I2C_TypeDef *I2Cx );
int i2c_stop( I2C_TypeDef *I2Cx );

#endif // I2C_H

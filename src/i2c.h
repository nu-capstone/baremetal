#ifndef I2C_H
#define I2C_H

#define I2C_BASE_ADDR       0x40005400
#define I2C_CTRL_REG1       ( I2C_BASE_ADDR + 0x0 )
#define I2C_CTRL_REG2       ( I2C_BASE_ADDR + 0x4 )
#define I2C_OAR_REG1        ( I2C_BASE_ADDR + 0x8 )
#define I2C_OAR_REG2        ( I2C_BASE_ADDR + 0xC )
#define I2C_DATA_REG        ( I2C_BASE_ADDR + 0x10 )
#define I2C_STATUS_REG1     ( I2C_BASE_ADDR + 0x14 )
#define I2C_STATUS_REG2     ( I2C_BASE_ADDR + 0x18 )
#define I2C_CLK_CTRL_REG    ( I2C_BASE_ADDR + 0x1C )
#define I2C_TRISE_REG       ( I2C_BASE_ADDR + 0x20 )
#define I2C_FLTR_REG        ( I2C_BASE_ADDR + 0x24 )

int i2c_configure( void );
int i2c_reset( void );
int i2c_send( char *data, int length );
int i2c_receive( char *data, int length );

#endif // I2C_H

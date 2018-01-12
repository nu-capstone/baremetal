/******************************************************************************
 * i2c handling
 */

#include "i2c.h"

/******************************************************************************
 */
static int
i2c_read_reg( int addr )
{
    volatile int *reg_addr = (volatile int *) addr;
    return *reg_addr;
}

/******************************************************************************
 */
static int
i2c_write_reg( int addr,
               int val )
{
    volatile int *reg_addr = (volatile int *) addr;
    *reg_addr = val;

    return 0;
}

/******************************************************************************
 */
int
i2c_configure( void )
{
    // NOTE Some of these might need to be programmed before every transfer
    // XXX Configure peripheral input clock to 4 MHz (fast mode) in I2C_CTRL_REG2
    
    // Configure clock control registers
    
    // Configure rise time register

    // Program I2C_CTRL_REG1 to enable peripheral
}

/******************************************************************************
 */
int
i2c_send( char *data,
          int length )
{
    int reg_data;
    // Remember to write start and stop conditions
    // START condition sets uC to master mode automatically

    // XXX START condition here
    reg_data = i2c_read_reg( I2C_CTRL_REG1 );
    reg_data |= 0x10;
    i2c_write_reg( I2C_CTRL_REG1, reg_data );

    // Read status reg 1 and write slave address to data register
    reg_data = i2c_read_reg( I2C_STATUS_REG1 );
    
    
    // Send slave address and transmit mode (LSB reset)
    
    // Read I2C_STATUS_REG1 and I2C_STATUS_REG2 registers 

}

/******************************************************************************
 */
int
i2c_receive( char *data,
             int length )
{

}

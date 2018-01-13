/******************************************************************************
 * i2c handling
 */

#include "i2c.h"

int
i2c_configure( i2c_t *i2c )
{
    // 16 or 32-bit accesses according to reference manual
    short *regptr;
    // XXX Do some shit before
    
<<<<<<< HEAD
    // Configure clock control registers
    
    // Configure rise time register

    // Program I2C_CTRL_REG1 to enable peripheral
}

/******************************************************************************
 */
int
i2c_send( i2c_t *i2c,
          char *data,
          int length )
{
    int reg_data;
    // Remember to write start and stop conditions
    // START condition sets uC to master mode automatically

    // START condition here
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
i2c_receive( i2c_t *i2c,
             char *data,
             int length )
{
=======
    regptr = (char *) I2C_OAR_REG1;
>>>>>>> parent of 3047f0e... Added adpd105 stuff and i2c stuff

}

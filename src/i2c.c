/******************************************************************************
 * i2c handling
 */

#include "i2c.h"

int
i2c_configure( void )
{
    // 16 or 32-bit accesses according to reference manual
    short *regptr;
    // XXX Do some shit before
    
    regptr = (char *) I2C_OAR_REG1;

}

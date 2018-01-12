#ifndef I2C_H
#define I2C_H

/******************************************************************************
 * Register Addresses
 */
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

/******************************************************************************
 * I2C states
 */
#define I2C_STATE_RESET		        0x00U,   /* Peripheral is not yet Initialized */
#define I2C_STATE_READY             0x20U,   /*!< Peripheral Initialized and ready for use */
#define I2C_STATE_BUSY              0x24U,   /*!< An internal process is ongoing */
#define I2C_STATE_BUSY_TX           0x21U,   /*!< Data Transmission process is ongoing */
#define I2C_STATE_BUSY_RX           0x22U,   /*!< Data Reception process is ongoing */
#define I2C_STATE_LISTEN            0x28U,   /*!< Address Listen Mode is ongoing */
#define I2C_STATE_BUSY_TX_LISTEN    0x29U,   /*!< Address Listen Mode and Data Transmission process is ongoing */
#define I2C_STATE_BUSY_RX_LISTEN    0x2AU,   /*!< Address Listen Mode and Data Reception process is ongoing                         */
#define I2C_STATE_ABORT             0x60U,   /*!< Abort user request ongoing */
#define I2C_STATE_TIMEOUT           0xA0U,   /*!< Timeout state */
#define I2C_STATE_ERROR             0xE0U    /*!< Error */

int i2c_configure( void );
int i2c_reset( void );
int i2c_send( char *data, int length );
int i2c_receive( char *data, int length );

#endif // I2C_H

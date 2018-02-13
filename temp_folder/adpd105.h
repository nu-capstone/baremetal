#ifndef ADPD105_H
#define ADPD105_H

#include <stdint.h>

/******************************************************************************
 * ADPD105 interfacing
 */

#define ADPD105_ADDR        0x64 // XXX Check this

/******************************************************************************
 * Register addresses
 */
#define AFE_STATUS_REG              0x0
#define AFE_INT_MASK_REG            0x1
#define AFE_GPIO_DRV_REG            0x2
#define AFE_FIFO_THRESH_REG         0x6
#define AFE_DEVID_REG               0x8
#define AFE_I2CS_ID_REG             0x9
#define AFE_CLK_RATIO_REG           0xa
#define AFE_GPIO_CTRL_REG           0xb
#define AFE_SLV_ADDR_KEY_REG        0xd
#define AFE_SW_RESET_REG            0xf
#define AFE_MODE_REG                0x10
#define AFE_SLOT_EN_REG             0x11
#define AFE_FSAMPLE_REG             0x12
#define AFE_PD_LED_SEL_REG          0x14
#define AFE_NUM_AVG_REG             0x15
#define AFE_SLOTA_CH1_OFFSET_REG    0x18
#define AFE_SLOTA_CH2_OFFSET_REG    0x19
#define AFE_SLOTA_CH3_OFFSET_REG    0x1a
#define AFE_SLOTA_CH4_OFFSET_REG    0x1b
#define AFE_SLOTB_CH1_OFFSET_REG    0x1e
#define AFE_SLOTB_CH2_OFFSET_REG    0x1f
#define AFE_SLOTB_CH3_OFFSET_REG    0x20
#define AFE_SLOTB_CH4_OFFSET_REG    0x21
#define AFE_ILED3_COARD_REG         0x22
#define AFE_ILED1_COARD_REG         0x23
#define AFE_ILED2_COARD_REG         0x24
#define AFE_ILED_FINE_REG           0x25
#define AFE_SLOTA_LED_PULSE_REG     0x30
#define AFE_SLOTA_NUM_PULSE_REG     0x31
#define AFE_LED_DISABLE_REG         0x34
#define AFE_SLOTB_LED_PULSE_REG     0x35
#define AFE_SLOTB_NUM_PULSE_REG     0x36
#define AFE_ALT_PWR_DN_REG          0x37
#define AFE_EXT_SYNC_STARTUP_REG    0x38
#define AFE_SLOTA_AFE_WINDOW_REG    0x39
#define AFE_SLOTB_AFE_WINDOW_REG    0x3b
#define AFE_PWR_CFG1_REG            0x3c
#define AFE_SLOTA_TIA_CFG_REG       0x42
#define AFE_SLOTA_AFE_CFG_REG       0x43
#define AFE_SLOTB_AFE_CFG_REG       0x44
#define AFE_SLOTB_TIA_CFG_REG       0x45
#define AFE_SAMPLE_CLK_REG          0x4b
#define AFE_CLK32M_ADJUST_REG       0x4d
#define AFE_ADC_CLOCK_REG           0x4e
#define AFE_EXY_SYNC_SEL_REG        0x4f
#define AFE_CLK32M_CAL_EN_REG       0x50
#define AFE_PWR_CFG2_REG            0x52
#define AFE_TIA_INDEP_GAIN_REG      0x55
#define AFE_DIGITAL_INT_EN_REG      0x58
#define AFE_DIG_INT_CFG_REG         0x5a
#define AFE_DATA_ACCESS_CTL_REG     0x5f
#define AFE_FIFO_ACCESS_REG         0x60
#define AFE_SLOTA_PD1_16BIT_REG     0x64
#define AFE_SLOTA_PD2_16BIT_REG     0x65
#define AFE_SLOTA_PD3_16BIT_REG     0x66
#define AFE_SLOTA_PD4_16BIT_REG     0x67
#define AFE_SLOTB_PD1_16BIT_REG     0x68
#define AFE_SLOTB_PD2_16BIT_REG     0x69
#define AFE_SLOTB_PD3_16BIT_REG     0x6a
#define AFE_SLOTB_PD4_16BIT_REG     0x6b
#define AFE_A_PD1_LOW_REG           0x70
#define AFE_A_PD2_LOW_REG           0x71
#define AFE_A_PD3_LOW_REG           0x72
#define AFE_A_PD4_LOW_REG           0x73
#define AFE_A_PD1_HIGH_REG          0x74
#define AFE_A_PD2_HIGH_REG          0x75
#define AFE_A_PD3_HIGH_REG          0x76
#define AFE_A_PD4_HIGH_REG          0x77
#define AFE_B_PD1_LOW_REG           0x78
#define AFE_B_PD2_LOW_REG           0x79
#define AFE_B_PD3_LOW_REG           0x7a
#define AFE_B_PD4_LOW_REG           0x7b
#define AFE_B_PD1_HIGH_REG          0x7c
#define AFE_B_PD2_HIGH_REG          0x7d
#define AFE_B_PD3_HIGH_REG          0x7e
#define AFE_B_PD4_HIGH_REG          0x7f

/******************************************************************************
 * Functions
 */

int afe_set_led_offset( uint8_t val );
int afe_set_led_width( uint8_t val );
int afe_set_led_period( uint8_t val );
int afe_set_led_pulses_n( uint8_t val );
int afe_set_afe_offset( uint32_t val );
int afe_set_afe_width( uint16_t val );

#endif // ADPD105_h

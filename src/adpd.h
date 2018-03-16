#ifndef ADPD_H
#define ADPD_H

void EXTI0_IRQHandler( void ); // isr for adpd
int adpd_init( void );
int adpd_start( void );
int adpd_write_reg( uint8_t reg_addr, uint16_t data );
uint16_t adpd_read_1word( uint8_t reg_addr );
int adpd_read_words( uint8_t reg_addr, uint16_t *buf, int length );

#endif // ADPD_H

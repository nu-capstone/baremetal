#ifndef IRQ_HANDLERS_H
#define IRQ_HANDLERS_H

#include "stm32f4xx.h"

void register_isr( IRQn_Type irq_num, void ( fn* )(void) );
void timer2_isr( void );

#endif

#ifndef __STC89C51_IT_H
#define __STC89C51_IT_H

#include "stc89c51.h"


/*---- Interrupt servicing function prototype ----*/

void EXIT0_IRQHandler(void);
void TIM0_IRQHandler(void);
void EXIT1_IRQHandler(void);
void TIM1_IRQHandler(void);
void UART_IRQHandler(void);
void TIM2_IRQHandler(void);

#endif


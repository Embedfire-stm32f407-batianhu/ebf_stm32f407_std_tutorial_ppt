#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

void Delay_ms(__IO u32 nTime);
void SysTick_Init(void);
void SysTick_Delay_Ms( __IO uint32_t ms);

#endif /* __SYSTICK_H */


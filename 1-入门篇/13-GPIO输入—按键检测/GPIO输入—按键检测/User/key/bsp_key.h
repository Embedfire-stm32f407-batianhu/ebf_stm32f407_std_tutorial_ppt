#ifndef _BSP_KEY_H 
#define _BSP_KEY_H 

#include "stm32f4xx.h"

#define KEY_ON      1
#define KEY_OFF      0

void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif  /* _BSP_KEY_H */



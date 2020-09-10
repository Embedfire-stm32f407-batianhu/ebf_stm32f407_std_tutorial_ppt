#include "stm32f4xx_gpio.h"

void GPIO_SetBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRL = GPIO_Pin;
}

void GPIO_ResetBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRH = GPIO_Pin;
}


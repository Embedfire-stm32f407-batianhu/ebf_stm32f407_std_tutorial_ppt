#ifndef __STM32F10X_GPIO_H
#define __STM32F10X_GPIO_H

#include "stm32f10x.h"

#define GPIO_Pin_0        ((uint16_t)(1<<0))
#define GPIO_Pin_1        ((uint16_t)(1<<1))
#define GPIO_Pin_2        ((uint16_t)(1<<2))
#define GPIO_Pin_3        ((uint16_t)(1<<3))
#define GPIO_Pin_4        ((uint16_t)(1<<4))
#define GPIO_Pin_5        ((uint16_t)(1<<5))
#define GPIO_Pin_6        ((uint16_t)(1<<6))
#define GPIO_Pin_7        ((uint16_t)(1<<7))
#define GPIO_Pin_8        ((uint16_t)(1<<8))
#define GPIO_Pin_9        ((uint16_t)(1<<9))
#define GPIO_Pin_10       ((uint16_t)(1<<10))
#define GPIO_Pin_11       ((uint16_t)(1<<11))
#define GPIO_Pin_12       ((uint16_t)(1<<12))
#define GPIO_Pin_13       ((uint16_t)(1<<13))
#define GPIO_Pin_14       ((uint16_t)(1<<14))
#define GPIO_Pin_15       ((uint16_t)(1<<15)
#define GPIO_Pin_All      ((uint16_t)0xffff)

typedef enum
{
	GPIO_Speed_10MHZ = 1,
	GPIO_Speed_2MHZ,
	GPIO_Speed_50MHZ	
}GPIOSpeed_TypeDef;

typedef enum
{ GPIO_Mode_AIN = 0x0,           // ģ������     (0000 0000)b
  GPIO_Mode_IN_FLOATING = 0x04,  // ��������     (0000 0100)b
  GPIO_Mode_IPD = 0x28,          // ��������     (0010 1000)b
  GPIO_Mode_IPU = 0x48,          // ��������     (0100 1000)b
  
  GPIO_Mode_Out_OD = 0x14,       // ��©���     (0001 0100)b
  GPIO_Mode_Out_PP = 0x10,       // �������     (0001 0000)b
  GPIO_Mode_AF_OD = 0x1C,        // ���ÿ�©��� (0001 1100)b
  GPIO_Mode_AF_PP = 0x18         // ����������� (0001 1000)b
}GPIOMode_TypeDef;

typedef struct
{
	uint16_t GPIO_Pin;
	GPIOSpeed_TypeDef GPIO_Speed;
	GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;



void GPIO_SetBits( GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void GPIO_RetsetBits( GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

#endif /* __STM32F10X_GPIO_H */


#ifndef _STM32F4XX_GPIO_H
#define _STM32F4XX_GPIO_H

#include "stm32f4xx.h"

#define    GPIO_Pin_0          ( (uint16_t )(1<<0) )
#define    GPIO_Pin_1          ( (uint16_t )(1<<1) )
#define    GPIO_Pin_2          ( (uint16_t )(1<<2) )
#define    GPIO_Pin_3          ( (uint16_t )(1<<3) )
#define    GPIO_Pin_4          ( (uint16_t )(1<<4) )
#define    GPIO_Pin_5          ( (uint16_t )(1<<5) )
#define    GPIO_Pin_6          ( (uint16_t )(1<<6) )
#define    GPIO_Pin_7          ( (uint16_t )(1<<7) )
#define    GPIO_Pin_8          ( (uint16_t )(1<<8) )
#define    GPIO_Pin_9          ( (uint16_t )(1<<9) )
#define    GPIO_Pin_10         ( (uint16_t )(1<<10) )
#define    GPIO_Pin_11         ( (uint16_t )(1<<11) )
#define    GPIO_Pin_12         ( (uint16_t )(1<<12) )
#define    GPIO_Pin_13         ( (uint16_t )(1<<13) )
#define    GPIO_Pin_14         ( (uint16_t )(1<<14) )
#define    GPIO_Pin_15         ( (uint16_t )(1<<15) )
#define    GPIO_Pin_All        ( (uint16_t )(0xffff) )

typedef enum
{
	GPIO_Mode_IN = 0X00,
	GPIO_Mode_OUT = 0X01,
	GPIO_Mode_AF = 0X02,
	GPIO_Mode_AN = 0X03
}GPIOMode_TypeDef;

typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01, 
  GPIO_PuPd_DOWN   = 0x02  
}GPIOPuPd_TypeDef;

typedef enum
{ 
  GPIO_OType_PP = 0x00,	
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;

typedef enum
{ 
  GPIO_Speed_2MHz   = 0x00, 
  GPIO_Speed_25MHz  = 0x01,
  GPIO_Speed_50MHz  = 0x02, 
  GPIO_Speed_100MHz = 0x03 
}GPIOSpeed_TypeDef;

/* 定义GPIO的初始化结构体 */
typedef struct
{
	uint16_t          GPIO_Pin;
	GPIOMode_TypeDef  GPIO_Mode;
	GPIOPuPd_TypeDef  GPIO_PuPd;
	GPIOOType_TypeDef GPIO_OType;	
	GPIOSpeed_TypeDef GPIO_Speed;	
}GPIO_InitTypeDef;


void GPIO_SetBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

#endif /* _STM32F4XX_GPIO_H */


#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define YHMINI   1
#define YHIOT    0

#if YHMINI
#define  LED1_GPIO_CLK         RCC_APB2Periph_GPIOC
#define  LED1_GPIO_PORT        GPIOC
#define  LED1_GPIO_PIN         GPIO_Pin_2

#define  LED2_GPIO_CLK         RCC_APB2Periph_GPIOC
#define  LED2_GPIO_PORT        GPIOC
#define  LED2_GPIO_PIN         GPIO_Pin_3

#elif YHIOT
#define  LED1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define  LED1_GPIO_PORT        GPIOB
#define  LED1_GPIO_PIN         GPIO_Pin_0

#define  LED2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define  LED2_GPIO_PORT        GPIOB
#define  LED2_GPIO_PIN         GPIO_Pin_1

#endif 

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_TOGGLE		 digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_OFF		   digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_ON			   digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)

void LED_GPIO_Config(void);


#endif /* __BSP_LED_H */


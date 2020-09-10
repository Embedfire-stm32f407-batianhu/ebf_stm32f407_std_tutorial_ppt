#ifndef _STM32F4XX_H
#define _STM32F4XX_H

#include <stdint.h>

/*  用来存放寄存器映射相关的代码 */

#define GPIOF_BASE    (( unsigned int )0x40021400)
#define RCC_BASE      (( unsigned int )0x40023800) 	
	
#define GPIOF_MODER   *(unsigned int *)(GPIOF_BASE+0X00)
#define GPIOF_OTYPER  *(unsigned int *)(GPIOF_BASE+0X04)
#define GPIOF_ODR     *(unsigned int *)(GPIOF_BASE+0X14)

#define RCC_AHB1ENR   *(unsigned int *)(RCC_BASE+0X30)


/* 外设寄存器结构体定义 */
//typedef unsigned int       uint32_t;
//typedef unsigned short int uint16_t;
typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint16_t BSRRL;
	uint16_t BSRRH;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
}GPIO_TypeDef;


#define GPIOF           ((GPIO_TypeDef *)GPIOF_BASE)



#endif /* _STM32F4XX_H */


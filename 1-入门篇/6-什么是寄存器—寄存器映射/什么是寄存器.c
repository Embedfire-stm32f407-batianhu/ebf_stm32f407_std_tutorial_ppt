/*=====================寄存器映射===========================*/
/* 51里面让PA口输出高电平 */
#include <reg51.h>
sfr PA0 0X80

PA0 = 0XFF;



/* STM32 里面让 PF口输出高电平 */

/* 寄存器映射 */

/*
 * 寄存器映射就是对芯片里面的某一个具有特殊功能的内存单元
 * 取一个别名的过程就叫做寄存器映射。
 */

*( unsigned int  *)0x40021414 = 0xFFFF;
#define GPIOF_ODR  *( unsigned int  *)0x40021414

GPIOF_ODR = 0XFFFF;

/*======================== C 语言 对寄存器的封装===================== */
#define GPIOF_BASE      (0x40021400)

#define GPIOF_MODER     *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_OTYPER    *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_OSPEEDR   *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_PUPDR     *( unsigned int  *)GPIOF_BASE+0X00)
#define GPIOF_IDR       *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_ODR       *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_BSRR      *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_LCKR      *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_AFRL      *( unsigned int  *)(GPIOF_BASE+0X00)
#define GPIOF_AFRH      *( unsigned int  *)(GPIOF_BASE+0X00)


typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;

typedef struct
{	
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint16_t AFRL;
	uint16_t AFRH;	
}GPIO_TypeDef;

#define GPIOA_BASE      (0x40020000)
#define GPIOB_BASE      (0x40020400)
#define GPIOC_BASE      (0x40020800)
#define GPIOD_BASE      (0x40020C00)
#define GPIOE_BASE      (0x40021000)
#define GPIOF_BASE      (0x40021400)


#define GPIOA      (GPIO_TypeDef *)GPIOA_BASE
#define GPIOB      (GPIO_TypeDef *)GPIOB_BASE
#define GPIOC      (GPIO_TypeDef *)GPIOC_BASE
#define GPIOD      (GPIO_TypeDef *)GPIOD_BASE
#define GPIOE      (GPIO_TypeDef *)GPIOE_BASE
#define GPIOF      (GPIO_TypeDef *)GPIOF_BASE


GPIOF->ODR = 0XFFFF;
















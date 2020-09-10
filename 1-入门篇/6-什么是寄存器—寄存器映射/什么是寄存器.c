/*=====================�Ĵ���ӳ��===========================*/
/* 51������PA������ߵ�ƽ */
#include <reg51.h>
sfr PA0 0X80

PA0 = 0XFF;



/* STM32 ������ PF������ߵ�ƽ */

/* �Ĵ���ӳ�� */

/*
 * �Ĵ���ӳ����Ƕ�оƬ�����ĳһ���������⹦�ܵ��ڴ浥Ԫ
 * ȡһ�������Ĺ��̾ͽ����Ĵ���ӳ�䡣
 */

*( unsigned int  *)0x40021414 = 0xFFFF;
#define GPIOF_ODR  *( unsigned int  *)0x40021414

GPIOF_ODR = 0XFFFF;

/*======================== C ���� �ԼĴ����ķ�װ===================== */
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
















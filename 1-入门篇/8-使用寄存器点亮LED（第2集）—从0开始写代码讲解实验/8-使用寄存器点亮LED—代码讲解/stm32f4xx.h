/*  用来存放寄存器映射相关的代码 */

#define GPIOF_BASE    (( unsigned int )0x40021400)
#define RCC_BASE      (( unsigned int )0x40023800) 	
	
#define GPIOF_MODER   *(unsigned int *)(GPIOF_BASE+0X00)
#define GPIOF_OTYPER  *(unsigned int *)(GPIOF_BASE+0X04)
#define GPIOF_ODR     *(unsigned int *)(GPIOF_BASE+0X14)

#define RCC_AHB1ENR   *(unsigned int *)(RCC_BASE+0X30)



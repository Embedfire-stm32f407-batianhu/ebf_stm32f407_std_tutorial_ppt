/*  用来存放寄存器映射相关的代码 */

#define RCC_AHB1ENR   *( unsigned int *)(0x40023800+0x30)
#define GPIOF_MODER   *( unsigned int *)(0x40021400+0x00)	
#define GPIOF_ODR     *( unsigned int *)(0x40021400+0x14)
	

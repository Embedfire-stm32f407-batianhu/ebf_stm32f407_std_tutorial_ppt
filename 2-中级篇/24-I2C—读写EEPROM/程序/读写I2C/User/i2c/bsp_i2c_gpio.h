#ifndef __BSP_I2C_GPIO_H
#define	__BSP_I2C_GPIO_H


#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define I2C_SCL_GPIO_PORT    	GPIOA		              /* GPIO�˿� */
#define I2C_SCL_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define I2C_SCL_GPIO_PIN			GPIO_Pin_2			        

#define I2C_SDA_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define I2C_SDA_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define I2C_SDA_GPIO_PIN			GPIO_Pin_3			        

//�������ŵ�ƽ
#if 1

	#define EEPROM_I2C_SDA_1()		GPIO_SetBits(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)
	#define EEPROM_I2C_SDA_0()		GPIO_ResetBits(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)

	#define EEPROM_I2C_SCL_1()		GPIO_SetBits(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN)
	#define EEPROM_I2C_SCL_0()		GPIO_ResetBits(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN)

	#define EEPROM_I2C_SDA_READ() GPIO_ReadInputDataBit(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)

#else

	#define EEPROM_I2C_SDA_1()		I2C_SDA_GPIO_PORT->BSRR = I2C_SDA_GPIO_PIN  //GPIO_SetBits(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)
	#define EEPROM_I2C_SDA_0()		I2C_SDA_GPIO_PORT->BRR = I2C_SDA_GPIO_PIN //GPIO_ResetBits(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)

	#define EEPROM_I2C_SCL_1()		I2C_SCL_GPIO_PORT->BSRR = I2C_SCL_GPIO_PIN//GPIO_SetBits(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN)
	#define EEPROM_I2C_SCL_0()		I2C_SCL_GPIO_PORT->BRR = I2C_SCL_GPIO_PIN //GPIO_ResetBits(I2C_SCL_GPIO_PORT,I2C_SCL_GPIO_PIN)

	#define EEPROM_I2C_SDA_READ() 	((I2C_SDA_GPIO_PORT->IDR & I2C_SDA_GPIO_PIN) != 0) //GPIO_ReadInputDataBit(I2C_SDA_GPIO_PORT,I2C_SDA_GPIO_PIN)

#endif

void i2c_GPIO_Config(void);
void i2c_START(void);
uint8_t i2c_WAIT_ASK(void);
void i2c_WRITE_BYTE(uint8_t data);
void i2c_STOP(void);
void i2c_NASK(void);
uint8_t i2c_READ_BYTE(void);
void i2c_ASK(void);

#endif /* __BSP_I2C_GPIO_H */

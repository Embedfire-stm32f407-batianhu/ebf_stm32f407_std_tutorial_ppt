#ifndef __BSP_I2C_EE_H
#define	__BSP_I2C_EE_H

#include "stm32f4xx.h"
#include <stdio.h>


//Òý½Å¶¨Òå
/*******************************************************/
#define EEPROM_PAGE_SIZE						8

#define EEPROM_I2C_ADDR							0xA0
#define STM32_I2C_OWN_ADDR						0x78

#define EEPROM_I2C                             	I2C1
#define EEPROM_I2C_CLK                         	RCC_APB1Periph_I2C1
#define EEPROM_I2C_BAUDRATE                    	400000  

#define EEPROM_I2C_SCL_GPIO_PORT                GPIOB
#define EEPROM_I2C_SCL_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define EEPROM_I2C_SCL_PIN                      GPIO_Pin_8
#define EEPROM_I2C_SCL_AF                       GPIO_AF_I2C1
#define EEPROM_I2C_SCL_SOURCE                   GPIO_PinSource8

#define EEPROM_I2C_SDA_GPIO_PORT                GPIOB
#define EEPROM_I2C_SDA_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define EEPROM_I2C_SDA_PIN                      GPIO_Pin_9
#define EEPROM_I2C_SDA_AF                       GPIO_AF_I2C1
#define EEPROM_I2C_SDA_SOURCE                   GPIO_PinSource9


/************************************************************/

void EEPROM_I2C_Config(void);
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data);
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data);
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t size);
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size);
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t* data, uint16_t size);
uint8_t Wait_For_Standby(void);
#endif /* __BSP_I2C_EE_H */

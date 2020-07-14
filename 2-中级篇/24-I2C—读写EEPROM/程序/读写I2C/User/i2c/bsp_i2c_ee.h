#ifndef __BSP_I2C_EE_H
#define	__BSP_I2C_EE_H


#include "stm32f10x.h"


#define EEPROM_READ_DIR 		0x01
#define EEPROM_WRITE_DIR 		0x00

#define EEPROM_ADDR					0xA0


uint8_t ee_CHECK_DEVICE(uint8_t addr);
uint8_t ee_WRITE_BYTES(uint8_t w_addr,uint8_t *data,uint16_t size);
uint8_t ee_READ_BYTES(uint8_t r_addr,uint8_t *data,uint16_t size);

#endif /* __BSP_I2C_EE_H */

#ifndef __BSP_SPI_FLASH_H
#define	__BSP_SPI_FLASH_H


#include "stm32f10x.h"
#include <stdio.h>


	
// SPI接口号
#define  SPI_FLASHx                   SPI1
#define  SPI_FLASH_CLK                RCC_APB2Periph_SPI1
#define  SPI_FLASH_APBxClkCmd         RCC_APB2PeriphClockCmd


// SPI GPIO 引脚宏定义
#define  SPI_FLASH_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  SPI_FLASH_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  SPI_FLASH_SCK_GPIO_PORT       GPIOA   
#define  SPI_FLASH_SCK_GPIO_PIN        GPIO_Pin_5

#define  SPI_FLASH_MOSI_GPIO_PORT       GPIOA
#define  SPI_FLASH_MOSI_GPIO_PIN        GPIO_Pin_7

#define  SPI_FLASH_MISO_GPIO_PORT       GPIOA
#define  SPI_FLASH_MISO_GPIO_PIN        GPIO_Pin_6

#define  SPI_FLASH_CS_GPIO_PORT       GPIOA
#define  SPI_FLASH_CS_GPIO_PIN        GPIO_Pin_4

#define  SPI_FLASH_CS_LOW()			GPIO_ResetBits(SPI_FLASH_CS_GPIO_PORT,SPI_FLASH_CS_GPIO_PIN);
#define  SPI_FLASH_CS_HIGH()		GPIO_SetBits(SPI_FLASH_CS_GPIO_PORT,SPI_FLASH_CS_GPIO_PIN);


#define  SPI_FLASH_WAIT_TIMEOUT     10000


/*命令定义-开头*******************************/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F

void SPI_GPIO_Config(void);
uint32_t SPI_FLASH_Read_JEDEC_ID(void);
void SPI_FLASH_Erase_Sector(uint32_t addr);
void SPI_FLASH_Read_Buffer(uint32_t addr,uint8_t *data,uint32_t size);
void SPI_FLASH_Page_Write(uint32_t addr,uint8_t *data,uint32_t size);
void SPI_FLASH_Write_Buff(uint32_t addr,uint8_t *data,uint32_t size);



#endif /* __BSP_SPI_FLASH_H */

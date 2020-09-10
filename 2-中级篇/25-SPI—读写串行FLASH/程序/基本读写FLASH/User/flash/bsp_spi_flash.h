#ifndef __SPI_FLASH_H
#define	__SPI_FLASH_H

#include "stm32f4xx.h"

#define DUMMY  0xFF

/*命令定义-开头*******************************/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		  0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	  0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 


/*SPI接口*/
#define FLASH_SPI                          	SPI1
#define FLASH_SPI_CLK                       RCC_APB2Periph_SPI1
#define FLASH_SPI_CLK_INIT									RCC_APB2PeriphClockCmd

#define FLASH_SPI_SCK_PIN                  GPIO_Pin_3                 
#define FLASH_SPI_SCK_GPIO_PORT            GPIOB                       
#define FLASH_SPI_SCK_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define FLASH_SPI_SCK_SOURCE               GPIO_PinSource3
#define FLASH_SPI_SCK_AF                   GPIO_AF_SPI1

#define FLASH_SPI_MOSI_PIN                  GPIO_Pin_5                
#define FLASH_SPI_MOSI_GPIO_PORT            GPIOB                       
#define FLASH_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define FLASH_SPI_MOSI_SOURCE               GPIO_PinSource5
#define FLASH_SPI_MOSI_AF                   GPIO_AF_SPI1

#define FLASH_SPI_MISO_PIN                  GPIO_Pin_4                
#define FLASH_SPI_MISO_GPIO_PORT            GPIOB                       
#define FLASH_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define FLASH_SPI_MISO_SOURCE               GPIO_PinSource4
#define FLASH_SPI_MISO_AF                   GPIO_AF_SPI1

#define FLASH_SPI_CS_PIN                  GPIO_Pin_6               
#define FLASH_SPI_CS_GPIO_PORT            GPIOG                      
#define FLASH_SPI_CS_GPIO_CLK             RCC_AHB1Periph_GPIOG

#define FLASH_SPI_CS_LOW()								GPIO_ResetBits(FLASH_SPI_CS_GPIO_PORT,FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_HIGH()								GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT,FLASH_SPI_CS_PIN)

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define FLASH_DEBUG_ON         0

#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)



void SPI_FLASH_Init(void);
uint8_t SPI_FLASH_Read_ID(void);
void SPI_FLASH_Write_Enable(void);
void SPI_FLASH_Erase_Sector(uint32_t addr);
void SPI_FLASH_Wait_For_Standby(void);
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size);
void SPI_FLASH_Write_Buff(uint32_t addr, uint8_t *buf, uint32_t size);

#endif /* __SPI_FLASH_H */

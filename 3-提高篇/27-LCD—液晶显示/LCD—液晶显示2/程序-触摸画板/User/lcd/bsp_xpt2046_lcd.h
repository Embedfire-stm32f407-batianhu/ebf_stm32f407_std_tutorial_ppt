#ifndef __XPT_2046_H
#define __XPT_2046_H

#include "stm32f10x.h"
#include <stdio.h>



/*SPI接口定义-开头****************************/

//CS(NSS)引脚 片选选普通GPIO即可
#define      XPT2046_SPI_CS_CLK                  RCC_APB2Periph_GPIOC    
#define      XPT2046_SPI_CS_PORT                 GPIOC
#define      XPT2046_SPI_CS_PIN                  GPIO_Pin_9

//SCK引脚
#define      XPT2046_SPI_SCK_CLK                 RCC_APB2Periph_GPIOC   
#define      XPT2046_SPI_SCK_PORT                GPIOC   
#define      XPT2046_SPI_SCK_PIN                 GPIO_Pin_8

//MOSI引脚
#define      XPT2046_SPI_MOSI_CLK                RCC_APB2Periph_GPIOC   
#define      XPT2046_SPI_MOSI_PORT               GPIOC
#define      XPT2046_SPI_MOSI_PIN                GPIO_Pin_10


//MISO引脚
#define      XPT2046_SPI_MISO_CLK                RCC_APB2Periph_GPIOC    
#define      XPT2046_SPI_MISO_PORT               GPIOC
#define      XPT2046_SPI_MISO_PIN                GPIO_Pin_11


//INT引脚
#define      XPT2046_INT_CLK                			RCC_APB2Periph_GPIOC    
#define      XPT2046_INT_PORT               			GPIOC 
#define      XPT2046_INT_PIN                			GPIO_Pin_12


#define  		SPI_XPT2046_CS_LOW()     						GPIO_ResetBits( XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN )
#define  		SPI_XPT2046_CS_HIGH()    						GPIO_SetBits( XPT2046_SPI_CS_PORT, XPT2046_SPI_CS_PIN )

#define  		SPI_XPT2046_SCK_LOW()     						GPIO_ResetBits( XPT2046_SPI_SCK_PORT, XPT2046_SPI_SCK_PIN )
#define  		SPI_XPT2046_SCK_HIGH()    						GPIO_SetBits( XPT2046_SPI_SCK_PORT, XPT2046_SPI_SCK_PIN )

#define  		SPI_XPT2046_MOSI_LOW()     						GPIO_ResetBits( XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN )
#define  		SPI_XPT2046_MOSI_HIGH()    						GPIO_SetBits( XPT2046_SPI_MOSI_PORT, XPT2046_SPI_MOSI_PIN )

#define  		SPI_XPT2046_MISO()     								GPIO_ReadInputDataBit( XPT2046_SPI_MISO_PORT, XPT2046_SPI_MISO_PIN )
#define  		SPI_XPT2046_INT()     								GPIO_ReadInputDataBit( XPT2046_INT_PORT, XPT2046_INT_PIN )


/*控制字***************************/
#define	  XPT2046_CHANNEL_X 	         0x90 	         //通道Y+的选择控制字	
#define	  XPT2046_CHANNEL_Y 	         0xd0	          //通道X+的选择控制字


/*信息输出*/
#define XPT2046_DEBUG_ON         1

#define XPT2046_INFO(fmt,arg...)           printf("<<-XPT2046-INFO->> "fmt"\n",##arg)
#define XPT2046_ERROR(fmt,arg...)          printf("<<-XPT2046-ERROR->> "fmt"\n",##arg)
#define XPT2046_DEBUG(fmt,arg...)          do{\
                                          if(XPT2046_DEBUG_ON)\
                                          printf("<<-XPT2046-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\

																					

																					
void XPT2046_GPIO_Init(void);   	
uint16_t XPT2046_Read_adc(uint8_t cmd);

#endif /* __XPT_2046_H */



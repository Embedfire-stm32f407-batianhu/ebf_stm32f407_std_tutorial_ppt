#ifndef __XPT_2046_H
#define __XPT_2046_H

#include "stm32f10x.h"
#include <stdio.h>



/*SPI�ӿڶ���-��ͷ****************************/

//CS(NSS)���� Ƭѡѡ��ͨGPIO����
#define      XPT2046_SPI_CS_CLK                  RCC_APB2Periph_GPIOC    
#define      XPT2046_SPI_CS_PORT                 GPIOC
#define      XPT2046_SPI_CS_PIN                  GPIO_Pin_9

//SCK����
#define      XPT2046_SPI_SCK_CLK                 RCC_APB2Periph_GPIOC   
#define      XPT2046_SPI_SCK_PORT                GPIOC   
#define      XPT2046_SPI_SCK_PIN                 GPIO_Pin_8

//MOSI����
#define      XPT2046_SPI_MOSI_CLK                RCC_APB2Periph_GPIOC   
#define      XPT2046_SPI_MOSI_PORT               GPIOC
#define      XPT2046_SPI_MOSI_PIN                GPIO_Pin_10


//MISO����
#define      XPT2046_SPI_MISO_CLK                RCC_APB2Periph_GPIOC    
#define      XPT2046_SPI_MISO_PORT               GPIOC
#define      XPT2046_SPI_MISO_PIN                GPIO_Pin_11


//INT����
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


/*������***************************/
#define	  XPT2046_CHANNEL_X 	         0x90 	         //ͨ��Y+��ѡ�������	
#define	  XPT2046_CHANNEL_Y 	         0xd0	          //ͨ��X+��ѡ�������


/*��Ϣ���*/
#define XPT2046_DEBUG_ON         1

#define XPT2046_INFO(fmt,arg...)           printf("<<-XPT2046-INFO->> "fmt"\n",##arg)
#define XPT2046_ERROR(fmt,arg...)          printf("<<-XPT2046-ERROR->> "fmt"\n",##arg)
#define XPT2046_DEBUG(fmt,arg...)          do{\
                                          if(XPT2046_DEBUG_ON)\
                                          printf("<<-XPT2046-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\

																					

																					
void XPT2046_GPIO_Init(void);   	
uint16_t XPT2046_Read_adc(uint8_t cmd);

#endif /* __XPT_2046_H */



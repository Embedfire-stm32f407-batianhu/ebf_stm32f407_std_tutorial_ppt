#ifndef __BSP_ILI9341_LCD_H
#define __BSP_ILI9341_LCD_H

#include "stm32f10x.h"
#include <stdio.h>





//CS(NSS)���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_CS_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_CS_PORT                 GPIOC
#define      ILI9341_CS_PIN                  GPIO_Pin_4

//RD���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_RD_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_RD_PORT                 GPIOC
#define      ILI9341_RD_PIN                  GPIO_Pin_5

//WE���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_WE_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_WE_PORT                 GPIOC
#define      ILI9341_WE_PIN                  GPIO_Pin_6

//DC���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_DC_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_DC_PORT                 GPIOC
#define      ILI9341_DC_PIN                  GPIO_Pin_7

//BK���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_BK_CLK                  RCC_APB2Periph_GPIOD  
#define      ILI9341_BK_PORT                 GPIOD
#define      ILI9341_BK_PIN                  GPIO_Pin_2

//D0-D15���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_DATA_CLK                  RCC_APB2Periph_GPIOB   
#define      ILI9341_DATA_PORT                 GPIOB
#define      ILI9341_DATA_PIN                  GPIO_Pin_All

#define  		LCD_BK_ON()     						GPIO_ResetBits( ILI9341_BK_PORT, ILI9341_BK_PIN )
#define  		LCD_BK_OFF()    						GPIO_SetBits( ILI9341_BK_PORT, ILI9341_BK_PIN )

#define  		LCD_CS_HIGH()     					GPIO_SetBits( ILI9341_CS_PORT, ILI9341_CS_PIN )
#define  		LCD_CS_LOW()    						GPIO_ResetBits( ILI9341_CS_PORT, ILI9341_CS_PIN )

#define  		LCD_DC_HIGH()     					GPIO_SetBits( ILI9341_DC_PORT, ILI9341_DC_PIN )
#define  		LCD_DC_LOW()    						GPIO_ResetBits( ILI9341_DC_PORT, ILI9341_DC_PIN )

#define  		LCD_WE_HIGH()     					GPIO_SetBits( ILI9341_WE_PORT, ILI9341_WE_PIN )
#define  		LCD_WE_LOW()    						GPIO_ResetBits( ILI9341_WE_PORT, ILI9341_WE_PIN )

#define  		LCD_RD_HIGH()     					GPIO_SetBits( ILI9341_RD_PORT, ILI9341_RD_PIN )
#define  		LCD_RD_LOW()    						GPIO_ResetBits( ILI9341_RD_PORT, ILI9341_RD_PIN )

#define  		LCD_DATA_OUT(data)     			ILI9341_DATA_PORT->ODR = data //GPIO_Write(ILI9341_DATA_PORT,data)
#define  		LCD_DATA_IN()     					GPIO_ReadInputData(ILI9341_DATA_PORT)

/*��ʼ��delay*/
#define      DEBUG_DELAY()       ILI9341_Delay(0xFFFF)       

/******************************* ���� ILI934 �������� ********************************/
#define      CMD_SetCoordinateX		 		    0x2A	     //����X����
#define      CMD_SetCoordinateY		 		    0x2B	     //����Y����
#define      CMD_SetPixel		 		          0x2C	     //�������


#define 			ILI9341_LESS_PIXEL	  							240			//Һ�����϶̷�������ؿ��
#define 			ILI9341_MORE_PIXEL	 								320			//Һ�����ϳ���������ؿ��

/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/
#define      BACKGROUND		                BLACK   //Ĭ�ϱ�����ɫ

#define      WHITE		 		                  0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF

/*ILIL9341�ӿڶ���-��β****************************/
void ILI9341_GPIO_Init(void);
uint16_t ILI9341_Read_ID(void);
void ILI9341_Init(void);
void ILI9341_GramScan ( uint8_t ucOption );
void ILI9341_Open_Window(uint16_t x,uint16_t y,uint16_t width, uint16_t heigh);
void ILI9341_Draw_Rect(uint16_t x,uint16_t y,uint16_t width, uint16_t heigh,uint16_t color);
void ILI9341_Draw_Point(uint16_t x,uint16_t y,uint16_t color);
#endif /* __BSP_ILI9341_LCD_H */


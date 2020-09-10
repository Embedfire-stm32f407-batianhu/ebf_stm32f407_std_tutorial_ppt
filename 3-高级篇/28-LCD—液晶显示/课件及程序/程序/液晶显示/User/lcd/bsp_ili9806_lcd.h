#ifndef __BSP_LCD_H
#define __BSP_LCD_H															    



#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"


#define Bank1_NOR_SRAM3_ADDR    ((uint32_t)(0x68000000))	


//ʹ��A0���ӵ�D/CX����
#define LCD_DATA_ADDR    ((uint32_t)(Bank1_NOR_SRAM3_ADDR | (1<<(0+1))))	 //0x68000002
#define LCD_DATA_CMD    ((uint32_t)(Bank1_NOR_SRAM3_ADDR &~ (1<<(0+1))))	 //0x68000000

#define      DEBUG_DELAY()               Delay(0x5000)

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

/******************************* ILI9806G ��ʾ��8080ͨѶ���Ŷ��� ***************************/
/******�����ź���******/
#define      FSMC_AF                       GPIO_AF_FSMC
//Ƭѡ��ѡ��NOR/SRAM��
#define      ILI9806G_CS_CLK                RCC_AHB1Periph_GPIOG  
#define      ILI9806G_CS_PORT               GPIOG
#define      ILI9806G_CS_PIN                GPIO_Pin_10
#define      ILI9806G_CS_PinSource          GPIO_PinSource10

//DC���ţ�ʹ��FSMC�ĵ�ַ�źſ��ƣ������ž����˷���LCDʱʹ�õĵ�ַ
//PF0ΪFSMC_A0
#define      ILI9806G_DC_CLK                RCC_AHB1Periph_GPIOF  
#define      ILI9806G_DC_PORT               GPIOF
#define      ILI9806G_DC_PIN                GPIO_Pin_0
#define      ILI9806G_DC_PinSource          GPIO_PinSource0

//дʹ��
#define      ILI9806G_WR_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_WR_PORT               GPIOD
#define      ILI9806G_WR_PIN                GPIO_Pin_5
#define      ILI9806G_WR_PinSource          GPIO_PinSource5

//��ʹ��
#define      ILI9806G_RD_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_RD_PORT               GPIOD
#define      ILI9806G_RD_PIN                GPIO_Pin_4
#define      ILI9806G_RD_PinSource          GPIO_PinSource4

//��λ����
#define      ILI9806G_RST_CLK               RCC_AHB1Periph_GPIOF 
#define      ILI9806G_RST_PORT              GPIOF
#define      ILI9806G_RST_PIN               GPIO_Pin_11

//��������
#define      ILI9806G_BK_CLK                RCC_AHB1Periph_GPIOF   
#define      ILI9806G_BK_PORT               GPIOF
#define      ILI9806G_BK_PIN                GPIO_Pin_9

/********�����ź���***************/
#define      ILI9806G_D0_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D0_PORT               GPIOD
#define      ILI9806G_D0_PIN                GPIO_Pin_14
#define      ILI9806G_D0_PinSource          GPIO_PinSource14

#define      ILI9806G_D1_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D1_PORT               GPIOD
#define      ILI9806G_D1_PIN                GPIO_Pin_15
#define      ILI9806G_D1_PinSource          GPIO_PinSource15

#define      ILI9806G_D2_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D2_PORT               GPIOD
#define      ILI9806G_D2_PIN                GPIO_Pin_0
#define      ILI9806G_D2_PinSource          GPIO_PinSource0

#define      ILI9806G_D3_CLK                RCC_AHB1Periph_GPIOD  
#define      ILI9806G_D3_PORT               GPIOD
#define      ILI9806G_D3_PIN                GPIO_Pin_1
#define      ILI9806G_D3_PinSource          GPIO_PinSource1

#define      ILI9806G_D4_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D4_PORT               GPIOE
#define      ILI9806G_D4_PIN                GPIO_Pin_7
#define      ILI9806G_D4_PinSource          GPIO_PinSource7

#define      ILI9806G_D5_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D5_PORT               GPIOE
#define      ILI9806G_D5_PIN                GPIO_Pin_8
#define      ILI9806G_D5_PinSource          GPIO_PinSource8

#define      ILI9806G_D6_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D6_PORT               GPIOE
#define      ILI9806G_D6_PIN                GPIO_Pin_9
#define      ILI9806G_D6_PinSource          GPIO_PinSource9

#define      ILI9806G_D7_CLK                RCC_AHB1Periph_GPIOE  
#define      ILI9806G_D7_PORT               GPIOE
#define      ILI9806G_D7_PIN                GPIO_Pin_10
#define      ILI9806G_D7_PinSource          GPIO_PinSource10

#define      ILI9806G_D8_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D8_PORT               GPIOE
#define      ILI9806G_D8_PIN                GPIO_Pin_11
#define      ILI9806G_D8_PinSource          GPIO_PinSource11

#define      ILI9806G_D9_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D9_PORT               GPIOE
#define      ILI9806G_D9_PIN                GPIO_Pin_12
#define      ILI9806G_D9_PinSource          GPIO_PinSource12

#define      ILI9806G_D10_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D10_PORT               GPIOE
#define      ILI9806G_D10_PIN                GPIO_Pin_13
#define      ILI9806G_D10_PinSource          GPIO_PinSource13

#define      ILI9806G_D11_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D11_PORT               GPIOE
#define      ILI9806G_D11_PIN                GPIO_Pin_14
#define      ILI9806G_D11_PinSource          GPIO_PinSource14

#define      ILI9806G_D12_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D12_PORT               GPIOE
#define      ILI9806G_D12_PIN                GPIO_Pin_15
#define      ILI9806G_D12_PinSource          GPIO_PinSource15

#define      ILI9806G_D13_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D13_PORT               GPIOD
#define      ILI9806G_D13_PIN                GPIO_Pin_8
#define      ILI9806G_D13_PinSource          GPIO_PinSource8

#define      ILI9806G_D14_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D14_PORT               GPIOD
#define      ILI9806G_D14_PIN                GPIO_Pin_9
#define      ILI9806G_D14_PinSource          GPIO_PinSource9

#define      ILI9806G_D15_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D15_PORT               GPIOD
#define      ILI9806G_D15_PIN                GPIO_Pin_10
#define      ILI9806G_D15_PinSource          GPIO_PinSource10


/*��Ϣ���*/
#define SRAM_DEBUG_ON         1

#define SRAM_INFO(fmt,arg...)           printf("<<-SRAM-INFO->> "fmt"\n",##arg)
#define SRAM_ERROR(fmt,arg...)          printf("<<-SRAM-ERROR->> "fmt"\n",##arg)
#define SRAM_DEBUG(fmt,arg...)          do{\
                                          if(SRAM_DEBUG_ON)\
                                          printf("<<-SRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)




											  
void LCD_Init(void);
uint16_t LCD_Get_ID(void);
void LCD_Draw_Rect(uint16_t x0,uint16_t x1,uint16_t y0,uint16_t y1,uint16_t color);


																					



#endif


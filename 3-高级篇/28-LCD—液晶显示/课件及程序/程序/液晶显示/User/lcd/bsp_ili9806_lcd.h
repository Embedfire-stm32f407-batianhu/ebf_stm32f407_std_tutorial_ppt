#ifndef __BSP_LCD_H
#define __BSP_LCD_H															    



#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"


#define Bank1_NOR_SRAM3_ADDR    ((uint32_t)(0x68000000))	


//使用A0连接到D/CX引脚
#define LCD_DATA_ADDR    ((uint32_t)(Bank1_NOR_SRAM3_ADDR | (1<<(0+1))))	 //0x68000002
#define LCD_DATA_CMD    ((uint32_t)(Bank1_NOR_SRAM3_ADDR &~ (1<<(0+1))))	 //0x68000000

#define      DEBUG_DELAY()               Delay(0x5000)

/******************************* 定义 ILI934 显示屏常用颜色 ********************************/
#define      BACKGROUND		                BLACK   //默认背景颜色

#define      WHITE		 		                  0xFFFF	   //白色
#define      BLACK                         0x0000	   //黑色 
#define      GREY                          0xF7DE	   //灰色 
#define      BLUE                          0x001F	   //蓝色 
#define      BLUE2                         0x051F	   //浅蓝色 
#define      RED                           0xF800	   //红色 
#define      MAGENTA                       0xF81F	   //红紫色，洋红色 
#define      GREEN                         0x07E0	   //绿色 
#define      CYAN                          0x7FFF	   //蓝绿色，青色 
#define      YELLOW                        0xFFE0	   //黄色 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF

/******************************* ILI9806G 显示屏8080通讯引脚定义 ***************************/
/******控制信号线******/
#define      FSMC_AF                       GPIO_AF_FSMC
//片选，选择NOR/SRAM块
#define      ILI9806G_CS_CLK                RCC_AHB1Periph_GPIOG  
#define      ILI9806G_CS_PORT               GPIOG
#define      ILI9806G_CS_PIN                GPIO_Pin_10
#define      ILI9806G_CS_PinSource          GPIO_PinSource10

//DC引脚，使用FSMC的地址信号控制，本引脚决定了访问LCD时使用的地址
//PF0为FSMC_A0
#define      ILI9806G_DC_CLK                RCC_AHB1Periph_GPIOF  
#define      ILI9806G_DC_PORT               GPIOF
#define      ILI9806G_DC_PIN                GPIO_Pin_0
#define      ILI9806G_DC_PinSource          GPIO_PinSource0

//写使能
#define      ILI9806G_WR_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_WR_PORT               GPIOD
#define      ILI9806G_WR_PIN                GPIO_Pin_5
#define      ILI9806G_WR_PinSource          GPIO_PinSource5

//读使能
#define      ILI9806G_RD_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_RD_PORT               GPIOD
#define      ILI9806G_RD_PIN                GPIO_Pin_4
#define      ILI9806G_RD_PinSource          GPIO_PinSource4

//复位引脚
#define      ILI9806G_RST_CLK               RCC_AHB1Periph_GPIOF 
#define      ILI9806G_RST_PORT              GPIOF
#define      ILI9806G_RST_PIN               GPIO_Pin_11

//背光引脚
#define      ILI9806G_BK_CLK                RCC_AHB1Periph_GPIOF   
#define      ILI9806G_BK_PORT               GPIOF
#define      ILI9806G_BK_PIN                GPIO_Pin_9

/********数据信号线***************/
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


/*信息输出*/
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


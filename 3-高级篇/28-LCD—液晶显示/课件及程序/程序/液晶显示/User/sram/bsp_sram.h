#ifndef __SRAM_H
#define __SRAM_H															    



#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"

//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=10 
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17 
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18
#define Bank1_SRAM4_ADDR    ((uint32_t)(0x6C000000))		

#define IS62WV51216_SIZE 0x100000  //512*16/2bits = 0x100000  ��1M�ֽ�


#define FSMC_GPIO_AF             GPIO_AF_FSMC

/*A��ַ�ź���*/    
#define FSMC_A0_GPIO_PORT        GPIOF
#define FSMC_A0_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A0_GPIO_PIN         GPIO_Pin_0
#define FSMC_A0_GPIO_PinSource   GPIO_PinSource0

#define FSMC_A1_GPIO_PORT        GPIOF
#define FSMC_A1_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A1_GPIO_PIN         GPIO_Pin_1
#define FSMC_A1_GPIO_PinSource   GPIO_PinSource1

#define FSMC_A2_GPIO_PORT        GPIOF
#define FSMC_A2_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A2_GPIO_PIN         GPIO_Pin_2
#define FSMC_A2_GPIO_PinSource   GPIO_PinSource2

#define FSMC_A3_GPIO_PORT        GPIOF
#define FSMC_A3_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A3_GPIO_PIN         GPIO_Pin_3
#define FSMC_A3_GPIO_PinSource   GPIO_PinSource3

#define FSMC_A4_GPIO_PORT        GPIOF
#define FSMC_A4_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A4_GPIO_PIN         GPIO_Pin_4
#define FSMC_A4_GPIO_PinSource   GPIO_PinSource4

#define FSMC_A5_GPIO_PORT        GPIOF
#define FSMC_A5_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A5_GPIO_PIN         GPIO_Pin_5
#define FSMC_A5_GPIO_PinSource   GPIO_PinSource5

#define FSMC_A6_GPIO_PORT        GPIOF
#define FSMC_A6_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A6_GPIO_PIN         GPIO_Pin_12
#define FSMC_A6_GPIO_PinSource   GPIO_PinSource12

#define FSMC_A7_GPIO_PORT        GPIOF
#define FSMC_A7_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A7_GPIO_PIN         GPIO_Pin_13
#define FSMC_A7_GPIO_PinSource   GPIO_PinSource13

#define FSMC_A8_GPIO_PORT        GPIOF
#define FSMC_A8_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A8_GPIO_PIN         GPIO_Pin_14
#define FSMC_A8_GPIO_PinSource   GPIO_PinSource14

#define FSMC_A9_GPIO_PORT        GPIOF
#define FSMC_A9_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define FSMC_A9_GPIO_PIN         GPIO_Pin_15
#define FSMC_A9_GPIO_PinSource   GPIO_PinSource15

#define FSMC_A10_GPIO_PORT        GPIOG
#define FSMC_A10_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A10_GPIO_PIN         GPIO_Pin_0
#define FSMC_A10_GPIO_PinSource   GPIO_PinSource0

#define FSMC_A11_GPIO_PORT        GPIOG
#define FSMC_A11_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A11_GPIO_PIN         GPIO_Pin_1
#define FSMC_A11_GPIO_PinSource   GPIO_PinSource1

#define FSMC_A12_GPIO_PORT        GPIOG
#define FSMC_A12_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A12_GPIO_PIN         GPIO_Pin_2
#define FSMC_A12_GPIO_PinSource   GPIO_PinSource2

#define FSMC_A13_GPIO_PORT        GPIOG
#define FSMC_A13_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A13_GPIO_PIN         GPIO_Pin_3
#define FSMC_A13_GPIO_PinSource   GPIO_PinSource3

#define FSMC_A14_GPIO_PORT        GPIOG
#define FSMC_A14_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A14_GPIO_PIN         GPIO_Pin_4
#define FSMC_A14_GPIO_PinSource   GPIO_PinSource4

#define FSMC_A15_GPIO_PORT        GPIOG
#define FSMC_A15_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_A15_GPIO_PIN         GPIO_Pin_5
#define FSMC_A15_GPIO_PinSource   GPIO_PinSource5

#define FSMC_A16_GPIO_PORT        GPIOD
#define FSMC_A16_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_A16_GPIO_PIN         GPIO_Pin_11
#define FSMC_A16_GPIO_PinSource   GPIO_PinSource11

#define FSMC_A17_GPIO_PORT        GPIOD
#define FSMC_A17_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_A17_GPIO_PIN         GPIO_Pin_12
#define FSMC_A17_GPIO_PinSource   GPIO_PinSource12

#define FSMC_A18_GPIO_PORT        GPIOD
#define FSMC_A18_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_A18_GPIO_PIN         GPIO_Pin_13
#define FSMC_A18_GPIO_PinSource   GPIO_PinSource13

/*D �����ź���*/
#define FSMC_D0_GPIO_PORT        GPIOD
#define FSMC_D0_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D0_GPIO_PIN         GPIO_Pin_14
#define FSMC_D0_GPIO_PinSource   GPIO_PinSource14

#define FSMC_D1_GPIO_PORT        GPIOD
#define FSMC_D1_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D1_GPIO_PIN         GPIO_Pin_15
#define FSMC_D1_GPIO_PinSource   GPIO_PinSource15

#define FSMC_D2_GPIO_PORT        GPIOD
#define FSMC_D2_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D2_GPIO_PIN         GPIO_Pin_0
#define FSMC_D2_GPIO_PinSource   GPIO_PinSource0

#define FSMC_D3_GPIO_PORT        GPIOD
#define FSMC_D3_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D3_GPIO_PIN         GPIO_Pin_1
#define FSMC_D3_GPIO_PinSource   GPIO_PinSource1

#define FSMC_D4_GPIO_PORT        GPIOE
#define FSMC_D4_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D4_GPIO_PIN         GPIO_Pin_7
#define FSMC_D4_GPIO_PinSource   GPIO_PinSource7

#define FSMC_D5_GPIO_PORT        GPIOE
#define FSMC_D5_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D5_GPIO_PIN         GPIO_Pin_8
#define FSMC_D5_GPIO_PinSource   GPIO_PinSource8

#define FSMC_D6_GPIO_PORT        GPIOE
#define FSMC_D6_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D6_GPIO_PIN         GPIO_Pin_9
#define FSMC_D6_GPIO_PinSource   GPIO_PinSource9

#define FSMC_D7_GPIO_PORT        GPIOE
#define FSMC_D7_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D7_GPIO_PIN         GPIO_Pin_10
#define FSMC_D7_GPIO_PinSource   GPIO_PinSource10

#define FSMC_D8_GPIO_PORT        GPIOE
#define FSMC_D8_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D8_GPIO_PIN         GPIO_Pin_11
#define FSMC_D8_GPIO_PinSource   GPIO_PinSource11

#define FSMC_D9_GPIO_PORT        GPIOE
#define FSMC_D9_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D9_GPIO_PIN         GPIO_Pin_12
#define FSMC_D9_GPIO_PinSource   GPIO_PinSource12

#define FSMC_D10_GPIO_PORT        GPIOE
#define FSMC_D10_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D10_GPIO_PIN         GPIO_Pin_13
#define FSMC_D10_GPIO_PinSource   GPIO_PinSource13

#define FSMC_D11_GPIO_PORT        GPIOE
#define FSMC_D11_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D11_GPIO_PIN         GPIO_Pin_14
#define FSMC_D11_GPIO_PinSource   GPIO_PinSource14

#define FSMC_D12_GPIO_PORT        GPIOE
#define FSMC_D12_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_D12_GPIO_PIN         GPIO_Pin_15
#define FSMC_D12_GPIO_PinSource   GPIO_PinSource15

#define FSMC_D13_GPIO_PORT        GPIOD
#define FSMC_D13_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D13_GPIO_PIN         GPIO_Pin_8
#define FSMC_D13_GPIO_PinSource   GPIO_PinSource8

#define FSMC_D14_GPIO_PORT        GPIOD
#define FSMC_D14_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D14_GPIO_PIN         GPIO_Pin_9
#define FSMC_D14_GPIO_PinSource   GPIO_PinSource9

#define FSMC_D15_GPIO_PORT        GPIOD
#define FSMC_D15_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_D15_GPIO_PIN         GPIO_Pin_10
#define FSMC_D15_GPIO_PinSource   GPIO_PinSource10

/*�����ź���*/  
/*CSƬѡ*/
/*NE4 ,��Ӧ�Ļ���ַ0x6C000000*/
#define FSMC_CS_GPIO_PORT        GPIOG
#define FSMC_CS_GPIO_CLK         RCC_AHB1Periph_GPIOG
#define FSMC_CS_GPIO_PIN         GPIO_Pin_12
#define FSMC_CS_GPIO_PinSource   GPIO_PinSource12

/*WEдʹ��*/
#define FSMC_WE_GPIO_PORT        GPIOD
#define FSMC_WE_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_WE_GPIO_PIN         GPIO_Pin_5
#define FSMC_WE_GPIO_PinSource   GPIO_PinSource5

/*OE��ʹ��*/
#define FSMC_OE_GPIO_PORT        GPIOD
#define FSMC_OE_GPIO_CLK         RCC_AHB1Periph_GPIOD
#define FSMC_OE_GPIO_PIN         GPIO_Pin_4
#define FSMC_OE_GPIO_PinSource   GPIO_PinSource4


/*UB��������*/
#define FSMC_UDQM_GPIO_PORT        GPIOE
#define FSMC_UDQM_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_UDQM_GPIO_PIN         GPIO_Pin_1
#define FSMC_UDQM_GPIO_PinSource   GPIO_PinSource1

/*LB��������*/
#define FSMC_LDQM_GPIO_PORT        GPIOE
#define FSMC_LDQM_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define FSMC_LDQM_GPIO_PIN         GPIO_Pin_0
#define FSMC_LDQM_GPIO_PinSource   GPIO_PinSource0


/*��Ϣ���*/
#define SRAM_DEBUG_ON         1

#define SRAM_INFO(fmt,arg...)           printf("<<-SRAM-INFO->> "fmt"\n",##arg)
#define SRAM_ERROR(fmt,arg...)          printf("<<-SRAM-ERROR->> "fmt"\n",##arg)
#define SRAM_DEBUG(fmt,arg...)          do{\
                                          if(SRAM_DEBUG_ON)\
                                          printf("<<-SRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)




											  
void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(uint8_t* pBuffer,uint32_t WriteAddr,uint32_t NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(uint8_t* pBuffer,uint32_t ReadAddr,uint32_t NumHalfwordToRead);

uint8_t SRAM_Test(void);

#endif


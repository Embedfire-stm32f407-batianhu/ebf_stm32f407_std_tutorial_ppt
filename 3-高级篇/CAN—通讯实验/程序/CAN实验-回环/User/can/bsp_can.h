#ifndef __BSP_CAN_H
#define	__BSP_CAN_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
#define TEST_CAN                             CAN2
//使用can2外设的时候，必须同时使能CAN1时钟
#define TEST_CAN_CLK                         (RCC_APB1Periph_CAN2|RCC_APB1Periph_CAN1) 
#define TEST_CAN_DIV                    			6  //分频因子

#define TEST_CAN_RX_GPIO_PORT                GPIOB
#define TEST_CAN_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define TEST_CAN_RX_PIN                      GPIO_Pin_12
#define TEST_CAN_RX_AF                       GPIO_AF_CAN2
#define TEST_CAN_RX_SOURCE                   GPIO_PinSource12

#define TEST_CAN_TX_GPIO_PORT                GPIOB
#define TEST_CAN_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define TEST_CAN_TX_PIN                      GPIO_Pin_13
#define TEST_CAN_TX_AF                       GPIO_AF_CAN2
#define TEST_CAN_TX_SOURCE                   GPIO_PinSource13

#define TEST_CAN_IRQHandler                  CAN2_RX0_IRQHandler
#define TEST_CAN_IRQ                 					CAN2_RX0_IRQn
/************************************************************/

void CAN_Config(void);
void CAN_Filter_Config(void);

#endif /* __BSP_CAN_H */

/**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   CAN驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./can/bsp_can.h"


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = TEST_CAN_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  CAN_Config 初始化CAN
  * @param  无
  * @retval 无
  */
void CAN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  CAN_InitTypeDef CAN_InitStructure;
		
  RCC_AHB1PeriphClockCmd(TEST_CAN_RX_GPIO_CLK|TEST_CAN_TX_GPIO_CLK,ENABLE);

  /* 使能 CAN 时钟 */
  RCC_APB1PeriphClockCmd(TEST_CAN_CLK, ENABLE);
	
	 /* 连接 PXx 到 CANx_Tx*/
  GPIO_PinAFConfig(TEST_CAN_RX_GPIO_PORT,TEST_CAN_RX_SOURCE,TEST_CAN_RX_AF);

  /*  连接 PXx 到 CANx__Rx*/
  GPIO_PinAFConfig(TEST_CAN_TX_GPIO_PORT,TEST_CAN_TX_SOURCE,TEST_CAN_TX_AF);

  
  /* GPIO初始化 */  
	/* 配置Tx引脚为复用功能  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = TEST_CAN_TX_PIN  ;  
  GPIO_Init(TEST_CAN_TX_GPIO_PORT, &GPIO_InitStructure);

  /* 配置Rx引脚为复用功能 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = TEST_CAN_RX_PIN;
  GPIO_Init(TEST_CAN_RX_GPIO_PORT, &GPIO_InitStructure);  
  
  /* 配置CAN 模式 */
  /* 完成CAN初始化配置 */
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = ENABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	
	//配置波特率 1Mbps
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
	CAN_InitStructure.CAN_Prescaler = TEST_CAN_DIV;
	
	//先使用回环模式测试，测试通过后再采用CAN_Mode_Normal模式在两个板子之间通讯
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;	
	CAN_Init(TEST_CAN, &CAN_InitStructure); 
	
  /* 嵌套向量中断控制器NVIC配置 */
	NVIC_Configuration();
  
	/* 使能FIFO 0 接收中断 */
	CAN_ITConfig(TEST_CAN, CAN_IT_FMP0, ENABLE);	
}

//初始化筛选器
void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_Filter_Struct;
	
	CAN_Filter_Struct.CAN_FilterNumber = 14;
	CAN_Filter_Struct.CAN_FilterScale = CAN_FilterScale_32bit ;
	CAN_Filter_Struct.CAN_FilterMode = CAN_FilterMode_IdMask ;//掩码模式
	CAN_Filter_Struct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0 ; //报文存储在FIFO 0
	CAN_Filter_Struct.CAN_FilterActivation = ENABLE ;
	
	CAN_Filter_Struct.CAN_FilterIdHigh = (((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000) >>16;
	CAN_Filter_Struct.CAN_FilterIdLow = ((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0x0000FFFF;
	CAN_Filter_Struct.CAN_FilterMaskIdHigh = 0xFFFF;
	CAN_Filter_Struct.CAN_FilterMaskIdLow = 0xFFFF;	
	
	CAN_FilterInit(&CAN_Filter_Struct);
}

/*********************************************END OF FILE**********************/

/**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   CAN����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./can/bsp_can.h"


 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = TEST_CAN_IRQ;
  /* �������ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  CAN_Config ��ʼ��CAN
  * @param  ��
  * @retval ��
  */
void CAN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  CAN_InitTypeDef CAN_InitStructure;
		
  RCC_AHB1PeriphClockCmd(TEST_CAN_RX_GPIO_CLK|TEST_CAN_TX_GPIO_CLK,ENABLE);

  /* ʹ�� CAN ʱ�� */
  RCC_APB1PeriphClockCmd(TEST_CAN_CLK, ENABLE);
	
	 /* ���� PXx �� CANx_Tx*/
  GPIO_PinAFConfig(TEST_CAN_RX_GPIO_PORT,TEST_CAN_RX_SOURCE,TEST_CAN_RX_AF);

  /*  ���� PXx �� CANx__Rx*/
  GPIO_PinAFConfig(TEST_CAN_TX_GPIO_PORT,TEST_CAN_TX_SOURCE,TEST_CAN_TX_AF);

  
  /* GPIO��ʼ�� */  
	/* ����Tx����Ϊ���ù���  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = TEST_CAN_TX_PIN  ;  
  GPIO_Init(TEST_CAN_TX_GPIO_PORT, &GPIO_InitStructure);

  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = TEST_CAN_RX_PIN;
  GPIO_Init(TEST_CAN_RX_GPIO_PORT, &GPIO_InitStructure);  
  
  /* ����CAN ģʽ */
  /* ���CAN��ʼ������ */
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = ENABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	
	//���ò����� 1Mbps
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
	CAN_InitStructure.CAN_Prescaler = TEST_CAN_DIV;
	
	//��ʹ�ûػ�ģʽ���ԣ�����ͨ�����ٲ���CAN_Mode_Normalģʽ����������֮��ͨѶ
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;	
	CAN_Init(TEST_CAN, &CAN_InitStructure); 
	
  /* Ƕ�������жϿ�����NVIC���� */
	NVIC_Configuration();
  
	/* ʹ��FIFO 0 �����ж� */
	CAN_ITConfig(TEST_CAN, CAN_IT_FMP0, ENABLE);	
}

//��ʼ��ɸѡ��
void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_Filter_Struct;
	
	CAN_Filter_Struct.CAN_FilterNumber = 14;
	CAN_Filter_Struct.CAN_FilterScale = CAN_FilterScale_32bit ;
	CAN_Filter_Struct.CAN_FilterMode = CAN_FilterMode_IdMask ;//����ģʽ
	CAN_Filter_Struct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0 ; //���Ĵ洢��FIFO 0
	CAN_Filter_Struct.CAN_FilterActivation = ENABLE ;
	
	CAN_Filter_Struct.CAN_FilterIdHigh = (((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000) >>16;
	CAN_Filter_Struct.CAN_FilterIdLow = ((uint32_t)0x1314<<3|CAN_ID_EXT|CAN_RTR_DATA)&0x0000FFFF;
	CAN_Filter_Struct.CAN_FilterMaskIdHigh = 0xFFFF;
	CAN_Filter_Struct.CAN_FilterMaskIdLow = 0xFFFF;	
	
	CAN_FilterInit(&CAN_Filter_Struct);
}

/*********************************************END OF FILE**********************/

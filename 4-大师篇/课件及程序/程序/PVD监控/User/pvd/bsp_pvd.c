/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �ض���c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����STM32 F103-MINI ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "./pvd/bsp_pvd.h"

 
 /**
  * @brief  PVD  ����,������������
  * @param  ��
  * @retval ��
  */
void PVD_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	//ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
  //�������ȼ�
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn; //����PVD�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
	
	//�����ж�Դ
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;	
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�������½��ض������ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

	
	//����Ϊ�ȼ�5���½���2.58V�����ж�
	PWR_PVDLevelConfig(PWR_PVDLevel_2V7);
	PWR_PVDCmd(ENABLE);
}


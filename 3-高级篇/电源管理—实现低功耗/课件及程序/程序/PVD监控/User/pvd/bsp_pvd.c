/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   pvd����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./pvd/bsp_pvd.h"   



 /**
  * @brief  ��ʼ��PVD����
  * @param  ��
  * @retval ��
  */
void PVD_Config(void)
{		
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* ʹ�� PWR ʱ�� ��ʹ��PVD����ʹ��PWRʱ��*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ��PVD_IRQn */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  /* ������ռ���ȼ���0 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* ���������ȼ���0 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	/* ѡ�� EXTI �ж�Դ EXTI_Line16 PVD�ж�Դ*/
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  /* �ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  /* �½��ش��� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  /* ʹ���ж�/�¼��� */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	//vdd���ŵĵ�ԴΪ2.84Vʱ����PVD�ж�
	PWR_PVDLevelConfig(PWR_PVDLevel_5);
	PWR_PVDCmd(ENABLE);



}
/*********************************************END OF FILE**********************/

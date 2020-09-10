/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   pvd配置
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./pvd/bsp_pvd.h"   



 /**
  * @brief  初始化PVD功能
  * @param  无
  * @retval 无
  */
void PVD_Config(void)
{		
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* 使能 PWR 时钟 ，使用PVD必须使能PWR时钟*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源：PVD_IRQn */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  /* 配置抢占优先级：0 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 配置子优先级：0 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	/* 选择 EXTI 中断源 EXTI_Line16 PVD中断源*/
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  /* 中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  /* 下降沿触发 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  /* 使能中断/事件线 */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	//vdd引脚的电源为2.84V时触发PVD中断
	PWR_PVDLevelConfig(PWR_PVDLevel_5);
	PWR_PVDCmd(ENABLE);



}
/*********************************************END OF FILE**********************/

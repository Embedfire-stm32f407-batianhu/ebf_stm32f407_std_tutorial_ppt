#include "stc89c51_tim.h"

/*
 * brief  : Initial TIM0 and TIM1
 * param_1: TIM0、TIM1
 * param_2: Timing_500us、Timing_1ms、Timing_10ms、Timing_50ms
 * param_3: TIM0_TimeBase_Mode_1、TIM0_TimeBase_Mode_2、TIM0_MeasrePW_Mode、TIM0_PusCnt_Mode
 *          TIM1_TimeBase_Mode_1、TIM1_TimeBase_Mode_2、TIM1_MeasrePW_Mode、TIM1_PusCnt_Mode 
 */
void TIM_Init(uchar TIMx, uint16 TIM_Reload, uchar TIM_Mode)
{
	   /* 定时器为16位装载模式 */
	if ((TIM_Mode == TIM0_TimeBase_Mode_1) && ((TIM_Mode == TIM1_TimeBase_Mode_1)))
	{	  
	  	if (TIMx == TIM0)
		{
		     TH0 = TIM_Reload >> 8;
			 TL0 = (uchar)TIM_Reload;
		}
		else
		{
			 TH1 = TIM_Reload >> 8;
			 TL1 = (uchar)TIM_Reload;
		}

	}	   /* 定时器为自动重载模式(8为模式) */
	else if ((TIM_Mode == TIM0_TimeBase_Mode_2) && ((TIM_Mode == TIM1_TimeBase_Mode_2)))
	{
	    if (TIMx == TIM0)
		{
		     TL0 = (uchar)TIM_Reload;
			 TH0 = (uchar)TIM_Reload;
		}
		else
		{
		     TL1 = (uchar)TIM_Reload;
			 TH1 = (uchar)TIM_Reload;
		}
	
	}
	else   /* 定时器为计数模式 */
	{
		 /* 不需要装载值 */
	}

    TMOD |= TIM_Mode;	
}


/*
 * brief  : Initial TIM2
 * param_1: Timing_500us、Timing_1ms、Timing_10ms、Timing_50ms
 * param_2: TIM2_TimeBase_Mode_1、TIM2_Capture_Mode、TIM2_PusCnt_Mode
 */
void TIM2_Init(uint16 TIM_Reload, uchar TIM_Mode)
{
	if (TIM_Mode == TIM2_TimeBase_Mode_1)
	{
	    TH2 = TIM_Reload >> 8;
		RCAP2H = TIM_Reload >> 8;
		TL2 = (uchar)TIM_Reload;
		RCAP2L = (uchar)TIM_Reload;    
	}
	   /* 其他模式不需要装载值 */

	T2CON = TIM_Mode;
}


/*
 * brief: 获取脉冲计数值或脉冲宽度值
 *        脉冲计数计算低电平的个数，脉冲宽度测P3.2、P3.3高电平时间，低电平停止计数
 *
 * param: TIM0、TIM1、TIM2
 */
uint16 GET_PulCnt_PW_Val(uchar TIMx)
{
    uint16 value;

	if (TIMx == TIM0)
	{
		value = TH0;
		value = (value << 8) | TL0;
	 }
	 else if (TIMx == TIM1)
	 {
	    value = TH1;
		value = (value << 8) | TL1;
	 }
	 else
	 {
	    value = TH2;
		value = (value << 8) | TL2;
	 }

	return (value);  
}


/*
 * brief: 获取捕获的值，低电平捕获
 */
uint16 TIM2_GET_CaptureVal(void)
{
    uint16 value;

	value = RCAP2H;
	value = (value << 8) | RCAP2L;

	return (value);
}


/*
 * brief : Change Timer Priority
 * parame: TIM0_Priority_0、TIM0_Priority_1、TIM0_Priority_2、TIM0_Priority_3
 *         TIM1_Priority_0、TIM1_Priority_1、TIM1_Priority_2、TIM1_Priority_3
 *         TIM2_Priority_0、TIM2_Priority_1  
 */
void TIM_PrioChange(uint16 Priority)
{	
	IPH |= Priority >> 8;
	IP |= (uchar)Priority;
	 
}


/*
 * brief  : 设置定时器重装载值，用在中断服务函数
 * param_1: TIM0、TIM1
 * param_2: Timing_500us、Timing_1ms、Timing_10ms、Timing_50ms 
 */
void TIM_SetReLoad(uchar TIMx, uint16 TIM_Reload)
{
    if (TIM0 == TIMx)
	{
	    TH0 = TIM_Reload >> 8;
		TL0 = (uchar)TIM_Reload;
	}
	else
	{
	    TH1 = TIM_Reload >> 8;
		TL1 = (uchar)TIM_Reload;
	}
}


/*-------------------------------------- End Of File ------------------------------------------------------*/

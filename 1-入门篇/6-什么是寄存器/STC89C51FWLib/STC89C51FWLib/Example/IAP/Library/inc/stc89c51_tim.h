#ifndef __STC89C51_TIM_H
#define __STC89C51_TIM_H

#include "stc89c51.h"

#define TIM0               0x00  /* Timer 0 flag */
#define TIM1               0x01  /* Timer 1 flag */

#define TIM0_MeasrePW	   0x08  /* Measure Pulse Wide For P3.2 */
#define TIM1_MeasrePW	   0x80  /* Measure Pulse Wide For P3.3 */

#define TIM0_PusCnt        0x04  /* Pulae Count For P3.4 */
#define TIM1_PusCnt        0x40  /* Pulae Count For P3.5 */  

#define TIM0_Mode_1	       0x01  /* 16 Bit Coumt Mode */
#define TIM1_Mode_1	       0x10  /* 16 Bit Coumt Mode */

#define TIM0_Mode_2	       0x02  /* 8 Bit Auto Reload */
#define TIM1_Mode_2	       0x20  /* 8 Bit Auto Reload */

#define TIM2_CapFlag       0x00  /* 定时器2捕获标志 */
#define TIM2_OverFFlag     0x01  /* 定时器2溢出标志 */

#define TIM0_TimeBase_Mode_1	   	TIM0_Mode_1
#define TIM0_TimeBase_Mode_2	   	TIM0_Mode_2
#define TIM0_MeasrePW_Mode          (TIM0_MeasrePW | TIM0_Mode_1)
#define TIM0_PusCnt_Mode			(TIM0_PusCnt | TIM0_Mode_1)

#define TIM1_TimeBase_Mode_1	   	TIM1_Mode_1
#define TIM1_TimeBase_Mode_2	   	TIM1_Mode_2
#define TIM1_MeasrePW_Mode          (TIM1_MeasrePW | TIM1_Mode_1)
#define TIM1_PusCnt_Mode		    (TIM1_PusCnt | TIM1_Mode_1)

#define TIM2_Capture_Mode           0x09  /* Capture For P1.1 */
#define TIM2_PusCnt_Mode            0x02  /* Pulae Count For P1.0 */ 
#define TIM2_TimeBase_Mode_1        0x00  /* 16 Bit Auto Reload */
     
#if (FOSC == 11059200L)  /* When FOSC is 11.0592MHz */
#define Timing_500us      ((uint16)(65536 - 461))
#define Timing_1ms        ((uint16)(65536 - 922))
#define Timing_10ms       ((uint16)(65536 - 9217))
#define Timing_50ms		  ((uint16)(65536 - 46083))  

#elif (FOSC == 12000000L)   /* When FOSC is 12MHz */
#define Timing_500us      ((uint16)(65536 - 500))
#define Timing_1ms        ((uint16)(65536 - 1000))
#define Timing_10ms       ((uint16)(65536 - 10000))
#define Timing_50ms       ((uint16)(65536 - 50000)) 
#endif

#define TIM0_Priority_0   0x0000
#define TIM0_Priority_1   0x0002
#define TIM0_Priority_2   0x0200
#define TIM0_Priority_3   0x0202

#define TIM1_Priority_0   0x0000
#define TIM1_Priority_1   0x0008	  
#define TIM1_Priority_2   0x0800
#define TIM1_Priority_3   0x0808

#define TIM2_Priority_0   0x0000
#define TIM2_Priority_1   0x0020
#define TIM2_Priority_2   0x0200  /* 仿真测试无效 */
#define TIM2_Priority_3   0x0220  /* 仿真测试无效 */


/*--------------------------------- Timer function prototype ------------------------------------------*/

void TIM_Init(uchar TIMx, uint16 TIM_Reload, uchar TIM_Mode);
void TIM2_Init(uint16 TIM_Reload, uchar TIM_Mode);

/* param: NewState = ENABLE or DISABLE */
#define TIM0_Cmd(NewState)             ((NewState) ? (TR0 = 1) : (TR0 = 0))     /* 开启或关闭定时器0 */
#define TIM1_Cmd(NewState)             ((NewState) ? (TR1 = 1) : (TR1 = 0))
#define TIM2_Cmd(NewState)             ((NewState) ? (TR2 = 1) : (TR2 = 0))
#define TIM0_ITCmd(NewState)           ((NewState) ? (IE |= 0x82) : (ET0 = 0))  /* 开启或关闭定时器0中断 */
#define TIM1_ITCmd(NewState)           ((NewState) ? (IE |= 0x88) : (ET1 = 0))
#define TIM2_ITCmd(NewState)           ((NewState) ? (IE |= 0xA0) : (ET2 = 0))

/* param: Flag ==  TIM2_CapFlag or TIM2_OverFFlag */
#define TIM2_CLR_Flag(Flag)       ((Flag) ? (TF2 = 0) : (EXF2 = 0))        /* 清除溢出标志或清除捕获标志 */

uint16 TIM2_GET_CaptureVal(void);                       /* 获取捕获的值 */
uint16 GET_PulCnt_PW_Val(uchar TIMx);                   /* 获取脉冲计数值或脉冲宽度 */
void TIM_PrioChange(uint16 Priority);                   /* 改变定时器的优先级 */
void TIM_SetReLoad(uchar TIMx, uint16 TIM_Reload);      /* 设置重装载值 */  

#endif
/*-------------------------------------- End Of File ------------------------------------------------------*/
 
#ifndef __STC89C51_EXIT_H
#define __STC89C51_EXIT_H

#include "stc89c51.h"

#define EXIT0  0x00  /* external interrupt 0 Flag (P3.2) */
#define EXIT1  0x01  /* external interrupt 1 Flag (P3.3) */

#define EXIT0_FallEdge    0x01  /* Falling Edge Touch */
#define EXIT0_LowLevel    0x00  /* Low Level Touch */

#define EXIT1_FallEdge    0x04  /* Falling Edge Touch */
#define EXIT1_LowLevel    0x00  /* Low Level Touch */

#define EXIT0_Priority_0  0x0000 
#define EXIT0_Priority_1  0x0001
#define EXIT0_Priority_2  0x0100
#define EXIT0_Priority_3  0x0101

#define EXIT1_Priority_0  0x0000 
#define EXIT1_Priority_1  0x0004
#define EXIT1_Priority_2  0x0400
#define EXIT1_Priority_3  0x0404

/*--------------------------------- EXIT function prototype -----------------------------------*/

/* parame: EXIT0_FallEdge、EXIT0_LowLevel、EXIT1_FallEdge、EXIT1_LowLevel */
#define EXIT0_Init(TouchEdge)            (TCON |= (TouchEdge))
#define EXIT1_Init(TouchEdge)            (TCON |= (TouchEdge))

/* param: NewState == ENABLE or DISABLE */
#define EXTI0_Cmd(NewState)              ((NewState) ? (EX0 = 1) : (EX0 = 0))  /* 开启或关闭外部中断0 */
#define EXTI1_Cmd(NewState)              ((NewState) ? (EX1 = 1) : (EX1 = 0))  
#define EXIT_IT_Cmd(NewState)            ((NewState) ? (EA = 1)  : (EA = 0))   /* 开启总中断 */

/* param: Exitx == EXIT1 or EXIT0 */
#define EXIT_CLR_ITFlag(Exitx)           ((Exitx) ? (IE1 = 0) : (IE0 = 0))    /* 清除中断标志，CPU响应中断后会自动清除，用于扫描模式 */
void EXIT_PrioChange(uint16 Priority);    /* 改变外部中断优先级 */

#endif
/*-------------------------------------- End Of File ------------------------------------------------------*/

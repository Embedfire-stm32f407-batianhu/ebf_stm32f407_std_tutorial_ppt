#ifndef __STC89C51_UART_H
#define __STC89C51_UART_H

#include "stc89c51.h"

#define Timer_Mode_2     0x20  /*TimerMode 2 to generate Baud Rate */
#define BaudRate_9600    0xfd  /* BaudRate = (2^SMOD / 32) * (T1 溢出率) 
                                 T1溢出率 = 1 / ((256 - X) * 12 / 11.0592 ) */
#define UART_RI_Flag     0x00
#define UART_TI_Flag     0x01
#define UART_Mode_1      0x50  /* 10 Bit Mode */

#define UART_Priority_0  0x0000
#define UART_Priority_1  0x0010
#define UART_Priority_2  0x1000
#define UART_Priority_3  0x1010	
 

/*--------------------------------- UART function prototype ------------------------------------------*/

void UART_Init(void);
/* param: NewState = ENABLE or DISABLE */
#define UART_Cmd(NewState)          ((NewState) ? (TR1 = 1)    : (TR1 = 0))   /* Open Timer 1 to generate baud rate */
#define UART_ITCmd(NewState)   		((NewState) ? (IE |= 0x90) : (ES = 0))    /* Enable EA and ES */

/* param: Flag == UART_RI_Flag or UART_TI_Flag */
#define USRT_CLR_ITFlag(Flag)      ((Flag) ? (TI = 0) : (RI = 0))  /* 清除中断标志 */
void UART_SendData(uchar Data);
uchar UART_ReceiveData(void);
void UART_PrioChange(uint16 Priority);	  /* 改变串口优先级 */

#endif
/*-------------------------------------- End Of File ------------------------------------------------------*/

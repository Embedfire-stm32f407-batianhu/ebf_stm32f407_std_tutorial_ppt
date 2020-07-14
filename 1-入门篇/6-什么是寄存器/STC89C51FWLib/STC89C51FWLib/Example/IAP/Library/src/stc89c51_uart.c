#include "stc89c51_uart.h"


/*
 * brief: 初始化串口，波特率为9600
 */
void UART_Init(void)
{
	 TMOD |= Timer_Mode_2;
	 TH1  = BaudRate_9600;
	 TL1  = BaudRate_9600; 
	 SCON |= UART_Mode_1;
}


/*
 * 
 */
void UART_SendData(uchar Data)
{
    SBUF = Data;
    while (!TI);  /* 当发送完成时，会先进入中断 */
    USRT_CLR_TI_Flag();
}


/*
 * return: 接收到的数据
 */
uchar UART_ReceiveData(void)
{
    while (!RI);
    USRT_CLR_RI_Flag();
  
	return (SBUF);
}


/*
 * brief : Change UART Interrupt Priority
 * parame: UART_Priority_0、UART_Priority_1、UART_Priority_2、UART_Priority_3 
 */
void UART_PrioChange(uint16 Priority)
{
    IPH |= Priority >> 8;
	IP |= (uchar)Priority; 
}

/*-------------------------------------- End Of File ------------------------------------------------------*/

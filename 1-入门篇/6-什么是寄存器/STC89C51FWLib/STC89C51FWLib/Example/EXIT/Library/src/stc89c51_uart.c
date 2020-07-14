#include "stc89c51_uart.h"


/*
 * brief: ��ʼ�����ڣ�������Ϊ9600
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
    while (!TI);  /* ���������ʱ�����Ƚ����ж� */
    USRT_CLR_ITFlag(UART_TI_Flag);
}


/*
 * return: ���յ�������
 */
uchar UART_ReceiveData(void)
{
    while (!RI);
    USRT_CLR_ITFlag(UART_RI_Flag);
  
	return (SBUF);
}


/*
 * brief : Change UART Interrupt Priority
 * parame: UART_Priority_0��UART_Priority_1��UART_Priority_2��UART_Priority_3 
 */
void UART_PrioChange(uint16 Priority)
{
    IPH |= Priority >> 8;
	IP |= (uchar)Priority; 
}

/*-------------------------------------- End Of File ------------------------------------------------------*/

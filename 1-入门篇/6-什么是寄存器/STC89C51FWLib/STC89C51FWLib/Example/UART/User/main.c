#include "stc89c51.h"

P0 = 0XFE;

sbit LED P0^0;

LED = 0;


int main(void)
{
	uchar i = 0;
		
  UART_Init();  /* ��ʼ�����ڣ�������Ϊ9600 */
	UART_Cmd(ENABLE);    /* �򿪴��� */
	UART_ITCmd(ENABLE);  /* �����ж� */	 

	for (i=0; i<10; i++)
	{		
		UART_SendData('a');	
	}

	while (1);
}


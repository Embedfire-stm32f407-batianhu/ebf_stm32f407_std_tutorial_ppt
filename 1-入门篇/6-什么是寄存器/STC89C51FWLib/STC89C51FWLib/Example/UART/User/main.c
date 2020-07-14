#include "stc89c51.h"

P0 = 0XFE;

sbit LED P0^0;

LED = 0;


int main(void)
{
	uchar i = 0;
		
  UART_Init();  /* 初始化串口，波特率为9600 */
	UART_Cmd(ENABLE);    /* 打开串口 */
	UART_ITCmd(ENABLE);  /* 开启中断 */	 

	for (i=0; i<10; i++)
	{		
		UART_SendData('a');	
	}

	while (1);
}


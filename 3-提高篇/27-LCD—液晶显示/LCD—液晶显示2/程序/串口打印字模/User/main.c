/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"

void print_charer(void);
void print_charer_2(void);

char text[] = "abcd";
char text2[] = "����";
//text = {0x61,0x62,0x63,0x64};
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USARTx,"����һ�������жϽ��ջ���ʵ��\n");
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	
	printf("text = %s\r\n",text);
	printf("text = %x\r\n",text[0]);
	printf("text = %x\r\n",text[1]);
	printf("text = %x\r\n",text[2]);
	printf("text = %x\r\n",text[3]);
	
	printf("text = %s\r\n",text2);
	printf("text = %x\r\n",text2[0]);
	printf("text = %x\r\n",text2[1]);
	printf("text = %x\r\n",text2[2]);
	printf("text = %x\r\n",text2[3]);
//	printf("text = %x\r\n",text2[4]);
//	printf("text = %x\r\n",text2[5]);
	
	print_charer();
		print_charer_2();
	
  while(1)
	{	
		
	}	
}

//���룬˳��
uint8_t charer[] = {0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x7F,0xF8,0x00,0x08,
										0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0xF8,0x00,0x08};/*"��",0*/


//���룬˳��
//uint8_t charer[] = 	{0xFE,0xFF,0xDE,0xF7,0xEE,0xF7,0xF6,0xEF,0xF6,0xDF,0xFE,0xFF,0x80,0x07,0xFF,0xF7,
//0xFF,0xF7,0xFF,0xF7,0xC0,0x07,0xFF,0xF7,0xFF,0xF7,0xFF,0xF7,0x80,0x07,0xFF,0xF7};/*"��",0*/
		
//���룬����
//uint8_t charer[] = {0x80,0x00,0x84,0x10,0x88,0x10,0x90,0x08,0x90,0x04,0x80,0x00,0xFE,0x1F,0x00,0x10,
//0x00,0x10,0x00,0x10,0xFC,0x1F,0x00,0x10,0x00,0x10,0x00,0x10,0xFE,0x1F,0x00,0x10};/*"��",0*/


uint8_t charer_2[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x38,0x00,
0x00,0x38,0x00,0x1F,0xFF,0xF8,0x1E,0x38,0x78,0x18,0x38,0x18,0x18,0x38,0x18,0x1F,0xFF,0xF8,0x1F,0xFF,0xF8,0x00,0x38,0x00,
0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00/*"��",0*/

};
						


void print_charer(void)
{
	uint16_t i,j;
	uint8_t ch;
	
	for(i=0;i<16;i++)
	{
		
		for(j=0;j<8;j++)
		{
			//charer[i*2]
			ch = (charer[i*2]<<j);
			
			if ((ch & 0x80) == 0)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}
			
		}
		
		for(j=0;j<8;j++)
		{
			//charer[i*2+1]
			ch = (charer[i*2+1]<<j);
			
			if ((ch & 0x80) == 0)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}			
		}

		printf("\r\n");
	}
}


void print_charer_2(void)
{
	uint16_t i,j;
	uint8_t ch;
	
	for(i=0;i<24;i++)
	{
		
		for(j=0;j<8;j++)
		{
			//charer[i*2]
			ch = (charer_2[i*3]<<j);
			
			if ((ch & 0x80) == 0)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}
			
		}
		
		for(j=0;j<8;j++)
		{
			//charer[i*2+1]
			ch = (charer_2[i*3+1]<<j);
			
			if ((ch & 0x80) == 0)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}			
		}
		
		for(j=0;j<8;j++)
		{
			//charer[i*2+1]
			ch = (charer_2[i*3+2]<<j);
			
			if ((ch & 0x80) == 0)
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}			
		}

		printf("\r\n");
	}
}

/*********************************************END OF FILE**********************/

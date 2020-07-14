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


#define PAGE_ADDR(n)   (0x08000000 + n*2048)

uint32_t write_buff[10];
uint32_t read_buff[10];

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint8_t i;
	uint32_t write_addr=0;
	uint32_t *wrtie_data_p;
	uint32_t *read_p ;
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	//����ڲ�FLASH����
	FLASH_Unlock();
	
	//д��ǰ�����Ȳ���
	FLASH_ErasePage(PAGE_ADDR(5));
	
	printf("\r\n�������");

	
	for(i=0;i<10;i++)
	{
		write_buff[i] = i;
	}
	
	//д��Ļ�ַ
	write_addr = PAGE_ADDR(5);
	wrtie_data_p = (uint32_t *)write_buff;
	
	for(i=0;i<10;i++)
	{
		//д������
		FLASH_ProgramWord(write_addr,*wrtie_data_p);
		write_addr += 4;	
		wrtie_data_p++;		
	}
	
	printf("\r\nд�����");
	
	//��������
	FLASH_Lock();
	
	
	//��ȡ����
	read_p = (uint32_t *)PAGE_ADDR(5);
	
	for(i=0;i<10;i++)
	{
		read_buff[i] = *read_p;
		read_p++;
	}
	
	printf("\r\n��ȡ���");
	
	for(i=0;i<10;i++)
	{
		printf("\r\nwrite[%d] = %d , read[%d] = %d",i,write_buff[i],i,read_buff[i]);
		if(write_buff[i] != read_buff[i])
		{
			printf("\r\n����У�鲻��");
			break;
		}
		
		if(i == 9)
		{
			printf("\r\nд����������ȡ��������ȫһ��");
		}
	}
	
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

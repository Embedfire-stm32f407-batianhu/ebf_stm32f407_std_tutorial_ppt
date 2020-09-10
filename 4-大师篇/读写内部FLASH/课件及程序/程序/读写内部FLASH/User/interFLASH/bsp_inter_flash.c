/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��д�ڲ�FLASH�Ĳ����ļ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./interFLASH/bsp_inter_flash.h"


#define TEST_ADDR  0x08008000
#define TEST_DATA  0x12

void inter_flash_test(void)
{
	char *byte_p = (char *)TEST_ADDR;
	uint16_t *half_word_p = (uint16_t *)TEST_ADDR;

	
	//1.����
	//2.����
	//3.д��
	//4.����
	//5.��ȡУ��
	
	FLASH_Status status;
	
	FLASH_Unlock();
	
	//�����ڶ�������
	status = FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n�����������");
	}
	else
	{
		printf("\r\n��������ʧ��");
	}
	
	//д������
	status = FLASH_ProgramByte(TEST_ADDR,TEST_DATA);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\nд�����");
	}
	else
	{
		printf("\r\nд��ʧ��");
	}
	
	//У��д��������Ƿ�����
	printf("\r\n��ȡ��ַ0x%x����������:0x%x",TEST_ADDR,*byte_p);
	
	
	
	//�����ڶ�������
	status = FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n�����������");
	}
	else
	{
		printf("\r\n��������ʧ��");
	}
		
	//д������
	status = FLASH_ProgramHalfWord(TEST_ADDR,0x55);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\nд�����");
	}
	else
	{
		printf("\r\nд��ʧ��");
	}
	
	//У��д��������Ƿ�����
	printf("\r\n��ȡ��ַ0x%x����������:0x%x",TEST_ADDR,*half_word_p);
	
	FLASH_Lock();
	
	//����֮���ٴζ�ȡ��У��д��������Ƿ�����
	printf("\r\n�������ȡ��ַ0x%x����������:0x%x",TEST_ADDR,*half_word_p);
	
}
/*********************************************END OF FILE**********************/

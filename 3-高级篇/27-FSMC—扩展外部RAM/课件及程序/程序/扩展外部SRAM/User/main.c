/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڽӷ����ԣ����ڽ��յ����ݺ����ϻش���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./sram/bsp_sram.h" 


#define SRAM_BASE_ADDR  0x6C000000
#define INER_SRAM_ADDR  0x20001000

volatile uint8_t testvalue __attribute((at(0x6C000050)));
volatile double testvalue_double __attribute((at(0x6C000080)));

//�������� ������ __attribute((at(ָ���ı�����ַ)));
//����ַΪ�ⲿSRAM�ռ�ʱ
//1.����Ϊȫ�ֱ���
//2.��������ĳ�ʼֵ��Ч
//3.�������FSMC��ʼ��֮���ʹ��

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	//����volatile��ֹCPU�Ż�
	volatile uint8_t * p = (uint8_t *)SRAM_BASE_ADDR;
	volatile uint16_t * p_16 = (uint16_t *)(SRAM_BASE_ADDR+10);
	volatile uint32_t * p_32 = (uint32_t *)(SRAM_BASE_ADDR+20);

	//����volatile��ֹCPU�Ż�
	volatile uint8_t * p_iner = (uint8_t *)INER_SRAM_ADDR;
	

	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	
	//��ʼ��FSMC
	FSMC_Config();	
	
	testvalue = 0xA;	
	printf("\ntestvalue������Ϊ:0x%x,���ַΪ:0x%x",testvalue,&testvalue);
	
	testvalue_double = 0.166;
	printf("\ntestvalue_double������Ϊ:%f,���ַΪ:0x%x",testvalue_double,&testvalue_double);


	/* ����һ���ַ��� */
	printf("\n����һ�������жϽ��ջ���ʵ��\n");
	
	//д�����
	*p = 0xAA;
	
	//��ȡ����
	printf("\nPд�������Ϊ:0x%x",*p);
	
		//д�����
	*p_16 = 0xABCD;
	
	//��ȡ����
	printf("\nP16д�������Ϊ:0x%x",*p_16);
	
			//д�����
	*p_32 = 0x01ABCDEF;
	
	//��ȡ����
	printf("\nP32д�������Ϊ:0x%x",*p_32);
	
	
	//д�����
	*p_iner = 0x77;
	
	//��ȡ����
	printf("\nд�������Ϊ:0x%x",*p_iner);
	
	
	
  while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


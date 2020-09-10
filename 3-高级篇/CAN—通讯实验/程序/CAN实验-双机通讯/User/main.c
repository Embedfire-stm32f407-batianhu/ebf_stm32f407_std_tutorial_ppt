/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   CANʵ��
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
#include "./can/bsp_can.h"
#include "./key/bsp_key.h" 

/// ����ȷ����ʱ
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

CanTxMsg test_TxMsg;

CanRxMsg test_RxMsg;

uint8_t rec_flag = 0;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint8_t mail_box;
	uint8_t i = 0;
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	Key_GPIO_Config();
	
	//��ʼ��CAN
	CAN_Config();
	//��ʼ��ɸѡ��
	CAN_Filter_Config();
	
	/* ����һ���ַ��� */
	printf("����һ��CANʵ��\n");
	
	printf("\r\n ʵ�鲽�裺\r\n");

	printf("\r\n 1.ʹ�ûػ�ģʽ������Ҫ�����ⲿоƬ\r\n");
	printf("\r\n 2.���¿������KEY1������ʹ��CAN���ⷢ��0-7�����ݰ���������չIDΪ0x1314 (���ڻػ�ģʽ�����Լ����͸��Լ�)\r\n");
	printf("\r\n 3.���������CAN���յ���չIDΪ0x1314�����ݰ�����������Դ�ӡ�����ڡ� \r\n");
	printf("\r\n 4.�����е�can������Ϊ1MBps��Ϊstm32��can������ʡ� \r\n");
	
  while(1)
	{	
		//���°�������������
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			//����Ҫ���͵�����
			test_TxMsg.StdId = 0;
			test_TxMsg.ExtId = 0x1314;
			test_TxMsg.IDE = CAN_ID_EXT ;		
			test_TxMsg.RTR = CAN_RTR_DATA ;			
			test_TxMsg.DLC = 8;
			
			for(i=0;i<8;i++)
			{
				test_TxMsg.Data[i] = i;
			}			
			
			printf("\r\n ׼����������");
			//��������
			mail_box = CAN_Transmit(TEST_CAN, &test_TxMsg);
			
			if(mail_box != CAN_TxStatus_NoMailBox)
			{
				//�ȴ�ֱ�����ݷ��͵�CAN�շ������
				while(CAN_TransmitStatus(TEST_CAN,mail_box) != CAN_TxStatus_Ok);
				
				//��һ����ʱ��ȴ�CAN�շ��������ݷ��͵�����
				can_delay(0x1000);				
				printf("\r\n �����������");
			}
			else
			{
				printf("\r\n no mail box");
			}		
		}
		
		
		//��������
		if(rec_flag == 1)
		{		

			printf("\r\nCAN Rx.StdId =%x",test_RxMsg.StdId);
			printf("\r\nCAN Rx.ExtId =%x",test_RxMsg.ExtId);
			printf("\r\nCAN Rx.IDE =%x",test_RxMsg.IDE);
			printf("\r\nCAN Rx.RTR =%x",test_RxMsg.RTR);
			printf("\r\nCAN Rx.DLC =%x",test_RxMsg.DLC);
			printf("\r\nCAN Rx.FMI =%x",test_RxMsg.FMI);
			
			for(i=0;i<test_RxMsg.DLC;i++)
			{
				printf("\r\nCAN Rx.Data[%d] =%x",i,test_RxMsg.Data[i]);
			}			
			
			rec_flag = 0;
			
		}
		
	}	
}



/*********************************************END OF FILE**********************/


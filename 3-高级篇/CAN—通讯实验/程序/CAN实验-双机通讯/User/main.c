/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   CAN实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./can/bsp_can.h"
#include "./key/bsp_key.h" 

/// 不精确的延时
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

CanTxMsg test_TxMsg;

CanRxMsg test_RxMsg;

uint8_t rec_flag = 0;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint8_t mail_box;
	uint8_t i = 0;
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	Key_GPIO_Config();
	
	//初始化CAN
	CAN_Config();
	//初始化筛选器
	CAN_Filter_Config();
	
	/* 发送一个字符串 */
	printf("这是一个CAN实验\n");
	
	printf("\r\n 实验步骤：\r\n");

	printf("\r\n 1.使用回环模式，不需要连接外部芯片\r\n");
	printf("\r\n 2.按下开发板的KEY1键，会使用CAN向外发送0-7的数据包，包的扩展ID为0x1314 (由于回环模式，是自己发送给自己)\r\n");
	printf("\r\n 3.若开发板的CAN接收到扩展ID为0x1314的数据包，会把数据以打印到串口。 \r\n");
	printf("\r\n 4.本例中的can波特率为1MBps，为stm32的can最高速率。 \r\n");
	
  while(1)
	{	
		//按下按键，发送数据
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			//设置要发送的数据
			test_TxMsg.StdId = 0;
			test_TxMsg.ExtId = 0x1314;
			test_TxMsg.IDE = CAN_ID_EXT ;		
			test_TxMsg.RTR = CAN_RTR_DATA ;			
			test_TxMsg.DLC = 8;
			
			for(i=0;i<8;i++)
			{
				test_TxMsg.Data[i] = i;
			}			
			
			printf("\r\n 准备发送数据");
			//发送数据
			mail_box = CAN_Transmit(TEST_CAN, &test_TxMsg);
			
			if(mail_box != CAN_TxStatus_NoMailBox)
			{
				//等待直至数据发送到CAN收发器完成
				while(CAN_TransmitStatus(TEST_CAN,mail_box) != CAN_TxStatus_Ok);
				
				//给一定的时间等待CAN收发器把数据发送到总线
				can_delay(0x1000);				
				printf("\r\n 发送数据完成");
			}
			else
			{
				printf("\r\n no mail box");
			}		
		}
		
		
		//接收数据
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


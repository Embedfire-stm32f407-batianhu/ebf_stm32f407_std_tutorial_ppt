/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I2C EEPROM(AT24C02)���ԣ��洢С��
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
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include "./led/bsp_led.h"
#include <string.h>


uint8_t cal_flag = 0;
uint8_t k;

/*�洢С�������������飬��7��*/
long double double_buffer[7] = {0};
int int_bufffer[7] = {0};

#define DOUBLE_ADDR       10
#define LONGINT_ADDR      70

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 
	uint8_t i;
	
	double w_temp=456.55;
	
	uint8_t r_temp[sizeof(w_temp)]={0};
	
  LED_GPIO_Config();

  /* ���ڳ�ʼ�� */
	USART_Config();
	
	printf("\r\n ����һ��EEPROM ��дС���ͳ�����ʵ�� \r\n");

	/* I2C �����(AT24C02)ʼ�� */
		i2c_CfgGpio();
   
	printf("\r\ndoublesize = %d",sizeof(w_temp));
	
	ee_WriteBytes((uint8_t *)&w_temp,0,sizeof(w_temp));
	
	ee_ReadBytes(r_temp, 0, sizeof(w_temp));
	
	for(i=0;i<sizeof(w_temp);i++)
	{
		printf("\r\ntemp[%d]=%x",i,r_temp[i]);
	}
//	printf("\r\nr_temp0=%x,r_temp1=%x,r_temp2=%x,r_temp3=%x",r_temp[0],r_temp[1],r_temp[2],r_temp[3]);
	
	
	printf("\r\n temp =%f",*(double *)r_temp+10);

//  		/*��ȡ���ݱ�־λ*/
//    ee_ReadBytes(&cal_flag, 0, 1);
//  
//    if( cal_flag != 0xCD )	/*����־����0xcd����ʾ֮ǰ����д������*/
//    {      
//        printf("\r\nû�м�⵽���ݱ�־��FLASHû�д洢���ݣ���������С��д��ʵ��\r\n");
//        cal_flag =0xCD;
//        
//        /*д���־��0��ַ*/
//        ee_WriteBytes(&cal_flag, 0, 1); 
//        
//        /*����Ҫд�������*/
//        for( k=0; k<7; k++ )
//        {
//           double_buffer[k] = k +0.1;
//           int_bufffer[k]=k*500+1 ;
//        }

//        /*д��С�����ݵ���ַ10*/
//        ee_WriteBytes((void*)double_buffer,DOUBLE_ADDR, sizeof(double_buffer));
//        /*д���������ݵ���ַ60*/
//        ee_WriteBytes((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
//              
//        printf("��оƬд�����ݣ�");
//        /*��ӡ������*/
//        for( k=0; k<7; k++ )
//        {
//          printf("С��tx = %LF\r\n",double_buffer[k]);
//          printf("����tx = %d\r\n",int_bufffer[k]);
//        }
//        
//        printf("\r\n�븴λ�����壬�Զ�ȡ���ݽ��м���\r\n");      
//		
//    }    
//    else
//    {      
//      	 printf("\r\n��⵽���ݱ�־\r\n");

//				/*��ȡС������*/
//        ee_ReadBytes((void*)double_buffer, DOUBLE_ADDR, sizeof(double_buffer));
//				
//				/*��ȡ��������*/
//        ee_ReadBytes((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
//	
//			
//				printf("\r\n��оƬ�������ݣ�\r\n");			
//        for( k=0; k<7; k++ )
//				{
//					printf("С�� rx = %LF \r\n",double_buffer[k]);
//					printf("���� rx = %d \r\n",int_bufffer[k]);				
//				}
//      
//    }   

  
  while (1)
  {      
  }
}

/*********************************************END OF FILE**********************/

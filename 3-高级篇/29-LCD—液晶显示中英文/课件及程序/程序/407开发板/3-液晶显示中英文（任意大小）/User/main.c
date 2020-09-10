/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   Һ����ʾ����
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
#include "./led/bsp_led.h"  
#include "./lcd/bsp_ili9806g_lcd.h"

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );

void Printf_Charater(void)   ;


int main(void)
{	
	//LCD ��ʼ��
	ILI9806G_Init ();         

	/* USART config */
	Debug_USART_Config();		

	
	printf("\r\n ********** Һ����������ʾ�����ֿ����ⲿFLASH��*********** \r\n"); 
	printf("\r\n ��������ʾ�����������Ķ������е�readme.txt�ļ�˵��������Ҫ���FLASH��ˢ��ģ����\r\n"); 

 //����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
 //���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
 //���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
	ILI9806G_GramScan ( 6 );
	
	Printf_Charater();
	
	while ( 1 )
	{
		LCD_Test();
	}
	
	
}



/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	/*��ʾ��ʾ����*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;	
	
	LCD_SetFont(&Font16x32);
	LCD_SetColors(RED,BLACK);

  ILI9806G_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */

	/********��ʾ�ַ���ʾ��*******/ 
  ILI9806G_DispStringLine_EN_CH(LINE(0),"����BH");
	//��ʾָ����С���ַ� 
	ILI9806G_DisplayStringEx(0,1*48,48,48,(uint8_t *)"����BH",0);
	ILI9806G_DisplayStringEx(0,2*56,56,56,(uint8_t *)"����BH",0);

	/********��ʾ����ʾ��*******/
	LCD_SetTextColor(GREEN);

	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"��ʾ�������� : %d ",testCNT);
  ILI9806G_ClearLine(LINE(7));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	ILI9806G_DispStringLine_EN(LINE(7),dispBuff);

	/*******��ʾͼ��ʾ��******/
  /* ��ֱ�� */
  
  ILI9806G_ClearLine(LINE(7));/* ����������� */
	LCD_SetTextColor(BLUE);

  ILI9806G_DispStringLine_EN_CH(LINE(7),"��ֱ��:");
  
	LCD_SetTextColor(RED);
  ILI9806G_DrawLine(50,270,420,275);  
  ILI9806G_DrawLine(50,300,420,375);
  
	LCD_SetTextColor(GREEN);
  ILI9806G_DrawLine(50,370,420,475);  
  ILI9806G_DrawLine(50,400,420,475);
	
	LCD_SetTextColor(BLUE);
  ILI9806G_DrawLine(50,420,420,325);  
  ILI9806G_DrawLine(50,450,420,395);
  
  Delay(0x2FFFFFF);
  
  ILI9806G_Clear(0,32*7,LCD_X_LENGTH,LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */
  
  
  /*������*/

  ILI9806G_ClearLine(LINE(7));	/* ����������� */
	LCD_SetTextColor(BLUE);

  ILI9806G_DispStringLine_EN_CH(LINE(7),"������:");

	LCD_SetTextColor(RED);
  ILI9806G_DrawRectangle(50,300,200,100,1);
	
	LCD_SetTextColor(GREEN);
  ILI9806G_DrawRectangle(100,300,200,120,0);
	
	LCD_SetTextColor(BLUE);
  ILI9806G_DrawRectangle(250,300,200,150,1);
  
  
  Delay(0x2FFFFFF);
	
	ILI9806G_Clear(0,32*7,LCD_X_LENGTH,LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */

  /* ��Բ */
  ILI9806G_ClearLine(LINE(7));	/* ����������� */
	LCD_SetTextColor(BLUE);
	
  ILI9806G_DispStringLine_EN_CH(LINE(7),"��Բ:");

	LCD_SetTextColor(RED);
	ILI9806G_DrawCircle(150,400,60,1);

	LCD_SetTextColor(GREEN);
	ILI9806G_DrawCircle(250,400,60,0);

	LCD_SetTextColor(BLUE);
	ILI9806G_DrawCircle(350,400,60,1);

  Delay(0x2FFFFFF);
  
  ILI9806G_Clear(0,32*7,LCD_X_LENGTH,LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */

}


/**
  * @brief  ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}



/*"��"�ַ�����ģ16x16 */ 	  
unsigned char charater_matrix[] =    
{ /*"��",0*/
0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x7F,0xF8,0x00,	0x08,
0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0xF8,0x00,0x08,

};   
  
/**
  * @brief  ʹ�ô�������λ����ӡ��ģ
	*					��ʾ��ģ��ʾԭ��
  * @retval ��
  */
void Printf_Charater(void)   
{   
	int i,j;   
	unsigned char kk; 
  
	/*i�����м���*/
  for ( i=0;i<16;i++)   
	{   
		/*j����һ�ֽ������ݵ���λ����*/
		/*һ�����صĵ�һ���ֽ�*/
    for(j=0; j<8; j++)   
    {      
			/*һ������λһ������λ�ش���*/
      kk = charater_matrix[2*i] << j ;  //����Jλ          
			if( kk & 0x80)     
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ�  
			}   
    }   
		/*һ�����صĵڶ����ֽ�*/
    for(j=0; j<8; j++)   
		{              
      kk = charater_matrix[2*i+1] << j ;  //����Jλ   
       
			if( kk & 0x80)         
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�   
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ� 
			}   
		}         
    printf("\n");    //�����һ�����أ����� 
	}   
	printf("\n\n"); 		//һ����������
}   


/*********************************************END OF FILE**********************/


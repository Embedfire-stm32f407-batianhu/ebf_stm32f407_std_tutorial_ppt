  /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi flash �ײ�Ӧ�ú���bsp 
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./lcd/bsp_xpt2046_lcd.h"



/*
1.��ʼ����������
2.��д���SPI��д����
3.��XPT2046���Ϳ����֣���������X,Y��ԭʼ�������꣨��ѹ���ݣ�

ԭʼ�����������꣺��ѹ 0-4096  ------ 0-3.3V
�߼����꣺��Ч��Һ�����ķֱ��� x:0-240  y:0-320
*/


/**
  * @brief  ���� XPT2046 �ļ�΢�뼶��ʱ����
  * @param  nCount ����ʱ����ֵ����λΪ΢��
  * @retval ��
  */	
static void XPT2046_DelayUS ( __IO uint32_t ulCount )
{
	uint32_t i;

	for ( i = 0; i < ulCount; i ++ )
	{
		uint8_t uc = 12;     //����ֵΪ12����Լ��1΢��  
	      
		while ( uc -- );     //��1΢��	

	}	
}


/**
  * @brief  ���ų�ʼ��
  * @param  ��
  * @retval ��
  */
void XPT2046_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	/* ʹ��SPI������ص�ʱ�� */
 	RCC_APB2PeriphClockCmd ( XPT2046_SPI_CS_CLK|XPT2046_SPI_SCK_CLK|
																XPT2046_SPI_MISO_CLK|XPT2046_SPI_MOSI_CLK|
																XPT2046_INT_CLK, ENABLE );
	
  /* ����SPI�� CS���ţ���ͨIO���� */
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);
	
  /* ����SPI�� SCK����*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_SCK_PIN;
  GPIO_Init(XPT2046_SPI_SCK_PORT, &GPIO_InitStructure);
	 
	/* ����SPI�� MOSI����*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
  GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);	

  /* ����SPI�� MISO����*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);
	
	/* ����INT����*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_INT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(XPT2046_INT_PORT, &GPIO_InitStructure);

  /* ֹͣ�ź� CS���Ÿߵ�ƽ*/
  SPI_XPT2046_CS_HIGH();
	
}
 
//дһ���ֽ�
void XPT2046_Write_Byte(uint8_t data)
{
	uint8_t i;
	
//	SPI_XPT2046_CS_LOW();
	SPI_XPT2046_SCK_LOW();
	SPI_XPT2046_MOSI_LOW();
	
	for(i=0;i<8;i++)
	{
		if(data&0x80)
		{
			SPI_XPT2046_MOSI_HIGH();  
		}
		else
		{
			SPI_XPT2046_MOSI_LOW();
		}
		
		XPT2046_DelayUS(5);
		
		SPI_XPT2046_SCK_HIGH();
		
		XPT2046_DelayUS(5);
		
		SPI_XPT2046_SCK_LOW();		
		
		data <<= 1;
	}
	
//	SPI_XPT2046_CS_HIGH();	

}


//��ȡ����
uint16_t XPT2046_Read_data(void)
{
	uint8_t i;
	uint16_t re_data = 0;
	
	SPI_XPT2046_SCK_HIGH();
	SPI_XPT2046_MOSI_LOW();
	
	for(i=0;i<12;i++)
	{
		re_data <<= 1;
		
		SPI_XPT2046_SCK_LOW();
		XPT2046_DelayUS(5);
		
		SPI_XPT2046_SCK_HIGH();
		
		re_data |= SPI_XPT2046_MISO();
		
	}	

	return re_data;

}

//��ȡadc����
uint16_t XPT2046_Read_adc(uint8_t cmd)
{
	uint16_t temp;
	
	SPI_XPT2046_CS_LOW();
	
	XPT2046_Write_Byte(cmd);
	
	temp = XPT2046_Read_data();	
	
	SPI_XPT2046_CS_HIGH();	
	
	return temp;
}

   
/*********************************************END OF FILE**********************/


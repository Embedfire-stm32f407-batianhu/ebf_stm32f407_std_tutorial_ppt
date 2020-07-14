/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "bsp_i2c_gpio.h"   

 /**
  * @brief  ��ʼ������i2c��IO
  * @param  ��
  * @retval ��
  */
void i2c_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����i2c��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( I2C_SCL_GPIO_CLK | I2C_SDA_GPIO_CLK , ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = I2C_SCL_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
		GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);	
		
	//SDA
	
		GPIO_InitStructure.GPIO_Pin = I2C_SDA_GPIO_PIN;
	
		GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);		


}

static void i2c_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
	*/
	for (i = 0; i < 10; i++);
}


//������ʼ�ź�
void i2c_START(void)
{
	EEPROM_I2C_SDA_1();	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SDA_0();	
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	
}


//���������ź�
void i2c_STOP(void)
{
	EEPROM_I2C_SDA_0();	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SDA_1();	
	i2c_Delay();	
}

//����Ӧ���ź�
void i2c_ASK(void)
{
	EEPROM_I2C_SDA_0();	
	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
	
	EEPROM_I2C_SDA_1();	//�ͷſ���Ȩ
	i2c_Delay();	
}

//������Ӧ���ź�
void i2c_NASK(void)
{
	EEPROM_I2C_SDA_1();	
	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();		
}


//�ȴ�Ӧ���ź� NASK��1   ASK��0
uint8_t i2c_WAIT_ASK(void)
{
	uint8_t reply;
	
	EEPROM_I2C_SDA_1();	//�ͷſ���Ȩ
	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	if( EEPROM_I2C_SDA_READ()==1 )
	{
		reply = 1;
	}
	else
	{
		reply = 0;
	}
	
	EEPROM_I2C_SCL_0();
	
	i2c_Delay();	

	return reply;
}

//д��һ���ֽ�
void i2c_WRITE_BYTE(uint8_t data)
{
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		if(data & 0x80)
		{
			EEPROM_I2C_SDA_1();
		}
		else
		{
			EEPROM_I2C_SDA_0();	
		}
		i2c_Delay();
		
		EEPROM_I2C_SCL_1();
		i2c_Delay();
		
		EEPROM_I2C_SCL_0();
		i2c_Delay();
		
		if(i==7)
		{
			EEPROM_I2C_SDA_1(); //�ͷſ���Ȩ
		}

		data<<=1;
	}		
}


//��ȡһ���ֽ�
uint8_t i2c_READ_BYTE(void)
{
	uint8_t i;
	
	uint8_t temp = 0;
	
	for(i=0;i<8;i++)
	{		
		temp<<=1;
		
		EEPROM_I2C_SCL_1();
		i2c_Delay();
		
		if( EEPROM_I2C_SDA_READ()==1 )
		{
			temp += 1;
		}
		
		EEPROM_I2C_SCL_0();
		i2c_Delay();
	}		
	
	return temp;
}





/*********************************************END OF FILE**********************/

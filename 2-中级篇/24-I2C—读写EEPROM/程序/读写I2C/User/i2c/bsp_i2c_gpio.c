/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "bsp_i2c_gpio.h"   

 /**
  * @brief  初始化控制i2c的IO
  * @param  无
  * @retval 无
  */
void i2c_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启i2c相关的GPIO外设时钟*/
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

	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
	for (i = 0; i < 10; i++);
}


//产生起始信号
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


//产生结束信号
void i2c_STOP(void)
{
	EEPROM_I2C_SDA_0();	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SDA_1();	
	i2c_Delay();	
}

//产生应答信号
void i2c_ASK(void)
{
	EEPROM_I2C_SDA_0();	
	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
	
	EEPROM_I2C_SDA_1();	//释放控制权
	i2c_Delay();	
}

//产生非应答信号
void i2c_NASK(void)
{
	EEPROM_I2C_SDA_1();	
	
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();		
}


//等待应答信号 NASK：1   ASK：0
uint8_t i2c_WAIT_ASK(void)
{
	uint8_t reply;
	
	EEPROM_I2C_SDA_1();	//释放控制权
	
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

//写入一个字节
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
			EEPROM_I2C_SDA_1(); //释放控制权
		}

		data<<=1;
	}		
}


//读取一个字节
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

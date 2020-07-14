  /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi flash 底层应用函数bsp 
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./lcd/bsp_xpt2046_lcd.h"



/*
1.初始化驱动引脚
2.编写软件SPI读写函数
3.向XPT2046发送控制字，让它测量X,Y的原始触摸坐标（电压数据）

原始触摸物理坐标：电压 0-4096  ------ 0-3.3V
逻辑坐标：等效于液晶屏的分辨率 x:0-240  y:0-320
*/


/**
  * @brief  用于 XPT2046 的简单微秒级延时函数
  * @param  nCount ：延时计数值，单位为微妙
  * @retval 无
  */	
static void XPT2046_DelayUS ( __IO uint32_t ulCount )
{
	uint32_t i;

	for ( i = 0; i < ulCount; i ++ )
	{
		uint8_t uc = 12;     //设置值为12，大约延1微秒  
	      
		while ( uc -- );     //延1微秒	

	}	
}


/**
  * @brief  引脚初始化
  * @param  无
  * @retval 无
  */
void XPT2046_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	/* 使能SPI引脚相关的时钟 */
 	RCC_APB2PeriphClockCmd ( XPT2046_SPI_CS_CLK|XPT2046_SPI_SCK_CLK|
																XPT2046_SPI_MISO_CLK|XPT2046_SPI_MOSI_CLK|
																XPT2046_INT_CLK, ENABLE );
	
  /* 配置SPI的 CS引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);
	
  /* 配置SPI的 SCK引脚*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_SCK_PIN;
  GPIO_Init(XPT2046_SPI_SCK_PORT, &GPIO_InitStructure);
	 
	/* 配置SPI的 MOSI引脚*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
  GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);	

  /* 配置SPI的 MISO引脚*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);
	
	/* 配置INT引脚*/
  GPIO_InitStructure.GPIO_Pin = XPT2046_INT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(XPT2046_INT_PORT, &GPIO_InitStructure);

  /* 停止信号 CS引脚高电平*/
  SPI_XPT2046_CS_HIGH();
	
}
 
//写一个字节
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


//读取数据
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

//读取adc数据
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


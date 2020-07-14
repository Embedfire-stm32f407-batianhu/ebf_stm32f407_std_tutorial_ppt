 /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ILI9341
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./lcd/bsp_ili9341_lcd.h"


/*
1.初始化跟液晶控制相关的引脚
  初始化时要确认配置GPIOB使用的PB3/PB4引脚，
	需要重定义才能用作普通GPIO
	
2.模拟8080时序
  写命令
	写数据
	读数据
	
3.通过读取ILI9341的ID测试函数
4.初始化液晶屏及配置扫描方向
5.往LCD坐标x,y写一个特定颜色像素点
*/


//根据液晶扫描方向而变化的XY像素宽度
//调用ILI9341_GramScan函数设置方向时会自动更改
uint16_t LCD_X_LENGTH = ILI9341_LESS_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9341_MORE_PIXEL;

//液晶屏扫描模式，本变量主要用于方便选择触摸屏的计算参数
//参数可选值为0-7
//调用ILI9341_GramScan函数设置方向时会自动更改
//LCD刚初始化完成时会使用本默认值
uint8_t LCD_SCAN_MODE = 6;

/**
  * @brief  用于 ILI9341 简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */	
static void ILI9341_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

#define ILI9341_DELAY()  //ILI9341_Delay(10)

/**
  * @brief  ILI9341_GPIO_Init初始化
  * @param  无
  * @retval 无
  */
void ILI9341_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能复用时钟AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//把PB3 PB4引脚用作普通GPIO
	//不能使用JTAG功能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	/* 使能引脚相关的时钟 */
 	RCC_APB2PeriphClockCmd (ILI9341_CS_CLK|ILI9341_RD_CLK|ILI9341_WE_CLK|
													ILI9341_DC_CLK|ILI9341_BK_CLK|ILI9341_DATA_CLK, ENABLE );
	
  /* 默认全配置成输出模式 */
  GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN;
  GPIO_Init(ILI9341_RD_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_WE_PIN;
  GPIO_Init(ILI9341_WE_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_DC_PIN;
  GPIO_Init(ILI9341_DC_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN;
  GPIO_Init(ILI9341_BK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
  GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);
	
	/*默认点亮背光*/
	LCD_BK_ON();
	
}


 
//写命令
void ILI9341_Write_CMD(uint16_t cmd)
{
	LCD_CS_LOW();
	ILI9341_DELAY();
	
	LCD_DC_LOW();
	ILI9341_DELAY();
	
	LCD_RD_HIGH();
	ILI9341_DELAY();
	
	LCD_DATA_OUT(cmd);	
	ILI9341_DELAY();
	
	LCD_WE_LOW();	
	ILI9341_DELAY();
	
	LCD_WE_HIGH();	
	ILI9341_DELAY();
	
	LCD_CS_HIGH();
}
 
//写数据
void ILI9341_Write_Data(uint16_t data)
{
	LCD_CS_LOW();
	ILI9341_DELAY();
	
	LCD_DC_HIGH();
	ILI9341_DELAY();
	
	LCD_RD_HIGH();
	ILI9341_DELAY();
	
	LCD_DATA_OUT(data);	
	ILI9341_DELAY();
	
	LCD_WE_LOW();	
	ILI9341_DELAY();
	
	LCD_WE_HIGH();	
	ILI9341_DELAY();
	
	LCD_CS_HIGH();	

}

//读数据
uint16_t ILI9341_Read_Data(void)
{
	uint16_t data;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 切换data端口为输入模式 */
  GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);		
	
	
	LCD_CS_LOW();
	ILI9341_DELAY();
	
	LCD_DC_HIGH();
	ILI9341_DELAY();
	
	LCD_WE_HIGH();	
	ILI9341_DELAY();	
	
	LCD_RD_LOW();
	ILI9341_DELAY();	
	
	data = LCD_DATA_IN();	
	ILI9341_DELAY();
		
	LCD_RD_HIGH();
	ILI9341_DELAY();	

	LCD_CS_HIGH();
	
	
	/* 切换data端口为输出模式 */
  GPIO_InitStructure.GPIO_Pin = ILI9341_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(ILI9341_DATA_PORT, &GPIO_InitStructure);		
	
	return data;
}

//读取ID
uint16_t ILI9341_Read_ID(void)
{
	uint16_t temp = 0 ;
	
	ILI9341_Write_CMD(0xD3);
	
	ILI9341_Read_Data();
	
	ILI9341_Read_Data();
	
	temp = ILI9341_Read_Data();
	temp <<=8;
	temp |= ILI9341_Read_Data();
	
	return temp;
	
}



/**
 * @brief  初始化ILI9341寄存器
 * @param  无
 * @retval 无
 */
void ILI9341_REG_Config ( void )
{	
	/*  Power control B (CFh)  */
	DEBUG_DELAY  ();
	ILI9341_Write_CMD ( 0xCF  );
	ILI9341_Write_Data ( 0x00  );
	ILI9341_Write_Data ( 0x81  );
	ILI9341_Write_Data ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xED );
	ILI9341_Write_Data ( 0x64 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x12 );
	ILI9341_Write_Data ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xE8 );
	ILI9341_Write_Data ( 0x85 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x78 );
	
	/*  Power control A (CBh) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xCB );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x2C );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x34 );
	ILI9341_Write_Data ( 0x02 );
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xF7 );
	ILI9341_Write_Data ( 0x20 );
	
	/* Driver timing control B */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xEA );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xB1 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x1B );
	
	/*  Display Function Control (B6h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xB6 );
	ILI9341_Write_Data ( 0x0A );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xC0 );
	ILI9341_Write_Data ( 0x35 );
	
	/* Power Control 2 (C1h) */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0xC1 );
	ILI9341_Write_Data ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	ILI9341_Write_CMD ( 0xC5 );
	ILI9341_Write_Data ( 0x45 );
	ILI9341_Write_Data ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	ILI9341_Write_CMD ( 0xC7 );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Enable 3G (F2h) */
	ILI9341_Write_CMD ( 0xF2 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Gamma Set (26h) */
	ILI9341_Write_CMD ( 0x26 );
	ILI9341_Write_Data ( 0x01 );
	DEBUG_DELAY ();
	
	/* Positive Gamma Correction */
	ILI9341_Write_CMD ( 0xE0 ); //Set Gamma
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x26 );
	ILI9341_Write_Data ( 0x24 );
	ILI9341_Write_Data ( 0x0B );
	ILI9341_Write_Data ( 0x0E );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x54 );
	ILI9341_Write_Data ( 0xA8 );
	ILI9341_Write_Data ( 0x46 );
	ILI9341_Write_Data ( 0x0C );
	ILI9341_Write_Data ( 0x17 );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	ILI9341_Write_CMD ( 0XE1 ); //Set Gamma
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x19 );
	ILI9341_Write_Data ( 0x1B );
	ILI9341_Write_Data ( 0x04 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x2A );
	ILI9341_Write_Data ( 0x47 );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x30 );
	ILI9341_Write_Data ( 0x38 );
	ILI9341_Write_Data ( 0x0F );
	
	/* memory access control set */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0x36 ); 	
	ILI9341_Write_Data ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
	DEBUG_DELAY ();
	
	/* column address control set */
	ILI9341_Write_CMD ( CMD_SetCoordinateX ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0xEF );
	
	/* page address control set */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( CMD_SetCoordinateY ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x01 );
	ILI9341_Write_Data ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY ();
	ILI9341_Write_CMD ( 0x3a ); 
	ILI9341_Write_Data ( 0x55 );
	
	/* Sleep Out (11h)  */
	ILI9341_Write_CMD ( 0x11 );	
	ILI9341_Delay ( 0xAFFf<<2 );
	DEBUG_DELAY ();
	
	/* Display ON (29h) */
	ILI9341_Write_CMD ( 0x29 ); 
		
}


/**
 * @brief  设置ILI9341的GRAM的扫描方向 
 * @param  ucOption ：选择GRAM的扫描方向 
 *     @arg 0-7 :参数可选值为0-7这八个方向
 *
 *	！！！其中0、3、5、6 模式适合从左至右显示文字，
 *				不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
 *		
 *	其中0、2、4、6 模式的X方向像素为240，Y方向像素为320
 *	其中1、3、5、7 模式下X方向像素为320，Y方向像素为240
 *
 *	其中 6 模式为大部分液晶例程的默认显示方向
 *	其中 3 模式为摄像头例程使用的方向
 *	其中 0 模式为BMP图片显示例程使用的方向
 *
 * @retval 无
 * @note  坐标图例：A表示向上，V表示向下，<表示向左，>表示向右
					X表示X轴，Y表示Y轴

------------------------------------------------------------
模式0：				.		模式1：		.	模式2：			.	模式3：					
					A		.					A		.		A					.		A									
					|		.					|		.		|					.		|							
					Y		.					X		.		Y					.		X					
					0		.					1		.		2					.		3					
	<--- X0 o		.	<----Y1	o		.		o 2X--->  .		o 3Y--->	
------------------------------------------------------------	
模式4：				.	模式5：			.	模式6：			.	模式7：					
	<--- X4 o		.	<--- Y5 o		.		o 6X--->  .		o 7Y--->	
					4		.					5		.		6					.		7	
					Y		.					X		.		Y					.		X						
					|		.					|		.		|					.		|							
					V		.					V		.		V					.		V		
---------------------------------------------------------				
											 LCD屏示例
								|-----------------|
								|			秉火Logo		|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|-----------------|
								屏幕正面（宽240，高320）

 *******************************************************/
void ILI9341_GramScan ( uint8_t ucOption )
{	
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;
	
	//根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
	LCD_SCAN_MODE = ucOption;
	
	//根据模式更新XY方向的像素宽度
	if(ucOption%2 == 0)	
	{
		//0 2 4 6模式下X方向像素宽度为240，Y方向为320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7模式下X方向像素宽度为320，Y方向为240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	ILI9341_Write_CMD ( 0x36 ); 
	ILI9341_Write_Data ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式
	ILI9341_Write_CMD ( CMD_SetCoordinateX ); 
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	ILI9341_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x 结束坐标低8位 */

	ILI9341_Write_CMD ( CMD_SetCoordinateY ); 
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	ILI9341_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y 结束坐标低8位 */

	/* write gram start */
	ILI9341_Write_CMD ( CMD_SetPixel );	
}


void ILI9341_Init(void)
{
	ILI9341_GPIO_Init();
	ILI9341_REG_Config();
	ILI9341_GramScan(6);
	ILI9341_Draw_Rect(0,0,LCD_X_LENGTH,LCD_Y_LENGTH,BLACK);
}

//设置要显示的矩形区域
void ILI9341_Open_Window(uint16_t x,uint16_t y,uint16_t width, uint16_t heigh)
{
	ILI9341_Write_CMD(CMD_SetCoordinateX);
	ILI9341_Write_Data( (x&0xFF00) >> 8);//sc高8位
	ILI9341_Write_Data( (x&0xFF) );//sc低8位
	ILI9341_Write_Data( ((x+width-1) & 0xFF00) >> 8);//ec高8位
	ILI9341_Write_Data( ((x+width-1)&0xFF) );//ec低8位
	
	ILI9341_Write_CMD(CMD_SetCoordinateY);
	ILI9341_Write_Data( (y&0xFF00) >> 8);//sp高8位
	ILI9341_Write_Data( (y&0xFF) );//sp低8位
	ILI9341_Write_Data( ((y+heigh-1) & 0xFF00) >> 8);//ep高8位
	ILI9341_Write_Data( ((y+heigh-1)&0xFF) );//ep低8位	
	
}

//画矩形
void ILI9341_Draw_Rect(uint16_t x,uint16_t y,uint16_t width, uint16_t heigh,uint16_t color)
{	
	uint32_t i;
	
	ILI9341_Open_Window(x,y,width,heigh);
	
	ILI9341_Write_CMD(CMD_SetPixel);
	for(i=0;i<width*heigh;i++)
	{	
		ILI9341_Write_Data(color);
	}
}

//画点
void ILI9341_Draw_Point(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9341_Open_Window(x,y,1,1);
	
	ILI9341_Write_CMD(CMD_SetPixel);
	ILI9341_Write_Data(color);	
}

/*********************************************END OF FILE**********************/

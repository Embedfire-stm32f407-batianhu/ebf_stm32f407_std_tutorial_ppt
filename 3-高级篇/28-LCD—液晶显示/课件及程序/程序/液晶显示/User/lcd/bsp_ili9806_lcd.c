/**
  ******************************************************************************
  * @file    sram.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   lcd驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */


//1.初始化FSMC控制相关的引脚
//2.初始化FSMC为异步NOR FLASH驱动模式
//3.编写向液晶屏读写数据 及 写入命令的函数
//4.向液晶屏发送寄存器配置
//5.控制液晶屏显示图形，进行测试


#include "./lcd/bsp_ili9806_lcd.h"	  


//
static void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/**
  * @brief  初始化控制LCD的IO
  * @param  无
  * @retval 无
  */
static void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能FSMC对应相应管脚时钟*/
	RCC_AHB1PeriphClockCmd ( 	
													/*控制信号*/
													ILI9806G_CS_CLK|ILI9806G_DC_CLK|ILI9806G_WR_CLK|
													ILI9806G_RD_CLK	|ILI9806G_BK_CLK|ILI9806G_RST_CLK|
													/*数据信号*/
													ILI9806G_D0_CLK|ILI9806G_D1_CLK|	ILI9806G_D2_CLK | 
													ILI9806G_D3_CLK | ILI9806G_D4_CLK|ILI9806G_D5_CLK|
													ILI9806G_D6_CLK | ILI9806G_D7_CLK|ILI9806G_D8_CLK|
													ILI9806G_D9_CLK | ILI9806G_D10_CLK|ILI9806G_D11_CLK|
													ILI9806G_D12_CLK | ILI9806G_D13_CLK|ILI9806G_D14_CLK|
													ILI9806G_D15_CLK	, ENABLE );
		
	
	/* 配置FSMC相对应的数据线,FSMC-D0~D15 */	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D0_PIN; 
    GPIO_Init(ILI9806G_D0_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D0_PORT,ILI9806G_D0_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D1_PIN; 
    GPIO_Init(ILI9806G_D1_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D1_PORT,ILI9806G_D1_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D2_PIN; 
    GPIO_Init(ILI9806G_D2_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D2_PORT,ILI9806G_D2_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D3_PIN; 
    GPIO_Init(ILI9806G_D3_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D3_PORT,ILI9806G_D3_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D4_PIN; 
    GPIO_Init(ILI9806G_D4_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D4_PORT,ILI9806G_D4_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D5_PIN; 
    GPIO_Init(ILI9806G_D5_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D5_PORT,ILI9806G_D5_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D6_PIN; 
    GPIO_Init(ILI9806G_D6_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D6_PORT,ILI9806G_D6_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D7_PIN; 
    GPIO_Init(ILI9806G_D7_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D7_PORT,ILI9806G_D7_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D8_PIN; 
    GPIO_Init(ILI9806G_D8_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D8_PORT,ILI9806G_D8_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D9_PIN; 
    GPIO_Init(ILI9806G_D9_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D9_PORT,ILI9806G_D9_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D10_PIN; 
    GPIO_Init(ILI9806G_D10_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D10_PORT,ILI9806G_D10_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D11_PIN; 
    GPIO_Init(ILI9806G_D11_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D11_PORT,ILI9806G_D11_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D12_PIN; 
    GPIO_Init(ILI9806G_D12_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D12_PORT,ILI9806G_D12_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D13_PIN; 
    GPIO_Init(ILI9806G_D13_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D13_PORT,ILI9806G_D13_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D14_PIN; 
    GPIO_Init(ILI9806G_D14_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D14_PORT,ILI9806G_D14_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D15_PIN; 
    GPIO_Init(ILI9806G_D15_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D15_PORT,ILI9806G_D15_PinSource,FSMC_AF);

	/* 配置FSMC相对应的控制线
	 * FSMC_NOE   :LCD-RD
	 * FSMC_NWE   :LCD-WR
	 * FSMC_NE1   :LCD-CS
	 * FSMC_A0    :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = ILI9806G_RD_PIN; 
    GPIO_Init(ILI9806G_RD_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_RD_PORT,ILI9806G_RD_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_WR_PIN; 
    GPIO_Init(ILI9806G_WR_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_WR_PORT,ILI9806G_WR_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_CS_PIN; 
    GPIO_Init(ILI9806G_CS_PORT, &GPIO_InitStructure);   
    GPIO_PinAFConfig(ILI9806G_CS_PORT,ILI9806G_CS_PinSource,FSMC_AF);  

    GPIO_InitStructure.GPIO_Pin = ILI9806G_DC_PIN; 
    GPIO_Init(ILI9806G_DC_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_DC_PORT,ILI9806G_DC_PinSource,FSMC_AF);
	

  /* 配置LCD复位RST控制管脚*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = ILI9806G_RST_PIN; 
	GPIO_Init ( ILI9806G_RST_PORT, & GPIO_InitStructure );
		
	/* 配置LCD背光控制管脚BK*/
	GPIO_InitStructure.GPIO_Pin = ILI9806G_BK_PIN; 
	GPIO_Init ( ILI9806G_BK_PORT, & GPIO_InitStructure );

}				  			


/**
  * @brief  初始化FSMC外设
  * @param  None. 
  * @retval None.
  */
static void FSMC_LCD_Init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

		
	/*使能FSMC外设时钟*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

	//地址建立时间（ADDSET）为5个HCLK,5/168M = 30ns
	readWriteTiming.FSMC_AddressSetupTime = 0x04;	

	//地址保持时间（ADDHLD）模式B未用到
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

	//数据保持时间（DATAST）+ 1个HCLK = 5/168M=30ns	
	readWriteTiming.FSMC_DataSetupTime = 0x04;		  
	
	//设置总线转换周期，仅用于复用模式的NOR操作
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	
	//设置时钟分频，仅用于同步类型的存储器
	readWriteTiming.FSMC_CLKDivision = 0x00;	

	//数据保持时间，仅用于同步型的NOR
	readWriteTiming.FSMC_DataLatency = 0x00;		
	
	//选择匹配为异步NOR FLASH的模式（模拟8080）
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;	 
    

	// 选择FSMC映射的存储区域： Bank1 sram3
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	
	//设置地址总线与数据总线是否复用，仅用于NOR
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	
	//设置要控制的存储器类型：NOR FLASH类型
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_NOR;   
	
	//存储器数据宽度：16位
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
	
	//设置是否使用突发访问模式，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
	
	//设置是否使能等待信号，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	
	//设置等待信号的有效极性，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	
	//设置是否支持把非对齐的突发操作，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
	
	//设置等待信号插入的时间，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	
	//存储器写使能 
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	
	//不使用等待信号
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
	
	// 不使用扩展模式，读写使用相同的时序
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
	
	//突发写操作
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	
	//读写时序配置
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	
	//读写同样时序，使用扩展模式时这个配置才有效
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  // 使能BANK										  
											
}


//往液晶屏发送数据
void ILI9806G_Write_Data(uint16_t data)
{
//	uint16_t *p = (uint16_t *)(LCD_DATA_ADDR) ;

//	*p = data; //液晶屏把data理解成数据	
	
	 *(__IO uint16_t *)(LCD_DATA_ADDR) = data ;
}

//往液晶屏发送命令
void ILI9806G_Write_Cmd(uint16_t cmd)
{
	__IO uint16_t *p = (__IO uint16_t *)(LCD_DATA_CMD) ;

	*p = cmd; //液晶屏把data理解成命令

}

//从液晶屏读取数据
uint16_t LCD_Read_Data(void)
{
	 __IO uint16_t *p = (__IO uint16_t *)(LCD_DATA_ADDR) ;	
	return *p;
}


//往液晶屏写入配置
void LCD_Reg_Config(void)
{
	
	//液晶厂商提供了两种版本的屏幕，性能一样，它们的驱动配置稍有区别，
	//本驱动通过#if #else #endif来设置，若屏幕显示花屏，请把#if 0改成#if 1，或1改成0
	//在2017-12-14日后购买的产品，使用#if 0
#if 0
	//旧版
	/* EXTC Command Set enable register */
	DEBUG_DELAY  ();
	ILI9806G_Write_Cmd ( 0xFF  );
	ILI9806G_Write_Data ( 0xFF  );
	ILI9806G_Write_Data ( 0x98  );
	ILI9806G_Write_Data ( 0x06  );

	/* GIP 1(BCh)  */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd(0xBC);
	ILI9806G_Write_Data(0x01); 
	ILI9806G_Write_Data(0x0E); 
	ILI9806G_Write_Data(0x61); 
	ILI9806G_Write_Data(0xFB); 
	ILI9806G_Write_Data(0x10); 
	ILI9806G_Write_Data(0x10); 
	ILI9806G_Write_Data(0x0B); 
	ILI9806G_Write_Data(0x0F); 
	ILI9806G_Write_Data(0x2E); 
	ILI9806G_Write_Data(0x73); 
	ILI9806G_Write_Data(0xFF); 
	ILI9806G_Write_Data(0xFF); 
	ILI9806G_Write_Data(0x0E); 
	ILI9806G_Write_Data(0x0E); 
	ILI9806G_Write_Data(0x00); 
	ILI9806G_Write_Data(0x03); 
	ILI9806G_Write_Data(0x66); 
	ILI9806G_Write_Data(0x63); 
	ILI9806G_Write_Data(0x01); 
	ILI9806G_Write_Data(0x00); 
	ILI9806G_Write_Data(0x00);

	/* GIP 2 (BDh) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd(0xBD);
	ILI9806G_Write_Data(0x01); 
	ILI9806G_Write_Data(0x23); 
	ILI9806G_Write_Data(0x45); 
	ILI9806G_Write_Data(0x67); 
	ILI9806G_Write_Data(0x01); 
	ILI9806G_Write_Data(0x23); 
	ILI9806G_Write_Data(0x45); 
	ILI9806G_Write_Data(0x67); 

	/* GIP 3 (BEh) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd(0xBE);
	ILI9806G_Write_Data(0x00); 
	ILI9806G_Write_Data(0x21); 
	ILI9806G_Write_Data(0xAB); 
	ILI9806G_Write_Data(0x60); 
	ILI9806G_Write_Data(0x22); 
	ILI9806G_Write_Data(0x22); 
	ILI9806G_Write_Data(0x22); 
	ILI9806G_Write_Data(0x22); 
	ILI9806G_Write_Data(0x22); 

	/* Vcom  (C7h) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xC7 );
	ILI9806G_Write_Data ( 0x6F );

	/* EN_volt_reg (EDh)*/
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xED );
	ILI9806G_Write_Data ( 0x7F );
	ILI9806G_Write_Data ( 0x0F );
	ILI9806G_Write_Data ( 0x00 );

	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xC0 );
	ILI9806G_Write_Data ( 0x37 );
	ILI9806G_Write_Data ( 0x0B );
	ILI9806G_Write_Data ( 0x0A );

	/* LVGL (FCh) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xFC );
	ILI9806G_Write_Data ( 0x0A );

	/* Engineering Setting (DFh) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xDF );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x20 );

	/* DVDD Voltage Setting(F3h) */
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0xF3 );
	ILI9806G_Write_Data ( 0x74 );

	/* Display Inversion Control (B4h) */
	ILI9806G_Write_Cmd ( 0xB4 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x00 );

	/* 480x854 (F7h)  */
	ILI9806G_Write_Cmd ( 0xF7 );
	ILI9806G_Write_Data ( 0x89 );

	/* Frame Rate (B1h) */
	ILI9806G_Write_Cmd ( 0xB1 );
	ILI9806G_Write_Data ( 0x00 );
	ILI9806G_Write_Data ( 0x12 );
	ILI9806G_Write_Data ( 0x10 );

	/* Panel Timing Control (F2h) */
	ILI9806G_Write_Cmd ( 0xF2 );
	ILI9806G_Write_Data ( 0x80 );
	ILI9806G_Write_Data ( 0x5B );
	ILI9806G_Write_Data ( 0x40 );
	ILI9806G_Write_Data ( 0x28 );

	DEBUG_DELAY ();

	/* Power Control 2 (C1h) */
	ILI9806G_Write_Cmd ( 0xC1 ); 
	ILI9806G_Write_Data ( 0x17 );
	ILI9806G_Write_Data ( 0x7D );
	ILI9806G_Write_Data ( 0x7A );
	ILI9806G_Write_Data ( 0x20 );

	DEBUG_DELAY ();

	ILI9806G_Write_Cmd(0xE0); 
	ILI9806G_Write_Data(0x00); //P1 
	ILI9806G_Write_Data(0x11); //P2 
	ILI9806G_Write_Data(0x1C); //P3 
	ILI9806G_Write_Data(0x0E); //P4 
	ILI9806G_Write_Data(0x0F); //P5 
	ILI9806G_Write_Data(0x0C); //P6 
	ILI9806G_Write_Data(0xC7); //P7 
	ILI9806G_Write_Data(0x06); //P8 
	ILI9806G_Write_Data(0x06); //P9 
	ILI9806G_Write_Data(0x0A); //P10 
	ILI9806G_Write_Data(0x10); //P11 
	ILI9806G_Write_Data(0x12); //P12 
	ILI9806G_Write_Data(0x0A); //P13 
	ILI9806G_Write_Data(0x10); //P14 
	ILI9806G_Write_Data(0x02); //P15 
	ILI9806G_Write_Data(0x00); //P16 

	DEBUG_DELAY ();

	ILI9806G_Write_Cmd(0xE1); 
	ILI9806G_Write_Data(0x00); //P1 
	ILI9806G_Write_Data(0x12); //P2 
	ILI9806G_Write_Data(0x18); //P3 
	ILI9806G_Write_Data(0x0C); //P4 
	ILI9806G_Write_Data(0x0F); //P5 
	ILI9806G_Write_Data(0x0A); //P6 
	ILI9806G_Write_Data(0x77); //P7 
	ILI9806G_Write_Data(0x06); //P8 
	ILI9806G_Write_Data(0x07); //P9 
	ILI9806G_Write_Data(0x0A); //P10 
	ILI9806G_Write_Data(0x0E); //P11 
	ILI9806G_Write_Data(0x0B); //P12 
	ILI9806G_Write_Data(0x10); //P13 
	ILI9806G_Write_Data(0x1D); //P14 
	ILI9806G_Write_Data(0x17); //P15 
	ILI9806G_Write_Data(0x00); //P16  

	/* Tearing Effect ON (35h)  */
	ILI9806G_Write_Cmd ( 0x35 );
	ILI9806G_Write_Data ( 0x00 );

	ILI9806G_Write_Cmd ( 0x3A );
	ILI9806G_Write_Data ( 0x55 );

	ILI9806G_Write_Cmd ( 0x11 );
	DEBUG_DELAY ();
	ILI9806G_Write_Cmd ( 0x29 );
	
#else
	//新版
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xFF);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x98);
	ILI9806G_Write_Data(0x06);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBA);
	ILI9806G_Write_Data(0x60);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBC);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x0E);
	ILI9806G_Write_Data(0x61);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x1B);
	ILI9806G_Write_Data(0x10);
	ILI9806G_Write_Data(0x73);
	ILI9806G_Write_Data(0x63);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0xD5);
	ILI9806G_Write_Data(0xD0);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x40); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBD);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x23);
	ILI9806G_Write_Data(0x45);
	ILI9806G_Write_Data(0x67);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x23);
	ILI9806G_Write_Data(0x45);
	ILI9806G_Write_Data(0x67);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBE);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x2D);
	ILI9806G_Write_Data(0xCB);
	ILI9806G_Write_Data(0xA2);
	ILI9806G_Write_Data(0x62);
	ILI9806G_Write_Data(0xF2);
	ILI9806G_Write_Data(0xE2);
	ILI9806G_Write_Data(0x22);
	ILI9806G_Write_Data(0x22);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC7);
	ILI9806G_Write_Data(0x63); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xED);
	ILI9806G_Write_Data(0x7F);
	ILI9806G_Write_Data(0x0F);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC0);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x0B);
	ILI9806G_Write_Data(0x00);   
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xFC);
	ILI9806G_Write_Data(0x08); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xDF);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x20);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF3);
	ILI9806G_Write_Data(0x74);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF9);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0xFD);
	ILI9806G_Write_Data(0x80);
	ILI9806G_Write_Data(0x80);
	ILI9806G_Write_Data(0xC0);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xB4);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x02); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF7);
	ILI9806G_Write_Data(0x81);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xB1);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x13);
	ILI9806G_Write_Data(0x13); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF2);
	ILI9806G_Write_Data(0xC0);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x40);
	ILI9806G_Write_Data(0x28);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC1);
	ILI9806G_Write_Data(0x17);
	ILI9806G_Write_Data(0x75);
	ILI9806G_Write_Data(0x75);
	ILI9806G_Write_Data(0x20); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xE0);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x0C);
	ILI9806G_Write_Data(0x0F);
	ILI9806G_Write_Data(0x15);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x07);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x06);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x16);
	ILI9806G_Write_Data(0x14);
	ILI9806G_Write_Data(0x3E);
	ILI9806G_Write_Data(0x3E);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xE1);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x12);
	ILI9806G_Write_Data(0x12);
	ILI9806G_Write_Data(0x13);
	ILI9806G_Write_Data(0x1c);
	ILI9806G_Write_Data(0x07);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x04);
	ILI9806G_Write_Data(0x1E);
	ILI9806G_Write_Data(0x1B);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x3A);
	ILI9806G_Write_Data(0x55); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x35);
	ILI9806G_Write_Data(0x00); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x11);
	DEBUG_DELAY() ;
	ILI9806G_Write_Cmd(0x29);	   
	DEBUG_DELAY()  ; 
#endif		
}

//读取液晶ID
uint16_t LCD_Get_ID(void)
{
	uint16_t id = 0;
	ILI9806G_Write_Cmd(0xd3);
	LCD_Read_Data();
	LCD_Read_Data();
	
	//高位
	id |= LCD_Read_Data();
	id<<=8;
	//低位
	id|= LCD_Read_Data();
	
	return id;
}

//背光
void LCD_Back_Light(uint8_t state)
{
	if(state == ENABLE)
		GPIO_SetBits(ILI9806G_BK_PORT,ILI9806G_BK_PIN);
	else
		GPIO_ResetBits(ILI9806G_BK_PORT,ILI9806G_BK_PIN);
}





//背光
void LCD_RST(void)
{		
	//低电平复位
	GPIO_ResetBits(ILI9806G_RST_PORT,ILI9806G_RST_PIN);

	DEBUG_DELAY();
	//高电平正常运行
	GPIO_SetBits(ILI9806G_RST_PORT,ILI9806G_RST_PIN);
	
	DEBUG_DELAY();

}
	
//液晶初始化函数
void LCD_Init(void)
{
	LCD_GPIO_Config();
	LCD_RST();
	FSMC_LCD_Init();
	LCD_Reg_Config();
	
	LCD_Back_Light(ENABLE);
	
}

//RGB888   == 红色 0xFF0000
//绘制矩形 RGB565   
void LCD_Draw_Rect(uint16_t x0,uint16_t x1,uint16_t y0,uint16_t y1,uint16_t color)
{
	
	uint32_t i = 0;
	ILI9806G_Write_Cmd(0x2a);
	ILI9806G_Write_Data((x0>>8)&0xFF); //x0高8位
	ILI9806G_Write_Data(x0&0xFF);
	ILI9806G_Write_Data((x1>>8)&0xFF); //x1高8位
	ILI9806G_Write_Data(x1&0xFF);
	
	ILI9806G_Write_Cmd(0x2b);
	ILI9806G_Write_Data((y0>>8)&0xFF); //y0高8位
	ILI9806G_Write_Data(y0&0xFF);
	ILI9806G_Write_Data((y1>>8)&0xFF); //y1高8位
	ILI9806G_Write_Data(y1&0xFF);
		
	ILI9806G_Write_Cmd(0x2c); //写入像素命令
	for(i=0;i<(x1-x0+1)*(y1-y0+1);i++)
	{
		ILI9806G_Write_Data(color);
	}
	
	

}




/*********************************************END OF FILE**********************/






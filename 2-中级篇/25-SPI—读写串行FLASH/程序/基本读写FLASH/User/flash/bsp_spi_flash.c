/**
  ******************************************************************************
  * @file    bsp_bsp_flash.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief  SPI FLASH 应用函数bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./flash/bsp_spi_flash.h"
#include "./usart/bsp_debug_usart.h"

/*
1.初始化相关引脚及SPI工作模式
2.编写基本的读写单个字节的流程函数
3.利用2的函数来组成各种命令
4.利用命令读写FLASH并校验数据
*/


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   


static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);




/**
  * @brief   SPI I/O配置
  * @param  无
  * @retval 无
  */
static void  SPI_GPIO_Config(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);
	
  RCC_AHB1PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MOSI_GPIO_CLK|
													FLASH_SPI_MISO_GPIO_CLK|FLASH_SPI_CS_GPIO_CLK, ENABLE);


  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);
  GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);  
  GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF);
   
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	//使用软件控制CS引脚
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
 
}

/**
  * @brief  SPI 工作模式配置
  * @param  无
  * @retval 无
  */
static void SPI_Mode_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure; 

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2 ;
	
	//mode 0
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b  ;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master ;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft ;

  SPI_Init(FLASH_SPI, &SPI_InitStructure);	                                      /* I2C1 初始化 */
  SPI_Cmd(FLASH_SPI, ENABLE);  	                                                /* 使能 I2C1 */
}

/**
  * @brief  SPI 外设(FLASH)初始化
  * @param  无
  * @retval 无
  */
void SPI_FLASH_Init(void)
{
  SPI_GPIO_Config(); 
 
  SPI_Mode_Config();
}


/**
  * @brief   通过SPI发送一个字节
  * @param   
  *		@arg data:要发送的数据
  * @retval  接收到的数据
  */
uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
	uint8_t re_data;
	
	//等待TXE标志
	SPITimeout = SPIT_FLAG_TIMEOUT;
  while(SPI_I2S_GetFlagStatus (FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }    
	
	SPI_I2S_SendData(FLASH_SPI, data);
	
	//等待RXNE标志 来确认发送完成，及准备读取数据
	SPITimeout = SPIT_FLAG_TIMEOUT;
	while(SPI_I2S_GetFlagStatus (FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(2);
  }   
	
	re_data = SPI_I2S_ReceiveData(FLASH_SPI);
	
	return re_data;
}

//读ID0 -ID7
uint8_t SPI_FLASH_Read_ID(void)
{
	uint8_t id;
	//控制片选引脚
	FLASH_SPI_CS_LOW();
	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReleasePowerDown);
	
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	
	//接收读取到的内容
	
	id = SPI_FLASH_ByteWrite(DUMMY);
	FLASH_SPI_CS_HIGH();
	return id;

}


//擦除扇区
//addr:必须对齐到要擦除的扇区的首地址
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
	//写使能
	SPI_FLASH_Write_Enable();
	
	
	//控制片选引脚
	FLASH_SPI_CS_LOW();
	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_SectorErase);
	
	//发送要擦除的地址
	SPI_FLASH_ByteWrite((addr>>16) & 0xFF);
	SPI_FLASH_ByteWrite((addr>>8) & 0xFF);
	SPI_FLASH_ByteWrite(addr & 0xFF);
	
	FLASH_SPI_CS_HIGH();	
	
	//等待内部时序完成
	SPI_FLASH_Wait_For_Standby();

}

//读取数据
//addr:要读取数据的首地址，
//buf:存储读取到的数据的指针
//size:要读取多少个数据
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	//控制片选引脚
	FLASH_SPI_CS_LOW();
	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReadData);
	
	//发送要读取的地址
	SPI_FLASH_ByteWrite((addr>>16) & 0xFF);
	SPI_FLASH_ByteWrite((addr>>8) & 0xFF);
	SPI_FLASH_ByteWrite(addr & 0xFF);	

	while(size--)
	{
		*buf = SPI_FLASH_ByteWrite(DUMMY);
		buf++;
	}
	
	FLASH_SPI_CS_HIGH();	
}


//写入数据
//addr:要写入数据的首地址，
//buf:要写入的数据的指针
//size:要写入多少个数据 不超过256
void SPI_FLASH_Write_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	uint32_t count=0;
	
	while(size--)
	{
		count++;
		
		//第一次执行，1,257,256*2+1,256*3+1,addr对齐到4096时
		
		if(count == 1 || (count%256) ==1 || (addr%4096)==0)
		{
			//结束上一次的页写入指令
			FLASH_SPI_CS_HIGH();	

			//等待上一次页写入的完成
			SPI_FLASH_Wait_For_Standby();
			
			//写使能
			SPI_FLASH_Write_Enable();	
			
			//控制片选引脚
			FLASH_SPI_CS_LOW();
			
			//指令代码
			SPI_FLASH_ByteWrite(W25X_PageProgram);
			
			//发送要写入的地址
			SPI_FLASH_ByteWrite((addr>>16) & 0xFF);
			SPI_FLASH_ByteWrite((addr>>8) & 0xFF);
			SPI_FLASH_ByteWrite(addr & 0xFF);	
		}			

		SPI_FLASH_ByteWrite(*buf);
		buf++;
		addr++;	
	}
	
	FLASH_SPI_CS_HIGH();	

	//等待内部时序完成
	SPI_FLASH_Wait_For_Standby();

}

//写使能
void SPI_FLASH_Write_Enable(void)
{
	//控制片选引脚
	FLASH_SPI_CS_LOW();
	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_WriteEnable);
	

	FLASH_SPI_CS_HIGH();
}

//等待直到空闲状态
void SPI_FLASH_Wait_For_Standby(void)
{
	uint8_t status ;
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReadStatusReg);
	
	SPITimeout = SPIT_LONG_TIMEOUT;
	
	while(1)
	{
		status = SPI_FLASH_ByteWrite(DUMMY);
		
		//如果条件成立，说明为空闲状态
		if((status & 0x01) == 0) 
			break;
		
		//若SPITimeout为0，表示已检测SPITimeout次都仍为busy，跳出循环
		if((SPITimeout--)==0)
		{
			SPI_TIMEOUT_UserCallback(3);
			break;
		}
	}	
	
	FLASH_SPI_CS_HIGH();
}



/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示SPI读取失败.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FLASH_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/

/**
  ******************************************************************************
  * @file    bsp_spi_flash.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SPI -FLASH驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火STM32 F103-MINI 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "./flash/bsp_spi_flash.h"

uint32_t time_out = SPI_FLASH_WAIT_TIMEOUT;


 /**
  * @brief  SPI GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void SPI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	// 打开SPI GPIO的时钟
	SPI_FLASH_GPIO_APBxClkCmd(SPI_FLASH_GPIO_CLK, ENABLE);
	
	// 打开SPI外设的时钟
	SPI_FLASH_APBxClkCmd(SPI_FLASH_CLK, ENABLE);

	// 将SPI 的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = SPI_FLASH_SCK_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_SCK_GPIO_PORT, &GPIO_InitStructure);
	
	//MOSI
	GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MOSI_GPIO_PIN;
	GPIO_Init(SPI_FLASH_MOSI_GPIO_PORT, &GPIO_InitStructure);		
	
	//MISO
	GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MISO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(SPI_FLASH_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	//CS 软件控制
	GPIO_InitStructure.GPIO_Pin = SPI_FLASH_CS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_CS_GPIO_PORT, &GPIO_InitStructure);			

	//配置SPI 工作模式
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b ;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft ;
	
	SPI_Init(SPI_FLASHx,&SPI_InitStructure);
	
	SPI_Cmd(SPI_FLASHx,ENABLE);
	
}

//出错时调用这个函数
uint8_t SPI_Timeout_CallBack(uint8_t data)
{
	printf("\r\nSPI 检测超时，错误代码：%d",data);
	
	return 0;
}


//发送一个字节
uint8_t SPI_FLASH_Send_Data(uint8_t data)
{
	uint8_t read_temp;	
	
	time_out = SPI_FLASH_WAIT_TIMEOUT;
	//检测TXE
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET)
	{
		//超时
		if(time_out-- == 0)
		{
			return SPI_Timeout_CallBack(1);
		}
	}	
	
	//检测到TXE标志
	SPI_I2S_SendData(SPI1,data);
	
	time_out = SPI_FLASH_WAIT_TIMEOUT;
	
	//检测RXNE
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)
	{	
		//超时
		if(time_out-- == 0)
		{
			return SPI_Timeout_CallBack(2);
		}
	}	
	
	read_temp = (uint8_t)SPI_I2S_ReceiveData (SPI1);
	
	return read_temp;
}

//接收一个字节
uint8_t SPI_FLASH_Receive_Data(void)
{
	return SPI_FLASH_Send_Data(0xFF);
}

//读取JEDEC ID
uint32_t SPI_FLASH_Read_JEDEC_ID(void)
{
	uint32_t id;
	
	//软件控制CS
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_JedecDeviceID);
	
	id = SPI_FLASH_Receive_Data();

	id<<=8;
	
	id |= SPI_FLASH_Receive_Data();
	
	id<<=8;
	id |= SPI_FLASH_Receive_Data();

	SPI_FLASH_CS_HIGH();
	
	return id;

}

//写使能
void SPI_FLASH_Write_Enable(void)
{
	//软件控制CS
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_WriteEnable);	

	SPI_FLASH_CS_HIGH();
}

//读取状态寄存器
void SPI_FLASH_WaitForWriteEnd(void)
{	
	uint8_t status;
	
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_ReadStatusReg);

	do
	{
		status = SPI_FLASH_Receive_Data();
	}	while(status & 0x01);//检测BUSY标志

	SPI_FLASH_CS_HIGH();
	
}


//擦除操作
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
	
	SPI_FLASH_WaitForWriteEnd();
	
	//擦除、写入前必须写使能
	SPI_FLASH_Write_Enable();
	
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_SectorErase);
	
	SPI_FLASH_Send_Data((addr &0xFF0000)>>16 );

	SPI_FLASH_Send_Data((addr &0x00FF00)>>8);

	SPI_FLASH_Send_Data((addr &0xFF));

	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_WaitForWriteEnd();

}

//读取操作
void SPI_FLASH_Read_Buffer(uint32_t addr,uint8_t *data,uint32_t size)
{		
	uint32_t i;
	
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_ReadData);
	
	SPI_FLASH_Send_Data((addr &0xFF0000)>>16 );

	SPI_FLASH_Send_Data((addr &0x00FF00)>>8);

	SPI_FLASH_Send_Data((addr &0xFF));
	
	for(i=0;i<size;i++)
	{
		*data = SPI_FLASH_Receive_Data();
		
		data++;
	}	

	SPI_FLASH_CS_HIGH();

}


//写入操作
//size不能大于256
void SPI_FLASH_Page_Write(uint32_t addr,uint8_t *data,uint32_t size)
{	
	uint32_t i;
	
	if(size>256)
	{
		printf("\r\npage write函数不能写入超过256个字节\r\n");
		return ;
	}	
	
	SPI_FLASH_WaitForWriteEnd();
	
	//擦除、写入前必须写使能
	SPI_FLASH_Write_Enable();
	
	SPI_FLASH_CS_LOW();
		
	SPI_FLASH_Send_Data(W25X_PageProgram);
	
	SPI_FLASH_Send_Data((addr &0xFF0000)>>16 );

	SPI_FLASH_Send_Data((addr &0x00FF00)>>8);

	SPI_FLASH_Send_Data((addr &0xFF));
	
	for(i=0;i<size;i++)
	{
		SPI_FLASH_Send_Data(*data); //发送要写入的数据
		data++;
	}	

	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_WaitForWriteEnd();

}




//写入操作
void SPI_FLASH_Write_Buff(uint32_t addr,uint8_t *data,uint32_t size)
{	
	uint32_t i;

	for(i=0;i<size;i++)
	{
	
		if(i == 0 || (addr % 256 == 0))
		{
			SPI_FLASH_CS_HIGH();
			
			SPI_FLASH_WaitForWriteEnd();
			
			//擦除、写入前必须写使能
			SPI_FLASH_Write_Enable();
			
			SPI_FLASH_CS_LOW();
				
			SPI_FLASH_Send_Data(W25X_PageProgram);
			
			SPI_FLASH_Send_Data((addr &0xFF0000)>>16 );

			SPI_FLASH_Send_Data((addr &0x00FF00)>>8);

			SPI_FLASH_Send_Data((addr &0xFF));
			
		}
		
		SPI_FLASH_Send_Data(*data); //发送要写入的数据
		data++;
		addr++;
		
	}

	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_WaitForWriteEnd();
}



/******end of file******/

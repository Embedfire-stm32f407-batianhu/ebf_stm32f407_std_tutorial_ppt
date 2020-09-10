/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   EEPROM驱动程序
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./iic/bsp_i2c_ee.h"

/*
要实现往EEPROM写入数据。
1.初始化硬件I2C
2.编写往EEPROM传输数据的函数（包括读和写）
3.利用读写函数往EEPROM写入数据，并读取进行校验
*/

#define TIME_OUT  0x00000FFF

uint32_t count_wait = TIME_OUT;



uint8_t Error_CallBack(uint8_t code);

 /**
  * @brief  EEPROM_I2C_Config初始化GPIO及I2C的模式
  * @param  无
  * @retval 无
  */
void EEPROM_I2C_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStructure;
		
  RCC_AHB1PeriphClockCmd(EEPROM_I2C_SCL_GPIO_CLK|EEPROM_I2C_SDA_GPIO_CLK,ENABLE);

  /* 使能 I2C 时钟 */
  RCC_APB1PeriphClockCmd(EEPROM_I2C_CLK, ENABLE);
	
	 /* 连接 PXx 到 IIC*/
  GPIO_PinAFConfig(EEPROM_I2C_SCL_GPIO_PORT,EEPROM_I2C_SCL_SOURCE,EEPROM_I2C_SCL_AF);

  /*  连接 PXx 到 IIC*/
  GPIO_PinAFConfig(EEPROM_I2C_SDA_GPIO_PORT,EEPROM_I2C_SDA_SOURCE,EEPROM_I2C_SDA_AF);
  
  /* GPIO SCL初始化 */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN  ;  
  GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* 初始化SDA */
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN  ; 
  GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //使用7位设备地址
	I2C_InitStructure.I2C_ClockSpeed = EEPROM_I2C_BAUDRATE;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = STM32_I2C_OWN_ADDR;

  I2C_Init(EEPROM_I2C, &I2C_InitStructure); 
	
	
  /* 使能I2C */
  I2C_Cmd(EEPROM_I2C, ENABLE);
}

//addr:要写入的存储单元地址
//data:要写入的数据
//return:0表示正常，非0为失败
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
	//产生起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(1);
		}
	}	
	
	//要发送的EEPROM设备地址,并设置为写方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(2);
		}
	}
	
	//发送要写入的存储单元地址
	I2C_SendData(EEPROM_I2C,addr);
	
	//重置 count_wait
	count_wait = TIME_OUT;	
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(3);
		}
	}
	
	//发送要写入的数据
	I2C_SendData(EEPROM_I2C,data);
	
	//重置 count_wait
	count_wait = TIME_OUT;		
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(4);
		}
	}
	
	//产生结束信号
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//等待写入完成
	return 	Wait_For_Standby();

}


//addr:要写入的存储单元首地址
//data:要写入的数据的指针
//size:要写入多少个数据（size小于等于8）
//return:0表示正常，非0为失败
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t size)
{
	//产生起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(12);
		}
	}	
	
	//要发送的EEPROM设备地址,并设置为写方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(13);
		}
	}
	
	//发送要写入的存储单元地址
	I2C_SendData(EEPROM_I2C,addr);
	
	//重置 count_wait
	count_wait = TIME_OUT;	
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(14);
		}
	}
	
	while(size--)
	{
		//发送要写入的数据
		I2C_SendData(EEPROM_I2C,*data);
		
		//重置 count_wait
		count_wait = TIME_OUT;		
		//等待EV8_2事件，直到检测成功
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
		{
			count_wait--;
			if(count_wait == 0 )
			{
				return Error_CallBack(15);
			}
		}
		
		data++;
	}
	
	//产生结束信号
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//等待写入完成
	return 	Wait_For_Standby();

}


//addr:要写入的存储单元首地址
//data:要写入的数据的指针
//size:要写入多少个数据
//return:0表示正常，非0为失败
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t* data, uint16_t size)
{

	// single_adrr = 1 = 1 % 8时  写入 EEPROM_PAGE_SIZE-single_adrr = 7
	uint8_t single_adrr = addr%EEPROM_PAGE_SIZE;
	
	if(single_adrr == 0)
	{	
		uint8_t num_of_page = size/EEPROM_PAGE_SIZE;	
		uint8_t single_byte = size%EEPROM_PAGE_SIZE;
		
		while(num_of_page--)
		{
			//调用页写入函数
			EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
			
			//等待写入完成
			Wait_For_Standby();
			
			addr += EEPROM_PAGE_SIZE;
			data += EEPROM_PAGE_SIZE;
		}
			
		//调用页写入函数
		EEPROM_Page_Write(addr, data, single_byte);
		
		//等待写入完成
		Wait_For_Standby();	
	}
	else //addr不对齐
	{
		uint8_t num_of_page,single_byte,sheng_yu;
		//第一次写入
		uint8_t first_size = EEPROM_PAGE_SIZE - single_adrr;
		
		//调用页写入函数
		EEPROM_Page_Write(addr, data, first_size);
		
		//等待写入完成
		Wait_For_Standby();
		
		addr += first_size;
		data += first_size;
		
		//剩下要写入的数据
		sheng_yu = size - first_size;
		
		num_of_page = sheng_yu/EEPROM_PAGE_SIZE;	
		single_byte = sheng_yu%EEPROM_PAGE_SIZE;	
	
		
		while(num_of_page--)
		{
			//调用页写入函数
			EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
			
			//等待写入完成
			Wait_For_Standby();
			
			addr += EEPROM_PAGE_SIZE;
			data += EEPROM_PAGE_SIZE;
		}
			
		//调用页写入函数
		EEPROM_Page_Write(addr, data, single_byte);
		
		//等待写入完成
		Wait_For_Standby();		
	
	}
	
	return 0;

}




//addr:要读取的存储单元地址
//data:用来存储 读取到的数据 的指针
//return:0表示正常，非0为失败
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
	//产生起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(5);
		}
	}	
	
	//要发送的EEPROM设备地址,并设置为写方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(6);
		}
	}
	
	//发送要读取的存储单元地址
	I2C_SendData(EEPROM_I2C,addr);
	
	//重置 count_wait
	count_wait = TIME_OUT;	
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(7);
		}
	}
	
	//------------------------------------------------------------------------
	//产生第二次起始信号	
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(8);
		}
	}	
	
	//************************读方向**********************************************
	//要发送的EEPROM设备地址,并设置为读方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Receiver);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(9);
		}
	}
	
	//作出非应答信号
	I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
		
	//重置 count_wait
	count_wait = TIME_OUT;		
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(10);
		}
	}
		
	//接收数据
	*data = I2C_ReceiveData(EEPROM_I2C);
		
	//产生结束信号
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 0;

}


//addr:要读取的存储单元首地址
//data:用来存储 读取到的数据 的指针
//size:要读取多少个数据
//return:0表示正常，非0为失败
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size)
{
	//产生起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(16);
		}
	}	
	
	//要发送的EEPROM设备地址,并设置为写方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(17);
		}
	}
	
	//发送要读取的存储单元地址
	I2C_SendData(EEPROM_I2C,addr);
	
	//重置 count_wait
	count_wait = TIME_OUT;	
	//等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(18);
		}
	}
	
	//------------------------------------------------------------------------
	//产生第二次起始信号	
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV5事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(19);
		}
	}	
	
	//************************读方向**********************************************
	//要发送的EEPROM设备地址,并设置为读方向
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Receiver);
	
	//重置 count_wait
	count_wait = TIME_OUT;
	//等待EV6事件，直到检测成功
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(20);
		}
	}
	
		
	while(size--)
	{
		if(size==0)
		{
			//作出非应答信号
			I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
		}
		else
		{
			//作出应答信号
			I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
		}
				
		//重置 count_wait
		count_wait = TIME_OUT;		
		//等待EV8_2事件，直到检测成功
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		{
			count_wait--;
			if(count_wait == 0 )
			{
				return Error_CallBack(21);
			}
		}
			
		//接收数据
		*data = I2C_ReceiveData(EEPROM_I2C);
		data++;
	}
		
	//产生结束信号
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 0;

}


//等待EEPROM内部写入操作完成
//为0表示正常等待完成，非0表示等待不到响应信号
uint8_t Wait_For_Standby(void)
{
	uint32_t check_count = 0xFFFFF;
	
	while(check_count--)
	{
		//产生起始信号
		I2C_GenerateSTART(EEPROM_I2C, ENABLE);
		
		//重置 count_wait
		count_wait = TIME_OUT;
		//等待EV5事件，直到检测成功
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		{
			count_wait--;
			if(count_wait == 0 )
			{
				return Error_CallBack(11);
			}
		}	
		
		//要发送的EEPROM设备地址,并设置为写方向
		I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
		
		//重置 count_wait
		count_wait = TIME_OUT;
		//等待EV6事件，直到检测成功
		while(count_wait--)
		{
			//若检测到响应，说明内部写时序完成，跳出等待函数
			if(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS)
			{
				//退出前停止本次通讯
				I2C_GenerateSTOP(EEPROM_I2C, ENABLE);	
				return 0;
			}			
		}		
	}
	
	//退出前停止本次通讯
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);	
	return 1;
}

//code:错误编码
uint8_t Error_CallBack(uint8_t code)
{
	printf("\r\nI2C error occur,code=%d\r\n", code);
	return code;
}

/*********************************************END OF FILE**********************/

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
  
#include "bsp_i2c_ee.h"   
#include "bsp_i2c_gpio.h"   

//检测EEPROM是否存在
//1表示没检测到EEPROM
//0表示EEPROM连接正常
uint8_t ee_CHECK_DEVICE(uint8_t addr)
{
	uint8_t result;
	
	i2c_START();
	
	//发送EEPROM设备地址
	i2c_WRITE_BYTE(addr);
	
	if(i2c_WAIT_ASK())
	{
		result = 1;
	}
	else
	{
		result = 0;
	} 
	
	i2c_NASK();
	
	i2c_STOP();
	
	return result;
	
}

//等待EEPROM内部时序完成
//1表示超时
//0表示完成
uint8_t ee_WAIT_STANDPY(void)
{	
	uint16_t cycle = 0;
	
	while(ee_CHECK_DEVICE(EEPROM_ADDR|EEPROM_WRITE_DIR))
	{
		cycle++;
		if(cycle>=10000)
			return 1;
	}
	
	return 0;
}


//往EEPROM写入一个字节
//正常：1 错误：0
uint8_t ee_WRITE_BYTES(uint8_t w_addr,uint8_t *data,uint16_t size)
{		
	
	uint16_t i;
	
	for(i=0;i<size;i++)
	{
		if(i==0 || (w_addr)%8 == 0)
		{		
			i2c_STOP();
			
			if(ee_WAIT_STANDPY())
				goto w_fail;	
			
			i2c_START();
			
			//发送EEPROM设备地址
			i2c_WRITE_BYTE(EEPROM_ADDR|EEPROM_WRITE_DIR);
			
			if(i2c_WAIT_ASK())
			{
				goto w_fail;
			}
			else
			{		
				//发送要写入的存储单元格地址
				i2c_WRITE_BYTE(w_addr);
				
				if(i2c_WAIT_ASK())
				{
					goto w_fail;
				}
			}
		}					
	
		//发送要写入的数据
		i2c_WRITE_BYTE(*data);	
		
		if(i2c_WAIT_ASK())
		{
			goto w_fail;
		}
		data++;
		w_addr++;
	
	}	
	
	i2c_STOP();

	if(ee_WAIT_STANDPY())
		goto w_fail;	
	
	return 1;

w_fail:	
	i2c_STOP();
	return 0;	
}



//从EEPROM读取一个字节
//正常：1 错误：0
uint8_t ee_READ_BYTES(uint8_t r_addr,uint8_t *data,uint16_t size)
{
	if(ee_WAIT_STANDPY())
		goto r_fail;
	
	i2c_START();
	
	//发送EEPROM设备地址
	i2c_WRITE_BYTE(EEPROM_ADDR|EEPROM_WRITE_DIR);
	
	if(i2c_WAIT_ASK())
	{
		goto r_fail;
	}
	else
	{
		
		//发送要读取的存储单元格地址
		i2c_WRITE_BYTE(r_addr);
		
		if(i2c_WAIT_ASK())
		{
			goto r_fail;
		}
		else
		{
			//发送第二次起始信号
			i2c_START();
			
			//发送第二次设备地址，读方式
			i2c_WRITE_BYTE(EEPROM_ADDR|EEPROM_READ_DIR);
			
			if(i2c_WAIT_ASK())
			{
				goto r_fail;
			}
			else
			{				
				uint16_t i;
				for(i=0;i<size;i++)
				{
					*data = i2c_READ_BYTE();
					
					if(i == size-1)
					{
						i2c_NASK();//接收数据够了，产生非应答信号
					}
					else	
					{						
						i2c_ASK();
					}
					
					data++;//指针指向下一个缓冲区
				}
			} 			
		}
	}
	
	i2c_STOP();
	return 1;

r_fail:	
	i2c_NASK();
	i2c_STOP();
	return 0;	
}

/*********************************************END OF FILE**********************/

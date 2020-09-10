/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   读写内部FLASH的测试文件
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./interFLASH/bsp_inter_flash.h"


#define TEST_ADDR  0x08008000
#define TEST_DATA  0x12

void inter_flash_test(void)
{
	char *byte_p = (char *)TEST_ADDR;
	uint16_t *half_word_p = (uint16_t *)TEST_ADDR;

	
	//1.解锁
	//2.擦除
	//3.写入
	//4.上锁
	//5.读取校验
	
	FLASH_Status status;
	
	FLASH_Unlock();
	
	//擦除第二个扇区
	status = FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n扇区擦除完成");
	}
	else
	{
		printf("\r\n扇区擦除失败");
	}
	
	//写入内容
	status = FLASH_ProgramByte(TEST_ADDR,TEST_DATA);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n写入完成");
	}
	else
	{
		printf("\r\n写入失败");
	}
	
	//校验写入的数据是否正常
	printf("\r\n读取地址0x%x到的内容是:0x%x",TEST_ADDR,*byte_p);
	
	
	
	//擦除第二个扇区
	status = FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n扇区擦除完成");
	}
	else
	{
		printf("\r\n扇区擦除失败");
	}
		
	//写入内容
	status = FLASH_ProgramHalfWord(TEST_ADDR,0x55);
	
	if(status == FLASH_COMPLETE)
	{
		printf("\r\n写入完成");
	}
	else
	{
		printf("\r\n写入失败");
	}
	
	//校验写入的数据是否正常
	printf("\r\n读取地址0x%x到的内容是:0x%x",TEST_ADDR,*half_word_p);
	
	FLASH_Lock();
	
	//上锁之后再次读取，校验写入的数据是否正常
	printf("\r\n上锁后读取地址0x%x到的内容是:0x%x",TEST_ADDR,*half_word_p);
	
}
/*********************************************END OF FILE**********************/

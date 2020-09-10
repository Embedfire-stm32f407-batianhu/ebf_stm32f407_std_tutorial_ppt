/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   读写保护驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./rw_protect/bsp_rw_protect.h"   
#include "./usart/bsp_debug_usart.h"
#include "./key/bsp_key.h" 

 /**
  * @brief  设置读保护
  * @param  无
  * @retval 无
  */
void Read_Protect_Config(void)
{		
	if(FLASH_OB_GetRDP() == RESET)
	{
		printf("\r\n当前保护级别为level 0 ，即将设置成level 1");
		
		FLASH_OB_Unlock();

		FLASH_OB_RDPConfig(OB_RDP_Level_1);

		if(FLASH_OB_Launch() == FLASH_COMPLETE)
		{
			printf("\r\n设置为level 1 完成 ");
		}
		
		FLASH_OB_Lock();
	}
	else
	{		
		printf("\r\n当前保护级别为level 1，按下key1可以解除保护，解除后，本程序会丢失");	
		
		while(1)
		{
			if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
			{
				printf("\r\n即将解除读保护");				
						
				FLASH_OB_Unlock();

				FLASH_OB_RDPConfig(OB_RDP_Level_0);
				
				printf("\r\n降级会擦除整片内部FLASH的内容，请耐心等待");

				if(FLASH_OB_Launch() == FLASH_COMPLETE)
				{
					printf("\r\n解除读保护完成，请复位 ");
				}
				
				FLASH_OB_Lock();

			}
		
		}
	}	

}


 /**
  * @brief  设置写保护
  * @param  无
  * @retval 无
  */
void Write_Protect_Config(void)
{		
	uint16_t wrp_status;
	wrp_status = FLASH_OB_GetWRP();
	if(wrp_status&0x7FF == 0x7FF )
	{
		printf("\r\n当前没有写保护");
		
		FLASH_OB_Unlock();

		FLASH_OB_WRPConfig(OB_WRP_Sector_0|OB_WRP_Sector_1 ,ENABLE);

		if(FLASH_OB_Launch() == FLASH_COMPLETE)
		{
			printf("\r\n设置写保护完成 ");
		}
		
		FLASH_OB_Lock();
	}
	else
	{		
		printf("\r\n当已设置了写保护，wrp_status = 0x%x，按key2解除写保护",wrp_status);	
		
		while(1)
		{
			if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON)
			{
				printf("\r\n即将解除写保护");				
						
				FLASH_OB_Unlock();

				FLASH_OB_WRPConfig(OB_WRP_Sector_0|OB_WRP_Sector_1 ,DISABLE);
				
				if(FLASH_OB_Launch() == FLASH_COMPLETE)
				{
					printf("\r\n解除写保护完成，请复位 ");
				}
				
				FLASH_OB_Lock();

			}
		
		}
	}	

}
/*********************************************END OF FILE**********************/

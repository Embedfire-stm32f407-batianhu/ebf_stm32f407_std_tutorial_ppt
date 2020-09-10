/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��д��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./rw_protect/bsp_rw_protect.h"   
#include "./usart/bsp_debug_usart.h"
#include "./key/bsp_key.h" 

 /**
  * @brief  ���ö�����
  * @param  ��
  * @retval ��
  */
void Read_Protect_Config(void)
{		
	if(FLASH_OB_GetRDP() == RESET)
	{
		printf("\r\n��ǰ��������Ϊlevel 0 ���������ó�level 1");
		
		FLASH_OB_Unlock();

		FLASH_OB_RDPConfig(OB_RDP_Level_1);

		if(FLASH_OB_Launch() == FLASH_COMPLETE)
		{
			printf("\r\n����Ϊlevel 1 ��� ");
		}
		
		FLASH_OB_Lock();
	}
	else
	{		
		printf("\r\n��ǰ��������Ϊlevel 1������key1���Խ������������󣬱�����ᶪʧ");	
		
		while(1)
		{
			if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
			{
				printf("\r\n�������������");				
						
				FLASH_OB_Unlock();

				FLASH_OB_RDPConfig(OB_RDP_Level_0);
				
				printf("\r\n�����������Ƭ�ڲ�FLASH�����ݣ������ĵȴ�");

				if(FLASH_OB_Launch() == FLASH_COMPLETE)
				{
					printf("\r\n�����������ɣ��븴λ ");
				}
				
				FLASH_OB_Lock();

			}
		
		}
	}	

}


 /**
  * @brief  ����д����
  * @param  ��
  * @retval ��
  */
void Write_Protect_Config(void)
{		
	uint16_t wrp_status;
	wrp_status = FLASH_OB_GetWRP();
	if(wrp_status&0x7FF == 0x7FF )
	{
		printf("\r\n��ǰû��д����");
		
		FLASH_OB_Unlock();

		FLASH_OB_WRPConfig(OB_WRP_Sector_0|OB_WRP_Sector_1 ,ENABLE);

		if(FLASH_OB_Launch() == FLASH_COMPLETE)
		{
			printf("\r\n����д������� ");
		}
		
		FLASH_OB_Lock();
	}
	else
	{		
		printf("\r\n����������д������wrp_status = 0x%x����key2���д����",wrp_status);	
		
		while(1)
		{
			if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON)
			{
				printf("\r\n�������д����");				
						
				FLASH_OB_Unlock();

				FLASH_OB_WRPConfig(OB_WRP_Sector_0|OB_WRP_Sector_1 ,DISABLE);
				
				if(FLASH_OB_Launch() == FLASH_COMPLETE)
				{
					printf("\r\n���д������ɣ��븴λ ");
				}
				
				FLASH_OB_Lock();

			}
		
		}
	}	

}
/*********************************************END OF FILE**********************/

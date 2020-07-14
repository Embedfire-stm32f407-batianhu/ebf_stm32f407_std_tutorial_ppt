/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_i2c_ee.h"   
#include "bsp_i2c_gpio.h"   

//���EEPROM�Ƿ����
//1��ʾû��⵽EEPROM
//0��ʾEEPROM��������
uint8_t ee_CHECK_DEVICE(uint8_t addr)
{
	uint8_t result;
	
	i2c_START();
	
	//����EEPROM�豸��ַ
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

//�ȴ�EEPROM�ڲ�ʱ�����
//1��ʾ��ʱ
//0��ʾ���
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


//��EEPROMд��һ���ֽ�
//������1 ����0
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
			
			//����EEPROM�豸��ַ
			i2c_WRITE_BYTE(EEPROM_ADDR|EEPROM_WRITE_DIR);
			
			if(i2c_WAIT_ASK())
			{
				goto w_fail;
			}
			else
			{		
				//����Ҫд��Ĵ洢��Ԫ���ַ
				i2c_WRITE_BYTE(w_addr);
				
				if(i2c_WAIT_ASK())
				{
					goto w_fail;
				}
			}
		}					
	
		//����Ҫд�������
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



//��EEPROM��ȡһ���ֽ�
//������1 ����0
uint8_t ee_READ_BYTES(uint8_t r_addr,uint8_t *data,uint16_t size)
{
	if(ee_WAIT_STANDPY())
		goto r_fail;
	
	i2c_START();
	
	//����EEPROM�豸��ַ
	i2c_WRITE_BYTE(EEPROM_ADDR|EEPROM_WRITE_DIR);
	
	if(i2c_WAIT_ASK())
	{
		goto r_fail;
	}
	else
	{
		
		//����Ҫ��ȡ�Ĵ洢��Ԫ���ַ
		i2c_WRITE_BYTE(r_addr);
		
		if(i2c_WAIT_ASK())
		{
			goto r_fail;
		}
		else
		{
			//���͵ڶ�����ʼ�ź�
			i2c_START();
			
			//���͵ڶ����豸��ַ������ʽ
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
						i2c_NASK();//�������ݹ��ˣ�������Ӧ���ź�
					}
					else	
					{						
						i2c_ASK();
					}
					
					data++;//ָ��ָ����һ��������
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

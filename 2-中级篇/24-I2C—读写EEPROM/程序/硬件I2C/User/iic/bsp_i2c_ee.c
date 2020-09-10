/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   EEPROM��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./iic/bsp_i2c_ee.h"

/*
Ҫʵ����EEPROMд�����ݡ�
1.��ʼ��Ӳ��I2C
2.��д��EEPROM�������ݵĺ�������������д��
3.���ö�д������EEPROMд�����ݣ�����ȡ����У��
*/

#define TIME_OUT  0x00000FFF

uint32_t count_wait = TIME_OUT;



uint8_t Error_CallBack(uint8_t code);

 /**
  * @brief  EEPROM_I2C_Config��ʼ��GPIO��I2C��ģʽ
  * @param  ��
  * @retval ��
  */
void EEPROM_I2C_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStructure;
		
  RCC_AHB1PeriphClockCmd(EEPROM_I2C_SCL_GPIO_CLK|EEPROM_I2C_SDA_GPIO_CLK,ENABLE);

  /* ʹ�� I2C ʱ�� */
  RCC_APB1PeriphClockCmd(EEPROM_I2C_CLK, ENABLE);
	
	 /* ���� PXx �� IIC*/
  GPIO_PinAFConfig(EEPROM_I2C_SCL_GPIO_PORT,EEPROM_I2C_SCL_SOURCE,EEPROM_I2C_SCL_AF);

  /*  ���� PXx �� IIC*/
  GPIO_PinAFConfig(EEPROM_I2C_SDA_GPIO_PORT,EEPROM_I2C_SDA_SOURCE,EEPROM_I2C_SDA_AF);
  
  /* GPIO SCL��ʼ�� */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN  ;  
  GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* ��ʼ��SDA */
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN  ; 
  GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //ʹ��7λ�豸��ַ
	I2C_InitStructure.I2C_ClockSpeed = EEPROM_I2C_BAUDRATE;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = STM32_I2C_OWN_ADDR;

  I2C_Init(EEPROM_I2C, &I2C_InitStructure); 
	
	
  /* ʹ��I2C */
  I2C_Cmd(EEPROM_I2C, ENABLE);
}

//addr:Ҫд��Ĵ洢��Ԫ��ַ
//data:Ҫд�������
//return:0��ʾ��������0Ϊʧ��
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
	//������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(1);
		}
	}	
	
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊд����
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(2);
		}
	}
	
	//����Ҫд��Ĵ洢��Ԫ��ַ
	I2C_SendData(EEPROM_I2C,addr);
	
	//���� count_wait
	count_wait = TIME_OUT;	
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(3);
		}
	}
	
	//����Ҫд�������
	I2C_SendData(EEPROM_I2C,data);
	
	//���� count_wait
	count_wait = TIME_OUT;		
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(4);
		}
	}
	
	//���������ź�
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//�ȴ�д�����
	return 	Wait_For_Standby();

}


//addr:Ҫд��Ĵ洢��Ԫ�׵�ַ
//data:Ҫд������ݵ�ָ��
//size:Ҫд����ٸ����ݣ�sizeС�ڵ���8��
//return:0��ʾ��������0Ϊʧ��
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t size)
{
	//������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(12);
		}
	}	
	
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊд����
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(13);
		}
	}
	
	//����Ҫд��Ĵ洢��Ԫ��ַ
	I2C_SendData(EEPROM_I2C,addr);
	
	//���� count_wait
	count_wait = TIME_OUT;	
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
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
		//����Ҫд�������
		I2C_SendData(EEPROM_I2C,*data);
		
		//���� count_wait
		count_wait = TIME_OUT;		
		//�ȴ�EV8_2�¼���ֱ�����ɹ�
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
	
	//���������ź�
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//�ȴ�д�����
	return 	Wait_For_Standby();

}


//addr:Ҫд��Ĵ洢��Ԫ�׵�ַ
//data:Ҫд������ݵ�ָ��
//size:Ҫд����ٸ�����
//return:0��ʾ��������0Ϊʧ��
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t* data, uint16_t size)
{

	// single_adrr = 1 = 1 % 8ʱ  д�� EEPROM_PAGE_SIZE-single_adrr = 7
	uint8_t single_adrr = addr%EEPROM_PAGE_SIZE;
	
	if(single_adrr == 0)
	{	
		uint8_t num_of_page = size/EEPROM_PAGE_SIZE;	
		uint8_t single_byte = size%EEPROM_PAGE_SIZE;
		
		while(num_of_page--)
		{
			//����ҳд�뺯��
			EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
			
			//�ȴ�д�����
			Wait_For_Standby();
			
			addr += EEPROM_PAGE_SIZE;
			data += EEPROM_PAGE_SIZE;
		}
			
		//����ҳд�뺯��
		EEPROM_Page_Write(addr, data, single_byte);
		
		//�ȴ�д�����
		Wait_For_Standby();	
	}
	else //addr������
	{
		uint8_t num_of_page,single_byte,sheng_yu;
		//��һ��д��
		uint8_t first_size = EEPROM_PAGE_SIZE - single_adrr;
		
		//����ҳд�뺯��
		EEPROM_Page_Write(addr, data, first_size);
		
		//�ȴ�д�����
		Wait_For_Standby();
		
		addr += first_size;
		data += first_size;
		
		//ʣ��Ҫд�������
		sheng_yu = size - first_size;
		
		num_of_page = sheng_yu/EEPROM_PAGE_SIZE;	
		single_byte = sheng_yu%EEPROM_PAGE_SIZE;	
	
		
		while(num_of_page--)
		{
			//����ҳд�뺯��
			EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
			
			//�ȴ�д�����
			Wait_For_Standby();
			
			addr += EEPROM_PAGE_SIZE;
			data += EEPROM_PAGE_SIZE;
		}
			
		//����ҳд�뺯��
		EEPROM_Page_Write(addr, data, single_byte);
		
		//�ȴ�д�����
		Wait_For_Standby();		
	
	}
	
	return 0;

}




//addr:Ҫ��ȡ�Ĵ洢��Ԫ��ַ
//data:�����洢 ��ȡ�������� ��ָ��
//return:0��ʾ��������0Ϊʧ��
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
	//������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(5);
		}
	}	
	
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊд����
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(6);
		}
	}
	
	//����Ҫ��ȡ�Ĵ洢��Ԫ��ַ
	I2C_SendData(EEPROM_I2C,addr);
	
	//���� count_wait
	count_wait = TIME_OUT;	
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(7);
		}
	}
	
	//------------------------------------------------------------------------
	//�����ڶ�����ʼ�ź�	
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(8);
		}
	}	
	
	//************************������**********************************************
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊ������
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Receiver);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(9);
		}
	}
	
	//������Ӧ���ź�
	I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
		
	//���� count_wait
	count_wait = TIME_OUT;		
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(10);
		}
	}
		
	//��������
	*data = I2C_ReceiveData(EEPROM_I2C);
		
	//���������ź�
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 0;

}


//addr:Ҫ��ȡ�Ĵ洢��Ԫ�׵�ַ
//data:�����洢 ��ȡ�������� ��ָ��
//size:Ҫ��ȡ���ٸ�����
//return:0��ʾ��������0Ϊʧ��
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size)
{
	//������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(16);
		}
	}	
	
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊд����
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(17);
		}
	}
	
	//����Ҫ��ȡ�Ĵ洢��Ԫ��ַ
	I2C_SendData(EEPROM_I2C,addr);
	
	//���� count_wait
	count_wait = TIME_OUT;	
	//�ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(18);
		}
	}
	
	//------------------------------------------------------------------------
	//�����ڶ�����ʼ�ź�	
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
	{
		count_wait--;
		if(count_wait == 0 )
		{
			return Error_CallBack(19);
		}
	}	
	
	//************************������**********************************************
	//Ҫ���͵�EEPROM�豸��ַ,������Ϊ������
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Receiver);
	
	//���� count_wait
	count_wait = TIME_OUT;
	//�ȴ�EV6�¼���ֱ�����ɹ�
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
			//������Ӧ���ź�
			I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
		}
		else
		{
			//����Ӧ���ź�
			I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
		}
				
		//���� count_wait
		count_wait = TIME_OUT;		
		//�ȴ�EV8_2�¼���ֱ�����ɹ�
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		{
			count_wait--;
			if(count_wait == 0 )
			{
				return Error_CallBack(21);
			}
		}
			
		//��������
		*data = I2C_ReceiveData(EEPROM_I2C);
		data++;
	}
		
	//���������ź�
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	return 0;

}


//�ȴ�EEPROM�ڲ�д��������
//Ϊ0��ʾ�����ȴ���ɣ���0��ʾ�ȴ�������Ӧ�ź�
uint8_t Wait_For_Standby(void)
{
	uint32_t check_count = 0xFFFFF;
	
	while(check_count--)
	{
		//������ʼ�ź�
		I2C_GenerateSTART(EEPROM_I2C, ENABLE);
		
		//���� count_wait
		count_wait = TIME_OUT;
		//�ȴ�EV5�¼���ֱ�����ɹ�
		while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		{
			count_wait--;
			if(count_wait == 0 )
			{
				return Error_CallBack(11);
			}
		}	
		
		//Ҫ���͵�EEPROM�豸��ַ,������Ϊд����
		I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDR, I2C_Direction_Transmitter);
		
		//���� count_wait
		count_wait = TIME_OUT;
		//�ȴ�EV6�¼���ֱ�����ɹ�
		while(count_wait--)
		{
			//����⵽��Ӧ��˵���ڲ�дʱ����ɣ������ȴ�����
			if(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS)
			{
				//�˳�ǰֹͣ����ͨѶ
				I2C_GenerateSTOP(EEPROM_I2C, ENABLE);	
				return 0;
			}			
		}		
	}
	
	//�˳�ǰֹͣ����ͨѶ
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);	
	return 1;
}

//code:�������
uint8_t Error_CallBack(uint8_t code)
{
	printf("\r\nI2C error occur,code=%d\r\n", code);
	return code;
}

/*********************************************END OF FILE**********************/

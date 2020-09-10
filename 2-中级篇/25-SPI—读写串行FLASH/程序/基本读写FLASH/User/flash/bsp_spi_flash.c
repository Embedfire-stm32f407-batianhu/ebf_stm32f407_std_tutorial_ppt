/**
  ******************************************************************************
  * @file    bsp_bsp_flash.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief  SPI FLASH Ӧ�ú���bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./flash/bsp_spi_flash.h"
#include "./usart/bsp_debug_usart.h"

/*
1.��ʼ��������ż�SPI����ģʽ
2.��д�����Ķ�д�����ֽڵ����̺���
3.����2�ĺ�������ɸ�������
4.���������дFLASH��У������
*/


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   


static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);




/**
  * @brief   SPI I/O����
  * @param  ��
  * @retval ��
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
	
	//ʹ���������CS����
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
 
}

/**
  * @brief  SPI ����ģʽ����
  * @param  ��
  * @retval ��
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

  SPI_Init(FLASH_SPI, &SPI_InitStructure);	                                      /* I2C1 ��ʼ�� */
  SPI_Cmd(FLASH_SPI, ENABLE);  	                                                /* ʹ�� I2C1 */
}

/**
  * @brief  SPI ����(FLASH)��ʼ��
  * @param  ��
  * @retval ��
  */
void SPI_FLASH_Init(void)
{
  SPI_GPIO_Config(); 
 
  SPI_Mode_Config();
}


/**
  * @brief   ͨ��SPI����һ���ֽ�
  * @param   
  *		@arg data:Ҫ���͵�����
  * @retval  ���յ�������
  */
uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
	uint8_t re_data;
	
	//�ȴ�TXE��־
	SPITimeout = SPIT_FLAG_TIMEOUT;
  while(SPI_I2S_GetFlagStatus (FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }    
	
	SPI_I2S_SendData(FLASH_SPI, data);
	
	//�ȴ�RXNE��־ ��ȷ�Ϸ�����ɣ���׼����ȡ����
	SPITimeout = SPIT_FLAG_TIMEOUT;
	while(SPI_I2S_GetFlagStatus (FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(2);
  }   
	
	re_data = SPI_I2S_ReceiveData(FLASH_SPI);
	
	return re_data;
}

//��ID0 -ID7
uint8_t SPI_FLASH_Read_ID(void)
{
	uint8_t id;
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();
	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReleasePowerDown);
	
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	
	//���ն�ȡ��������
	
	id = SPI_FLASH_ByteWrite(DUMMY);
	FLASH_SPI_CS_HIGH();
	return id;

}


//��������
//addr:������뵽Ҫ�������������׵�ַ
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
	//дʹ��
	SPI_FLASH_Write_Enable();
	
	
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();
	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_SectorErase);
	
	//����Ҫ�����ĵ�ַ
	SPI_FLASH_ByteWrite((addr>>16) & 0xFF);
	SPI_FLASH_ByteWrite((addr>>8) & 0xFF);
	SPI_FLASH_ByteWrite(addr & 0xFF);
	
	FLASH_SPI_CS_HIGH();	
	
	//�ȴ��ڲ�ʱ�����
	SPI_FLASH_Wait_For_Standby();

}

//��ȡ����
//addr:Ҫ��ȡ���ݵ��׵�ַ��
//buf:�洢��ȡ�������ݵ�ָ��
//size:Ҫ��ȡ���ٸ�����
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();
	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReadData);
	
	//����Ҫ��ȡ�ĵ�ַ
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


//д������
//addr:Ҫд�����ݵ��׵�ַ��
//buf:Ҫд������ݵ�ָ��
//size:Ҫд����ٸ����� ������256
void SPI_FLASH_Write_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	uint32_t count=0;
	
	while(size--)
	{
		count++;
		
		//��һ��ִ�У�1,257,256*2+1,256*3+1,addr���뵽4096ʱ
		
		if(count == 1 || (count%256) ==1 || (addr%4096)==0)
		{
			//������һ�ε�ҳд��ָ��
			FLASH_SPI_CS_HIGH();	

			//�ȴ���һ��ҳд������
			SPI_FLASH_Wait_For_Standby();
			
			//дʹ��
			SPI_FLASH_Write_Enable();	
			
			//����Ƭѡ����
			FLASH_SPI_CS_LOW();
			
			//ָ�����
			SPI_FLASH_ByteWrite(W25X_PageProgram);
			
			//����Ҫд��ĵ�ַ
			SPI_FLASH_ByteWrite((addr>>16) & 0xFF);
			SPI_FLASH_ByteWrite((addr>>8) & 0xFF);
			SPI_FLASH_ByteWrite(addr & 0xFF);	
		}			

		SPI_FLASH_ByteWrite(*buf);
		buf++;
		addr++;	
	}
	
	FLASH_SPI_CS_HIGH();	

	//�ȴ��ڲ�ʱ�����
	SPI_FLASH_Wait_For_Standby();

}

//дʹ��
void SPI_FLASH_Write_Enable(void)
{
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();
	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_WriteEnable);
	

	FLASH_SPI_CS_HIGH();
}

//�ȴ�ֱ������״̬
void SPI_FLASH_Wait_For_Standby(void)
{
	uint8_t status ;
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReadStatusReg);
	
	SPITimeout = SPIT_LONG_TIMEOUT;
	
	while(1)
	{
		status = SPI_FLASH_ByteWrite(DUMMY);
		
		//�������������˵��Ϊ����״̬
		if((status & 0x01) == 0) 
			break;
		
		//��SPITimeoutΪ0����ʾ�Ѽ��SPITimeout�ζ���Ϊbusy������ѭ��
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
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾSPI��ȡʧ��.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FLASH_ERROR("SPI �ȴ���ʱ!errorCode = %d",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/

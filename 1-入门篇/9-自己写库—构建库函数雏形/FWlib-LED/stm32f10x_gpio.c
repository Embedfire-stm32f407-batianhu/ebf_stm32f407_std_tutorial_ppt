#include "stm32f10x_gpio.h"

void GPIO_SetBits( GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRR = GPIO_Pin;
}

void GPIO_RetsetBits( GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BRR = GPIO_Pin;
}

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
/*---------------------- GPIO ģʽ���� --------------------------*/
  // ���������GPIO_Mode�ĵ���λ�ݴ���currentmode
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
	
  // bit4��1��ʾ�����bit4��0�������� 
  // �ж�bit4��1����0������ѡ�ж������뻹�����ģʽ
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
	// ���ģʽ��Ҫ��������ٶ�
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*-------------GPIO CRL �Ĵ������� CRL�Ĵ��������ŵ�8λIO- -------*/
  // ���ö˿ڵ�8λ����Pin0~Pin7
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
	// �ȱ���CRL�Ĵ�����ֵ
    tmpreg = GPIOx->CRL;
		
	// ѭ������Pin0��ʼ��ԣ��ҳ������Pin
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
	 // pos��ֵΪ1����pinposλ
      pos = ((uint32_t)0x01) << pinpos;
      
	  // ��pos���������GPIO_PIN��λ�����㣬Ϊ������ж���׼��
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
			
	  //��currentpin=pos,���ҵ�ʹ�õ�����
      if (currentpin == pos)
      {
		// pinpos��ֵ������λ������4������Ϊ�Ĵ�����4���Ĵ���λ����һ������
        pos = pinpos << 2;
       //�ѿ���������ŵ�4���Ĵ���λ���㣬�����Ĵ���λ����
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
				
        // ��Ĵ���д�뽫Ҫ���õ����ŵ�ģʽ
        tmpreg |= (currentmode << pos);  
				
		// �ж��Ƿ�Ϊ��������ģʽ
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
		  // ��������ģʽ������Ĭ����0����BRR�Ĵ���д1�ɶ�������0
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }				
        else
        {
          // �ж��Ƿ�Ϊ��������ģʽ
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
		    // ��������ģʽ������Ĭ��ֵΪ1����BSRR�Ĵ���д1�ɶ�������1
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
		// ��ǰ�洦�����ݴ�ֵд�뵽CRL�Ĵ���֮��
    GPIOx->CRL = tmpreg;
  }
/*-------------GPIO CRH �Ĵ������� CRH�Ĵ��������Ÿ�8λIO- -----------*/
  // ���ö˿ڸ�8λ����Pin8~Pin15
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
		// // �ȱ���CRH�Ĵ�����ֵ
    tmpreg = GPIOx->CRH;
		
	// ѭ������Pin8��ʼ��ԣ��ҳ������Pin
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
			
      // pos���������GPIO_PIN��λ������
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
			
	 //��currentpin=pos,���ҵ�ʹ�õ�����
      if (currentpin == pos)
      {
		//pinpos��ֵ������λ������4������Ϊ�Ĵ�����4���Ĵ���λ����һ������
        pos = pinpos << 2;
        
	    //�ѿ���������ŵ�4���Ĵ���λ���㣬�����Ĵ���λ����
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
				
        // ��Ĵ���д�뽫Ҫ���õ����ŵ�ģʽ
        tmpreg |= (currentmode << pos);
        
		// �ж��Ƿ�Ϊ��������ģʽ
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
		  // ��������ģʽ������Ĭ����0����BRR�Ĵ���д1�ɶ�������0
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
         // �ж��Ƿ�Ϊ��������ģʽ
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
		  // ��������ģʽ������Ĭ��ֵΪ1����BSRR�Ĵ���д1�ɶ�������1
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
	// ��ǰ�洦�����ݴ�ֵд�뵽CRH�Ĵ���֮��
    GPIOx->CRH = tmpreg;
  }
}


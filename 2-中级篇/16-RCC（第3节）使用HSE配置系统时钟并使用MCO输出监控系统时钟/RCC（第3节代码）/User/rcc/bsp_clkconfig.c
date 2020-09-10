#include "bsp_clkconfig.h"

void User_SetSysClock(void)
{	
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	
	/* 复位RCC的所有寄存器 */
	RCC_DeInit();
  
  /* Enable HSE */
	/* 使能HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
	/* 等待HSE启动稳定，如果超时则退出 */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

	/* HSE 启动成功 */
  if (HSEStatus == (uint32_t)0x01)
  {
    /* Select regulator voltage output Scale 1 mode */
		/* 选择电压调节器的模式为1 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; 
    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;    
    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
  
    /* Configure the main PLL */
		/* 配置主PLL */
//    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
//                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24); 
		
    RCC->PLLCFGR = 25 | (336 << 6) | (((2 >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (7 << 24); 		
    
    /* Enable the main PLL */
		/* 使能主PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till the main PLL is ready */
		/* 等待主PLL稳定 */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		/* 配置FLASH预取指，指令缓存，数据缓存，等待周期 */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		
    /* Select the main PLL as system clock source */
		/* 选择主PLL时钟作为系统时钟 */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
		/* 确保主PLL时钟选为系统时钟 */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
		/* HSE 启动失败，在这里添加启动失败的处理代码 */
  }

}


void HSE_SetSysClock(uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{		
	ErrorStatus HSE_ErrorStatus = ERROR; 
	/* 复位RCC的所有寄存器 */
	RCC_DeInit();  

	/* 使能HSE */
	RCC_HSEConfig(RCC_HSE_ON); 
	HSE_ErrorStatus = RCC_WaitForHSEStartUp();
	
	if( HSE_ErrorStatus == SUCCESS )
	{
		/* 选择电压调节器的模式为1 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div4);
		RCC_PCLK2Config(RCC_HCLK_Div2);
		
		RCC_PLLConfig(RCC_PLLSource_HSE, PLLM, PLLN, PLLP, PLLQ);
		
		RCC_PLLCmd(ENABLE);		
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET )
		{}
			
		/* 配置FLASH预取指，指令缓存，数据缓存，等待周期 */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
			
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);			
		while( RCC_GetSYSCLKSource() != 0x08 ){}
	}
		else
	 {
		 /* HSE启动失败，在这里添加错误处理代码 */
	 }
}



void MCO1_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
													   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void MCO2_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC, ENABLE);
													   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}
















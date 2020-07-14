static void SetSysClockTo72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 和 PCLK1 配置 */    
  /* 使能 HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON); 

	/* 等待HSE稳定，并做超时处理 */
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

	/* HSE启动成功，程序可以继续往下执行 */
  if (HSEStatus == (uint32_t)0x01)
  {
		/* 使能预取指 */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

		/* FLASH的等待时间 */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

 
    /* HCLK = SYSCLK = 72M */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;      
    /* PCLK2 = HCLK =72M */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;    
    /* PCLK1 = HCLK = 36M */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
		
		/*  PLL 配置: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);

    /* 使能 PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* 等待PLL稳定 */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }    

		/* 选择PLLCLK为系统时钟 */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

		/* 等待PLLCLK作为系统时钟切换完成 */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { 
		/* HSE启动失败，用户可以在这里添加错误处理代码 */
  }
}
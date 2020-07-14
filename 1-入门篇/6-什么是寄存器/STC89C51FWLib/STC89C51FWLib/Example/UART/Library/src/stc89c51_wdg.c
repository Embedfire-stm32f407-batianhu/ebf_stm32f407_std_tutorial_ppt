#include "stc89c51_wdg.h"


/*
 * brief: 获取电源复位标志，是上电复位还是复位引脚或看门狗复位
 */
PowerUpState GET_PowerUp_Flag(void)
{
    uchar  Flag = PowerUp_Flag;
	PowerUpState  PowerState = PowerUpReset;  

    Flag &= PCON;

	if (Flag == 0)
	{
	    PowerState =  Pin_WDG_Reset;   
    }
	else
	{
	    PCON &= ~PowerUp_Flag;    
	}
	
	return (PowerState);
}

/*-------------------------------------- End Of File ------------------------------------------------------*/
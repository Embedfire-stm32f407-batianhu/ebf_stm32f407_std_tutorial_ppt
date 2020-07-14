#include "stc89c51_wdg.h"


/*
 * brief: ��ȡ��Դ��λ��־�����ϵ縴λ���Ǹ�λ���Ż��Ź���λ
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
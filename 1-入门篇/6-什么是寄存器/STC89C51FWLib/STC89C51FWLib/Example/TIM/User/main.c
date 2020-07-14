#include "stc89c51.h"


int main(void)
{
    TIM_Init(TIM0,Timing_50ms, TIM0_TimeBase_Mode_1);
	TIM0_Cmd(ENABLE);
	TIM0_ITCmd(ENABLE);
						
    while (1) ;

}
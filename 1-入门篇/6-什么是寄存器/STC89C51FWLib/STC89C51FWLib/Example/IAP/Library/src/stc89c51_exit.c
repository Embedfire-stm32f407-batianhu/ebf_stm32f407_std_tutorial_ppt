#include "stc89c51_exit.h"


/*
 * brief: Change External Interrupt Priority
 * param: EXIT0_Priority_0、EXIT0_Priority_1、EXIT0_Priority_2、EXIT0_Priority_3
 *        EXIT1_Priority_0、EXIT1_Priority_1、EXIT1_Priority_2、EXIT1_Priority_3  
 */
void EXIT_PrioChange(uint16 Priority)
{	
    IPH |= Priority >> 8;
	IP |= (uchar)Priority; 
}

/*-------------------------------------- End Of File ------------------------------------------------------*/

#include "stc89c51.h"


int main(void)
{
    EXIT1_Init(EXIT1_FallEdge);  /* �½��ش��� */
	EXTI1_Cmd(ENABLE);  /* �����ⲿ�ж�1 */

	EXIT0_Init(EXIT0_FallEdge);
	EXTI0_Cmd(ENABLE);

	EXIT_IT_Cmd(ENABLE);  /* �������ж� */

	while (1);
}
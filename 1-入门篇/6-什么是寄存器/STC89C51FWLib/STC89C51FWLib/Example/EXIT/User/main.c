#include "stc89c51.h"


int main(void)
{
    EXIT1_Init(EXIT1_FallEdge);  /* 下降沿触发 */
	EXTI1_Cmd(ENABLE);  /* 开启外部中断1 */

	EXIT0_Init(EXIT0_FallEdge);
	EXTI0_Cmd(ENABLE);

	EXIT_IT_Cmd(ENABLE);  /* 开启总中断 */

	while (1);
}
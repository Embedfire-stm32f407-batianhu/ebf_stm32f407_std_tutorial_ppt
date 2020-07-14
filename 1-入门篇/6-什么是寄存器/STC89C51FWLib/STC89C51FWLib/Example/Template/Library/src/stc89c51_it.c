
/*----------------- �жϷ����� ------------------*/

#include "stc89c51_it.h" 


/*
 * bruef: �ⲿ�ж�0���жϴ�����
 *        �жϱ�־ IE0 ִ���жϷ�������,Ӳ���Զ����
 */
void EXIT0_IRQHandler(void) interrupt 0
{

}


/*
 * brief: ��ʱ��0���жϴ�����
 *        TF1 �����жϣ�Ӳ���Զ�����
 */
void TIM0_IRQHandler(void) interrupt 1
{
    static uchar count = 0;

	TIM_SetReLoad(TIM0, Timing_50ms);

	 if (count == 20)
	 {
	   P1 ^= 0xff;
	   count = 0;
	 }

	 count++;
	 
}


/*
 * brief: �ⲿ�ж�1���жϴ����� 
 *        �жϱ�־ IE1 ִ���жϷ�������,Ӳ���Զ����
 */
void EXIT1_IRQHandler(void) interrupt 2
{

}


/*
 * brief����ʱ��1���жϴ�����
 */
void TIM1_IRQHandler(void) interrupt 3
{

}


/*
 * brief�������жϴ�����
 *        �жϱ�־���ڷ��ͻ���ܺ��������
 */
void UART_IRQHandler(void) interrupt 4
{
    if (RI != 0)  /* ���жϿ���ʱ���������Ҳ������жϣ�������Ҫ�ж� */
	{

	}
} 


/*
 * brief: ��ʱ��2�жϴ�����
 *        ����Ҫ��װ��ֵ��Ӳ���Զ�����
 */
void TIM2_IRQHandler(void) interrupt 5
{

} 

/*-------------------------------------- End Of File ------------------------------------------------------*/

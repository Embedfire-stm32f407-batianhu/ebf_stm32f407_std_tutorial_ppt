/*
 * ʵ������LED_0��LED_6������������Ź���λ�͸�λ���Ÿ�λʱ��LED_7����
 *           ���رյ�Դ���ϵ�ʱ��LED_7��
 */

#include "stc89c51.h"


void Delay_ms(uint16 z);

sbit LED_7 = P1^7;


int main(void)
{
    uchar flag = 0, a = 0xfe;
 
    WDG_CntPeriod(WDG_CntPeriod_2275ms);   /* ���ÿ��Ź���λʱ�� */
	WDG_ResetCounter();  /* ��λ�����������¼��� */
	WDG_Cmd(ENABLE);     /* �������Ź� */

	flag = GET_PowerUp_Flag();  /* ��ȡ��Դ��λ��־ */ 
	LED_7 = flag;  /* ��Դ��λ��־��LED_7����1����LED��Ϊ��Դ�ϵ縴λ������Ϊ���Ź���λ���ֶ���λ����LED����*/	 

	while (1)
	{
		Delay_ms(300);
		P1 &= (a <<= 1);  /* P1�Ž�LED */
		Delay_ms(300);

	//	WDG_ResetCounter();  /* ��λ�����������¼���,���Ź����Ḵλ */
	}
}


void Delay_ms(uint16 z)  /* ��׼ȷ����ʱ */
{
	uint16 x, y;

	for (x=z; x>0; x--)
	{
	    for (y=100; y>0; y--);
	}	
}



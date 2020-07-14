#include "stc89c51_iap.h"


/*
 * brief: �����в���ǰ����Ҫ�����õȴ�ʱ�䲢����IAP  
 */
void IAP_Init(void)
{
    IAP_Cmd(ENABLE);
	IAP_CONTR |= IAP_WaitPeriod;
}


/*
 * parame: ��ַ��Χ 0x2000 -- 0x2FFF
 * return: ���ض��������� 
 */
uchar IAP_ReadData(uint16 Address)
{
    EA = 0;	  /* ��ֹ�жϴ�϶��ڲ�EEPROMD�Ĳ��� */
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Read;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;

	return (IAP_DATA);
}


/*
 * brief : �ֽڱ��ǰ�����ֽڱ���Ϊ�գ�����Ҫ�Ȳ���
 * parame: ��ַ��Χ 0x2000 -- 0x2FFF 
 */
void IAP_WriteData(uint16 Address, uchar ByteData)
{
    EA = 0;	    /* ��ֹ�жϴ�϶��ڲ�EEPROMD�Ĳ��� */
    IAP_DATA = ByteData;
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Write;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;
}


/*
 * brief : ������������һ���ֽڵĵ�ַ����������ַ,��Ƭ�����Զ�������Ӧ������
 * parame: ��ַ��Χ 0x2000 -- 0x2FFF 
 */
void IAP_EraseSector(uint16 Address)
{
    EA = 0;	   /* ��ֹ�жϴ�϶��ڲ�EEPROMD�Ĳ��� */
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Erase;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;
}


/*-------------------------------------- End Of File ------------------------------------------------------*/

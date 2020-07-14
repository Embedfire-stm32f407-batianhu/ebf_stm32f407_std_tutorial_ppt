#ifndef __STC89C51_IAP_H
#define __STC89C51_IAP_H

#include "stc89c51.h"

#define IAP_CMD_0       0x00    /* Standby ����ģʽ����IAP���� */
#define IAP_CMD_Read    0x01    /* AP-Flash / Data-Flash Read */
#define IAP_CMD_Write   0x02    /* AP-Flash / Data-Flash Program */
#define IAP_CMD_Erase   0x03    /* AP-Flash / Data-Flash Sector Erase */
#define IAP_CMD_ENABLE  0X46B9  /* ʹ������Ч */

/*
 * | ���õȴ�ʱ��   |          CPU�ȴ���ʱ�䣨��е���ڣ�						   |
 * |                |   read   |   write  |   erase   |   Recommended System Clock |
 * |    0x03        |    6     |    30    |    5471   |       5MHz				   |
 * |    0x02        |    11    |    60    |    10942  |       10MHz				   | 
 * |    0x01        |    22    |    120   |    21885  |       20MHz				   |
 * |    0x00        |    43    |    240   |    43769  |       40MHz 		       |
 */
#define IAP_WaitPeriod  0x02    /* ����ͺ�CPU�ȴ�������ɵ�ʱ�� */


/* STC89C52RC 4k��EEPROM��ַ��Χ */
#define FirstSector_StaAddr    0x2000  /* ��һ������ʼ��ַ */
#define FirstSector_EndAddr    0x21FF  /* ��һ����������ַ */
#define SecSector_StaAddr      0x2200
#define SecSector_EndAddr      0x23FF
#define ThirdSector_StaAddr    0x2400
#define ThirdSector_EndAddr    0x25FF
#define FourSector_StaAddr     0x2600
#define FourSector_EndAddr     0x27FF
#define FifSector_StaAddr      0x2800
#define FifSector_EndAddr      0x29FF
#define SixSector_StaAddr      0x2a00
#define SixSector_EndAddr      0x2BFF
#define SevenSector_StaAddr    0x2C00
#define SevenSector_EndAddr    0x2DFF
#define EighSector_StaAddr     0x2E00
#define EighSector_EndAddr     0x2FFF


/*--------------------------------- IAP function prototype -----------------------------------*/

void IAP_Init(void);
uchar IAP_ReadData(uint16 Address);
void IAP_WriteData(uint16 Address, uchar ByteData);
void IAP_EraseSector(uint16 Address);
/* param: NewState = ENABLE or DISABLE */
#define IAP_Cmd(NewState)                ((NewState) ? (IAP_CONTR |= 0x80) : (IAP_CONTR &= ~0x80))  /* ����IAP */
#define ISPArea_Switch(NewState)         ((NewState) ? (IAP_CONTR |= 0x40) : (IAP_CONTR &= ~0x40))  /* ���û����л���ISP����
         ���л���ϵͳ ISP ��س�������ʼִ�г����ѹ̻��� ISP ������                                  ִ�дˡ���������
		   ������ϵͳ���س��򣬼��P3.0/RxD ��û�кϷ�����������,����Ҫ��λ                            ��Ҫִ�������λ                           
           ���Ƕ�STC89C52RC �ڲ�8K Flash���б��                                                                        */

#define Generate_SWReset(NewState)       ((NewState) ? (IAP_CONTR |= 0x20) : (IAP_CONTR &= ~0x20))  /* �����λ,��λ��Ӳ���Զ����� */

#endif
/*-------------------------------------- End Of File -------------------------------------------*/

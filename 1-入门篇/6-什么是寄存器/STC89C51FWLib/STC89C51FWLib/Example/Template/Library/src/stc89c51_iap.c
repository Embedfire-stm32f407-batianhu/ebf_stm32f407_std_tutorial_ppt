#include "stc89c51_iap.h"


/*
 * brief: 在所有操作前，需要先配置等待时间并开启IAP  
 */
void IAP_Init(void)
{
    IAP_Cmd(ENABLE);
	IAP_CONTR |= IAP_WaitPeriod;
}


/*
 * parame: 地址范围 0x2000 -- 0x2FFF
 * return: 返回读到的数据 
 */
uchar IAP_ReadData(uint16 Address)
{
    EA = 0;	  /* 防止中断打断对内部EEPROMD的操作 */
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Read;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;

	return (IAP_DATA);
}


/*
 * brief : 字节编程前，该字节必须为空，即需要先擦除，否则读取数据错误
 * parame: 地址范围 0x2000 -- 0x2FFF 
 */
void IAP_WriteData(uint16 Address, uchar ByteData)
{
    EA = 0;	    /* 防止中断打断对内部EEPROMD的操作 */
    IAP_DATA = ByteData;
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Write;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;
}


/*
 * brief : 扇区里面任意一个字节的地址都是扇区地址,单片机会自动擦除对应的扇区
 * parame: 地址范围 0x2000 -- 0x2FFF 
 */
void IAP_EraseSector(uint16 Address)
{
    EA = 0;	   /* 防止中断打断对内部EEPROMD的操作 */
    IAP_ADDRH = (Address >> 8);
    IAP_ADDRL = Address;
	IAP_CMD = IAP_CMD_Erase;
    IAP_TRIG = (IAP_CMD_ENABLE >> 8);
	IAP_TRIG = IAP_CMD_ENABLE;
	EA = 1;
}


/*-------------------------------------- End Of File ------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "./flash/bsp_spi_flash.h"

//�����߼��豸��
#define SD_CARD     0
#define SPI_FLASH   1

#define FLASH_SECTOR_SIZE  4096


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = 0;
	uint32_t spi_result;

	switch (pdrv) {
	case SD_CARD :
		//SD ��״̬���ط�֧
		// translate the reslut code here

		return stat;

	case SPI_FLASH :
		//SPI FLASH ״̬���ط�֧
	
		spi_result = SPI_FLASH_ReadDeviceID();
		if(spi_result == 0x17)
		{
			stat &= ~STA_NOINIT; //stat���λΪ0����ʾSPI FLASHΪ����״̬
		}
		else
		{
			stat |= STA_NOINIT; //stat���λΪ1����ʾSPI FLASHΪ������״̬
		}

		return stat;
	}
	
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case SD_CARD :
		//SD ��ʼ����֧


		// translate the reslut code here

		return stat;

	case SPI_FLASH :
		//SPI_FLASH ��ʼ����֧
		SPI_FLASH_Init();
		stat = disk_status(SPI_FLASH);

		return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :
		//SD ��ȡ��֧


		// translate the reslut code here

		return res;

	case SPI_FLASH :
		//SPI_FLASH ��ȡ��֧
		//��Ҫ��ȡ��������ת���ɵ�ַ
	
		sector+=1536;
	
		SPI_FLASH_BufferRead((u8*)buff,sector*FLASH_SECTOR_SIZE, count*FLASH_SECTOR_SIZE);

		//Ĭ��ÿ�ζ���������ȡ
		return RES_OK;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :
		//SD д���֧


		// translate the reslut code here

		return res;

	case SPI_FLASH :
		//SPI_FLASH д���֧
	
		sector+=1536;
	
		while(count--)
		{
			//д��ǰ�Ȳ���
			SPI_FLASH_SectorErase(sector*FLASH_SECTOR_SIZE);
		
			//��Ҫд���������ת���ɵ�ַ
		
			SPI_FLASH_BufferWrite((u8*)buff,sector*FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
			
			sector++;
			buff += FLASH_SECTOR_SIZE;
		}
		//Ĭ��ÿ�ζ���������ȡ
		return RES_OK;

	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch(pdrv)
	{
		case SD_CARD :
			//SD ��֧


			// translate the reslut code here

			return res;

		case SPI_FLASH :
			//SPI_FLASH ��֧
				switch(cmd)
				{
					//�洢�����ж��ٸ�sector���ļ�ϵͳͨ����ֵ��ô洢���ʵ�����
					case GET_SECTOR_COUNT:
						*(DWORD *)buff = (16*1024*1024/FLASH_SECTOR_SIZE)-1536;//4096-1536
						res = RES_OK;
						break;
					
					//ÿ�������ĸ���
					case GET_SECTOR_SIZE:
						*(WORD  *)buff = FLASH_SECTOR_SIZE;
						res = RES_OK;
						break;

					
					//��ȡ��������С������ ��sectorΪ��λ
					case GET_BLOCK_SIZE:
						*(DWORD  *)buff = 1;
						res = RES_OK;
						break;
					
					//д��ͬ����disk_write�����Ѿ���ɣ�����Ĭ�Ϸ���ok
					case CTRL_SYNC:
						res = RES_OK;
						break;
					
					default:
						res = RES_PARERR;	
						break;
					
				}

			return res;

	}

	return RES_PARERR;
}
#endif


//��ȡʱ��
DWORD get_fattime (void)
{

	return 0;
}

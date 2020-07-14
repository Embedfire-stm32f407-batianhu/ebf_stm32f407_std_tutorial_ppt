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

/* Definitions of physical drive number for each drive */
#define SD_CARD			0	
#define SPI_FLASH		1	
#define USB					2	


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	
	uint32_t FlashID = 0;
	DSTATUS stat = 0;
//	int result;

	switch (pdrv) {
	case SD_CARD :
//		result = ATA_disk_status();

		// translate the reslut code here

		return stat;

	case SPI_FLASH :
			FlashID = SPI_FLASH_ReadID();	
			if (FlashID == sFLASH_ID)
			{
				stat = 0;
			}
			else
			{
				stat |= STA_NOINIT;
			}

		return stat;

	case USB :
//		result = USB_disk_status();

		// translate the reslut code here

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
//		result = ATA_disk_initialize();

		// translate the reslut code here

		return stat;

	case SPI_FLASH :
		SPI_FLASH_Init();

		return disk_status(SPI_FLASH);

	case USB :
//		result = USB_disk_initialize();

		// translate the reslut code here

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
		// translate the arguments here

//		result = ATA_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case SPI_FLASH :
		sector+=514;
		SPI_FLASH_BufferRead(buff,sector*4096,count*4096);
		return RES_OK;

	case USB :
		// translate the arguments here

//		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
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
		// translate the arguments here

//		result = ATA_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case SPI_FLASH :
		
		sector+=514;
		
		SPI_FLASH_SectorErase(sector*4096);
	
		SPI_FLASH_BufferWrite((u8* )buff,sector*4096,count*4096);
	
		return RES_OK;

	case USB :
		// translate the arguments here

//		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
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

	switch (pdrv) {
	case SD_CARD :

		// Process of the command for the ATA drive

		return res;

	case SPI_FLASH :
				switch(cmd)
				{
					case GET_SECTOR_COUNT:
						*(DWORD *)buff = 2048-514; //有2048个扇区
						break;
					
					case GET_SECTOR_SIZE:
						*(WORD *)buff = 4096;//每个扇区4096个字节
						break;
					
					case GET_BLOCK_SIZE:
						*(DWORD *)buff = 1;//
						break;			
				}				
			res = RES_OK;
				
		return res;

	case USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}
#endif

//返回时间
DWORD get_fattime (void)
{
	return 0;
}

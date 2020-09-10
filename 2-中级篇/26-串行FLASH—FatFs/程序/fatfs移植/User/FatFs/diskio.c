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

//定义逻辑设备号
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
		//SD 卡状态返回分支
		// translate the reslut code here

		return stat;

	case SPI_FLASH :
		//SPI FLASH 状态返回分支
	
		spi_result = SPI_FLASH_ReadDeviceID();
		if(spi_result == 0x17)
		{
			stat &= ~STA_NOINIT; //stat最低位为0，表示SPI FLASH为正常状态
		}
		else
		{
			stat |= STA_NOINIT; //stat最低位为1，表示SPI FLASH为不正常状态
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
		//SD 初始化分支


		// translate the reslut code here

		return stat;

	case SPI_FLASH :
		//SPI_FLASH 初始化分支
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
		//SD 读取分支


		// translate the reslut code here

		return res;

	case SPI_FLASH :
		//SPI_FLASH 读取分支
		//把要读取的扇区号转换成地址
	
		sector+=1536;
	
		SPI_FLASH_BufferRead((u8*)buff,sector*FLASH_SECTOR_SIZE, count*FLASH_SECTOR_SIZE);

		//默认每次都能正常读取
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
		//SD 写入分支


		// translate the reslut code here

		return res;

	case SPI_FLASH :
		//SPI_FLASH 写入分支
	
		sector+=1536;
	
		while(count--)
		{
			//写入前先擦除
			SPI_FLASH_SectorErase(sector*FLASH_SECTOR_SIZE);
		
			//把要写入的扇区号转换成地址
		
			SPI_FLASH_BufferWrite((u8*)buff,sector*FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
			
			sector++;
			buff += FLASH_SECTOR_SIZE;
		}
		//默认每次都能正常读取
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
			//SD 分支


			// translate the reslut code here

			return res;

		case SPI_FLASH :
			//SPI_FLASH 分支
				switch(cmd)
				{
					//存储介质有多少个sector，文件系统通过该值获得存储介质的容量
					case GET_SECTOR_COUNT:
						*(DWORD *)buff = (16*1024*1024/FLASH_SECTOR_SIZE)-1536;//4096-1536
						res = RES_OK;
						break;
					
					//每个扇区的个数
					case GET_SECTOR_SIZE:
						*(WORD  *)buff = FLASH_SECTOR_SIZE;
						res = RES_OK;
						break;

					
					//获取擦除的最小个数， 以sector为单位
					case GET_BLOCK_SIZE:
						*(DWORD  *)buff = 1;
						res = RES_OK;
						break;
					
					//写入同步在disk_write函数已经完成，这里默认返回ok
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


//获取时间
DWORD get_fattime (void)
{

	return 0;
}

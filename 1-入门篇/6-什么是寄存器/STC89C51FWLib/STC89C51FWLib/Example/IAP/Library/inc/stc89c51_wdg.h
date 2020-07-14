#ifndef __STC89C51_WDG_H
#define __STC89C51_WDG_H

#include "stc89c51.h"

#if (FOSC == 11059200L)

/* 看门狗溢出时间 = (12 x Prescale x 32768) / 11059200 = Prescale x 393216 / 11059200 */
#define WDG_CntPeriod_71ms    0x00  /* Prescale is 2  */
#define WDG_CntPeriod_142ms   0x01  /* Prescale is 4  */
#define WDG_CntPeriod_284ms   0x02  /* Prescale is 8  */
#define WDG_CntPeriod_258ms   0x03  /* Prescale is 16 */
#define WDG_CntPeriod_1137ms  0x04  /* Prescale is 32 */  
#define WDG_CntPeriod_2275ms  0x05  /* Prescale is 64 */
#define WDG_CntPeriod_4551ms  0x06  /* Prescale is 128 */
#define WDG_CntPeriod_9102ms  0x07  /* Prescale is 256 */

#elif (FOSC == 12000000L)   /* FOSC Is 12MHz */

#define WDG_CntPeriod_65ms    0x00  /* Prescale is 2  */
#define WDG_CntPeriod_131ms   0x01  /* Prescale is 4  */
#define WDG_CntPeriod_262ms   0x02  /* Prescale is 8  */
#define WDG_CntPeriod_524ms   0x03  /* Prescale is 16 */
#define WDG_CntPeriod_1048ms  0x04  /* Prescale is 32 */  
#define WDG_CntPeriod_2097ms  0x05  /* Prescale is 64 */
#define WDG_CntPeriod_4194ms  0x06  /* Prescale is 128 */ 
#define WDG_CntPeriod_8388ms  0x07  /* Prescale is 256 */
#endif

#define PowerUp_Flag          0x10  /* 电源上电状态 */

typedef enum
{
    PowerUpReset = 0xff,
	Pin_WDG_Reset = 0x00

} PowerUpState; 


/*--------------------------------- Watch Dog function prototype ------------------------------------------*/

/* param: NewState = ENABLE or DISABLE */
#define WDG_Cmd(NewState)                   ((NewState) ? (WDT_CONTR |= 0x20) : (WDT_CONTR &= ~0x20))
#define WDG_Idle_Count(NewState)            ((NewState) ? (WDT_CONTR |= 0x08) : (WDT_CONTR &= ~0x08))  /* Watch Dog 在 IDEL 模式计数 */

#define WDG_ResetCounter(void)              (WDT_CONTR |= 0x10)         /* 复位计数器，重新计数*/
#define WDG_CntPeriod(Period)               (WDT_CONTR |= (Period))     /* 设置看门狗复位时间 */
PowerUpState  GET_PowerUp_Flag(void);        /* 获取电源复位标志 */
#define En_PowerDown_Mode(void)             (PCON |= 0x02)    /* 进入 Power Down 模式，只能由外部中断唤醒 */  
#define En_Idel_Mode(void)                  (PCON |= 0X01)    /* 进入 IDLE 模式，任一中断唤醒 */

#endif
/*-------------------------------------- End Of File ------------------------------------------------------*/

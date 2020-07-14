#ifndef __STC89C52RC_H
#define __STC89C52RC_H

#include <reg52.h>

sfr IPH       = 0xB7;  /* 8052 Interrupt Priority High Register */
sfr WDT_CONTR = 0xE1;  /* 8052 Watch Dog Register */
sfr IAP_DATA  = 0xE2;
sfr IAP_ADDRH = 0xE3;
sfr IAP_ADDRL = 0xE4;
sfr IAP_CMD   = 0xE5;
sfr IAP_TRIG  = 0xE6;
sfr IAP_CONTR = 0XE7; 

/*  IPH  */
sbit PT2H   = IP^5;   /* 该位仿真测试无效, 定时器2的优先级2、3 */
sbit PSH    = IP^4;
sbit PT1H   = IP^3;
sbit PX1H   = IP^2;
sbit PT0H   = IP^1;
sbit PX0H   = IP^0;

/* 根据实际定义晶振频率，否者会影响定时器和看门狗时间精度 */
#define FOSC  11059200L  
//#define FOSC  12000000L 

#define     __I     volatile const            /* defines 'read only' permissions      */
#define     __O     volatile                  /* defines 'write only' permissions     */
#define     __IO    volatile                  /* defines 'read / write' permissions   */

typedef unsigned char        uchar;
typedef unsigned short int   uint16;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#include "stc89c51_conf.h"  /* 包含所有外设头文件 */
#endif
/*-------------------------------------- End Of File ------------------------------------------------------*/

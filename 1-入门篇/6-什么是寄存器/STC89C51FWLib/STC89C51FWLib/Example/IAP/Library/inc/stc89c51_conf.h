/*
 * brief: 包含外设头文件
 *        注不注释都一样，KEIL3以下版本会将添加到项目的C文件都编译到HEX文件,所以当C文件有没调用的函数时，会有警告。
 *                             警告的内容为两串大写的英文：没有调用xxx函数,不用管忽略即可。
 *                        KEIL4以上版本只会编译用到的C文件
 *        在编写应用程序时，只需要包含"stc89c51.h"即可
 */
#ifndef __STC89C51_CONF_H
#define __STC89C51_CONF_H

  #include "stc89c51_exit.h"
  #include "stc89c51_iap.h"
  #include "stc89c51_tim.h"
  #include "stc89c51_uart.h"
  #include "stc89c51_wdg.h"	 
  						   
#endif

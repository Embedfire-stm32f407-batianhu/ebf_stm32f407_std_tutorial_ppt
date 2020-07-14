
/*----------------- 中断服务函数 ------------------*/

#include "stc89c51_it.h" 


/*
 * bruef: 外部中断0的中断处理函数
 *        中断标志 IE0 执行中断服务程序后,硬件自动清除
 */
void EXIT0_IRQHandler(void) interrupt 0
{

}


/*
 * brief: 定时器0的中断处理函数
 *        TF1 开启中断，硬件自动清零
 */
void TIM0_IRQHandler(void) interrupt 1
{
    static uchar count = 0;

	TIM_SetReLoad(TIM0, Timing_50ms);

	 if (count == 20)
	 {
	   P1 ^= 0xff;
	   count = 0;
	 }

	 count++;
	 
}


/*
 * brief: 外部中断1的中断处理函数 
 *        中断标志 IE1 执行中断服务程序后,硬件自动清除
 */
void EXIT1_IRQHandler(void) interrupt 2
{

}


/*
 * brief：定时器1的中断处理函数
 */
void TIM1_IRQHandler(void) interrupt 3
{

}


/*
 * brief：串口中断处理函数
 *        中断标志已在发送或接受函数中清除
 */
void UART_IRQHandler(void) interrupt 4
{
    if (RI != 0)  /* 当中断开启时，发送完成也会产生中断，所以需要判断 */
	{

	}
} 


/*
 * brief: 定时器2中断处理函数
 *        不需要重装载值，硬件自动重载
 */
void TIM2_IRQHandler(void) interrupt 5
{

} 

/*-------------------------------------- End Of File ------------------------------------------------------*/

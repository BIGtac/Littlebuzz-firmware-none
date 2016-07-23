/********************************************************************
作者：Songyimiao
建立日期: 20151129
版本：V2.0
喵呜实验室版权所有
/********************************************************************/
#include "gpio.h" 

/***************************************************************
** 作　  者: Songyimiao
** 官    网：http://www.miaowlabs.com
** 淘    宝：http://miaowlabs.taobao.com
** 日　  期: 2015年11月29日
** 函数名称: GPIO_INIT()
** 功能描述: GPIO初始化函数            
** 输　  入:   
** 输　  出:   
** 备    注: 
********************喵呜实验室版权所有**************************
***************************************************************/
void GPIOInit()
{
	//所有I/O口全设为准双向，弱上拉模式
	P0M0=0x00;
	P0M1=0x00;
	P1M0=0x00;
	P1M1=0x00;
	P2M0=0x00;      
	P2M1=0x00;
	P3M0=0x00;
	P3M1=0x00;	
	P4M0=0x00;
	P4M1=0x00;
	P5M0=0x00;
	P5M1=0x00;	   
   
	//设置需要使用的PWM输出口为强推挽模式
	P2M0=0x0E;
	P2M1=0x00;
	P3M0=0x80;
	P3M1=0x00;


}
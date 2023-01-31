/*************    功能说明    **************
文 件 名：U51timer.c
功    能：定时器初始化
修改日期：2017-03-27
******************************************/

#include	"U51V2.h"
//========================================================================
// 函数: init_T_us_P(unsigned char T,unsigned int us,bit P)
// 描述: 初始化定时器。
// 参数: . 
// 返回: .
// 版本: VER1.0
// 日期: 2017-03-27
// 备注: .
//========================================================================
unsigned char init_T_us_P(unsigned char T,unsigned int us,bit P)
{
	unsigned int T0_us;
	T0_us=65536/(MainFosc_KHZ/1000);
	if(us == 0 || us > T0_us)
		return 1;
	else if(T!=int_T0 && T!=int_T2)
		return 2;
	else{
		T0_us=65536-MainFosc_KHZ*us/1000;
		if(T==int_T0){
			AUXR |= 0x80;		//定时器时钟1T模式
			TMOD &= 0xF0;		//设置定时器模式
			PT0 = P;		//设置优先级
			TL0 = T0_us%256;		//设置定时初值
			TH0 = T0_us/256;		//设置定时初值
			//TF0 = 0;		//清除TF0标志
			ET0 = 1;		//定时器0中断开
		}
		else{
			AUXR |= 0x04;		//定时器时钟1T模式
			//if(P)				//T2无优先级设置
			TL2 = T0_us%256;		//设置定时初值
			TH2 = T0_us/256;		//设置定时初值
			//TF0 = 0;		//清除TF2标志
			IE2  |=  (1<<2);		//定时器2中断开
		}
		return 0;
	}
}
/*=================更新日志==================
日期：2017-03-27
	unsigned char init_T_us_P(unsigned char T,unsigned int us,bit P)
日期：2017-04-24
	修正P参数优先级设置
******************************************/
#ifndef	__U51V2_H
#define	__U51V2_H

/*定义主时钟，根据实际修改*****************/

//#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟

/*定义LED端口，根据实际修改*****************/
#define	L_OE		P_P2	//使能
#define	L_SI		PD7	//数据
#define	L_SCLK		PD4	//移位
#define	L_RCLK		PD5	//锁存


/*************    功能说明    **************
文 件 名：U51V2.h
功    能：本文件为U51-2模块式开发板的配套驱动头文件，
	  需在主函数文件中包含本文件即可使用，
	  包含本头文件后,不用另外再包含"STC15.h"
******************************************/
#include "STC15.h"

/******************** 以下不需修改 ***********************/
#define	MainFosc_KHZ	MAIN_Fosc / 1000
//U51-2端口定义
//数字端口
#define	U51_PD	P2
sbit PD0        =   P2^0;
sbit PD1        =   P2^1;
sbit PD2        =   P2^2;
sbit PD3        =   P2^3;
sbit PD4        =   P2^4;
sbit PD5        =   P2^5;
sbit PD6        =   P2^6;
sbit PD7        =   P2^7;
//模拟端口
sbit PA0        =   P1^0;
sbit PA1        =   P1^1;
sbit PA2        =   P1^2;
sbit PA3        =   P1^3;
sbit PA4        =   P1^4;
sbit PA5        =   P1^5;
//外部中断端口
sbit P_I0		=	P3^2;
sbit P_I1		=	P3^3;
//T0计数端口
sbit P_T0		=	P3^4;
//串行接口
sbit S1_RX		=	P3^0;
sbit S1_TX		=	P3^1;
sbit S3_RX		=	P1^6;
sbit S3_TX		=	P1^7;
//PWM端口
sbit P_P0		=	P3^5;
sbit P_P1		=	P3^6;
sbit P_P2		=	P3^7;
//比较器端口
sbit P_C0		=	P5^4;
sbit P_C1		=	P5^5;

#define		Low			0
#define		No			0
#define		Off			0
#define		Hight			1
#define		Yes			1
#define		On			1
/*   中断向量号   */
#define		int_I0		0
#define		int_T0		1
#define		int_I1		2
#define		int_UART	4
#define		int_ADC		5
#define		int_T2		12
/*   总中断开关控制   */
#define 	EA_On()	 				EA = 1				//允许总中断
#define 	EA_Off()	 			EA = 0				//禁止总中断
/*   定时器运行控制   */
#define 	T0_Run()	 			TR0 = 1				//允许定时器0计数
#define 	T0_Stop()	 			TR0 = 0				//禁止定时器0计数
#define 	T2_Run()	 			AUXR |=  (1<<4)		//允许定时器2计数
#define 	T2_Stop()	 			AUXR &= ~(1<<4)		//禁止定时器2计数
/*   LED控制（可PWM调亮度）   */
#define 	LED_On()				L_OE = 0
#define 	LED_Off()				L_OE = 1
/********************毫秒延时函数，最大255毫秒*************/
void  delay_ms(unsigned char ms);
/********************一般延时函数，最大255*************/
void  delay(unsigned char i);
/********************LED数码管显示函数*************/
void  display_LED_idx(unsigned char seg,unsigned char idx);
/********************定时器初始化函数*************/
unsigned char init_T_us_P(unsigned char T,unsigned int us,bit P);
/********************外部中断初始化函数*************/
void  init_INT_M_P(unsigned char I,bit M,bit P);
/********************AD初始化函数*************/
void  init_AD(unsigned char ch);
/********************查询读取10位AD结果*************/
unsigned int get_AD(unsigned char ch);
/********************串口初始化*************/
unsigned char init_UART_baud_P(unsigned char ch,unsigned int baud,bit P);
/********************串口发送字节*************/
void send_byte(unsigned char b);

#endif

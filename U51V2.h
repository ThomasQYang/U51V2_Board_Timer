#ifndef	__U51V2_H
#define	__U51V2_H

/*������ʱ�ӣ�����ʵ���޸�*****************/

//#define MAIN_Fosc		22118400L	//������ʱ��
//#define MAIN_Fosc		12000000L	//������ʱ��
#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
//#define MAIN_Fosc		24000000L	//������ʱ��

/*����LED�˿ڣ�����ʵ���޸�*****************/
#define	L_OE		P_P2	//ʹ��
#define	L_SI		PD7	//����
#define	L_SCLK		PD4	//��λ
#define	L_RCLK		PD5	//����


/*************    ����˵��    **************
�� �� ����U51V2.h
��    �ܣ����ļ�ΪU51-2ģ��ʽ���������������ͷ�ļ���
	  �����������ļ��а������ļ�����ʹ�ã�
	  ������ͷ�ļ���,���������ٰ���"STC15.h"
******************************************/
#include "STC15.h"

/******************** ���²����޸� ***********************/
#define	MainFosc_KHZ	MAIN_Fosc / 1000
//U51-2�˿ڶ���
//���ֶ˿�
#define	U51_PD	P2
sbit PD0        =   P2^0;
sbit PD1        =   P2^1;
sbit PD2        =   P2^2;
sbit PD3        =   P2^3;
sbit PD4        =   P2^4;
sbit PD5        =   P2^5;
sbit PD6        =   P2^6;
sbit PD7        =   P2^7;
//ģ��˿�
sbit PA0        =   P1^0;
sbit PA1        =   P1^1;
sbit PA2        =   P1^2;
sbit PA3        =   P1^3;
sbit PA4        =   P1^4;
sbit PA5        =   P1^5;
//�ⲿ�ж϶˿�
sbit P_I0		=	P3^2;
sbit P_I1		=	P3^3;
//T0�����˿�
sbit P_T0		=	P3^4;
//���нӿ�
sbit S1_RX		=	P3^0;
sbit S1_TX		=	P3^1;
sbit S3_RX		=	P1^6;
sbit S3_TX		=	P1^7;
//PWM�˿�
sbit P_P0		=	P3^5;
sbit P_P1		=	P3^6;
sbit P_P2		=	P3^7;
//�Ƚ����˿�
sbit P_C0		=	P5^4;
sbit P_C1		=	P5^5;

#define		Low			0
#define		No			0
#define		Off			0
#define		Hight			1
#define		Yes			1
#define		On			1
/*   �ж�������   */
#define		int_I0		0
#define		int_T0		1
#define		int_I1		2
#define		int_UART	4
#define		int_ADC		5
#define		int_T2		12
/*   ���жϿ��ؿ���   */
#define 	EA_On()	 				EA = 1				//�������ж�
#define 	EA_Off()	 			EA = 0				//��ֹ���ж�
/*   ��ʱ�����п���   */
#define 	T0_Run()	 			TR0 = 1				//����ʱ��0����
#define 	T0_Stop()	 			TR0 = 0				//��ֹ��ʱ��0����
#define 	T2_Run()	 			AUXR |=  (1<<4)		//����ʱ��2����
#define 	T2_Stop()	 			AUXR &= ~(1<<4)		//��ֹ��ʱ��2����
/*   LED���ƣ���PWM�����ȣ�   */
#define 	LED_On()				L_OE = 0
#define 	LED_Off()				L_OE = 1
/********************������ʱ���������255����*************/
void  delay_ms(unsigned char ms);
/********************һ����ʱ���������255*************/
void  delay(unsigned char i);
/********************LED�������ʾ����*************/
void  display_LED_idx(unsigned char seg,unsigned char idx);
/********************��ʱ����ʼ������*************/
unsigned char init_T_us_P(unsigned char T,unsigned int us,bit P);
/********************�ⲿ�жϳ�ʼ������*************/
void  init_INT_M_P(unsigned char I,bit M,bit P);
/********************AD��ʼ������*************/
void  init_AD(unsigned char ch);
/********************��ѯ��ȡ10λAD���*************/
unsigned int get_AD(unsigned char ch);
/********************���ڳ�ʼ��*************/
unsigned char init_UART_baud_P(unsigned char ch,unsigned int baud,bit P);
/********************���ڷ����ֽ�*************/
void send_byte(unsigned char b);

#endif

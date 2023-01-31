/*************    ����˵��    **************
�� �� ����U51AD.c
��    �ܣ�ADת����ʼ������ѯ10λAD���
�޸����ڣ�2017-03-29
******************************************/

#include	"U51V2.h"

void init_AD(unsigned char ch)
{
	P1M1 |=(0x01<<ch);
	P1ASF|=(0x01<<ch);
	ADC_CONTR=0xE0;
}
//========================================================================
// ����: unsigned int get_AD(unsigned char ch)
// ����: ��ѯ����һ��ADC���.
// ����: ch: ѡ��Ҫת����ADC.
// ����: 10λADC���.
// �汾: V1.0, 2012-10-22
//========================================================================
unsigned int get_AD(unsigned char ch)	//ch = 0~7
{
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR |= (0x08 | ch); 	//start ADC
	NOP4();

	while((ADC_CONTR & 0x10) == 0)	;	//wait for ADC finish
	ADC_CONTR &= ~0x10;		//���ADC������־
	return	(((unsigned int)ADC_RES << 2) | (ADC_RESL & 3));
}
/*=================������־==================
���ڣ�2017-03-29
	init_AD(unsigned char ch);unsigned int get_AD(unsigned char ch)
******************************************/
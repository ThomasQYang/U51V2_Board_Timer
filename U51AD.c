/*************    功能说明    **************
文 件 名：U51AD.c
功    能：AD转换初始化，查询10位AD结果
修改日期：2017-03-29
******************************************/

#include	"U51V2.h"

void init_AD(unsigned char ch)
{
	P1M1 |=(0x01<<ch);
	P1ASF|=(0x01<<ch);
	ADC_CONTR=0xE0;
}
//========================================================================
// 函数: unsigned int get_AD(unsigned char ch)
// 描述: 查询法读一次ADC结果.
// 参数: ch: 选择要转换的ADC.
// 返回: 10位ADC结果.
// 版本: V1.0, 2012-10-22
//========================================================================
unsigned int get_AD(unsigned char ch)	//ch = 0~7
{
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR |= (0x08 | ch); 	//start ADC
	NOP4();

	while((ADC_CONTR & 0x10) == 0)	;	//wait for ADC finish
	ADC_CONTR &= ~0x10;		//清除ADC结束标志
	return	(((unsigned int)ADC_RES << 2) | (ADC_RESL & 3));
}
/*=================更新日志==================
日期：2017-03-29
	init_AD(unsigned char ch);unsigned int get_AD(unsigned char ch)
******************************************/
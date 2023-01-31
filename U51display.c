/*************    功能说明    **************
文 件 名：U51display.c
功    能：LED数码管显示驱动
修改日期：2017-11-02
******************************************/

#include	"U51V2.h"

////========================================================================
//// 函数: void  delay(unsigned char i)
//// 描述: us级一般延时函数。
//// 参数: i,延时时长，只支持1~255. 
//// 返回: none.
//// 版本: VER1.0
//// 日期: 2017-03-13
//// 备注: 本函数延时与系统时钟有关.
////========================================================================
//void delay(unsigned char i){
//	while(--i);
//}

//========================================================================
// 函数: void  display_LED_idx(unsigned char seg,unsigned char idx)
// 描述: LED数码管显示函数。
// 参数: seg,段码序号；idx,显示位置号. 
// 返回: none.
// 版本: VER1.0
// 日期: 2017-03-14
// 备注: 在U51V2.h头文件定义相应端口，建议在主函数文件中定义显示缓冲数组，长度为8，对应8个数码管.
//========================================================================
unsigned char code LED_SEG[]=
	{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
	 0x77,0x7C,0x39,0x5E,0x79,0x71,0x40,0x00,0x00,0x00,
	 0xBF,0x86,0x5B+0x80,0x4F+0x80,0x66+0x80,0x6D+0x80,0x7D+0x80,0x07+0x80,0x7F+0x80,0x6F+0x80,};
unsigned char code LED_BIT[]=
	{0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
void  display_LED_idx(unsigned char seg,unsigned char idx)
{
	unsigned char i,dat;
	dat=LED_SEG[seg];
	for(i=0;i<16;i++){
		if(i==8)
			dat=LED_BIT[idx];
		dat <<= 1;
		L_SI = CY;
		L_SCLK=1;
		L_SCLK=0;
	}
	L_RCLK=1;
	L_RCLK=0;
}
/*=================更新日志==================
日期：2017-03-25
	display_LED_idx(unsigned char seg,unsigned char idx)
日期：2017-11-02
	更新V30硬件支持
******************************************/
#include "pbdata.h"

void delay(u32 nCount)
{
	for(;nCount != 0;nCount--);
}

void delay_us(u32 us)
{
	   u32 tmp;
	   SysTick->LOAD = 9 * us;	  //自动重载寄存器
	   SysTick->VAL = 0x00;		   //当前值寄存器
	   SysTick->CTRL = 0X01;	   //时钟源选择HCLK/8  0/1/2/16位设置
	   do
	   {
	   		tmp = SysTick->VAL;
	   }while(tmp&0x01 && (!tmp&(1 < 16)));
}

void delay_ms(u32 ms)
{
	   u32 tmp;
	   SysTick->LOAD = 9000 * ms;	  //自动重载寄存器
	   SysTick->VAL = 0x00;		   //当前值寄存器
	   SysTick->CTRL = 0X01;	   //时钟源选择HCLK/8  0/1/2/16位设置
	   do
	   {
	   		tmp = SysTick->VAL;
	   }while(tmp&0x01 && !(tmp&(1 < 16)));
}

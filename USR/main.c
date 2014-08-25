#include "pbdata.h"
#include "led.h"
#include "misc.h"
#include "stm32f10x_tim.h"

void RCC_Configration(void)
{
	 SystemInit();
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	  //定时器时钟使能
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	 //端口复用使能，因为要使用PWM
}

void GPIO_Configration(void)
{
	GPIO_LED_Configration();
}


void TIM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		
	TIM_OCInitTypeDef TIM_OCInitStructure;

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	  // 定时器管脚映射,部分重映像到PB5，PB5正好为接led的管脚（搜索“复用功能重映射”）

	TIM_TimeBaseStructure.TIM_Period = 2000; 		   //设置初始值,定时1s
	TIM_TimeBaseStructure.TIM_Prescaler = 35999;   //设置预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 		//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//pwm 初始化
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;		 //设置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;			 //	输出使能？？？？？
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;				 //设置输出极性

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);		//选择定时器通道2
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);	  //预装载使能
	TIM_Cmd(TIM3,ENABLE);				 //定时器外设打开
}

int main(void)
{
		u8 led_fx = 1;
		u16 led_dt = 0;
		RCC_Configration();
		GPIO_Configration();
		TIM_Configuration();
		while(1)
	   {
	   	// delay_ms(10);
		 if(led_fx==1)
		 {
		 	led_dt++;
		 }
		 else
		 {
		   led_dt--;
		 }
	
		 if(led_dt>1000)  led_fx=0;
	   	 if(led_dt==0)	 led_fx=1;
	
		 TIM_SetCompare2(TIM3,led_dt);
	   }	
}

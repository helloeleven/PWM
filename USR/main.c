#include "pbdata.h"
#include "led.h"
#include "misc.h"
#include "stm32f10x_tim.h"

void RCC_Configration(void)
{
	 SystemInit();
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	  //��ʱ��ʱ��ʹ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	 //�˿ڸ���ʹ�ܣ���ΪҪʹ��PWM
}

void GPIO_Configration(void)
{
	GPIO_LED_Configration();
}


void TIM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		
	TIM_OCInitTypeDef TIM_OCInitStructure;

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	  // ��ʱ���ܽ�ӳ��,������ӳ��PB5��PB5����Ϊ��led�Ĺܽţ����������ù�����ӳ�䡱��

	TIM_TimeBaseStructure.TIM_Period = 2000; 		   //���ó�ʼֵ,��ʱ1s
	TIM_TimeBaseStructure.TIM_Prescaler = 35999;   //����Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 		//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//pwm ��ʼ��
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;		 //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;			 //	���ʹ�ܣ���������
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;				 //�����������

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);		//ѡ��ʱ��ͨ��2
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);	  //Ԥװ��ʹ��
	TIM_Cmd(TIM3,ENABLE);				 //��ʱ�������
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

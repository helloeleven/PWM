#include "led.h"
#include "pbdata.h"


void GPIO_LED_Configration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//设置为复用输出，PWM输出
	GPIO_Init(GPIO_LED,&GPIO_InitStructure);
}

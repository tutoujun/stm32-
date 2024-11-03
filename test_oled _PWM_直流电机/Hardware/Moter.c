#include "stm32f10x.h"                  // Device header
#include "PWM.h"
void Moter_Init(void){
	PWM_LED_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_PinSource10);
	GPIO_ResetBits(GPIOB,GPIO_PinSource11);
}
void SetSpeed(uint16_t v){
	LED_Compare4(v);
}


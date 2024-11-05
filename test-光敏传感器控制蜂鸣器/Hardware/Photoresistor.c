#include "stm32f10x.h"                  // Device header
void Photoresistor(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
uint8_t ReadPhotoresister(){
	int Bit=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0){
		Bit=1;
	}else{
		Bit=0;
	}
	return Bit;
}

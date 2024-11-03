#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "Timer.h"
#include "Encoder.h"
int8_t num;

int main(void){
	OLED_Init();
	Encoder_Init();
	Timer_Init();
	OLED_ShowString(1,1,"cnt:");
	while(1){
		OLED_ShowSignedNum(1,5,num,5);
		
		
	}
}
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		num=GetEncoderCounter();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "Timer.h"
int8_t num;

int main(void){
	OLED_Init();
	Timer_Init();
	LED_Init();
	OLED_ShowString(1,1,"num:");
	while(1){
		OLED_ShowNum(1,5,num,3);
		if(num%10==0&& num!=0){
			LED_TURN();
			num=0;
		}
	}
}
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET){
		num++;
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}

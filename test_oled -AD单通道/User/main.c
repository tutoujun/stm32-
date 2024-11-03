#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "AD.h"
#include "Timer.h"
#include "delay.h"
int main(void){
	OLED_Init();
	
	Timer_Init();
	LED_Init();
	LED_OFF();
	
	AD_single_Init();
	OLED_ShowString(2,1,"the count:");
	OLED_ShowNum(2,11,0,4);
	while(1){
		LED_OFF();
		Delay_ms(50);
		OLED_ShowNum(2,11,GetAIN(),4);
	}
}

void ADC1_2_IRQHandler(void){
	if(ADC_GetITStatus(ADC1,ADC_IT_AWD)==SET){
		LED_ON();
		ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);
	}
	
	
}




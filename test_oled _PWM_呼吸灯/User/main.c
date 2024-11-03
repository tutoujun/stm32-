#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "PWM.h"
uint8_t i;
int main(void){
	OLED_Init();
	PWM_LED_Init();
	
	
	
	OLED_ShowString(2,2,"the count:");
	
	while(1){
		for(i=0;i<=100;i++){
			LED_Compare4(i);
			Delay_ms(10);
		}
		for(i=0;i<=100;i++){
			LED_Compare4(100-i);
			Delay_ms(10);
		}
	}
}



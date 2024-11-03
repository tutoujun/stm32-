#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
int main(void){
	OLED_Init();
	LED_Init();
	KEY_Init();
	uint32_t i=0;
	
	OLED_ShowString(2,2,"the count:");
	OLED_ShowNum(2,12,i,1);
	while(1){
		if(KEY_GetNum()==1){
			LED_TURN();
			i++;
			OLED_Clear();
			OLED_ShowString(2,2,"the count:");
			OLED_ShowNum(2,12,i,1);
		}
	}
}

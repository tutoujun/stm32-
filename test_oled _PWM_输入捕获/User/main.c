#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "IC.h"
#include "PWM.h"


int main(void){
	OLED_Init();
	PWM_LED_Init();
	IC_Init();
	OLED_ShowString(2,1,"fre:      hz");
	SetPrescaler(7200-1);
	while(1){
		OLED_ShowNum(2,5,IC_GetFreq(),6);
	}
}



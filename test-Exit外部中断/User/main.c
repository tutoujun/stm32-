#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "CountSensor.h"
int main(void){
	uint16_t count;
	LED_Init();
	LED_OFF();
	OLED_Init();
	CountSensor_Init();
	while(1){
		OLED_ShowNum(1,1,Get_Count(),4);
	}
}

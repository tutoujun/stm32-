#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
int main(void){
	LED_Init();
	LED_OFF();
	KEY_Init();
	while(1){
		if(KEY_GetNum()==1){
			LED_TURN();
		}
	}
}

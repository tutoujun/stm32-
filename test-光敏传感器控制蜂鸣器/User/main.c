#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "Photoresistor.h"
int main(void){
	LED_Init();
	LED_OFF();
	
	Photoresistor();
	while(1){
		if(ReadPhotoresister()==1){
			LED_TURN();
		}
	}
}

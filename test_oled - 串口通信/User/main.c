#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "usart1.h"
int main(void){
	OLED_Init();
	Usart1_Init();
	
	OLED_ShowString(2,2,"the count:");
	
	sendNum(67890);
	while(1){
		
	}
}

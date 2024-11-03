#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "usart1.h"
	uint8_t data=0;
int main(void){
	OLED_Init();
	Usart1_Init();

	while(1){	
			if(Get_RxFlag()==1){
				data=Get_RxData();
				OLED_ShowHexNum(1,1,data,2);
			}
	}
}



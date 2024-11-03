#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "usart1.h"
#include "string.h"
	uint8_t data=0;
int main(void){
	OLED_Init();
	Usart1_Init();
	LED_Init();
	OLED_ShowString(1,1,"TxPacket:");
	OLED_ShowString(3,1,"RxPacket:");
	while(1){	
		if(Get_RxFlag()==1){
			
			OLED_ShowString(4,1,"               ");
			OLED_ShowString(4,1,RxDataPacket);
			if(strcmp(RxDataPacket,"LED_ON")==0){
				LED_ON();
				sendString(RxDataPacket);
			}
			else if(strcmp(RxDataPacket,"LED_OFF")==0){
				LED_OFF();
				sendString(RxDataPacket);
				OLED_ShowString(2,1,"               ");
			OLED_ShowString(2,1,"LED_OFF");
			}
			else{
				sendString("ERROR");
			}
		}
	}
}



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
	uint8_t arrray[]={0x01,0x02,0x03,0x04};
	sendDataPacket(arrray,4);
	while(1){	
		if(Get_RxFlag()==1){
			OLED_ShowHexNum(1,1,RxDataPacket[0],2);
			OLED_ShowHexNum(1,4,RxDataPacket[1],2);
			OLED_ShowHexNum(1,7,RxDataPacket[2],2);
			OLED_ShowHexNum(1,10,RxDataPacket[3],2);
		}
	}
}



#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "w25q.h"
int main(void){
	uint8_t m;
	uint8_t sdata=0x22;
	uint8_t s=0x00;
	uint16_t data=0x00;
	OLED_Init();
	
	w25q_init();
	w25q_readID(&m,&data);
	
	OLED_ShowHexNum(1,1,data,4);
	w25q_sectorErase(0x000000);
	
	w25q_writeData(0x000000,&sdata,1);
	w25q_readData(0x000000,&s,1);
	
	OLED_ShowHexNum(2,2,s,2);
	while(1){
		
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "nrf.h"
int main(void){
	OLED_Init();
	nRF24l01Init();
	nRF24l01_RxCONFIG();
	
	u8 RxBuf[32]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	while(1){
		if(nRF24l01_getValueStatus()==0){
			nRF24l01_RxDATA(RxBuf);
			OLED_ShowHexNum(2,1,RxBuf[9],2);
			OLED_ShowHexNum(2,4,RxBuf[10],2);
			
			OLED_ShowHexNum(2,7,RxBuf[11],2);
			OLED_ShowHexNum(2,10,RxBuf[12],2);
			
			OLED_ShowHexNum(3,1,RxBuf[13],2);
			OLED_ShowHexNum(3,4,RxBuf[14],2);
							
			OLED_ShowHexNum(3,7,RxBuf[15],2);
			OLED_ShowHexNum(3,10,RxBuf[16],2);
			
			OLED_ShowHexNum(4,1,RxBuf[17],2);
			OLED_ShowHexNum(4,4,RxBuf[18],2);
							
			OLED_ShowHexNum(4,7,RxBuf[19],2);
			OLED_ShowHexNum(4,10,RxBuf[20],2);
		}
		
		
	}
}

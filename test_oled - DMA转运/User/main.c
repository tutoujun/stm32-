#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "MyDMA.h"
uint8_t a[]={0x01,0x02,0x03,0x04}, b[]={0,0,0,0};
int main(void){
	
	OLED_Init();
	myDMA_Init((uint32_t)a,(uint32_t)b,4);
	
	while(1){
		OLED_ShowString(1,1,"addrA:");
		OLED_ShowNum(1,7,(uint32_t)a,8);
		OLED_ShowString(2,1,"A:");
		OLED_ShowNum(2,3,a[0],2);
		OLED_ShowNum(2,6,a[1],2);
		OLED_ShowNum(2,9,a[2],2);
		OLED_ShowNum(2,12,a[3],2);
		OLED_ShowString(3,1,"addrB:");
		OLED_ShowNum(3,7,(uint32_t)b,8);
		OLED_ShowString(4,1,"A:");
		OLED_ShowNum(4,3,b[0],2);
		OLED_ShowNum(4,6,b[1],2);
		OLED_ShowNum(4,9,b[2],2);
		OLED_ShowNum(4,12,b[3],2);
		Delay_ms(1000);
		DMA_transfer();
		OLED_ShowString(3,1,"addrB:");
		OLED_ShowNum(3,7,(uint32_t)b,8);
		OLED_ShowString(4,1,"A:");
		OLED_ShowNum(4,3,b[0],2);
		OLED_ShowNum(4,6,b[1],2);
		OLED_ShowNum(4,9,b[2],2);
		OLED_ShowNum(4,12,b[3],2);
		Delay_ms(1000);
		a[0]++;
		a[1]++;
		a[2]++;
		a[3]++;
	}
}

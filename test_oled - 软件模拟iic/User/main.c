#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "MY_IIC.h"
int main(void){
	OLED_Init();
	MY_IIC_Init();
	Start_iic();
	SendByte_IIC(0xD0);
	uint8_t i=ReceiveACK_IIC();
	STOP_IIC();
	
	OLED_ShowString(2,2,"the count:");
	OLED_ShowNum(2,12,i,1);
	while(1){
		
	}
}

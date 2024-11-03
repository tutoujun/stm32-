#include "stm32f10x.h"                  // Device header
#include "OLED.H"
#include "KEY.h"
#include "Moter.h"
uint8_t i;
int main(void){
	uint16_t v=0;
	OLED_Init();
	KEY_Init();
	Moter_Init();
	OLED_ShowString(2,2,"the count:");
	OLED_ShowNum(2,12,v,3);
	while(1){
		if(KEY_GetNum()==1){
			v+=20;
			OLED_ShowNum(2,12,v,3);
			if(v<=100){
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);
				GPIO_SetBits(GPIOB,GPIO_Pin_11);
				SetSpeed(v);
			}
			else if(v>100&&v<=200){
				
				GPIO_ResetBits(GPIOB,GPIO_Pin_11);
				GPIO_SetBits(GPIOB,GPIO_Pin_10);
				SetSpeed(v-100);
				if(v==200){
					v=0;
				}
			}
		}
	}
}



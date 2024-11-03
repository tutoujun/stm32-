#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "Servo.h"
uint8_t i;
int main(void){
	OLED_Init();
	Servo_Init();
	KEY_Init();
	float i=0;
	SetAngle(i);
	OLED_Clear();
	OLED_ShowString(2,2,"the count:");
	OLED_ShowNum(2,12,i,3);
	while(1){
		if(KEY_GetNum()==1){
			
			i+=30;
			if(i>180){
				i=0;
			}
			SetAngle(i);
			OLED_ShowNum(2,12,i,3);
		}
	}
}



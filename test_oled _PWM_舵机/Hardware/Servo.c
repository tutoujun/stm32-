#include "stm32f10x.h"                  // Device header
#include "PWM.h"
void Servo_Init(void){
	PWM_LED_Init();
}
void SetAngle(float Angle){
	LED_Compare4((Angle/180)*20+5);
}

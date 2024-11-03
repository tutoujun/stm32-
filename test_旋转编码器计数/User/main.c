#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "Encoder.h"
int16_t num; 
int16_t i;
int16_t GetFlag(void);
int main(void){
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"counter:");
	OLED_ShowString(2,1,"flag:");
	while(1){
		num+=GetFlag();
		OLED_ShowSignedNum(1,9,num,2);
		
	}
}
int16_t GetFlag(void){
	int16_t temp;
	temp=i;
	i=0;
	return temp;
}
void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
				i --;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1)==SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			i ++;
		}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

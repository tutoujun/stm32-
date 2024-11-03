#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "ExitTimer.h"
int8_t num=0;
int main(void){
	OLED_Init();
	ExitTimer_Init();
	OLED_ShowString(1,1,"num:");
	OLED_ShowString(2,1,"cnt:");
	while(1){
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1){
			
			OLED_ShowString(3,1,"high ");
		}else{
			
			OLED_ShowString(3,1,"level");
		}
		
		OLED_ShowNum(1,5,num,3);
		OLED_ShowNum(2,5,GetCnt(),3);
	}
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1){
			num++;
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "LED.h"
#include "KEY.h"
#include "MyI2C.h"
#include "MPU6050.h"
int main(void){
	OLED_Init();
	MPU6050_Init();
	uint8_t ID= MPU6050_ReadReg(0x75);
	MPU6050_WreteReg(0x6B,0x00);//оƬ�ϵ��Ĭ����˯��ģʽ��д��Ĵ�����Ч����������Ҫ���˯��ģʽ
	OLED_ShowNum(1,1,ID,3);
	
	while(1){
		
	}
	return 0;
}

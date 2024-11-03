#include "stm32f10x.h"                  // Device header
void Usart1_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=8;
	USART_Init(USART1,&USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
}
void sendByte(uint8_t data){
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
void sendString(char* string){
	int i;
	for(i=0;string[i]!='\0';i++){
		sendByte(string[i]);
	}
}
void sendArray(uint8_t* array,int length){
	int i;
	for(i=0;i<length;i++){
		sendByte(array[i]);
	}
	
}
void sendNum(int num){
	int array[10];
	int lenth=0;
	int i;
	if(num==0){
		sendByte(0x30);
	}else{
		while(num){
			i=num%10;
			num=num/10;
			array[lenth++]=i;
		}
	}
	for(i=lenth-1;i>=0;i--){
		sendByte(0x30+array[i]);
	}
}




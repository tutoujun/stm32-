#include "stm32f10x.h"                  // Device header
#define SCL_PORT       GPIOB
#define SCL_PIN        GPIO_Pin_10
#define SDA_PORT       GPIOB
#define SDA_PIN        GPIO_Pin_11
#define High            1
#define Low             1
//#define OLED_W_SCL(x)     GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)(x))
//#define OLED_W_SDA(x)     GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)(x))
void MyI2C_W_SCL(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)(BitValue));
}

void MyI2C_W_SDA(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)(BitValue));
}
uint8_t MyI2C_R_SDA(void){
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	return BitValue;
}
void MyI2C_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
	
}

void MyI2C_Start(){
	MyI2C_W_SDA(High);
	MyI2C_W_SCL(High);
	MyI2C_W_SDA(Low);
	MyI2C_W_SCL(Low);
}
void MyI2C_End(void){
	MyI2C_W_SDA(Low);
	MyI2C_W_SCL(High);
	MyI2C_W_SDA(High);
}
void MyI2C_SendByte(uint8_t Byte){
	uint8_t Bit=0x80;
	int i;
	for(i=0;i<8;i++){
		MyI2C_W_SDA(Byte&Bit);
		Bit=Bit>>1;
		MyI2C_W_SCL(High);
		MyI2C_W_SCL(Low);
	}
		
}
uint8_t MyI2CReceiveByte(void){
	uint8_t Byte;
	uint8_t i;
	MyI2C_W_SDA(High);
	
	for(i=7;i>=0;i--){
		MyI2C_W_SCL(High);
		Byte=Byte|(MyI2C_R_SDA()<<i);
		MyI2C_W_SCL(Low);
	}
	return Byte;
}
void MyI2C_SendACK(uint8_t Bit){
	MyI2C_W_SDA(Bit);
	MyI2C_W_SCL(High);
	MyI2C_W_SCL(Low);
}
uint8_t MyI2C_ReceiveACK(void){
	uint8_t Bit;
	MyI2C_W_SDA(High);
	MyI2C_W_SCL(High);
	Bit=MyI2C_R_SDA();
	MyI2C_W_SCL(Low);
	return Bit;
}









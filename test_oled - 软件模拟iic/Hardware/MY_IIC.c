#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void MY_IIC_W_SCL(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}
void MY_IIC_W_SDA(uint8_t BitValue){
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}
uint8_t MY_IIC_R_SDA(void){
	uint8_t BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}
void MY_IIC_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)1);
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)1);

}

void Start_iic(void){
	MY_IIC_W_SDA(1);
	MY_IIC_W_SCL(1);
	MY_IIC_W_SDA(0);
	MY_IIC_W_SCL(0);
}

void STOP_IIC(void){
	MY_IIC_W_SDA(0);
	MY_IIC_W_SCL(1);
	MY_IIC_W_SDA(1);
}

void SendByte_IIC(uint8_t Data){
	uint8_t i;
	
	for(i=0;i<8;i++){
		MY_IIC_W_SDA(Data&(0x80>>i));
		MY_IIC_W_SCL(1);
		MY_IIC_W_SCL(0);
	}
}
uint8_t Receive_IIC(void){
	uint8_t i,data;
	MY_IIC_W_SDA(1);
	for(i=0;i<8;i++){
		MY_IIC_W_SCL(1);
		if(MY_IIC_R_SDA()==1){
			data|=(0x80>>1);
			
		}
		MY_IIC_W_SCL(1);
	}
}
void SendAck_IIC(uint8_t ACK){
	MY_IIC_W_SDA(ACK);
	MY_IIC_W_SCL(1);
	MY_IIC_W_SCL(0);
}
uint8_t ReceiveACK_IIC(void){
	uint8_t ACKBit;
	MY_IIC_W_SDA(1);
	MY_IIC_W_SCL(1);
	ACKBit=MY_IIC_R_SDA();
	MY_IIC_W_SCL(0);
	return ACKBit;
}















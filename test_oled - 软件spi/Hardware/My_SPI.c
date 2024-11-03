#include "stm32f10x.h"                  // Device header
void SPI_W_SCK_Bit(uint8_t ValueBit){
	GPIO_WriteBit(GPIOA,GPIO_Pin_6,(BitAction)ValueBit);
}
void SPI_W_DI_Bit(uint8_t ValueBit){
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)ValueBit);
}
void SPI_W_CS_Bit(uint8_t ValueBit){
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)ValueBit);
}
uint8_t SPI_R_DO_Bit(void){
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
}
void My_SPI_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_7;//4是片选线，6是时钟线，7是MOSI线
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//5是MISO线
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	SPI_W_CS_Bit(1);
	SPI_W_SCK_Bit(0);
}

void My_SPI_Start(void){
	SPI_W_CS_Bit(0);
	
}
uint8_t SPI_SwapByte(uint8_t sdata){
	uint8_t i, data=0x00;
	for(i=0;i<8;i++){
		SPI_W_DI_Bit(sdata&(0x80>>i));
		SPI_W_SCK_Bit(1);
		if(SPI_R_DO_Bit()==1){
			data|=(0x80>>i);
		}
		SPI_W_SCK_Bit(0);
	}
	return data;
	
}
void My_SPI_Stop(void){
	SPI_W_CS_Bit(1);
	
}
































#include "stm32f10x.h"                  // Device header
#include "My_SPI.h"
void w25q_init(void){
	My_SPI_Init();
}

//查看厂家和设备id的驱动
void w25q_readID(uint8_t *m,uint16_t* data){
	My_SPI_Start();
	SPI_SwapByte(0x9F);
	*m=SPI_SwapByte(0xFF);
	*data=SPI_SwapByte(0xFF);
	*data<<=8;
	*data|=SPI_SwapByte(0xFF);
	My_SPI_Stop();
}
void w25q_writeEnable(void){
	My_SPI_Start();
	SPI_SwapByte(0x06);
	My_SPI_Stop();
}
void w25q_readBusyStatus(void){
	My_SPI_Start();
	SPI_SwapByte(0x05);
	while((SPI_SwapByte(0x05)&0x01)==0x01);
	My_SPI_Stop();
	
}
void w25q_writeData(uint32_t address,uint8_t* data,int length){
	w25q_writeEnable();
	int i=0;
	My_SPI_Start();
	SPI_SwapByte(0x02);
	SPI_SwapByte((address)>>16);
	SPI_SwapByte((address)>>8);
	SPI_SwapByte(address);
	for(i=0;i<length;i++){
		SPI_SwapByte(data[i]);
	}
	My_SPI_Stop();
	w25q_readBusyStatus();
}
void w25q_sectorErase(uint32_t address){
	w25q_writeEnable();
	
	My_SPI_Start();
	SPI_SwapByte(0x20);
	SPI_SwapByte((address)>>16);
	SPI_SwapByte((address)>>8);
	SPI_SwapByte(address);
	My_SPI_Stop();
	w25q_readBusyStatus();
}
void w25q_readData(uint32_t address,uint8_t* data,int length){
	int i=0;
	My_SPI_Start();
	SPI_SwapByte(0x03);
	SPI_SwapByte((address)>>16);
	SPI_SwapByte((address)>>8);
	SPI_SwapByte(address);
	for(i=0;i<length;i++){
		data[i]=SPI_SwapByte(0xFF);
	}
	My_SPI_Stop();
	
}















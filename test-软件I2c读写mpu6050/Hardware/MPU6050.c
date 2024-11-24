#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"
void MPU6050_WreteReg(uint8_t RegAddress,uint8_t Data){
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveACK();
	MyI2C_End();
}
uint8_t MPU6050_ReadReg(uint8_t RegAddress){
	uint8_t Data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveACK();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveACK();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS|0x01);
	MyI2C_ReceiveACK();
	Data=MyI2CReceiveByte();
	MyI2C_SendACK(1);//不给应答，结束对话
	MyI2C_End();
	return Data;
	
}
void MPU6050_Init(){
	MyI2C_Init();
}
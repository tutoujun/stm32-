#ifndef __MPU6050__H
#define __MPU6050__H
void MPU6050_WreteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init();
#endif
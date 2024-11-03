#ifndef __USART1_H
#define __USART1_H
#include <stdint.h>
extern char RxDataPacket[100];
void Usart1_Init(void);
void sendByte(uint8_t data);
void sendString(char* string);
void sendArray(uint8_t* array,int length);
void sendNum(int num);
uint8_t Get_RxFlag(void);
uint8_t Get_RxData(void);
void sendDataPacket(uint8_t* array,uint8_t lenth);
#endif


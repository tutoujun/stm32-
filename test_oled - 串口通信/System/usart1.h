#ifndef __USART1_H
#define __USART1_H
#include <stdint.h>
void Usart1_Init(void);
void sendByte(uint8_t data);
void sendString(char* string);
void sendArray(uint8_t* array,int length);
void sendNum(int num);
#endif


#ifndef __MY_SPI_H
#define __MY_SPI_H
#include "stdint.h"
void My_SPI_Init(void);
void My_SPI_Start(void);
uint8_t SPI_SwapByte(uint8_t sdata);
void My_SPI_Stop(void);
#endif


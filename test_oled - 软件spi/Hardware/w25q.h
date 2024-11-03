#ifndef __MY_SPI_H
#define __MY_SPI_H
#include "stdint.h"
void w25q_init(void);

//查看厂家和设备id的驱动
void w25q_readID(uint8_t *m,uint16_t* data);
void w25q_writeEnable(void);
void w25q_readBusyStatus(void);
void w25q_writeData(uint32_t* address,uint8_t* data,int length);
void w25q_sectorErase(uint32_t* address);
void w25q_readData(uint32_t* address,uint8_t* data,int length);

#endif

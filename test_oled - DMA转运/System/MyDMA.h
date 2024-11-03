#ifndef __MYDMA_H
#define __MYDMA_H
#include "stdint.h"
void myDMA_Init(uint32_t addrA,uint32_t addrB,uint32_t c);
void DMA_transfer(void);
#endif

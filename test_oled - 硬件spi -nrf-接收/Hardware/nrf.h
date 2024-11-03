#ifndef __NRF_H
#define __NRF_H
#include "stdint.h"
void nRF24l01Init(void);
void CE_LOW(void);
void CE_HIGH(void);
u8 Nrf24l01_WriteReg(u8 reg,u8 value);
u8 Nrf24l01_ReadReg(u8 reg);
u8 Nrf24l01_WriteBuf(u8 reg, u8 *pBuf, u8 len);
u8 Nrf24l01_ReadBuf(u8 reg, u8 *pBuf, u8 len);
void nRF24l01_RxCONFIG(void);
u8 nRF24l01_getValueStatus(void);
u8 nRF24l01_RxDATA(uint8_t *rxbuf);

#endif






#ifndef __MYI2C__H
#define __MYI2C__H
void MyI2C_Init(void);
void MyI2C_Start();
void MyI2C_End(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2CReceiveByte(void);
void MyI2C_SendACK(uint8_t Bit);
uint8_t MyI2C_ReceiveACK(void);
#endif

#ifndef __MY_IIC_H
#define __MY_IIC_H
void MY_IIC_Init(void);
void Start_iic(void);
void STOP_IIC(void);
void SendByte_IIC(uint8_t Data);
uint8_t Receive_IIC(void);
void SendAck_IIC(uint8_t ACK);
uint8_t ReceiveACK_IIC(void);
#endif
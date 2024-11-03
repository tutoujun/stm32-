//此文件定义了nrf24l01所用的指令集以及寄存器地址
#ifndef __NRF24l01_H
#define __NRF24l01_H
#include "stdint.h"
//指令集(nrf24l01寄存器操作命令)
#define Read_Reg       (uint8_t)0x00    //读配置寄存器，低5位为寄存器地址
#define Write_Reg      (uint8_t)0x20    //写配置寄存器，低5位为寄存器地址
#define RD_RX_Pload    (uint8_t)0x61    //读Rx有效数据，1~32字节
#define WR_TX_Pload    (uint8_t)0xA0    //写Tx有效数据，1~32字节
#define Flush_Tx       (uint8_t)0xE1    //清除Tx FIFO寄存器，发射模式下使用
#define Flush_Rx       (uint8_t)0xE2    //清除Tx FIFO寄存器，接收模式下使用
#define Reuse_Tx_PL    (uint8_t)0xE3    //重新使用上一包数据，在CE为高的过程中，数据包被不断地重新发射
#define NOP            (uint8_t)0xFF    //空操作，可以用来读状态寄存器
#define W_ACK_PAYLOAD  (uint8_t)0xA8    //Write Payload to be transmitted together with


//寄存器地址
#define CONFIG         (uint8_t)0x00    //配置寄存器，
										//(PRIM_RX)bit0:1接收模式，0发射模式；
										//(PWR_UP)bit1:1是上电模式(power up) 0是掉电模式power down;
										//(CRCO)bit2:0是CRC编码只有一个字节(8位)，1是CRC编码只有两个字节
										//(EN_CRC)bit3:0是CRC失能，1是CRC使能;
										//(MASK_MAX_RT)bit4:0是(达到最大重发次数中断)使能，1屏蔽中断
										//(MASK_TX_DS)bit5:发送数据中断屏蔽位，1发送数据中断被屏蔽，0解除屏蔽
										//(MASK_RX_DR)bit6:接收数据中断屏蔽位，1接收数据中断被屏蔽，0解除屏蔽
										//bit7:保留位，默认为0
#define EN_AA          (uint8_t)0x01    //使能自动应答功能  bit0~5,对应通道0~5,6~7为保留位
#define EN_RXADDR      (uint8_t)0x02    //接收地址允许,bit0~5,对应通道0~5 6~7保留
#define SETUP_AW       (uint8_t)0x03    //设置地址宽度(所有通道)，0x00不合法   0x01地址为3字节   0x10地址为4字节   0x11地址为5字节 ,如果地址小于5字节，地址只有低位有效
#define SETUP_RETR     (uint8_t)0x04    //是否使用自动重发，0~3bit表示自动重发次数，0000表示禁止自动重发，0001自动重发一次...，1111自动重发15次
										//4~7位是两次重发的间隔时间 0000表示250us,0001表示500us ... 1111表示250*(15+1)us
#define RF_CH          (uint8_t)0x05    //射频信道，bit0~6是工作通道频率，bit7是保留位0,Fo=(2400+RF_CH)MZ  ,其中无线频道设置的频率分辨率为1MHz。
#define RF_SETUP       (uint8_t)0x06    //射频配置寄存器  bit:7 为1时使能连续载波发送，
										//bit:6保留位
										//bit5:RF_DR_LOW 
										//bit4:PLL_LOCK:测试时使用，我也不知道有啥用
										//bit3:RF_DR_HIGH
										//[RF_DR_LOW,RF_DR_HIGH]:0x00 1Mbps 0x01:2Mbps  0x10:250kbps  0x11:保留位，不使用
										//bit2~bit1: 0x00 18dBm   0x01:12dBm 0x10:6dBm 0x11:0dbm
										//bit0:无效位，填啥都行
#define StATUS         (uint8_t)0x07    //状态寄存器，bit7保留位
										//bit6:收到数据标志位，收到数据置1，写1清零
										//bit5:数据发送完成标志位，如果工作在自动应答模式，则必须收到ACK才会置1，写1清零
										//bit4:达到最大重发次数标志，写1清零
										//bit3~1:000~101:数据通道号，110未使用 111:RX_FIFO寄存器空
										//bit0:TX FIFO寄存器满标志1,0:TX FIFO寄存器未满
#define RX_ADDR_P0     (uint8_t)0x0A    //数据通道0接收地址设置寄存器  bit39~0:地址一共有5个字节，默认是5字节
#define TX_ADDR        (uint8_t)0x10    //发送地址设置寄存器  bit39~0:地址一共有5个字节，默认是5字节
#define RX_PW_P0       (uint8_t)0x11 	//数据通道0有效数据宽度设置寄存器，7和6是保留位，5~0位:取0非法，1~32:1~32字节
#define FEATURE        (uint8_t)0x1d
#define DYNPD          (uint8_t)0x1c
#endif 



								
								

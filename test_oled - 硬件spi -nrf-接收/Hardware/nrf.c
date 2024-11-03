#include "stm32f10x.h"                  // Device header
#include "My_SPI.h"
#include "nrf24l01.h"
#include "delay.h"
/*
端口映射：
PA3:对应CE,模块控制引脚
PA4:对应CSN,模块片选引脚，用于开始一个spi通信，这里封装到start和stop函数里面了
PA5:对应SPI总线时钟，这里使用的是硬件SPI，不用管他
PA6:MISO，
pA7:MOSI
IRQ:中断信号输出，这里没有使用
*/

#define TX_ADR_WIDTH          5   	//5字节的地址宽度
#define RX_ADR_WIDTH          5   	//5字节的地址宽度
#define TX_PLOAD_WIDTH        32  	//32字节的用户数据宽度
#define RX_PLOAD_WIDTH        32  	//32字节的用户数据宽度
u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};//发送地址
u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};//接收地址
void nRF24l01Init(void){
	My_SPI_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void CE_LOW(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
}
void CE_HIGH(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
}
/*****************************************************************************
*函  数：u8 Nrf24l01_WriteReg(u8 reg,u8 value)
*功  能：向指定寄存器地址，写一个字节数据
*参  数：reg： 寄存器地址
*       val:  要写入的值
*返回值：status
*****************************************************************************/

u8 Nrf24l01_WriteReg(u8 reg,u8 value)
{
	u8 status;    
	My_SPI_Start();
	status = SPI_SwapByte(reg) ;
	SPI_SwapByte(value);
	My_SPI_Stop();    
	return status;
}
/*****************************************************************************
*函  数：u8 NRF24l01_read_reg(u8 reg)
*功  能：向指定寄存器地址，读出一字节数据
*参  数：reg： 寄存器地址
*返回值：reg_val(第二个读取到的字节)
*****************************************************************************/
u8 Nrf24l01_ReadReg(u8 reg)
{
	u8 reg_val;    
	My_SPI_Start();
	SPI_SwapByte(reg);
	reg_val = SPI_SwapByte(0xFF);
	My_SPI_Stop();
	return reg_val;
}
/*****************************************************************************
*函  数：u8 Nrf24l01_WriteBuf(u8 reg, u8 *pBuf, u8 len)
*功  能：写一组数据到寄存器
*参  数：reg： 寄存器地址
*       pBuf： 要写入数据的地址
*        len:  要写入的数据长度
*返回值：status
*****************************************************************************/
u8 Nrf24l01_WriteBuf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status;    
	My_SPI_Start();
	status = SPI_SwapByte(reg);
	for(u8 i=0; i<len; i++)	{
		SPI_SwapByte(pBuf[i]);		
	}
	My_SPI_Stop();   
	return status;
}
/*****************************************************************************
*函  数： u8 vNrf24l01_ReadBuf(u8 reg, u8 *pBuf, u8 len)
*功  能： 向指定寄存器地址，读出指定长度的数据
*参  数： reg :    寄存器地址
*        pBuf :   数据存放缓冲区
*        len  :   读取的字节数量
*返回值： status : 设备状态字
*****************************************************************************/
u8 Nrf24l01_ReadBuf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status;	
	My_SPI_Start();
	status = SPI_SwapByte(reg);
	for(u8 i = 0; i<len ;i++){
		pBuf[i] = SPI_SwapByte(0xFF);		
	}
	My_SPI_Stop();    
	return status;
} 
/*****************************************************************************
*函  数： u8 nRF24l01_RxCONFIG(void)
*功  能： 配置nrf为接收模式
*参  数：void
*返回值： status : void
*****************************************************************************/
void nRF24l01_RxCONFIG(void){
	CE_LOW();
	Nrf24l01_WriteReg(Write_Reg + RF_CH,        89);                // 射频通道，即频率(0-125),这里的通道是
	Nrf24l01_WriteReg(Write_Reg + RF_SETUP,   0x0F);                // 设置TX发射参数,0db增益,2Mbps,低噪声增益关闭 （注意：低噪声增益关闭/开启直接影响通信,要开启都开启，要关闭都关闭0x0f）0x07
	Nrf24l01_WriteReg(Write_Reg + SETUP_AW,   0x03);                // 地址长度，默认值时0x03,即5字节
	Nrf24l01_WriteBuf(Write_Reg + TX_ADDR,    (u8*)TX_ADDRESS, 5);  // 写TX节点地址， 地址宽度：5字节，40位 
	Nrf24l01_WriteBuf(Write_Reg + RX_ADDR_P0, (u8*)TX_ADDRESS, 5);  // 设置TX节点地址,主要为了使能ACK，， 地址宽度：5字节，40位
	Nrf24l01_WriteReg(Write_Reg + SETUP_RETR, 0x1A);                // 设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次 0x1A	
	Nrf24l01_WriteReg(Write_Reg + EN_RXADDR,  0x01);                // 使能通道0的接收地址  
	Nrf24l01_WriteReg(Write_Reg + EN_AA,      0x01);                // 使能通道0自动应答
	Nrf24l01_WriteReg(Write_Reg + RX_PW_P0,     32);                // 选择通道0的有效数据宽度  
	Nrf24l01_WriteReg(Flush_Tx,                0xff);                // 清除TX_FIFO
	Nrf24l01_WriteReg(Write_Reg+StATUS,       0X7E);                // 清除所有中断,防止一进去接收模式就触发中断    
	Nrf24l01_WriteReg(Write_Reg+CONFIG,       0x0F);                // 配置为接收模式  
	CE_HIGH();
}
u8 nRF24l01_getValueStatus(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
}
u8 nRF24l01_RxDATA(uint8_t *rxbuf){
	uint8_t sta;		 
	sta=Nrf24l01_ReadReg(Read_Reg+StATUS);  //读取状态寄存器的值    	 
	Nrf24l01_WriteReg(Write_Reg+StATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&0x40)//接收到数据
	{
		Nrf24l01_ReadBuf(RD_RX_Pload,rxbuf,RX_PLOAD_WIDTH);//读取数据
		Nrf24l01_WriteReg(Flush_Rx,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}









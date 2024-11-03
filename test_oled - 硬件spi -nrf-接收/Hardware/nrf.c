#include "stm32f10x.h"                  // Device header
#include "My_SPI.h"
#include "nrf24l01.h"
#include "delay.h"
/*
�˿�ӳ�䣺
PA3:��ӦCE,ģ���������
PA4:��ӦCSN,ģ��Ƭѡ���ţ����ڿ�ʼһ��spiͨ�ţ������װ��start��stop����������
PA5:��ӦSPI����ʱ�ӣ�����ʹ�õ���Ӳ��SPI�����ù���
PA6:MISO��
pA7:MOSI
IRQ:�ж��ź����������û��ʹ��
*/

#define TX_ADR_WIDTH          5   	//5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH          5   	//5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH        32  	//32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH        32  	//32�ֽڵ��û����ݿ��
u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};//���յ�ַ
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
*��  ����u8 Nrf24l01_WriteReg(u8 reg,u8 value)
*��  �ܣ���ָ���Ĵ�����ַ��дһ���ֽ�����
*��  ����reg�� �Ĵ�����ַ
*       val:  Ҫд���ֵ
*����ֵ��status
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
*��  ����u8 NRF24l01_read_reg(u8 reg)
*��  �ܣ���ָ���Ĵ�����ַ������һ�ֽ�����
*��  ����reg�� �Ĵ�����ַ
*����ֵ��reg_val(�ڶ�����ȡ�����ֽ�)
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
*��  ����u8 Nrf24l01_WriteBuf(u8 reg, u8 *pBuf, u8 len)
*��  �ܣ�дһ�����ݵ��Ĵ���
*��  ����reg�� �Ĵ�����ַ
*       pBuf�� Ҫд�����ݵĵ�ַ
*        len:  Ҫд������ݳ���
*����ֵ��status
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
*��  ���� u8 vNrf24l01_ReadBuf(u8 reg, u8 *pBuf, u8 len)
*��  �ܣ� ��ָ���Ĵ�����ַ������ָ�����ȵ�����
*��  ���� reg :    �Ĵ�����ַ
*        pBuf :   ���ݴ�Ż�����
*        len  :   ��ȡ���ֽ�����
*����ֵ�� status : �豸״̬��
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
*��  ���� u8 nRF24l01_RxCONFIG(void)
*��  �ܣ� ����nrfΪ����ģʽ
*��  ����void
*����ֵ�� status : void
*****************************************************************************/
void nRF24l01_RxCONFIG(void){
	CE_LOW();
	Nrf24l01_WriteReg(Write_Reg + RF_CH,        89);                // ��Ƶͨ������Ƶ��(0-125),�����ͨ����
	Nrf24l01_WriteReg(Write_Reg + RF_SETUP,   0x0F);                // ����TX�������,0db����,2Mbps,����������ر� ��ע�⣺����������ر�/����ֱ��Ӱ��ͨ��,Ҫ������������Ҫ�رն��ر�0x0f��0x07
	Nrf24l01_WriteReg(Write_Reg + SETUP_AW,   0x03);                // ��ַ���ȣ�Ĭ��ֵʱ0x03,��5�ֽ�
	Nrf24l01_WriteBuf(Write_Reg + TX_ADDR,    (u8*)TX_ADDRESS, 5);  // дTX�ڵ��ַ�� ��ַ��ȣ�5�ֽڣ�40λ 
	Nrf24l01_WriteBuf(Write_Reg + RX_ADDR_P0, (u8*)TX_ADDRESS, 5);  // ����TX�ڵ��ַ,��ҪΪ��ʹ��ACK���� ��ַ��ȣ�5�ֽڣ�40λ
	Nrf24l01_WriteReg(Write_Reg + SETUP_RETR, 0x1A);                // �����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10�� 0x1A	
	Nrf24l01_WriteReg(Write_Reg + EN_RXADDR,  0x01);                // ʹ��ͨ��0�Ľ��յ�ַ  
	Nrf24l01_WriteReg(Write_Reg + EN_AA,      0x01);                // ʹ��ͨ��0�Զ�Ӧ��
	Nrf24l01_WriteReg(Write_Reg + RX_PW_P0,     32);                // ѡ��ͨ��0����Ч���ݿ��  
	Nrf24l01_WriteReg(Flush_Tx,                0xff);                // ���TX_FIFO
	Nrf24l01_WriteReg(Write_Reg+StATUS,       0X7E);                // ��������ж�,��ֹһ��ȥ����ģʽ�ʹ����ж�    
	Nrf24l01_WriteReg(Write_Reg+CONFIG,       0x0F);                // ����Ϊ����ģʽ  
	CE_HIGH();
}
u8 nRF24l01_getValueStatus(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
}
u8 nRF24l01_RxDATA(uint8_t *rxbuf){
	uint8_t sta;		 
	sta=Nrf24l01_ReadReg(Read_Reg+StATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	Nrf24l01_WriteReg(Write_Reg+StATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&0x40)//���յ�����
	{
		Nrf24l01_ReadBuf(RD_RX_Pload,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		Nrf24l01_WriteReg(Flush_Rx,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}









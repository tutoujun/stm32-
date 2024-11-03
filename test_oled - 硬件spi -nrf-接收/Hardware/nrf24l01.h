//���ļ�������nrf24l01���õ�ָ��Լ��Ĵ�����ַ
#ifndef __NRF24l01_H
#define __NRF24l01_H
#include "stdint.h"
//ָ�(nrf24l01�Ĵ�����������)
#define Read_Reg       (uint8_t)0x00    //�����üĴ�������5λΪ�Ĵ�����ַ
#define Write_Reg      (uint8_t)0x20    //д���üĴ�������5λΪ�Ĵ�����ַ
#define RD_RX_Pload    (uint8_t)0x61    //��Rx��Ч���ݣ�1~32�ֽ�
#define WR_TX_Pload    (uint8_t)0xA0    //дTx��Ч���ݣ�1~32�ֽ�
#define Flush_Tx       (uint8_t)0xE1    //���Tx FIFO�Ĵ���������ģʽ��ʹ��
#define Flush_Rx       (uint8_t)0xE2    //���Tx FIFO�Ĵ���������ģʽ��ʹ��
#define Reuse_Tx_PL    (uint8_t)0xE3    //����ʹ����һ�����ݣ���CEΪ�ߵĹ����У����ݰ������ϵ����·���
#define NOP            (uint8_t)0xFF    //�ղ���������������״̬�Ĵ���
#define W_ACK_PAYLOAD  (uint8_t)0xA8    //Write Payload to be transmitted together with


//�Ĵ�����ַ
#define CONFIG         (uint8_t)0x00    //���üĴ�����
										//(PRIM_RX)bit0:1����ģʽ��0����ģʽ��
										//(PWR_UP)bit1:1���ϵ�ģʽ(power up) 0�ǵ���ģʽpower down;
										//(CRCO)bit2:0��CRC����ֻ��һ���ֽ�(8λ)��1��CRC����ֻ�������ֽ�
										//(EN_CRC)bit3:0��CRCʧ�ܣ�1��CRCʹ��;
										//(MASK_MAX_RT)bit4:0��(�ﵽ����ط������ж�)ʹ�ܣ�1�����ж�
										//(MASK_TX_DS)bit5:���������ж�����λ��1���������жϱ����Σ�0�������
										//(MASK_RX_DR)bit6:���������ж�����λ��1���������жϱ����Σ�0�������
										//bit7:����λ��Ĭ��Ϊ0
#define EN_AA          (uint8_t)0x01    //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5,6~7Ϊ����λ
#define EN_RXADDR      (uint8_t)0x02    //���յ�ַ����,bit0~5,��Ӧͨ��0~5 6~7����
#define SETUP_AW       (uint8_t)0x03    //���õ�ַ���(����ͨ��)��0x00���Ϸ�   0x01��ַΪ3�ֽ�   0x10��ַΪ4�ֽ�   0x11��ַΪ5�ֽ� ,�����ַС��5�ֽڣ���ַֻ�е�λ��Ч
#define SETUP_RETR     (uint8_t)0x04    //�Ƿ�ʹ���Զ��ط���0~3bit��ʾ�Զ��ط�������0000��ʾ��ֹ�Զ��ط���0001�Զ��ط�һ��...��1111�Զ��ط�15��
										//4~7λ�������ط��ļ��ʱ�� 0000��ʾ250us,0001��ʾ500us ... 1111��ʾ250*(15+1)us
#define RF_CH          (uint8_t)0x05    //��Ƶ�ŵ���bit0~6�ǹ���ͨ��Ƶ�ʣ�bit7�Ǳ���λ0,Fo=(2400+RF_CH)MZ  ,��������Ƶ�����õ�Ƶ�ʷֱ���Ϊ1MHz��
#define RF_SETUP       (uint8_t)0x06    //��Ƶ���üĴ���  bit:7 Ϊ1ʱʹ�������ز����ͣ�
										//bit:6����λ
										//bit5:RF_DR_LOW 
										//bit4:PLL_LOCK:����ʱʹ�ã���Ҳ��֪����ɶ��
										//bit3:RF_DR_HIGH
										//[RF_DR_LOW,RF_DR_HIGH]:0x00 1Mbps 0x01:2Mbps  0x10:250kbps  0x11:����λ����ʹ��
										//bit2~bit1: 0x00 18dBm   0x01:12dBm 0x10:6dBm 0x11:0dbm
										//bit0:��Чλ����ɶ����
#define StATUS         (uint8_t)0x07    //״̬�Ĵ�����bit7����λ
										//bit6:�յ����ݱ�־λ���յ�������1��д1����
										//bit5:���ݷ�����ɱ�־λ������������Զ�Ӧ��ģʽ��������յ�ACK�Ż���1��д1����
										//bit4:�ﵽ����ط�������־��д1����
										//bit3~1:000~101:����ͨ���ţ�110δʹ�� 111:RX_FIFO�Ĵ�����
										//bit0:TX FIFO�Ĵ�������־1,0:TX FIFO�Ĵ���δ��
#define RX_ADDR_P0     (uint8_t)0x0A    //����ͨ��0���յ�ַ���üĴ���  bit39~0:��ַһ����5���ֽڣ�Ĭ����5�ֽ�
#define TX_ADDR        (uint8_t)0x10    //���͵�ַ���üĴ���  bit39~0:��ַһ����5���ֽڣ�Ĭ����5�ֽ�
#define RX_PW_P0       (uint8_t)0x11 	//����ͨ��0��Ч���ݿ�����üĴ�����7��6�Ǳ���λ��5~0λ:ȡ0�Ƿ���1~32:1~32�ֽ�
#define FEATURE        (uint8_t)0x1d
#define DYNPD          (uint8_t)0x1c
#endif 



								
								

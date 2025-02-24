#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"

//PA11
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3;} 
//IO��������   
#define	DHT11_DQ_OUT(X)  GPIO_WriteBit(GPIOA, GPIO_Pin_0, X)
#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ����
u8 DHT11_Read_Byte(void);//��ȡһ���ֽ�
u8 DHT11_Read_Bit(void);//��ȡһλ
u8 DHT11_Check(void);//���DHT11
void DHT11_Rst(void);//��λDHT11   

#endif

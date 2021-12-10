#ifndef __MYIIC_H
#define __MYIIC_H
#include "SYSTEM/system.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


#define OLED_PORT 			GPIOB   
#define OLED_PIN 			GPIO_Pin_14|GPIO_Pin_15
#define OLED_PORT_RCC		RCC_APB2Periph_GPIOB


   	   		   
//IO��������
#define OLED_SDA_IN()  {OLED_PORT->CRH&=0x0FFFFFFF;OLED_PORT->CRH|=(unsigned int)8<<4*7;}
#define OLED_SDA_OUT() {OLED_PORT->CRH&=0x0FFFFFFF;OLED_PORT->CRH|=(unsigned int)3<<4*7;}

//IO��������	 
#define OLED_IIC_SCL    PBout(14) //SCL
#define OLED_IIC_SDA    PBout(15) //SDA	 
#define OLED_READ_SDA   PBin(15)  //����SDA 

//IIC���в�������
void OLED_IIC_Init(void);                //��ʼ��IIC��IO��				 
void OLED_IIC_Start(void);				//����IIC��ʼ�ź�
void OLED_IIC_Stop(void);	  			//����IICֹͣ�ź�
void OLED_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 OLED_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void OLED_IIC_Ack(void);					//IIC����ACK�ź�
void OLED_IIC_NAck(void);				//IIC������ACK�ź�

void OLED_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 OLED_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif



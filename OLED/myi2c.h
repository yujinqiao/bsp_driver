#ifndef __MYIIC_H
#define __MYIIC_H
#include "SYSTEM/system.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


#define OLED_PORT 			GPIOB   
#define OLED_PIN 			GPIO_Pin_14|GPIO_Pin_15
#define OLED_PORT_RCC		RCC_APB2Periph_GPIOB


   	   		   
//IO方向设置
#define OLED_SDA_IN()  {OLED_PORT->CRH&=0x0FFFFFFF;OLED_PORT->CRH|=(unsigned int)8<<4*7;}
#define OLED_SDA_OUT() {OLED_PORT->CRH&=0x0FFFFFFF;OLED_PORT->CRH|=(unsigned int)3<<4*7;}

//IO操作函数	 
#define OLED_IIC_SCL    PBout(14) //SCL
#define OLED_IIC_SDA    PBout(15) //SDA	 
#define OLED_READ_SDA   PBin(15)  //输入SDA 

//IIC所有操作函数
void OLED_IIC_Init(void);                //初始化IIC的IO口				 
void OLED_IIC_Start(void);				//发送IIC开始信号
void OLED_IIC_Stop(void);	  			//发送IIC停止信号
void OLED_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 OLED_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void OLED_IIC_Ack(void);					//IIC发送ACK信号
void OLED_IIC_NAck(void);				//IIC不发送ACK信号

void OLED_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 OLED_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif



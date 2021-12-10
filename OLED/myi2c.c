#include "OLED/myi2c.h"
#include "SYSTICK/SysTick.h"
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

//��ʼ��IIC
void OLED_IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(OLED_PORT_RCC, ENABLE);	
	   
	GPIO_InitStructure.GPIO_Pin = OLED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_PORT, &GPIO_InitStructure);
 
	OLED_IIC_SCL=1;
	OLED_IIC_SDA=1;

}
//����IIC��ʼ�ź�
void OLED_IIC_Start(void)
{
	OLED_SDA_OUT();     //sda�����
	OLED_IIC_SDA=1;	  	  
	OLED_IIC_SCL=1;
	Delay_us(4);
 	OLED_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	OLED_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void OLED_IIC_Stop(void)
{
	OLED_SDA_OUT();//sda�����
	OLED_IIC_SCL=0;
	OLED_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	OLED_IIC_SCL=1; 
	OLED_IIC_SDA=1;//����I2C���߽����ź�
	Delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 OLED_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	OLED_SDA_IN();      //SDA����Ϊ����  
	OLED_IIC_SDA=1;Delay_us(1);	   
	OLED_IIC_SCL=1;Delay_us(1);	 
	while(OLED_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			OLED_IIC_Stop();
			return 1;
		}
	}
	OLED_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void OLED_IIC_Ack(void)
{
	OLED_IIC_SCL=0;
	OLED_SDA_OUT();
	OLED_IIC_SDA=0;
	Delay_us(2);
	OLED_IIC_SCL=1;
	Delay_us(2);
	OLED_IIC_SCL=0;
}
//������ACKӦ��		    
void OLED_IIC_NAck(void)
{
	OLED_IIC_SCL=0;
	OLED_SDA_OUT();
	OLED_IIC_SDA=1;
	Delay_us(2);
	OLED_IIC_SCL=1;
	Delay_us(2);
	OLED_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void OLED_IIC_Send_Byte(u8 txd)
{                        
//    u8 t;   
//	SDA_OUT(); 	    
//    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
//    for(t=0;t<8;t++)
//    {              
//        IIC_SDA=(txd&0x80)>>7;
//        txd<<=1; 	  
//		Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
//		IIC_SCL=1;
//		Delay_us(2); 
//		IIC_SCL=0;	
//		Delay_us(2);
//    }




    u8 t;    
    OLED_SDA_OUT();       
    OLED_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ��� 
    for(t=0;t<8;t++) 
    {               
        OLED_IIC_SDA=(txd&0x80)>>7; 
        txd<<=1;     
        Delay_us(2);   //��TEA5767��������ʱ���Ǳ���� 
        OLED_IIC_SCL=1; 
        Delay_us(2);  
        OLED_IIC_SCL=0;
        Delay_us(2); 
    }
    OLED_IIC_Wait_Ack();    
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 OLED_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	OLED_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        OLED_IIC_SCL=0; 
        Delay_us(2);
		OLED_IIC_SCL=1;
        receive<<=1;
        if(OLED_READ_SDA)receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        OLED_IIC_NAck();//����nACK
    else
        OLED_IIC_Ack(); //����ACK   
    return receive;
}




























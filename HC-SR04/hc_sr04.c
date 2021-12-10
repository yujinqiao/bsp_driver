#include "HC-SR04/hc_sr04.h"
#include "stdio.h"
#include "main.h"



/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  


// �ж����ȼ�����
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ����
 *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
 *  TIM_Period               ����
 *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */





static void BASIC_TIM_Mode_Config(void)
{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//		
//		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
//    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
//	
//		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
//    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;	

//	  // ʱ��Ԥ��Ƶ��Ϊ
//    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM_Prescaler;
//	
//		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
//    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//		
//		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
//    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//		
//		// �ظ���������ֵ��������ʱ��û�У����ù�
//		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
//	
//	  // ��ʼ����ʱ��
//    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
//		
//		// ����������жϱ�־λ
//    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
//	  
//		// �����������ж�
//    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
//		
//		// ʹ�ܼ�����
//    TIM_Cmd(BASIC_TIM, DISABLE);	




    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE); //ʱ��ʹ��
	TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =BASIC_TIM_Prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		BASIC_TIM, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(BASIC_TIM, ENABLE);  //ʹ��TIMx����



}

void BASIC_TIM_Init(void)
{
//	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}



uint16_t msHcCount;
 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void HC_SR04_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( Trig_GPIO_CLK | Echo_GPIO_CLK , ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = Trig_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(Trig_GPIO_PORT, &GPIO_InitStructure);	
	    GPIO_ResetBits(Trig_GPIO_PORT,Trig_GPIO_PIN);

		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = Echo_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(Echo_GPIO_PORT, &GPIO_InitStructure);
	    GPIO_ResetBits(Echo_GPIO_PORT,Echo_GPIO_PIN);
		
}
void OpenTimerForHc()        //�򿪶�ʱ��
{
//	    printf("open timer\r\n");
        TIM_SetCounter(BASIC_TIM,0);//�������
        msHcCount = 0;
        TIM_Cmd(BASIC_TIM, ENABLE);  //ʹ��TIMx����
}
 
void CloseTimerForHc()        //�رն�ʱ��
{
//		printf("close timer\r\n");
        TIM_Cmd(BASIC_TIM, DISABLE);  //ʹ��TIMx����
}
//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;//�õ�MS
        t += TIM_GetCounter(BASIC_TIM);//�õ�US
        BASIC_TIM->CNT = 0;  //��TIM2�����Ĵ����ļ���ֵ����
        Delay_Ms(50);
        return t;
}
//Ϊ�����������Ӱ�죬ȡ������ݵ�ƽ��ֵ���м�Ȩ�˲���
float Hcsr04GetLength(void )//��ȡ���ľ���
{
        u32 t = 0;
        int i = 0;
        float lengthTemp = 0;
        float sum = 0;
        while(i!=5)
        {
        GPIO_SetBits(Trig_GPIO_PORT,Trig_GPIO_PIN);
        Delay_Us(20);
		Delay_Us(20);
        GPIO_ResetBits(Trig_GPIO_PORT,Trig_GPIO_PIN);
		while( (GPIO_ReadInputDataBit(Echo_GPIO_PORT, Echo_GPIO_PIN)) == Bit_RESET);
			//printf("Echo is heigh\r\n");
            OpenTimerForHc();        //�򿪶�ʱ��
            i = i + 1;
         while( (GPIO_ReadInputDataBit(Echo_GPIO_PORT, Echo_GPIO_PIN)) == Bit_SET);
			//printf("Echo is low\r\n");
            CloseTimerForHc();        //�رն�ʱ��
            t = GetEchoTimer();        //��ȡʱ��,�ֱ���Ϊ1US
            lengthTemp = ((float)t/58.0);//cm
            sum = lengthTemp + sum ;
			//printf("ÿһ��%f\r\n",lengthTemp);
        
    }
        lengthTemp = sum/5.0;
        return lengthTemp;
}
void Delay_Ms(uint16_t time)  //��ʱ����
{ 
    Public.bsp_DelayMS(time);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Us
** ��������: ��ʱ1us (��ͨ���������ж�����׼ȷ��)
** ����������time (us) ע��time<65535                 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //��ʱ����
{ 
    Public.bsp_DelayUS(time);
}



void  BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		msHcCount ++;
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update);  		 
	}		 	
}


void   getLength(void)
{
    float  length=0;
    length = Hcsr04GetLength();
 
    printf("%0.1f",length);

    gVarInfo.ucLength=(int)length;
    
    printf("%d",gVarInfo.ucLength);
    
}

/*********************************************END OF FILE**********************/


#include "HC-SR04/hc_sr04.h"
#include "stdio.h"
#include "main.h"



/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  


// 中断优先级配置
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            都有
 *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
 *  TIM_Period               都有
 *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */





static void BASIC_TIM_Mode_Config(void)
{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//		
//		// 开启定时器时钟,即内部时钟CK_INT=72M
//    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
//	
//		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
//    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;	

//	  // 时钟预分频数为
//    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM_Prescaler;
//	
//		// 时钟分频因子 ，基本定时器没有，不用管
//    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//		
//		// 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
//    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//		
//		// 重复计数器的值，基本定时器没有，不用管
//		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
//	
//	  // 初始化定时器
//    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
//		
//		// 清除计数器中断标志位
//    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
//	  
//		// 开启计数器中断
//    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
//		
//		// 使能计数器
//    TIM_Cmd(BASIC_TIM, DISABLE);	




    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE); //时钟使能
	TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =BASIC_TIM_Prescaler; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		BASIC_TIM, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(BASIC_TIM, ENABLE);  //使能TIMx外设



}

void BASIC_TIM_Init(void)
{
//	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}



uint16_t msHcCount;
 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void HC_SR04_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( Trig_GPIO_CLK | Echo_GPIO_CLK , ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = Trig_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(Trig_GPIO_PORT, &GPIO_InitStructure);	
	    GPIO_ResetBits(Trig_GPIO_PORT,Trig_GPIO_PIN);

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = Echo_GPIO_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		/*调用库函数，初始化GPIO*/
		GPIO_Init(Echo_GPIO_PORT, &GPIO_InitStructure);
	    GPIO_ResetBits(Echo_GPIO_PORT,Echo_GPIO_PIN);
		
}
void OpenTimerForHc()        //打开定时器
{
//	    printf("open timer\r\n");
        TIM_SetCounter(BASIC_TIM,0);//清除计数
        msHcCount = 0;
        TIM_Cmd(BASIC_TIM, ENABLE);  //使能TIMx外设
}
 
void CloseTimerForHc()        //关闭定时器
{
//		printf("close timer\r\n");
        TIM_Cmd(BASIC_TIM, DISABLE);  //使能TIMx外设
}
//获取定时器时间
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;//得到MS
        t += TIM_GetCounter(BASIC_TIM);//得到US
        BASIC_TIM->CNT = 0;  //将TIM2计数寄存器的计数值清零
        Delay_Ms(50);
        return t;
}
//为了消除余震的影响，取五次数据的平均值进行加权滤波。
float Hcsr04GetLength(void )//获取最后的距离
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
            OpenTimerForHc();        //打开定时器
            i = i + 1;
         while( (GPIO_ReadInputDataBit(Echo_GPIO_PORT, Echo_GPIO_PIN)) == Bit_SET);
			//printf("Echo is low\r\n");
            CloseTimerForHc();        //关闭定时器
            t = GetEchoTimer();        //获取时间,分辨率为1US
            lengthTemp = ((float)t/58.0);//cm
            sum = lengthTemp + sum ;
			//printf("每一次%f\r\n",lengthTemp);
        
    }
        lengthTemp = sum/5.0;
        return lengthTemp;
}
void Delay_Ms(uint16_t time)  //延时函数
{ 
    Public.bsp_DelayMS(time);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Us
** 功能描述: 延时1us (可通过仿真来判断他的准确度)
** 参数描述：time (us) 注意time<65535                 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //延时函数
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


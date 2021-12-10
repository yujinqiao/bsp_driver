#include "BEEP/beep.h"
#include "SYSTICK/SysTick.h"
/**
 * 功能：初始化BEEP
 * 参数：None
 * 返回值：None
 */
void initBEEP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO初始化结构体

	RCC_APB2PeriphClockCmd(BEEP_PORT_RCC, ENABLE); //使能GPIO和复用外设时钟
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;		  		//设置对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		//设置推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		//工作速度50MHz
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);			  		//设置生效
	GPIO_SetBits(BEEP_PORT, BEEP_PIN);				  		//默认低电平，LED不亮
}

/**
 * 功能：点亮LED
 * 参数：None
 * 返回值：None
 */
void openBEEP(void)
{
	GPIO_ResetBits(BEEP_PORT, BEEP_PIN); //设置引脚为低电平	
}

/**
 * 功能：熄灭LED
 * 参数：None
 * 返回值：None
 */
void closeBEEP(void)
{
	GPIO_SetBits(BEEP_PORT, BEEP_PIN); //设置引脚为高电平
}

/**
 * 功能：LED闪烁
 * 参数：times：闪烁次数 open_ms:高电平持续时间 close_ms：低电平持续时间
 * 返回值：None
 */
void blinkBEEP(u8 times,u32 open_ms,u32 close_ms)
{
	u8 t; //用于翻转计数
//	GPIO_ResetBits(GPIOB, GPIO_Pin_5); //设置引脚为低电平
	for(t=0;t<times;++t)
	{
		toggleBEEP();       //翻转为高电平
		Delay_ms(open_ms);
		toggleBEEP();       //翻转为低电平
		Delay_ms(close_ms);
	}

	
}

/**
 * 功能：翻转LED
 * 参数：None
 * 返回值：None
 */
void toggleBEEP(void)
{
	BEEP_PORT->ODR ^= BEEP_PIN;
}


#ifndef __HC_SR04_H
#define __HC_SR04_H	 

#include "SYSTICK/SysTick.h"

#define Trig_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define Trig_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
 #define Trig_GPIO_PIN		GPIO_Pin_9			        /* 连接到SCL时钟线的GPIO */


#define Echo_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define Echo_GPIO_CLK 	    RCC_APB2Periph_GPIOB	/* GPIO端口时钟 */
#define Echo_GPIO_PIN		GPIO_Pin_8        /* 连接到SCL时钟线的GPIO */


void HC_SR04_GPIO_Config(void);
void OpenTimerForHc(void);        //打开定时器
void CloseTimerForHc(void);        //关闭定时器
u32 GetEchoTimer(void);      //获取定时器时间
float Hcsr04GetLength(void );//获取最后的距离
void Delay_Ms(uint16_t time);  //延时函数
void Delay_Us(uint16_t time);  //延时函数




/********************基本定时器TIM参数定义，只限TIM6、7************/
#define BASIC_TIM4 // 如果使用TIM7，注释掉这个宏即可

#ifdef  BASIC_TIM4 // 使用基本定时器TIM6
#define            BASIC_TIM                   TIM4
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM4
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         72-1
#define            BASIC_TIM_IRQ               TIM4_IRQn
#define            BASIC_TIM_IRQHandler        TIM4_IRQHandler

#else  // 使用基本定时器TIM7
#define            BASIC_TIM                   TIM7
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         71
#define            BASIC_TIM_IRQ               TIM7_IRQn
#define            BASIC_TIM_IRQHandler        TIM7_IRQHandler

#endif
/**************************函数声明********************************/

void BASIC_TIM_Init(void);

void   getLength(void);

#endif



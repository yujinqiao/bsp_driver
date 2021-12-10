#ifndef __HC_SR04_H
#define __HC_SR04_H	 

#include "SYSTICK/SysTick.h"

#define Trig_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define Trig_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
 #define Trig_GPIO_PIN		GPIO_Pin_9			        /* ���ӵ�SCLʱ���ߵ�GPIO */


#define Echo_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define Echo_GPIO_CLK 	    RCC_APB2Periph_GPIOB	/* GPIO�˿�ʱ�� */
#define Echo_GPIO_PIN		GPIO_Pin_8        /* ���ӵ�SCLʱ���ߵ�GPIO */


void HC_SR04_GPIO_Config(void);
void OpenTimerForHc(void);        //�򿪶�ʱ��
void CloseTimerForHc(void);        //�رն�ʱ��
u32 GetEchoTimer(void);      //��ȡ��ʱ��ʱ��
float Hcsr04GetLength(void );//��ȡ���ľ���
void Delay_Ms(uint16_t time);  //��ʱ����
void Delay_Us(uint16_t time);  //��ʱ����




/********************������ʱ��TIM�������壬ֻ��TIM6��7************/
#define BASIC_TIM4 // ���ʹ��TIM7��ע�͵�����꼴��

#ifdef  BASIC_TIM4 // ʹ�û�����ʱ��TIM6
#define            BASIC_TIM                   TIM4
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM4
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         72-1
#define            BASIC_TIM_IRQ               TIM4_IRQn
#define            BASIC_TIM_IRQHandler        TIM4_IRQHandler

#else  // ʹ�û�����ʱ��TIM7
#define            BASIC_TIM                   TIM7
#define            BASIC_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM_Period            1000-1
#define            BASIC_TIM_Prescaler         71
#define            BASIC_TIM_IRQ               TIM7_IRQn
#define            BASIC_TIM_IRQHandler        TIM7_IRQHandler

#endif
/**************************��������********************************/

void BASIC_TIM_Init(void);

void   getLength(void);

#endif



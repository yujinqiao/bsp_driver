#ifndef __BSP_ADC_H
#define __BSP_ADC_H	
#include "SYSTEM/system.h"



#define  TEMP_RCC     RCC_APB2Periph_GPIOC
#define  TEMP_GPIO    GPIOC
#define  TEMP_PIN     GPIO_Pin_0

void  TEMP_ADC_Init(void);
u16 TEMP_Get_Adc_Average(u8 ch,u8 times);

#define  HUMI_RCC     RCC_APB2Periph_GPIOA
#define  HUMI_GPIO    GPIOA
#define  HUMI_PIN     GPIO_Pin_1

void  HUMI_ADC_Init(void);
u16 HUMI_Get_Adc_Average(u8 ch,u8 times);






 
#endif 

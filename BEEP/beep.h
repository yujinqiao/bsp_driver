
#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f10x.h"

//typedef enum
//{
//    ON = 0x01,
//    OFF = 0
//}BEEPSTA;





#define BEEP_PORT 			GPIOB  
#define BEEP_PIN 			GPIO_Pin_3
#define BEEP_PORT_RCC		RCC_APB2Periph_GPIOB
#define BEEP_OUTPUT          PBout(3)


void initBEEP(void);
void openBEEP(void);
void closeBEEP(void);
void toggleBEEP(void);
void blinkBEEP(u8 times,u32 open_ms,u32 close_ms);

#endif

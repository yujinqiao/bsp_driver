#include "BEEP/beep.h"
#include "SYSTICK/SysTick.h"
/**
 * ���ܣ���ʼ��BEEP
 * ������None
 * ����ֵ��None
 */
void initBEEP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����GPIO��ʼ���ṹ��

	RCC_APB2PeriphClockCmd(BEEP_PORT_RCC, ENABLE); //ʹ��GPIO�͸�������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;		  		//���ö�Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  		//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		//�����ٶ�50MHz
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);			  		//������Ч
	GPIO_SetBits(BEEP_PORT, BEEP_PIN);				  		//Ĭ�ϵ͵�ƽ��LED����
}

/**
 * ���ܣ�����LED
 * ������None
 * ����ֵ��None
 */
void openBEEP(void)
{
	GPIO_ResetBits(BEEP_PORT, BEEP_PIN); //��������Ϊ�͵�ƽ	
}

/**
 * ���ܣ�Ϩ��LED
 * ������None
 * ����ֵ��None
 */
void closeBEEP(void)
{
	GPIO_SetBits(BEEP_PORT, BEEP_PIN); //��������Ϊ�ߵ�ƽ
}

/**
 * ���ܣ�LED��˸
 * ������times����˸���� open_ms:�ߵ�ƽ����ʱ�� close_ms���͵�ƽ����ʱ��
 * ����ֵ��None
 */
void blinkBEEP(u8 times,u32 open_ms,u32 close_ms)
{
	u8 t; //���ڷ�ת����
//	GPIO_ResetBits(GPIOB, GPIO_Pin_5); //��������Ϊ�͵�ƽ
	for(t=0;t<times;++t)
	{
		toggleBEEP();       //��תΪ�ߵ�ƽ
		Delay_ms(open_ms);
		toggleBEEP();       //��תΪ�͵�ƽ
		Delay_ms(close_ms);
	}

	
}

/**
 * ���ܣ���תLED
 * ������None
 * ����ֵ��None
 */
void toggleBEEP(void)
{
	BEEP_PORT->ODR ^= BEEP_PIN;
}


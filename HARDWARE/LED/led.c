#include "led.h"
#include "delay.h"


//��ʼ��PA0��PA1Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTBʱ��
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB0 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOBA,4	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);				 //PB0 �����
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PB0 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA14
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);				 //PB14 �����


}
 
void Led_Test(void)
{
		LED1(ON);
	  Delay_ms(500);
	  LED1(OFF);
	  Delay_ms(500);
		LED1(ON);
	  Delay_ms(500);
		LED1(OFF);
	  Delay_ms(500);
	 
}

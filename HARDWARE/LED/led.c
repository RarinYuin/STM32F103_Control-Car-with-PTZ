#include "led.h"
#include "delay.h"


//初始化PA0和PA1为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTB时钟
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB0 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOBA,4	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);				 //PB0 输出高
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PB0 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA14
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);				 //PB14 输出低


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

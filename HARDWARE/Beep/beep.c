#include "beep.h"
#include "delay.h"


void Beep_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA8	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);				 //PA8 输出高

}
 
void Beep_Test(void)
{
		BEEP(ON);
	  Delay_ms(500);
		BEEP(OFF);
	  Delay_ms(500);
}

void N_Beep(char n)
{
	char i=0;
	for(i=0;i<n;i++)
	{
		BEEP(ON);
	  Delay_ms(150);
		BEEP(OFF);
	  Delay_ms(150);
	}
}
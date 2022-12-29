#include "key.h"
#include "delay.h"

 	    
//按键初始化函数 
//PB5和PB6 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTB时钟

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOB5
	

	
} 
//按键处理函数
//返回按键值

u8 KEY_Scan()
{	 
 
	if(KEY0==0)
	{
		//delay_ms(10);//去抖动 
		Delay_ms(10);

		if(KEY0==0)
		while(KEY0==0);
		return KEY0_PRES;
	}     
	return 0;// 无按键按下
}

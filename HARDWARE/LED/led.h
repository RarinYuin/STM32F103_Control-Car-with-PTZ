#ifndef __LED_H
#define __LED_H	 

#include "sys.h"

#define ON  0
#define OFF 1
#define LED1(a) if(a) \
											GPIO_SetBits(GPIOA,GPIO_Pin_4); \
								else \
											GPIO_ResetBits(GPIOA,GPIO_Pin_4)


void LED_Init(void);//≥ı ºªØ
void Led_Test(void);
		 				    
#endif

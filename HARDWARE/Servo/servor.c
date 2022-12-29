#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "common.h"


#define MAXPWM 2505		 //舵机最大PWM控制脉宽2.5ms宏定义


u8 count1;				 //每个变量用作8路舵机先后赋值控制
//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	 
//TIM_TimeBaseInitTypeDef TIM_Time1BaseStructure;

extern uint16 CPWM[MOTOR_NUM];

/**********************************舵机初始化************************************/
void Servor_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
/************************GPIO电平反转函数1*****************************************/ 

void Flip_GPIO_One(void)
{
	switch(count1)								 //将20ms的舵机控制周期分成8份，每2.5ms控制一个舵机运转
	{  											      //每个定时器控制8路舵机运转，3个定时器控制24路舵机运转
		case 1: 
			if (CPWM[1] >= 2000){
				CPWM[1] = 2000;
			}else if(CPWM[1] <= 1000){
				CPWM[1] = 1000;
			}
			TIM2->ARR=CPWM[1];				 //将第一个舵机脉冲宽度值赋值给定时器2			
			GPIO_SetBits(GPIOA,GPIO_Pin_11);  //同时拉高控制舵机1的引脚的电
		break;
		
		case 2:
			if (CPWM[1] >= 2000){
				CPWM[1] = 2000;
			}else if(CPWM[1] <= 1000){
				CPWM[1] = 1000;
			}
			TIM2->ARR=MAXPWM-CPWM[1]; 		 //将2.5ms减去PWM脉宽值的数据赋值定时器2
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);//同时拉低控制舵机1引脚的电平 
			break;							 //控制舵机1的引脚在剩下20ms-CPM[0]时间内将一直保持低电平，舵机1按照CPWM值转动

		case 3:	
			if (CPWM[2] >= 2000){
				CPWM[2] = 2000;
			}else if(CPWM[2] <= 1000){
				CPWM[2] = 1000;
			}
			TIM2->ARR=CPWM[2]; 
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			//	GPIO_SetBits(GPIOC,GPIO_Pin_1);		
				break;
		
		case 4:	
			if (CPWM[2] >= 2000){
				CPWM[2] = 2000;
			}else if(CPWM[2] <= 1000){
				CPWM[2] = 1000;
			}
			TIM2->ARR=MAXPWM-CPWM[2]; 
			GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
			count1=0;
			//	GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
				break;

//		case 5:	
//			TIM2->ARR=CPWM[3];  
//		//		GPIO_SetBits(GPIOC,GPIO_Pin_2); 
//				break;
//		
//		case 6:	
//			TIM2->ARR=MAXPWM-CPWM[3];  
//		//		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//				break;

//		case 7:	
//			 TIM2->ARR=CPWM[4];  
//			//  GPIO_SetBits(GPIOC,GPIO_Pin_3); 
//				break;
//		
//		case 8:	
//			 TIM2->ARR=MAXPWM-CPWM[4];  
//			//	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//				break;

//		case 9:	
//			TIM2->ARR=CPWM[5];  
//			//	GPIO_SetBits(GPIOC,GPIO_Pin_4); 
//				break;
//		
//		case 10:
//			TIM2->ARR=MAXPWM-CPWM[5];  
//			//	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
//				break;

//		case 11:
//			TIM2->ARR=CPWM[6];  
//			//	GPIO_SetBits(GPIOC,GPIO_Pin_5); 
//				break;
//		
//		case 12:
//			TIM2->ARR=MAXPWM-CPWM[6];  
//			//	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
//				break;

//		case 13:
//			TIM2->ARR=CPWM[7];  
//			//GPIO_SetBits(GPIOC,GPIO_Pin_6); 
//				break;
//		
//		case 14:
//			  TIM2->ARR=MAXPWM-CPWM[7];  
//			//	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
//				break;

//		case 15:
//			TIM2->ARR=CPWM[8];  
//     // GPIO_SetBits(GPIOC,GPIO_Pin_7); 
//				break;
//		
//		case 16:
//			TIM2->ARR=MAXPWM-CPWM[8]; 
//     // GPIO_ResetBits(GPIOC,GPIO_Pin_7);
//				count1=0; 
//				break;
		default:break;
	}	
}


/**********************************************************************************/   
/************************舵机控制函数1*********************************************/
void Servo1(void)
{		
	count1++; 
	Flip_GPIO_One();						 //反转IO电平

}


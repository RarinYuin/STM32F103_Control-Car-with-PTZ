#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "common.h"


#define MAXPWM 2505		 //������PWM��������2.5ms�궨��


u8 count1;				 //ÿ����������8·����Ⱥ�ֵ����
//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	 
//TIM_TimeBaseInitTypeDef TIM_Time1BaseStructure;

extern uint16 CPWM[MOTOR_NUM];

/**********************************�����ʼ��************************************/
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
/************************GPIO��ƽ��ת����1*****************************************/ 

void Flip_GPIO_One(void)
{
	switch(count1)								 //��20ms�Ķ���������ڷֳ�8�ݣ�ÿ2.5ms����һ�������ת
	{  											      //ÿ����ʱ������8·�����ת��3����ʱ������24·�����ת
		case 1: 
			if (CPWM[1] >= 2000){
				CPWM[1] = 2000;
			}else if(CPWM[1] <= 1000){
				CPWM[1] = 1000;
			}
			TIM2->ARR=CPWM[1];				 //����һ�����������ֵ��ֵ����ʱ��2			
			GPIO_SetBits(GPIOA,GPIO_Pin_11);  //ͬʱ���߿��ƶ��1�����ŵĵ�
		break;
		
		case 2:
			if (CPWM[1] >= 2000){
				CPWM[1] = 2000;
			}else if(CPWM[1] <= 1000){
				CPWM[1] = 1000;
			}
			TIM2->ARR=MAXPWM-CPWM[1]; 		 //��2.5ms��ȥPWM����ֵ�����ݸ�ֵ��ʱ��2
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);//ͬʱ���Ϳ��ƶ��1���ŵĵ�ƽ 
			break;							 //���ƶ��1��������ʣ��20ms-CPM[0]ʱ���ڽ�һֱ���ֵ͵�ƽ�����1����CPWMֵת��

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
/************************������ƺ���1*********************************************/
void Servo1(void)
{		
	count1++; 
	Flip_GPIO_One();						 //��תIO��ƽ

}


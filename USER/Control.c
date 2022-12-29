#include "Control.h"
#include "control_app.h"
#include "key.h"
#include "adc.h"
u8 time = 0;
#define	LED PAout(4)  
u8 led_time=0;
extern u8 delay_50,delay_flag; 
extern char menu;
extern int Motor_A,Motor_B,Target_A,Target_B;  //电机舵机控制相关      
//int Voltage_Temp,Voltage_Count,Voltage_All,sum;
extern int Voltage;                                //电池电压采样相关的变量

void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);
		led_time++;
		time++;
		if(delay_flag==1){
			 if(++delay_50==20)	 {delay_50=0,delay_flag=0;}                      //给主函数提供50ms的精准延时
		 }
		if(led_time==50){
			led_time=0;
			LED=~LED;
		}

		if(menu==1){
			App_control_car();			
		}
	}
}


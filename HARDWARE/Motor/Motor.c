#include "motor.h"
#include "delay.h"

void Motor_Gpio_init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);// 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
   //设置该引脚为复用输出功能,输出TIM3 CH3 CH4 PWM脉冲波形  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 |GPIO_Pin_8|GPIO_Pin_9; //TIM3_CH3 //TIM3_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}




void PWM2_Init(u16 arr,u16 psc){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;							//设置在下一个更新事件装入活动的自动重装载寄存器周期的值 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc;						//设置用来作为 TIMx 时钟频率除数的预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//重复寄存器，用于自动更新
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//②初始化 TIMx

	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //脉宽调制模式 通道1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//使能互补端输出
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //死区后输出状态
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//死区后互补端输出状态
	TIM_OCInitStructure.TIM_Pulse = 0; 							//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //设置互补端输出极性
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH1 预装载使能
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH2 预装载使能
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH3 预装载使能
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH4 预装载使能
	
	TIM_Cmd(TIM4, ENABLE); //④使能 TIM4
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE); //⑤MOE 主输出使能
	
	TIM_SetAutoreload(TIM4, arr);
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
	
	return;	
} 

/***************************************为左右轮赋值************************************/
void Set_Pwm_Motor1(int PWM_a){
	if(PWM_a < 0)	PWMA2 = 7200, PWMA1 = 7200 + PWM_a;
	else 	PWMA1 = 7200, PWMA2 = 7200 - PWM_a;
}


void Set_Pwm_Motor2(int PWM_b){
	if(PWM_b < 0)	PWMB1 = 7200, PWMB2 = 7200 + PWM_b;
	else	PWMB2 = 7200,PWMB1 = 7200 - PWM_b;
}


#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "sys.h"
#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4
void PWM2_Init(u16 arr,u16 psc);
void Motor_Gpio_init(void);
void Set_Pwm(int motor_a,int motor_b);
void Set_Pwm_Motor1(int motor_a);
void Set_Pwm_Motor2(int motor_b);
#endif

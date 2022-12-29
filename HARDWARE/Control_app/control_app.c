#include "control_app.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#include "common.h"
#include "beep.h"
#include<string.h>
#include<stdlib.h>
#define TRUE   1
#define FALSE  0
#define	Be PDout(2)  
unsigned int pwm_num;
unsigned int Motor_Pwm_Dif = 1500;
uint16 UartRec[8] = {1500,1500,1500,1500,1500,1500,1500,1500};
extern u32 Motor_Pwm;
extern unsigned char flag_RecFul;
extern uint16 CPWM[MOTOR_NUM];
extern uint8 redata[500];   // 定义接收数据变量数组
extern char menu;

/***********************************接收数据判断********************************************/
int Is_Car_Front(const char *string){
	if(strncmp(string,"BUPD",4) == 0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Back(const char *string){
	if(strncmp(string,"BDND",4) == 0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Left(const char *string){
	if(strncmp(string,"BLTD",4) == 0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Right(const char *string){
	if(strncmp(string,"BRTD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Speed_Add(const char *string){
	if(strncmp(string,"BUAD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Speed_Slow(const char *string){
		if(strncmp(string,"BUMD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_KD(const char *string){
		if(strncmp(string,"BUKD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}
int Is_Car_horning(const char *string){
		if(strncmp(string,"BUSD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Nohorning(const char *string){
		if(strncmp(string,"BUSN",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_ZDY(const char *string){
		if(strncmp(string,"BUZD",4) == 0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Stop(const char *string){
	if((strncmp(string,"<BLTU>",6)==0) || (strncmp(string,"<BDNU>",6)==0) || \
		   (strncmp(string,"<BUPU>",6)==0)||(strncmp(string,"<BRTU>",6)==0) ||(strncmp(string,"BSTD",4)==0)|| \
	   (strncmp(string,"BLTU",4)==0)||(strncmp(string,"BDNU",4)==0)||(strncmp(string,"BUPU",4)==0)||(strncmp(string,"BRTU",4)==0))
	{
		return TRUE;
	}
	else{
		return FALSE;
	}	
}

/**********************************滑动条数据解码************************************/
void Motor_Dif_Change(const char *str){
	unsigned char motor_num = 0;		     
	unsigned int  motor_time = 0;	  
	unsigned char num_now = 0;		   
	unsigned char dif_now = 0;		  
	unsigned char time_now = 0;		   
	unsigned char flag_num = 0;		  
	unsigned char flag_dif = 0;		  
	unsigned char flag_time = 0;
	unsigned int Motor_Pwm_Dif_Buff = 0;
	unsigned int i = 0;
	unsigned int plat_buf[2] = {0, 0};

	while( str[i]!='\n'  && i < 500){
		if(flag_num == 1){
			if(str[i]!='P'){
				num_now = ASC_To_Valu(str[i]);
				motor_num = motor_num * 10 + num_now;
			}
			else  					
				flag_num = 0;
		}

		if(flag_dif == 1){
			if((str[i] != 'T') & (str[i] != '#')){							
				dif_now = ASC_To_Valu(str[i]);
				Motor_Pwm_Dif_Buff= Motor_Pwm_Dif_Buff * 10 + dif_now;
			}else{
				flag_dif = 0;
				if(Motor_Pwm_Dif_Buff > 2500)
					Motor_Pwm_Dif_Buff = 2500;
				//Motor_Pwm_Dif = Motor_Pwm_Dif_Buff;
				UartRec[motor_num] = Motor_Pwm_Dif_Buff;
				pwm_num = motor_num;
				Motor_Pwm_Dif_Buff = 0;
				motor_num = 0;
			}
		}

		if(flag_time == 1){
			time_now = ASC_To_Valu(str[i]);
			motor_time = motor_time * 10 + time_now;
			UartRec[0] = motor_time;	   
			if(str[i+1] == '\r'){	
				if(motor_time <= 100){
					if(pwm_num != 1 && pwm_num != 2){ 
						CPWM[pwm_num] = UartRec[pwm_num];
					}else if(pwm_num == 1 || pwm_num == 2){
						if(UartRec[pwm_num] != plat_buf[pwm_num - 1]){
							CPWM[pwm_num] = UartRec[pwm_num];
						}
					}
					plat_buf[0] = UartRec[1];
					plat_buf[1] = UartRec[2];
				}
			}
		}
		
		Motor_Pwm_Dif = CPWM[6];
		
		if(str[i]=='#')
			flag_num=1;
		if(str[i]=='P')
			flag_dif=1;
		if(str[i]=='T')
			flag_time=1;
		i++;
	}	  
}

/***********************************小车控制函数****************************************/
void App_control(const char *str){
	if(Is_Car_Front(str)){					//小车前进
		Set_Pwm_Motor1(Motor_Pwm);
		Set_Pwm_Motor2(Motor_Pwm);
	}
	else if(Is_Car_Back(str)){				//小车后退
		Set_Pwm_Motor1(-Motor_Pwm);
		Set_Pwm_Motor2(-Motor_Pwm);
	}
	else if(Is_Car_Left(str)){				//小车左转
		Set_Pwm_Motor1(Motor_Pwm - Motor_Pwm_Dif);		//基准速度减去差速值
		Set_Pwm_Motor2(Motor_Pwm);
	}
	else if(Is_Car_Right(str)){				//小车右转
		Set_Pwm_Motor1(Motor_Pwm);
		Set_Pwm_Motor2(Motor_Pwm - Motor_Pwm_Dif);
	}
	else if(Is_Car_Stop(str)){				//小车停止
		Set_Pwm_Motor1(0);
		Set_Pwm_Motor2(0);
	}
	else if(Is_Car_Speed_Add(str)){			//提高基准速度
		Motor_Pwm += 200; 
		if(Motor_Pwm >= 2500) Motor_Pwm = 2500;
	}
	else if(Is_Car_Speed_Slow(str)){			//降低基准速度
		Motor_Pwm -= 200;		 
		if(Motor_Pwm <= 1000) Motor_Pwm = 1000;
	}
	else if(Is_Car_horning(str)){				//小车鸣笛
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	}
	else if(Is_Car_Nohorning(str)){			//小车停止鸣笛
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
	}
	else if(Is_Car_ZDY(str)){
		CPWM[1] = 1500;						//云台复位
		CPWM[2] = 1500;
	}else if(Is_Car_KD(str)){
		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14)){
			GPIO_ResetBits(GPIOA, GPIO_Pin_14);
		}else if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14) == 0){
			GPIO_SetBits(GPIOA, GPIO_Pin_14);
		}
	}
	else {
		Motor_Dif_Change(str);					//差速值控制
	}
}

void App_control_car(void)
{
    if(flag_RecFul)
	{
	  //printf("%s",USART_RX_BUF);
	  flag_RecFul=0;
	  App_control(redata);
	}
}

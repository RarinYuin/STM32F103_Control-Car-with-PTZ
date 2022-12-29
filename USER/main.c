#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"	    				//����stm32��ϵͳͷ�ļ�
#include "servor.h"							//����GPIO��ͷ�ļ�
#include "usart.h"		  					//��������ͨ������ͷ�ļ�
#include "delay.h"						//����ϵͳ��ʱ����ͷ�ļ�
#include "timer.h"					//������ʱ������ͷ�ļ�
#include "key.h"
#include "led.h"
#include "beep.h"
#include "common.h"
#include "adc.h"
#include "motor.h"
#include "control_app.h"
#include "oled.h"
#include "show.h"
int Voltage_Temp, Voltage_Count, Voltage_All, sum;
int Voltage;                                //��ص�ѹ������صı���
u32 value;									
u32 key, key_bak;
extern u32 a;		  						//a�������������ϵͳ�δ�ʱ���ɼ���������ʱ��
extern uint8 flag_RecFul;
int Encoder_A_EXTI;
uint16 CPWM[MOTOR_NUM]= {1500,1500,1500,1500,1500,1500,1500,1500,1500};
char redata[500] = {0};    // ����������ݱ�������
uint16 adc_value = 0;
int Motor_Pwm = 3000;
char menu = 1;
u8 delay_50,delay_flag; 
void scan_ps2(void);
void Check_Power(void);
void ps2_handle(void);
void Check_Battery(void);

/*****************************������***********************************************/
int main(void){   
	SysTick_Init();									   //ϵͳ�δ�ʱ����ʼ��
	Servor_GPIO_Config();									   //GPIO��ʼ��
	Uart_Init(2);	
	Uart_Init(3);
	Timer_Init();									   //��ʱ����ʼ��
	Timer_ON();										   //������ʱ��	 		
	LED_Init();	
	Beep_Init();
	Uart_Init(1);
	OLED_Init();                    //=====OLED��ʼ��	
	Adc_Init();
	USART_Config(USART1,115200); 
	USART_Config(USART2,115200); 
	USART_Config(USART3,115200); 
	Motor_Gpio_init();
	PWM2_Init(7199,0);  // ��ʼ���������Ƶ�� 72/(5+1)  12KHZ
	Led_Test();
	Beep_Test();

	while (1){
		
		Check_Battery();	                                 //=====��ȡ��ص�ѹ		
		oled_show();          //===��ʾ����
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //ͨ����ʱ�ж�ʵ�ֵ�50ms��׼��ʱ
	}
} 


void Check_Battery(void){
	Voltage_Temp=Get_battery_volt();		                                 //=====��ȡ��ص�ѹ		
	Voltage_Count++;                                                     //=====ƽ��ֵ������
	Voltage_All+=Voltage_Temp;                                           //=====��β����ۻ�
	if(Voltage_Count==10) Voltage=Voltage_All/10,Voltage_All=0,Voltage_Count=0;//=====��ƽ��ֵ		 
}


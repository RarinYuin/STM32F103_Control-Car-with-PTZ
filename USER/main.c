#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"	    				//包含stm32库系统头文件
#include "servor.h"							//包含GPIO库头文件
#include "usart.h"		  					//包含串口通信设置头文件
#include "delay.h"						//包含系统定时器库头文件
#include "timer.h"					//包含定时器设置头文件
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
int Voltage;                                //电池电压采样相关的变量
u32 value;									
u32 key, key_bak;
extern u32 a;		  						//a用来计数，配合系统滴答定时器可检测代码运行时间
extern uint8 flag_RecFul;
int Encoder_A_EXTI;
uint16 CPWM[MOTOR_NUM]= {1500,1500,1500,1500,1500,1500,1500,1500,1500};
char redata[500] = {0};    // 定义接收数据变量数组
uint16 adc_value = 0;
int Motor_Pwm = 3000;
char menu = 1;
u8 delay_50,delay_flag; 
void scan_ps2(void);
void Check_Power(void);
void ps2_handle(void);
void Check_Battery(void);

/*****************************主函数***********************************************/
int main(void){   
	SysTick_Init();									   //系统滴答定时器初始化
	Servor_GPIO_Config();									   //GPIO初始化
	Uart_Init(2);	
	Uart_Init(3);
	Timer_Init();									   //定时器初始化
	Timer_ON();										   //开启定时器	 		
	LED_Init();	
	Beep_Init();
	Uart_Init(1);
	OLED_Init();                    //=====OLED初始化	
	Adc_Init();
	USART_Config(USART1,115200); 
	USART_Config(USART2,115200); 
	USART_Config(USART3,115200); 
	Motor_Gpio_init();
	PWM2_Init(7199,0);  // 初始化电机工作频率 72/(5+1)  12KHZ
	Led_Test();
	Beep_Test();

	while (1){
		
		Check_Battery();	                                 //=====读取电池电压		
		oled_show();          //===显示屏打开
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //通过定时中断实现的50ms精准延时
	}
} 


void Check_Battery(void){
	Voltage_Temp=Get_battery_volt();		                                 //=====读取电池电压		
	Voltage_Count++;                                                     //=====平均值计数器
	Voltage_All+=Voltage_Temp;                                           //=====多次采样累积
	if(Voltage_Count==10) Voltage=Voltage_All/10,Voltage_All=0,Voltage_Count=0;//=====求平均值		 
}


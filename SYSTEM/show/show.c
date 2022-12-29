#include "show.h"
#include "oled.h"
#include "common.h"
extern int Voltage;            //��ص�ѹ������صı���
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void){           
	OLED_ShowString(20,00,"Robot System");  	
	OLED_ShowString(00,24,"MODE:");    		//����ģʽ
	OLED_ShowString(40,24,"APP Control");    //APP����ģʽ
	OLED_ShowString(0,48,"VOLTAGE:");    //��ѹֵ
	OLED_ShowString(68,48,".");  
	OLED_ShowString(90,48,"V");  
	OLED_ShowNumber(55,48,Voltage/100,2,12);
	OLED_ShowNumber(78,48,Voltage%100,2,12);
	if(Voltage%100<10) 	OLED_ShowNumber(72,48,0,2,12);

	OLED_Refresh_Gram();	
}

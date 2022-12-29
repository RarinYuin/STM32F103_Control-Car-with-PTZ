#ifndef __BEEP_H__
#define __BEEP_H__
#include "sys.h"

#define ON  0
#define OFF 1
#define BEEP(a) if(a) \
											GPIO_SetBits(GPIOA,GPIO_Pin_8); \
								else \
											GPIO_ResetBits(GPIOA,GPIO_Pin_8)
								
#define	Beep PAout(8)  //Ñ¡ÖÐFLASH										

void Beep_Init(void);
void Beep_Test(void);
void N_Beep(char n);
#endif

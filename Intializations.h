#include "GPIO_Driver.h"
#include "Interrupt_Driver.h"
#include "GPTM_Driver.h"
#include "PWM_Driver.h"
#include "Systick_Timer.h"

#ifndef __Intializations_H__
#define __Intializations_H__

extern void PORTS_Intialization(void);                                          //To initialize ports
extern void GPTM_Intialization(void);                                           //To initialize GPTM
extern void LED(char type[],int mode);                                          //To control different colors
extern void PWM_Initialization(void);





#endif
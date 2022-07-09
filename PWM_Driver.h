#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include <math.h> 





#ifndef __PWM_Driver_H__
#define __PWM_Driver_H__

//define of clk of each port
#define CLK_PWM0 	(0x01)
#define CLK_PWM1 	(0x02)
#define CLK_PWM2 	(0x04)
#define CLK_PWM3 	(0x08)




extern void CLK_Enable_PWM_Module(int PWM_Module_Number);                            //Clock for Port
extern void USE_PWM_CLK_DIVIDER(char type[10]);                  //Unlock for port
extern void CLK_PWM_DIVIDER(int Clk_Divider);                         //Enable or Disable Analog and Digital
extern void PWM_START_STOP(int PWM_Module_Number,int Generator,char type[10]);          //General i/o or Alternative Function
extern void PWM_MAXIMUM_LOAD_VALUE(int PWM_Module_Number,int Sub_Module,int Load_Value);
extern void PWM_COMPARE_VALUE(int PWM_Module_Number,int Sub_Module,char Comparator,int Compare_Value);
extern void PWM_GENERATOR_VALUE(int PWM_Module_Number,int Sub_Module,char Generator);
extern int PWM_VALUE(int PWM_Module_Number,int Generator);
extern void PWM_MODULE_ENABLE(int PWM_Module_Number,int Channel,char type[10]);
extern void PULSE_WITDH_MODULATION(int PWM_Module_Number,int Sub_Module,char Generator,char Compartor,int Clk_Speed_MHZ,int PWM_Speed_KHZ, int Duty_Cycle); 



#endif
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifndef GPTM_Intialization_h
#define GPTM_Intialization_h

extern void CLK_Enable_GPTM_Module(int timer_number);                                                                //To Eable CLK for specific port
extern void Enable_Timer_Number(int timer_number,char type[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Option(int timer_number,char option[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Mode(int timer_number,char mode[10]);           //Enable or Disable Analog and Digital
extern void Timer_Number_Ticks(int timer_number,int ticks);           //Enable or Disable Analog and Digital
extern void Timer_Number_Clk_Divider(int timer_number,int new_clk);
extern void GPTM_Delay_Seconds(int timer_number,int seconds);






#endif

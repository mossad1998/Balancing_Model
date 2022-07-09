#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#ifndef Systick_Timer_h
#define Systick_Timer_h



extern void Systick_Delay_Seconds(int seconds );
extern void Flag_of_Half_Second();
extern void Systick_Configure();

#endif

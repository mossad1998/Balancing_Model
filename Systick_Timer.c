#include "Systick_Timer.h"


void Systick_Delay_Seconds(int seconds )
  {
     int ticks = seconds *2 ;
     int counter = 0 ;
     NVIC_ST_CTRL_R = 0x5;                                       //Enable timer
     while(counter <= ticks)
     {
      if( NVIC_ST_CTRL_R & 0x10000)
      counter++;
     }
  }
void Systick_Configure()
  {
     NVIC_ST_CTRL_R = 0;                                          //Disable SysTick during setup
     NVIC_ST_RELOAD_R = 8000000-1;                                    //Time of one millisecond    
  }
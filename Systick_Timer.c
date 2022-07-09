#include "Systick_Timer.h"


void Systick_Delay_Seconds(float seconds )
  {
     int ticks = seconds *2 ;
     int counter = 0 ;
     while(counter <= ticks)
     {
      Flag_of_Half_Second();
      counter++;
     }
  }
void Flag_of_Half_Second()
  {
     NVIC_ST_CTRL_R = 0x5;                                       //Enable timer
     while(1)
      {
        if( NVIC_ST_CTRL_R & 0x10000)
        {
        Systick_Configure();    
        return ;
        }
      }
  }

void Systick_Configure()
  {
     NVIC_ST_CTRL_R = 0;                                          //Disable SysTick during setup
     NVIC_ST_RELOAD_R = 8000000-1;                                    //Time of one millisecond    
  }
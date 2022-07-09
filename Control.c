#include "Control.h"

void Main_Control(void)
{
int val =2;
while(1) { 
            bool data1 = PIN_READ_DIGITAL('F',0);
            bool data2 = PIN_READ_DIGITAL('F',4);
            if(data2!=1)
            {
              PWM_MODULE_ENABLE(1,7,"Disable");
              val = 2;
            }
  if(data1!=1)
  {
  PWM_START_STOP(1,3,"Stop");	
  //PWM1_3_CTL_R = 0;
  //printf("pwm is %d",val);
  PULSE_WITDH_MODULATION(1,3,'B','A',16,8,val);
  
  PWM_START_STOP(1,3,"Start");
  //PWM1_3_CTL_R = 1;
  
  PWM_MODULE_ENABLE(1,7,"Enable");
  
  Systick_Delay_Seconds(1);
    if(val<90)
    val=val+2;
  
    

  }
        }



}
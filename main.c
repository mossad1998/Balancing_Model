#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "I2C_Driver.h"
#include "Systick_Timer.h"
#include "I2C.h"
#include "PWM_Driver.h"



void main()
{  
  
  int val = 2;
  
  
  
  CLK_Enable_PWM_Module(1);
  Systick_Configure();
  
  CLK_Enable('F');                                                          //Enable Clock for Port F
  GPIO_PORT_LOCK('F');                                                      //Unlock for port F
  
  USE_PWM_CLK_DIVIDER("Disable");
  
  PIN_FUNCTION_SELECT('F',3,"Alternative");
  PIN_FUNCTION_SELECT('F',0,"General I/O");
    PIN_FUNCTION_SELECT('F',4,"General I/O");

  //GPIO_PORTF_AFSEL_R = 8;
  
  PIN_CONFIGURE('F',3,"PWM");
  PIN_INPUT_OUTPUT('F',0,"Input");
    PIN_INPUT_OUTPUT('F',4,"Input");

  //GPIO_PORTF_PCTL_R &= ~0x0000F000;
  //GPIO_PORTF_PCTL_R |= 0x00005000;
    
  PIN_ANALOG_DIGITAL('F',0,"Digital");
  PIN_ANALOG_DIGITAL('F',4,"Digital");
  PIN_ANALOG_DIGITAL('F',3,"Digital");
  
  PIN_PULLUP_RESISTOR('F',0,"Pullup");
  PIN_PULLUP_RESISTOR('F',4,"Pullup");

  
  //PWM_START_STOP(1,3,"Stop");
  //PWM1_3_CTL_R = 0;
  
  //PULSE_WITDH_MODULATION(1,3,'B','A',16,8,0);
  
 // PWM_START_STOP(1,3,"Start");
  //PWM1_3_CTL_R = 1;
  
  PWM_MODULE_ENABLE(1,7,"Disable");
  


  
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
  printf("pwm is %d",val);

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
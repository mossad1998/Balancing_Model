#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "I2C_Driver.h"
#include "Systick_Timer.h"
#include "I2C.h"
#include "PWM_Driver.h"



void main()
{  
  CLK_Enable_PWM_Module(1);
  
  CLK_Enable('F');                                                          //Enable Clock for Port F
  GPIO_PORT_LOCK('F');                                                      //Unlock for port F
  
  USE_PWM_CLK_DIVIDER("Disable");
  
  PIN_FUNCTION_SELECT('F',3,"Alternative");
  //GPIO_PORTF_AFSEL_R = 8;
  
  PIN_CONFIGURE('F',3,"PWM");
  //GPIO_PORTF_PCTL_R &= ~0x0000F000;
  //GPIO_PORTF_PCTL_R |= 0x00005000;
    
  PIN_ANALOG_DIGITAL('F',3,"Digital");
  
  PWM_START_STOP(1,3,"Stop");
  //PWM1_3_CTL_R = 0;
  
  PULSE_WITDH_MODULATION(1,3,'B','A',16,1,50);
  
  PWM_START_STOP(1,3,"Start");
  //PWM1_3_CTL_R = 1;
  
  PWM_MODULE_ENABLE(1,7,"Enable");
 


      for(;;) { }
  
}
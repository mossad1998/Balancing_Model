#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "GPTM_Driver.h"
#include "PWM_Driver.h"
#include "Interrupt_Driver.h"
#include "Intializations.h"
#include "Control.h"
#include <stdint.h>
#include "stdio.h"
void main()
{     
  PORTS_Intialization();
  GPTM_Intialization();
  PWM_Initialization();
  Main_Control();
      

      __asm("CPSIE  I");
      while(1)
       {
        
       }
}

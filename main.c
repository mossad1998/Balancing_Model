#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "I2C_Driver.h"
#include "Systick_Timer.h"
#include "PWM_Driver.h"



void main()
{  
    //CLK_Enable_I2C_Module(1);
    SYSCTL_RCGCI2C_R |= 0x02;
    
    //CLK_Enable('A');
    SYSCTL_RCGCGPIO_R |= 0x01;
    
    //PIN_FUNCTION_SELECT('A',6,"Alternative");
    //PIN_FUNCTION_SELECT('A',7,"Alternative");
    GPIO_PORTA_AFSEL_R |= 0xC0;
    
    //PIN_CONFIGURE('A',6,"I2C");
    //PIN_CONFIGURE('A',7,"I2C");
    GPIO_PORTA_PCTL_R &= ~0xFF000000;
    GPIO_PORTA_PCTL_R |= 0x33000000;
    
    //PIN_ANALOG_DIGITAL('A',6,"Digital");
    //PIN_ANALOG_DIGITAL('A',7,"Digital");
    GPIO_PORTA_DEN_R |= 0xC0;
    
    //PIN_OPEN_DRAIN('A',7);
    GPIO_PORTA_ODR_R |= 0x80;
    
    //I2C_Mode_Function(1,"Master");
    I2C1_MCR_R = 0x10;
    
    //I2C_Speed_Kbps(100,1,16);
    I2C1_MTPR_R = 7;
    
    //I2C_Scan_Address(1,7);
              

          //*I2C_MSA_R[timer_number] = (i <<1)+1 ;
      
          I2C1_MSA_R = 0x1E << 1;
          I2C1_MDR_R = 0;
          I2C1_MCS_R = 3;
          
          //I2C1_MCS_R = 3;
          
          //*I2C_MCS_R[timer_number] |= 1UL << 0;
          //*I2C_MCS_R[timer_number] |= 1UL << 1;

          while(I2C1_MCS_R & 1);
          
          int error = I2C1_MCS_R & 0xE; 

          //printf("Iteration is :%d",i);
          printf("Error0 is :%d",error);
          printf("\n");
         I2C1_MSA_R = (0x1E << 1) + 1;
          while(I2C1_MCS_R & 1);
          
          error = I2C1_MCS_R & 0xE; 
          printf("Error1 is :%d",error);





}


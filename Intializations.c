#include "Intializations.h"
int time_period = 0;
bool stop = 0 ;
bool before_stop = 1;
bool reset = 0;
  


void GPTM_Intialization(void)                                                   //To initialize GPTM
{
      CLK_Enable_GPTM_Module(1);                                                //Enable Clock for Timer 1
      Enable_Timer_Number(1,"Disable");                                         //To Disable Timer 1
      Timer_Number_Option(1,"16");                                              //specify 32 bit for timer 1
      Timer_Number_Mode(1,"periodic");                                          //specify Periodic Mode for timer 1
      Timer_Number_Clk_Divider(1,64000);
      Timer_Number_Ticks(1,64000);                                           //To interrupt every 1 Second
      GPTM_Clear_Interrupt(1,'A');                                              //To clear GPTM interrupt flag
      GPTM_Unmask(1,'A');                                                       //To unmask GPTM Timer 1
      Enable_Timer_Number(1,"Enable");                                          //To Enable Timer 1
      
      Interrupt_Priority(&NVIC_PRI15_R,13,3);                                   //To specify priority of 3 for Timer 1 interrupt
      Interrupt_Enable(&NVIC_EN0_R,21);                                         //To Enable interrupt for Timer 1

}


void PORTS_Intialization(void)                                                  //To initialize PortF
{
    CLK_Enable('F');                                                          //Enable Clock for Port F
    GPIO_PORT_LOCK('F');        
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
}
 



void LED(char type[],int mode)                                                  //To control led
{
 if(strcmp(type , "GREEN")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',3,"HIGH");                                   //Turn ON Green LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',3,"LOW");                                    //Turn OFF Green LED                                           
      }
          else if (strcmp(type , "RED")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',1,"HIGH");                                   //Turn ON Red LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',1,"LOW");                                    //Turn OFF Red LED
      }
          else if (strcmp(type , "BLUE")==0)
      {
          if(mode==1)
             PIN_WRITE_DIGITAL('F',2,"HIGH");                                   //Turn ON Blue LED
          else if (mode==0)
             PIN_WRITE_DIGITAL('F',2,"LOW");                                    //Turn OFF BLue LED                                                     
      }
}



void Timer_Handler(void)
  {
      if(GPTM_Interrupt_Flag(1,'A'))
      {
          bool static flag=1;
          if(flag==1)
              {
                PIN_WRITE_DIGITAL('F',2,"HIGH");
                flag=0;
              }
           else
              {
                PIN_WRITE_DIGITAL('F',2,"LOW");
                flag=1;
              }
      }
      GPTM_Clear_Interrupt(1,'A');
  }


void PWM_Initialization(void)
{
    Systick_Configure();
  
  CLK_Enable_PWM_Module(1);
  USE_PWM_CLK_DIVIDER("Disable");
  PWM_MODULE_ENABLE(1,7,"Disable");
}

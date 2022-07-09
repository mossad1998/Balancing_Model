#include "PWM_Driver.h"

int CLK_PWM_Modules[]={CLK_PWM0,CLK_PWM1,CLK_PWM2,CLK_PWM3};                  //Array of CLK values for each port           

volatile uint32_t* PWM_CONTROL_R[]={&PWM0_0_CTL_R,&PWM0_1_CTL_R,&PWM0_2_CTL_R,&PWM0_3_CTL_R,
                                      &PWM1_0_CTL_R,&PWM1_1_CTL_R,&PWM1_2_CTL_R,&PWM1_3_CTL_R};

volatile uint32_t* PWM_LOAD_R[]={&PWM0_0_LOAD_R,&PWM0_1_LOAD_R,&PWM0_2_LOAD_R,&PWM0_3_LOAD_R,
                                 &PWM1_0_LOAD_R,&PWM1_1_LOAD_R,&PWM1_2_LOAD_R,&PWM1_3_LOAD_R};

volatile uint32_t* PWM_COUNTER_R[]={&PWM0_0_COUNT_R,&PWM0_1_COUNT_R,&PWM0_2_COUNT_R,&PWM0_3_COUNT_R,
                                      &PWM1_0_COUNT_R,&PWM1_1_COUNT_R,&PWM1_2_COUNT_R,&PWM1_3_COUNT_R};

volatile uint32_t* PWM_GENERATOR_R[]={&PWM0_0_GENA_R,&PWM0_0_GENB_R,&PWM0_1_GENA_R,&PWM0_1_GENB_R,
                                      &PWM0_2_GENA_R,&PWM0_2_GENB_R,&PWM0_3_GENA_R,&PWM0_3_GENB_R,
                                      &PWM1_0_GENA_R,&PWM1_0_GENB_R,&PWM1_1_GENA_R,&PWM1_1_GENB_R,
                                      &PWM1_2_GENA_R,&PWM1_2_GENB_R,&PWM1_3_GENA_R,&PWM1_3_GENB_R};

volatile uint32_t* PWM_COMPARE_R[]={&PWM0_0_CMPA_R,&PWM0_0_CMPB_R,&PWM0_1_CMPA_R,&PWM0_1_CMPB_R,
                                    &PWM0_2_CMPA_R,&PWM0_2_CMPB_R,&PWM0_3_CMPA_R,&PWM0_3_CMPB_R,
                                    &PWM1_0_CMPA_R,&PWM1_0_CMPB_R,&PWM1_1_CMPA_R,&PWM1_1_CMPB_R,
                                    &PWM1_2_CMPA_R,&PWM1_2_CMPB_R,&PWM1_3_CMPA_R,&PWM1_3_CMPB_R};

volatile uint32_t* PWM_ENABLE_R[]={&PWM0_ENABLE_R,&PWM1_ENABLE_R};





void CLK_Enable_PWM_Module(int PWM_Module_Number)                                                                 //To Eable CLK for specific port
{
  SYSCTL_RCGCPWM_R |= CLK_PWM_Modules[PWM_Module_Number];
    volatile uint32_t dummy ;                                                                   //To wait untill enabling the CLK
    dummy = SYSCTL_RCGCPWM_R ;                                             
}


void USE_PWM_CLK_DIVIDER(char type[10])                                                             //To Unlock port F or D
{
    if(strcmp(type , "Enable")==0)
  {
    SYSCTL_RCC_R |= 1UL << 20;
  }
  else if (strcmp(type , "Disable")==0)
  {                                  
    SYSCTL_RCC_R &= ~(1UL << 20);
  }  

}


void CLK_PWM_DIVIDER(int Clk_Divider)                                   //To choose digital or analog
{
    double Divider_Value = (log10(Clk_Divider)/log10(2))-1;
    SYSCTL_RCC_R = (int)Divider_Value << 16;
}


void PWM_START_STOP(int PWM_Module_Number,int Generator,char type[10])
{
  
  int index = Generator + 3*PWM_Module_Number;
  if(strcmp(type , "Start")==0)
  {
    *PWM_CONTROL_R[index] = 1;
  }
  else if (strcmp(type , "Disable")==0)
  {                                  
    *PWM_GENERATOR_R[index] = 0;
  }  

}

void PWM_MAXIMUM_LOAD_VALUE(int PWM_Module_Number,int Sub_Module,int Load_Value)
{  
  
  int index = Sub_Module + 4*PWM_Module_Number;

  *PWM_LOAD_R[index] = Load_Value;

}

void PWM_COMPARE_VALUE(int PWM_Module_Number,int Sub_Module,char Comparator,int Compare_Value)
{
  int index = (Comparator - 65) + 2*Sub_Module + 8*PWM_Module_Number;
  *PWM_COMPARE_R[index] = Compare_Value;
}

void PWM_GENERATOR_VALUE(int PWM_Module_Number,int Sub_Module,char Generator)
{
  int index = (Generator - 65) + 2*Sub_Module + 8*PWM_Module_Number;
  *PWM_GENERATOR_R[index] = 0x8C;
}

int PWM_VALUE(int PWM_Module_Number,int Generator)
{
    int index = Generator + 3*PWM_Module_Number;
    return *PWM_COUNTER_R[index];
}

void PWM_MODULE_ENABLE(int PWM_Module_Number,int Channel,char type[10])
{  
  if(strcmp(type , "Enable")==0)
  {
    *PWM_ENABLE_R[PWM_Module_Number] |= 1UL << Channel;
  }
  else if (strcmp(type , "Disable")==0)
  {                                  
    *PWM_ENABLE_R[PWM_Module_Number] &= ~(1UL << Channel);
  }  
}
void PULSE_WITDH_MODULATION(int PWM_Module_Number,int Sub_Module,char Generator,char Compartor,int Clk_Speed_MHZ,int PWM_Speed_KHZ, int Duty_Cycle)
{
  int Load_Value = (Clk_Speed_MHZ*1000000)/(PWM_Speed_KHZ*1000);
  int Compare_Value = (100-Duty_Cycle)*(Load_Value/100);
  //PWM1_3_GENB_R = 0x0000008C;
  PWM_GENERATOR_VALUE(PWM_Module_Number,Sub_Module,Generator);
  
  //PWM1_3_LOAD_R = 16000;
  PWM_MAXIMUM_LOAD_VALUE(PWM_Module_Number,Sub_Module,Load_Value);
  
  //PWM1_3_CMPA_R = 14000;
  PWM_COMPARE_VALUE(PWM_Module_Number,Sub_Module,Compartor,Compare_Value);
}

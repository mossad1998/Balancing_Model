#include "GPTM_Driver.h"

volatile uint32_t* TIMERS_R[]={&TIMER0_CTL_R,&TIMER1_CTL_R,&TIMER2_CTL_R,
                               &TIMER3_CTL_R,&TIMER4_CTL_R,&TIMER5_CTL_R};


volatile uint32_t* TIMERS_CFG_R[]={&TIMER0_CFG_R,&TIMER1_CFG_R,&TIMER2_CFG_R,
                                   &TIMER3_CFG_R,&TIMER4_CFG_R,&TIMER5_CFG_R};

volatile uint32_t* TIMERS_TAMR_R[]={&TIMER0_TAMR_R,&TIMER1_TAMR_R,&TIMER2_TAMR_R,
                                   &TIMER3_TAMR_R,&TIMER4_TAMR_R,&TIMER5_TAMR_R};

volatile uint32_t* TIMERS_TAPR_R[]={&TIMER0_TAPR_R,&TIMER1_TAPR_R,&TIMER2_TAPR_R,
                                     &TIMER3_TAPR_R,&TIMER4_TAPR_R,&TIMER5_TAPR_R};

volatile uint32_t* TIMERS_Aload_R[]={&TIMER0_TAILR_R,&TIMER1_TAILR_R,&TIMER2_TAILR_R,
                                     &TIMER3_TAILR_R,&TIMER4_TAILR_R,&TIMER5_TAILR_R};

volatile uint32_t* TIMERS_Clear_R[]={&TIMER0_ICR_R,&TIMER1_ICR_R,&TIMER2_ICR_R,
                                     &TIMER3_ICR_R,&TIMER4_ICR_R,&TIMER5_ICR_R};

volatile uint32_t* TIMERS_Flag_R[]={&TIMER0_RIS_R,&TIMER1_RIS_R,&TIMER2_RIS_R,
                                     &TIMER3_RIS_R,&TIMER4_RIS_R,&TIMER5_RIS_R};



void CLK_Enable_GPTM_Module(int timer_number)
  {
    SYSCTL_RCGCTIMER_R |= (1UL << timer_number);
  }

void Enable_Timer_Number(int timer_number,char type[10])
  {
    if(strcmp(type , "Enable")==0)
      {
      *TIMERS_R[timer_number] |= 1UL << 0;                                                         //To Enable DEN
      }
    else if (strcmp(type , "Disable")==0)
      {
      *TIMERS_R[timer_number] &= ~(1UL << 0);                                                    //To Disable AMSEL
      }
  }

void Timer_Number_Option(int timer_number,char option[10])
  {
    if((strcmp(option,"16"))==0)
      *TIMERS_CFG_R[timer_number] = 0x4;
    else if((strcmp(option,"32"))==0)
      *TIMERS_CFG_R[timer_number] = 0x0;
    else if ((strcmp(option,"RTC"))==0)
      *TIMERS_CFG_R[timer_number] = 0x1;
  }

void Timer_Number_Mode(int timer_number,char mode[10])
  {
    if((strcmp(mode,"one_shot"))==0)
      *TIMERS_TAMR_R[timer_number] |= 0x1;
    else if((strcmp(mode,"periodic"))==0)
      *TIMERS_TAMR_R[timer_number] |= 0x2;
    else if((strcmp(mode,"capture"))==0)
      *TIMERS_TAMR_R[timer_number] |= 0x3;
  }

void Timer_Number_Ticks(int timer_number,int ticks)
  {
    *TIMERS_Aload_R[timer_number] = ticks-1;
    *TIMERS_Clear_R[timer_number]= 1;
  }

void Timer_Number_Clk_Divider(int timer_number,int new_clk)
  {
    int divider = 16000000/new_clk;
    *TIMERS_TAPR_R[timer_number] = divider;
  }

void GPTM_Delay_Seconds(int timer_number,int seconds)
  {    
    //*TIMERS_Clear_R[timer_number]= 1;
    Enable_Timer_Number(1,"Enable");
    for(int i=0;i<seconds;i++)
    {
         while((*TIMERS_Flag_R[timer_number] & 0x1)==0);
         *TIMERS_Clear_R[timer_number]= 1;
    }
 
  }








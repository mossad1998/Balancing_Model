#include "I2C_Driver.h"

int CLK_I2C_Modules[]={CLK_I2C0,CLK_I2C1,CLK_I2C2,CLK_I2C3};                  //Array of CLK values for each port           

volatile uint32_t* I2C_MCR_R[]={&I2C0_MCR_R,&I2C1_MCR_R,&I2C2_MCR_R,&I2C3_MCR_R};

volatile uint32_t* I2C_MTPR_R[]={&I2C0_MTPR_R,&I2C1_MTPR_R,&I2C2_MTPR_R,&I2C3_MTPR_R};

volatile uint32_t* I2C_MSA_R[]={&I2C0_MSA_R,&I2C1_MSA_R,&I2C2_MSA_R,&I2C3_MSA_R};

volatile uint32_t* I2C_MDR_R[]={&I2C0_MDR_R,&I2C1_MDR_R,&I2C2_MDR_R,&I2C3_MDR_R};

volatile uint32_t* I2C_MCS_R[]={&I2C0_MCS_R,&I2C1_MCS_R,&I2C2_MCS_R,&I2C3_MCS_R};






                  


void CLK_Enable_I2C_Module(int timer_number)                                                                 //To Eable CLK for specific port
{
  SYSCTL_RCGCI2C_R |= CLK_I2C_Modules[timer_number];
    volatile uint32_t dummy ;                                                                   //To wait untill enabling the CLK
    dummy = SYSCTL_RCGCI2C_R ;                                             
}

void I2C_Mode_Function(char type[10],int timer_number)                                                             //To Unlock port F or D
{
    if(strcmp(type , "Master")==0)
  {
    *I2C_MCR_R[timer_number] =0x10;//|= 1UL << 4;                                                    //To Disable AMSEL
    //*I2C_MCR_R[timer_number] &= ~(1UL << 0);                                                    //To Disable AMSEL

  }
  else if (strcmp(type , "Slave")==0)
  {
    *I2C_MCR_R[timer_number] |= 1UL << 5;                                                    //To Disable AMSEL
    *I2C_MCR_R[timer_number] &= ~(1UL << 0);
  }  

}


void I2C_Speed_Kbps(int I2C_Speed,int timer_number,int Clk_Speed)                                   //To choose digital or analog
{
  int TPR = ((Clk_Speed*1000000)/(20*I2C_Speed*1000))-1;
  *I2C_MTPR_R[timer_number] = TPR;

}

char I2C_Write(int timer_number,int number_of_byte,char *data,char memory_address, int slave_address)                                  //To choose input/output or alternative
{
    char error;
    *I2C_MSA_R[timer_number] = (slave_address <<1)+1 ;
    *I2C_MDR_R[timer_number] = memory_address ;
    *I2C_MCS_R[timer_number] |= 1UL << 0;
    *I2C_MCS_R[timer_number] |= 1UL << 1;
    
    while(*I2C_MCS_R[timer_number] & 1);
    error = *I2C_MCS_R[timer_number] & 0xE; 
    if(error)
      return error;
    
  return 0;
}
int I2C_Scan_Address(int timer_number, int number_of_address_bit)
{
    int error;
    float addresses_number = pow(2,number_of_address_bit)-1;
    for(int address = 1; address <= addresses_number;address++)
    {
          *I2C_MSA_R[timer_number] = (address <<1)+1 ;
          *I2C_MCS_R[timer_number] |= 1UL << 0;
          *I2C_MCS_R[timer_number] |= 1UL << 1;
          while(*I2C_MCS_R[timer_number] & 1);
          error = *I2C_MCS_R[timer_number] & 0xE; 
          
          if(error == 0)
            return address;
          
    }

}




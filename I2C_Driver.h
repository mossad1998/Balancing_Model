#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include <math.h> 





#ifndef __I2C_Driver_H__
#define __I2C_Driver_H__

//define of clk of each port
#define CLK_I2C0 	(0x01)
#define CLK_I2C1 	(0x02)
#define CLK_I2C2 	(0x04)
#define CLK_I2C3 	(0x08)




extern void CLK_Enable_I2C_Module(int timer_number);                            //Clock for Port
extern void I2C_Mode_Function(char type[10],int timer_number);                  //Unlock for port
extern void I2C_Speed_Kbps(int I2C_Speed,int timer_number,int Clk_Speed);                         //Enable or Disable Analog and Digital
extern char I2C_Write(int timer_number,int number_of_byte,char *data,char memory_address, int slave_address);          //General i/o or Alternative Function
extern int I2C_Scan_Address(int timer_number, int number_of_address_bit);          //General i/o or Alternative Function


#endif
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>




#ifndef __Interrupt_Driver_H__
#define __Interrupt_Driver_H__





extern void PIN_Edge_Level_Trigger(char port_name,int pin,char type[15]);           //Enable or Disable Analog and Digital
extern void PIN_Both_Edge_Trigger(char port_name,int pin,char type[10]);           //Enable or Disable Analog and Digital
extern void PIN_Rising_Falling_Trigger(char port_name,int pin,char type[10]);           //Enable or Disable Analog and Digital
extern void PIN_Clear_Interrupt(char port_name,int pin);           //Enable or Disable Analog and Digital
extern void PIN_Unmask(char port_name,int pin);           //Enable or Disable Analog and Digital
extern void Interrupt_Priority(volatile uint32_t * priority_R,int bits,int priority);           //Enable or Disable Analog and Digital
extern void Interrupt_Enable(volatile uint32_t * Interrupt_Enable_R,int bits);           //Enable or Disable Analog and Digital
extern bool PIN_Interrupt_Flag(char port_name,int pin);           //Enable or Disable Analog and Digital

extern void UART_Unmask(int UART_module,char type[3]);           //Enable or Disable Analog and Digital
extern bool UART_Interrupt_Flag(int UART_module,char type[3]);           //Enable or Disable Analog and Digital
extern void UART_Clear_Interrupt(int UART_module,char type[3]);           //Enable or Disable Analog and Digital

extern void GPTM_Unmask(int timer_number,char type);           //Enable or Disable Analog and Digital
extern bool GPTM_Interrupt_Flag(int timer_number,char type);           //Enable or Disable Analog and Digital
extern void GPTM_Clear_Interrupt(int timer_number,char type);           //Enable or Disable Analog and Digital


#endif
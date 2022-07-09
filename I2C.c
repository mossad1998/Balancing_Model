// File: I2C.c
// Title:       I2C Driver for TM4C123GH6PM
// Description: Implements I2C using CMSIS. At the moment, only I2C module 1 is implemented.
//              The clock speed (SCL) is 100 KHz
//
//              Functions:
//              I2Cx_MasterOpen
//              I2Cx_WriteData
//              I2Cx_ReadData
//              Where 'x' is the module number. For example, I2C module 1 is I2C1_functionName
//
//              Pinout:
//              SCL     SDA     Module
//              =======================
//              PA6     PA7     I2C1
//
// Author:      William Huang
// Date:        2016/12/10
// Revision:    2016/12/10 - First bring-up
// Bugs:        None at the moment.
// 
//  
#include "tm4c123gh6pm.h"
#include "I2C.h"

// void I2C1_MasterOpen(void)
// Opens I2C Module 1 with clock speed of 100 kHz assuming bus speed is 16 MHz
// PA6 - I2C1 SCL 
// PA7 - I2C1 SDA
void I2C1_MasterOpen(void)
{
    // Enable I2C Module 1 Clock
    SYSCTL_RCGCI2C_R |= (1U << 1);
    while(!(SYSCTL_RCGCI2C_R & (1U << 1)));
    
    // Enable GPIO A Clock
    SYSCTL_RCGCGPIO_R |= (1U << 0);
    while(!(SYSCTL_RCGCGPIO_R & (1U << 0)));
    
    // Enable alternate function on PA6, PA7
    // Port Control set to I2C function
    // and digital enable PA6, PA7
    GPIO_PORTA_AFSEL_R    |= (1U << 6) | (1U << 7);
    GPIO_PORTA_PCTL_R     |= (3U << 24) | (3U << 28);
    GPIO_PORTA_DEN_R      |= (1U << 6) | (1U << 7);
    
    // SDA Line requires to be open collector
    GPIO_PORTA_ODR_R      |= (1U << 7);
    
    // I2C1 Master Function Enable
    I2C1_MCR_R = 0x00000010;
    
    // Set clock speed to 100kHz
    // System clock is 16 MHz
    // TPR  = System Clock / (( 2 * (SCL_LP + SCL_HP) * SCL_CLK ) - 1)
    //      = (16 000 000) / (( 2 * (6 + 4) * 100 000) - 1)
    //      = 7
    I2C1_MTPR_R = 0x00000007;
    
}

// void I2C1_BeginTransmission(uint8_t slaveAddress, uint8_t rs)
// Set's the slave's address into Master Slave Address register
// uint8_t slaveAddress : address of slave
// uint8_t rs : receive or send bit.
//              0 = Transmit
//              1 = Receive
static void I2C1_BeginTransmission(uint8_t slaveAddress, uint8_t rs)
{

    I2C1_MSA_R = (slaveAddress << 1) + rs;   
}

// static uint8_t I2C1_WriteByte(uint8_t data, uint8_t start, uint8_t run, uint8_t stop)
// Sends a byte to the slave device.
// uint_8t data  : data to send to slave device. Can be actualy payload data or register address
// uint8_t start : 
// uint8_t run   :
// uint8_t stop  :
// return: uint8_t return value. 0 = no error, 1 = error error has occured
static uint8_t I2C1_WriteByte(uint8_t data, uint8_t start, uint8_t run, uint8_t stop)
{
    uint8_t error;
    I2C1_MDR_R = data;
    
    // If start bit sent, check if I2C Bus for busy bit
    // If busy, wait until it is busy
    if(start)
    {
        while(I2C1_MCS_R & 0x40);
    }
    
    I2C1_MCS_R = ( (run << 0) | (start << 1) | (stop << 2) );
    
    while(I2C1_MCS_R & 0x01);
    
    error = (I2C1_MCS_R & 0x02) >> 1;
    printf("Error is : %d", error);
    
    return error;
}

// uint8_t I2C1_WriteData(uint8_t slaveAddress, uint8_t regAddress, uint8_t data)
// uint8_t slaveAddress : address of the slave device
// uint8_t regAddress   : address of the register to write the data to
// uint8_t data         : data to write to the register
// return: uint8_t return value. 0 = no error. 1 = error while setting register address, 2 = error while writing data to register address
uint8_t I2C1_WriteData(uint8_t slaveAddress, uint8_t regAddress, uint8_t data)
{
    uint8_t error = 0;
    I2C1_BeginTransmission(slaveAddress, 0);        //  Set slave address to write to
    error = I2C1_WriteByte(regAddress, 1, 1, 0);    //  Set register address to write to
    if(error != 0)
    {
        error = 1;
        return error;
    }
    
    error = I2C1_WriteByte(data, 0, 1, 1);          //  Send data to specified register address of slave device 
        if(error != 0)
    {
        error = 2;
        return error;
    }
    
    return error;
}

// uint8_t I2C1_ReadData(uint8_t slaveAddress, uint8_t regAddress, uint8_t *data)
// uint8_t slaveAddress : address of the slave device
// uint8_t regAddress   : address of the register to write the data to
// uint8_t *data        : pointer to where to store data to
// return: uint8_t return value. 0 = no error. 1 = error while setting register address, 2 = error while writing data to register address
uint8_t I2C1_ReadData(uint8_t slaveAddress, uint8_t regAddress, uint8_t *data)
{
    uint8_t error = 0;
    I2C1_BeginTransmission(slaveAddress, 1);        //  Set slave address to read from
    error = I2C1_WriteByte(regAddress, 1, 1, 1);    //  Set register address to read from
    if(error != 0)
    {
        error = 1;
        return error;
    }
    *data = I2C1_MDR_R;
    return error;
}
#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void I2C1_MasterOpen(void);
uint8_t I2C1_WriteData(uint8_t slaveAddress, uint8_t regAddress, uint8_t data);
uint8_t I2C1_ReadData(uint8_t slaveAddress, uint8_t regAddress, uint8_t *data);

#endif
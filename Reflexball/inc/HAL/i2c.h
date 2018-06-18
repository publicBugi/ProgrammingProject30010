#ifndef _I2C_H
#define _I2C_H

#include "stm32f30x_conf.h"
#include "30010_io.h"


void I2C_Write(uint16_t address, uint8_t reg, uint8_t val);
void I2C_Read(uint16_t address, uint8_t reg, int8_t* vals, uint8_t n);
void I2C_init();






#endif

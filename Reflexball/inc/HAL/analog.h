#ifndef _ANALOG_H
#define _ANALOG_H

#include "stm32f30x_conf.h"

void initAnalog();
uint16_t readAnalog(char channel);
uint16_t analogRand();
void initDACNoise();
uint16_t DACRand();
#endif

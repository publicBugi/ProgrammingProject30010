#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f30x_conf.h"


void initGPIO();
void initLED();
void SetLed(char R, char G, char B);
uint8_t readJoystick();
void initAnalog();
uint16_t readAnalog(char channel);
uint16_t analogRand();
#endif

#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f30x_conf.h"


void Ini();

void IniJoy() ;
void IniLED();
void SetLed(char R, char G, char B);
uint8_t readJoystick();
#endif

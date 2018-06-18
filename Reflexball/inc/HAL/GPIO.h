#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f30x_conf.h"
#include "i2c.h"

void initGPIO();
void initLED();
void SetLed(char R, char G, char B);
void UpdateRGB(int playerHP);
uint8_t readJoystick();
void initAnalog();
uint16_t readAnalog(char channel);
uint16_t analogRand();
void initJoystick();
int32_t readRoll(uint8_t Average, uint8_t Sensitivity);
#endif

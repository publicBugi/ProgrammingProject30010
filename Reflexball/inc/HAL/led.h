#ifndef _LED_H
#define _LED_H
#include "30010_io.h"
#include "stm32f30x_conf.h"

void initLED();
void SetLed(char R, char G, char B);
void UpdateRGB(int playerHP);

#endif

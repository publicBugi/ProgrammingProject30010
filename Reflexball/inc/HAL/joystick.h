#ifndef _JOYSTICK_H
#define _JOYSTICK_H
#include "30010_io.h"
#include "stm32f30x_conf.h"

void initJoystick();

uint8_t readJoystick();

#endif

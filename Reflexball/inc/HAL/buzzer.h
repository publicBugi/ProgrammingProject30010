#ifndef _BUZZER_H
#define _BUZZER_H

#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "timer.h"
void initBuzzer();
void setFreq(uint16_t freq);
void playSound(uint16_t freq, uint8_t duration);
#endif

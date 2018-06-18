
#ifndef _TIMER_H_
#define _TIMER_H_

#include "30010_io.h"


struct time {
	uint32_t time_hseconds;
	uint8_t time_sec;
	uint8_t time_min;
	uint8_t time_hour;
	uint8_t change;
};

volatile struct time clk;

void TIM15_IRQHandler(void);
void initTime(volatile struct time *clk);
void incrementTime(volatile struct time *clk);
void wait(uint32_t delay);
void initInterrupt();

#endif




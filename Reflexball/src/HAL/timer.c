#include "timer.h"

void wait(uint32_t delay){
    uint32_t prevTime = clk.time_hseconds;
    while (clk.time_hseconds - prevTime < delay){}
}


void initTime(volatile struct time *clk) {
	clk->time_hseconds = 0;
	clk->time_sec = 0;
	clk->time_min = 0;
	clk->time_hour = 0;
	clk->change = 1;
}

void incrementTime(volatile struct time *clk) {
    ++clk->time_hseconds;
	clk->time_sec = (clk->time_hseconds / 100);
	clk->time_min = (clk->time_sec / 60);
	clk->time_hour = clk->time_min / 60;
	clk->change = 1;
}

void TIM1_BRK_TIM15_IRQHandler(void) {
	// Interrupt function!
	incrementTime(&clk);
	TIM15->SR &= ~0x0001; // End the interrupt.
	}

void initInterrupt(){
    RCC->APB2ENR |= RCC_APB2Periph_TIM15;

    TIM15->CR1 = 0x0000; // Disable Timer
    TIM15->ARR = 63999; // Auto Reload Value
    TIM15->PSC = 9;     // Prescaler value
    TIM15->DIER |= 0x0001; // Enable timer interrupt

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

    TIM15->CR1 |= 0x0001; // Enable timer
}




// TIMER 2 INTERRUPT
//void initInterrupt(){
//	RCC->APB1ENR |= RCC_APB1Periph_TIM2; 	// Clock line for timer 2
//    TIM2->CR1 = 0x00000001; 				// Configure [0 0 0 0 UIF 0 CKD ARPE CMS DIR OPM UDIS CEN]
//    TIM2->ARR = 0x0009C3FF;					// Relead Value = 63999 = 1/100 Second.
//    TIM2->PSC = 0x00000000;					// Preset = 0;
//
//    TIM2->DIER |= 0x0001;					// Timer 2 Interrupts Enabled
//    NVIC_SetPriority(TIM2_IRQn, 0);
//    NVIC_EnableIRQ(TIM2_IRQn);
//}

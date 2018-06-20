#include "timer.h"
/*
 * TIMER MODULE
 * Description: Contains functions to generate a 100 Hz interrupt to maintain time.
 * Uses a Global Volatile variable "globalTime" to store time in 1/100th of a second.
 */


/* Developer    : Hørdur Andreasen
 * Description  : Configure TIMER 15 to 100 Hz interrupt.
 * Argument     : None
 * Return value : Void
 */
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

/* Developer    : Hørdur Andreasen
 * Description  : Hardware Interrupt, Increments globalTIme by one. Updates at 100 Hz.
 * Argument     : Void
 * Return value : Void
 */
void TIM1_BRK_TIM15_IRQHandler(void) {
	// Interrupt function!
    globalTime++;
	TIM15->SR &= ~0x0001; // End the interrupt.
}

/* Developer    : Hørdur Andreasen
 * Description  : Hardware Interrupt, Increments globalTIme by one. Updates at 100 Hz.
 * Argument     : Void
 * Return value : Void
 */
void wait(uint32_t delay){
    uint32_t prevTime = globalTime;
    while (globalTime - prevTime < delay){}
}



#ifndef _TIMER_H_
#define _TIMER_H_

/*
 * TIMER MODULE
 * Description: Contains functions to generate a 100 Hz interrupt to maintain time.
 * Uses a Global Volatile variable "globalTime" to store time in 1/100th of a second.
 */

#include "30010_io.h"

// Global Variable Necessary. Cannot enter Hardware IRQ handler without it.
volatile uint32_t globalTime;

/* Developer    : Hørdur Andreasen
 * Description  : Configure TIMER 15 to 100 Hz interrupt.
 * Argument     : None
 * Return value : Void
 */
void initInterrupt();

/* Developer    : Hørdur Andreasen
 * Description  : Hardware Interrupt, Increments globalTIme by one. Updates at 100 Hz.
 * Argument     : Void
 * Return value : Void
 */
void TIM1_BRK_TIM15_IRQHandler(void);

/* Developer    : Hørdur Andreasen
 * Description  : Hardware Interrupt, Increments globalTIme by one. Updates at 100 Hz.
 * Argument     : Void
 * Return value : Void
 */
void wait(uint32_t delay);


#endif




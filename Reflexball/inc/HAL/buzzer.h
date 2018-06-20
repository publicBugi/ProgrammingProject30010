#ifndef _BUZZER_H
#define _BUZZER_H

#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "timer.h"


/* Developer    : Hørdur Andreasen
 * Description  : Configure TIMER 2 to Square wave with 50% duty cycle. Used for Piezo Buzzer
 * Argument     : None
 * Return value : Void
 */
void initBuzzer();

/* Developer    : Hørdur Andreasen
 * Description  : Set frequency of piezo.
 * Argument     : Frequency
 * Return value : Void
 */
void setFreq(uint16_t freq);

/* Developer    : Hørdur Andreasen
 * Description  : Play a given frequency, for the given duration.
 * Argument     : Frequency, Duration
 * Return value : Void
 */
void playSound(uint16_t freq, uint8_t duration);
#endif

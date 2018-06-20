#ifndef _ANALOG_H
#define _ANALOG_H

#include "stm32f30x_conf.h"

/* Developer    : Hørdur Andreasen
 * Description  : Configure ADC + Pins. 1 Floating input, and 2 Voltage Dividers.
 * Argument     : None
 * Return value : void
 */
void initAnalog();

/* Developer    : Hørdur Andreasen
 * Description  : Read from MBed Potentiometers.
 * Argument     : Selected Channel (1 or 2).
 * Return value : uint16_t Analog Value
 */
uint16_t readAnalog(char channel);

/* Developer    : Hørdur Andreasen
 * Description  : Read floating input; Outdated but kept for nostalgic reasons.
 * Argument     : None
 * Return value : uint16_t Random Analog Value
 */
uint16_t analogRand();

/* Developer    : Hørdur Andreasen
 * Description  : Configure DAC Registers to Generate Noise. Random values but the same every game.
 * Argument     : None
 * Return value : Void
 */
void initDACNoise();

/* Developer    : Hørdur Andreasen
 * Description  : Read Random Function from Digital to Analog Conversion; Generated through Linear Shift Register.
 * Argument     : None
 * Return value : uint16_t Random Value
 */
uint16_t DACRand();


#endif

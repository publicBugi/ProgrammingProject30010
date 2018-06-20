#ifndef _ACCEL_H
#define _ACCEL_H

#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "i2c.h"

/* Developer    : Hørdur Andreasen
 * Description  : Read the ROLL (X? Register) from the 3-Axis Accelerometer MMA7660.
 * Argument     : Average = How often to average (Keep low), Sensitivity = Reduce controller sensitivity)
 * Return value : uint32_t Average Roll.
 */
int32_t readRoll(uint8_t Average, uint8_t Sensitivity) ;

#endif

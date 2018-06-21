#ifndef _STRIKER_H_
#define _STRIKER_H_


#include "30010_io.h"
#include "i2c.h"

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2

struct striker_t {
	uint8_t currpos;            // Current Position
	uint8_t prevpos;            // Previous Position
	uint8_t strikersize;        // Striker size (10% of PuTTy Width)
	uint8_t strikerinc;         // Striker Increments (Size/5)
};

/* Developer    : Hørdur Andreasen
 * Description  : Update Striker based on readRoll(). Keep within Bounds + Deadzone.
 * Argument     : GameArray (Update striker collision), Striker (update Striker position)
 * Return value : Void
 */
void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker);



 #endif

#ifndef _STRIKER_H_
#define _STRIKER_H_


#include "30010_io.h"
#include "i2c.h"

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2

struct striker_t {
	uint8_t currpos;
	uint8_t prevpos;
	uint8_t strikersize;
	uint8_t strikerinc;
	uint8_t pwrFLAGS;
};

void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker);



 #endif

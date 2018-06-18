#ifndef _COLLISION_H_
#define _COLLISION_H_


#include "30010_io.h"
#include "bricks.h"
#include "striker.h"
#include "ball.h"
#include "ansi.h"

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2


char* CollisionDetect(uint8_t gameArray[putHeight][putWidth], struct ball_t *ball);


void BallHitStricker(int k);

 #endif


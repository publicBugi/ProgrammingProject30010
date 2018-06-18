#ifndef _GAME_H_
#define _GAME_H_

#include "30010_io.h"
#include "vectortrig.h"
#include "timer.h"
#include "GPIO.h"
#include "striker.h"
#include "ball.h"
#include "collision.h"
#include "powerup.h"
#include "bricks.h"

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2
#define maxBricks 100






uint8_t initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime, uint8_t *brickHeight, uint8_t *brickWidth);


uint8_t runGame(uint8_t *level, uint16_t *PlayerScore, char Graph[512] , char LCDData[4][128]);


 #endif

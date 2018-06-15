#include "vectortrig.h"
#include "30010_io.h"
#include "timer.h"
#include "GPIO.h"

#ifndef _GAME_H_
#define _GAME_H_

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2
#define maxBricks 100

struct ball_t {
    struct vector_t PrevPos, NextPos, DirVec;
    uint16_t DegreeIndex;
};

struct pwrUp {
    uint8_t posX, posY;
    uint8_t alive;
    uint8_t enable;
};

struct brick_t {
    uint8_t posX, posY, MaxHP, currHP, pwrUP;
};

struct striker_t {
	uint8_t currpos;
	uint8_t prevpos;
	int32_t currAccel;
	uint8_t strikersize;
	uint8_t strikerinc;
};

uint8_t initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime, uint8_t *brickHeight, uint8_t *brickWidth);
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);
void updateBall(struct ball_t *ball, uint8_t velMod);
void drawBall(struct ball_t *ball);
void updateBallSpeed(struct ball_t *ball, int8_t velMod);
void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker);
uint8_t runGame(uint8_t *level, uint16_t *PlayerScore);
char* CollisionDetect(uint8_t gameArray[putHeight][putWidth], struct ball_t *ball);
void BallHitStricker(int k);
void drawBox(struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth);
void getStrikerPosition(struct striker_t *striker);
 #endif

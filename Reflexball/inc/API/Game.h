#include "vectortrig.h"
#include "30010_io.h"
#include <stdlib.h>
#include "timer.h"

#ifndef _GAME_H_
#define _GAME_H_

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2
#define maxBricks 40

struct ball_t {
    struct vector_t PrevPos, NextPos, DirVec;
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
	uint8_t strikersize;
	uint8_t strikerinc;
};

void initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime);
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);
void updateBall(struct ball_t *ball, uint8_t velMod);
void drawBall(struct ball_t *ball);
void updateBallSpeed(struct ball_t *ball, int8_t velMod);
void updateStriker(char gameArray[putHeight][putWidth], struct striker_t *striker, uint8_t position);
uint16_t runGame(uint8_t *level);
char* CollisionDetect(uint8_t gameArray[putHeight][putWidth], struct ball_t *ball);
void BallHitStricker(int k);
void drawBox(struct brick_t *brick);
/*void CountDown();
int CollisionDetect(struct ball_t *ball, struct box_t *box);
void UpdateBallAngle();
void UpdateBallSpeed();
void SpawnPowerup();
void updateStrikerPosition();
void UpdatePowerup();
void DrawPowerup(); */
 #endif

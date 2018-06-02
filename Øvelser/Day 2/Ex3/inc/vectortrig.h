#include "lut.h"
#include <stdio.h>
#include "ansi.h"

#ifndef _VECTORTRIG_H_
#define _VECTORTRIG_H_

struct vector_t  {
    int32_t x, y;

};

struct ball_t {
    struct vector_t PosVec, VelVec;
};

int32_t getSin(int degree);
int32_t getCos(int index);
void initVector(struct vector_t *v, int32_t x, int32_t y);
void printVector(struct vector_t *v);
void rotateVector(struct vector_t *v, int index);
void translateVector(struct vector_t *v, int32_t x, int32_t y);
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);
void updateBall(struct ball_t *ball, int32_t k);
int32_t To2d14(int natval, int decval);
void drawBall(struct ball_t *ball);
 #endif

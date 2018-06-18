#ifndef _BALL_H_
#define _BALL_H_


#include "30010_io.h"
#include "vectortrig.h"
#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2

// Ball
struct ball_t {
    struct vector_t PrevPos, NextPos, DirVec;
    uint16_t DegreeIndex;
};

// Initialize
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);

// Update functions
void updateBall(struct ball_t *ball, uint8_t velMod);
void updateBallSpeed(struct ball_t *ball, int8_t velMod);
void UpdateBallAngle(struct ball_t *ball, uint8_t gameArray[putHeight][putWidth]);

// VISUAL
void drawBall(struct ball_t *ball);

#endif

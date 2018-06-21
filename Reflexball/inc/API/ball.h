#ifndef _BALL_H_
#define _BALL_H_


#include "30010_io.h"
#include "vectortrig.h"
#include "game.h"
#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2

// Ball
struct ball_t {
    struct vector_t PrevPos, NextPos, DirVec;
    int16_t DegreeIndex;
};

// Initialize
/* Developer    : Hørdur Andreasen
 * Description  : Initialize instance of ball at position given by Arguments, with given speed by arguments.
 * Argument     : Ball, Position, Velocity.
 * Return value : Void
 */
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);

// Update functions
/* Developer    : Hørdur Andreasen
 * Description  : Update ball position; Set new to previous. Calculate new.
 * Argument     : Ball, VelMod.
 * Return value : Void
 */
void updateBall(struct ball_t *ball, uint8_t velMod);


void UpdateBallAngle(struct ball_t *ball, uint8_t gameArray[putHeight][putWidth], uint8_t TypeOfHit);

// VISUAL

/* Developer    : Hørdur Andreasen
 * Description  : Draw Ball; Remove old position, draw new position.
 * Argument     : Ball
 * Return value : Void
 */
void drawBall(struct ball_t *ball);

#endif

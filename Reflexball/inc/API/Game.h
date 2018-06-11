
#ifndef _GAME_H_
#define _GAME_H_
struct ball_n {
    struct vector_t Position, NextPosition, DirectVector;
};

struct pwrUp {
    int posX, posY;
    int alive = 0;
    int enable = 0;
};

struct brick {
    int posX, posY, MaxHP, pwrUP, CurrentHP ;
};

void GenerateGameArray();//char gameArray[][][], struct brick BrickArray, struct striker *Striker, int *Level, int *DifficultyTime
void initBall();//struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy
void updateBall();//struct ball_t *ball, int32_t k)
void drawBall(struct ball_t *ball);
void CountDown();
int CollisionDetect();//struct ball_t *ball, struct box_t *box
void UpdateBallAngle();
void UpdateBallSpeed();
void SpawnPowerup();
void updateStrikerPosition();
void UpdatePowerup();
void DrawPowerup();
 #endif

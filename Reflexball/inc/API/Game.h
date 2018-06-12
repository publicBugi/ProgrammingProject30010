
#ifndef _GAME_H_
#define _GAME_H_
struct ball_n {
    struct vector_t PrevPos, NextPos, DirVec;
};

struct pwrUp {
    int posX, posY;
    int alive;
    int enable;
};

struct brick_t {
    int posX, posY, MaxHP, currHP, pwrUP;
};

struct striker_t {
	int pos;
}

void initGameArray(char gameArray[][], struct brick_t brickArray[], struct striker_t *Striker, int *Level, int *DifficultyTime); 
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy);
void updateBall(struct ball_t *ball, uint8_t velMod);
void drawBall(struct ball_t *ball);
void updateBallSpeed(struct ball_t *ball, int8_t velMod);

/*void CountDown();
int CollisionDetect(struct ball_t *ball, struct box_t *box);
void UpdateBallAngle();
void UpdateBallSpeed();
void SpawnPowerup();
void updateStrikerPosition();
void UpdatePowerup();
void DrawPowerup(); */
 #endif

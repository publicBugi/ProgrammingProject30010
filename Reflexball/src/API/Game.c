#include "vector.h"

// Game Array [PuTTyWidth] [PuTTyHeight].
// 0 = No Collission
// 1 = Wall
// 2 = Striker 1
// 3 = Striker 2
// 4 = Striker 3
// 5 = Striker 4
// 6 = Striker 5

void initGameArray(char gameArray[][], struct brick_t brickArray[], struct striker_t *Striker, int *Level, int *DifficultyTime) {
	// Size of Screen
	int MaxColI = sizeof(gameArray) / sizeof(gameArray[0][0]);
	int MaxRowI = sizeof(gameArray) / MaxColI;
	
	// Generate Walls at edges
	for (int i = 0; i < MaxRowI; i++){
		gameArray[i][0] = 1;
		gameArray[i][MaxColI-1] = 1;
	}
	for (int i = 0; i < MaxColI; i++){
		gameArray[0][i] = 1;
	}
	
	// Set Speed level of time (Define TimeConst)
	const int TimeConst = 500;
	DifficultyTime = TimeConst >> Level;
	
	// Brick Constants
	const int brickXLength = 3;
	const int brickYLength = 5;
	const int BricksPerRow = BrickXLength/MaxRowI + 1;
	const int RowsOfBricks = 5;
	
	// Generate bricks in brickarray and draw in gameArray.
	for (int r = 1; r <= RowsOfBricks + 1; r++) { 			// 4 Rows of Bricks
		for (int i = 6; i < BricksPerRow; i++) {		// 5 Columns of Bricks per row
			// Define indexed brick.
			int index = i*r;
			brickArray[index]->posX = 2+(i-6)*brickXLength;
			brickArray[index]->posY = 2+(r-1)*brickYLength;
			brickArray[index]->maxHP = 2*Level + rand() % 3;
			brickArray[index]->currHP = brickArray.maxHP;
			brickArray[index]->pwrUP = rand() % 2 == 0 ? 1 : 0; // Rand requires stdio.h; Alternative is analogread noise.
			// Draw the new brick.
			for (int RowI = brickArray[index]->posX; RowI < brickArray[index]->posX + brickXLenght; RowI++) {
				for (int ColI = brickArray[index]->posY; ColI < brickArray[index]->posY + brickYLength; ColI++){
					gameArray[RowI][ColI] = index;
				}
			}
		}
	}
		
	// Striker Initial Position
	Striker->pos = PuTTyWidth / 2 - 2;
	for (int i = 0; i < 5; i++){
		gameArray[PuTTyHeight - 5][Striker->pos + i] = i + 2;
	}
}

void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy) {
    /*ball->PosVec.x = XPos << 14;
    ball->PosVec.y = YPos << 14;
    ball->VelVec.x = Vx << 14;
    ball->VelVec.y = Vy << 14;
    ball->NextPos.x = 0;
    ball->NextPos.y = 0;*/

    initVector(&ball->PrevPos, XPos, YPos);
    initVector(&ball->VelVec, Vx, Vy);
    initVector(&ball->NextPos, 0, 0);
}

void updateBall(struct ball_t *ball, uint8_t velMod) {
	ball->PrevPos = ball->NextPos;
    ball->NextPos.x = ball->PrevPos.x + (ball->VelVec.x >> velMod);
    ball->NextPos.y = ball->PrevPos.y + (ball->VelVec.y >> velMod);
}

void drawBall(struct ball_t *ball){
    gotoXY(ball->PrevPos.x >> 14, ball->PrevPos.y >> 14);
	putchar(32);
    gotoXY(ball->NextPos.x >> 14, ball->NextPos.y >> 14);
    putchar(111);
}

void updateBallSpeed(struct ball_t *ball, int8_t velMod) {
	if (velMod < 0) {
		ball->VelVec.x >>= VelMod;
		ball->VelVec.y >>= VelMod;
	}
	else {
		ball->VelVec.x <<= VelMod;
		ball->VelVec.y <<= VelMod;
	}
}


/*
void CountDown(){

}

int CollisionDetect(struct ball_t *ball, struct box_t *box){
    char returnval = 0;
    if ((ball->PosVec.x >> 14) == box->x1) {
            returnval = 1;
            if (ball->VelVec.y > 0){
                    rotateVector(&ball->VelVec, -128);
            }
            else{
                    rotateVector(&ball->VelVec, 128);
            }
    }
    else if((ball->PosVec.x >> 14) == box->x2){
            returnval = 1;
            if (ball->VelVec.y > 0){
                    rotateVector(&ball->VelVec, 128);
            }
            else{
                    rotateVector(&ball->VelVec, -128);
            }
    }
    if ((ball->PosVec.y >> 14) == box->y1) {
            returnval = 1;
            if (ball->VelVec.x > 0){
                    rotateVector(&ball->VelVec, 128);
            }
            else{
                    rotateVector(&ball->VelVec, -128);
            }
    }
    else if ((ball->PosVec.y >> 14) == box->y2) {
            returnval = 1;
            if (ball->VelVec.x > 0){
                    rotateVector(&ball->VelVec, -128);
            }
            else{
                    rotateVector(&ball->VelVec, 128);
            }
    }
    return returnval;
}

void UpdateBallAngle() {

}

void UpdateBallSpeed() {

}

void SpawnPowerup() {

}

void updateStrikerPosition() {

}

void UpdatePowerup() {

}

void DrawPowerup(){

} */

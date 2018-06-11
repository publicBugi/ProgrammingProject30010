

void GenerateGameArray(char gameArray[][], struct brick brickArray[], struct striker *Striker, int *Level, int *DifficultyTime) {
	int MaxColI = sizeof(gameArray) / sizeof(gameArray[0][0]);
	int MaxRowI = sizeof(gameArray) / MaxColI;
	
	// Generate Walls
	for (int i = 0; i < MaxRowI; i++){
		gameArray[i][0] = 1;
		gameArray[i][MaxColI-1] = 1;
	}
	for (int i = 0; i < MaxColI; i++){
		gameArray[0][i] = 1;
	}
	
	// Set Speed level of time (Define TimeConst)
	DifficultyTime = TimeConst >> Level;
	
	// Brick Constants
	const brickXLength = 3;
	const brickYLength = 5;
	// Generate bricks in brickarray and draw in gameArray.
	for (int r = 1; r < 5; r++) { 			// 4 Rows of Bricks
		for (int i = 6; i < 6; i++) {		// 5 Columns of Bricks per row
			// Define indexed brick.
			brickArray[i*r].posX = 2+(i-6)*brickXLength;
			brickArray[i*r].posY = 2+(r-1)*brickYLength;
			brickArray[i*r].maxHP = 2*Level;
			brickArray[i*r].currHP = brickArray.maxHP;
			brickArray[i*r].pwrUP = rand() % 2 == 0 ? 1 : 0; // Rand requires stdio.h; Alternative is analogread noise.
			// Draw the new brick.
			for (int RowI = brickArray[i*r].posX; RowI < brickArray[i*r].posX + brickXLenght; RowI++) {
				for (int ColI = brickArray[i*r].posY; ColI < brickArray[i*r].posY + brickYLength; ColI++){
					gameArray[RowI][ColI] = i*r;
				}
			}
		}
	}
}

void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy) {
    ball->PosVec.x = XPos << 14;
    ball->PosVec.y = YPos << 14;
    ball->VelVec.x = Vx << 14;
    ball->VelVec.y = Vy << 14;

    /*initVector(ball->PosVec, int32_t XPos, int32_t YPos);
    initVector(ball->VelVec, int32_t Vx, int32_t Vy);*/
}

void updateBall(struct ball_t *ball, int32_t k) {
    ball->PosVec.x = ball->PosVec.x + (ball->VelVec.x >> k);
    ball->PosVec.y = ball->PosVec.y + (ball->VelVec.y >> k);
}

void drawBall(struct ball_t *ball){
    gotoXY(ball->PosVec.x >> 14, ball->PosVec.y >> 14);
    putchar(111);
}

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

}

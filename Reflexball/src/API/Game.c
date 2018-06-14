
#include "Game.h"




// Game Array [putWidth] [putHeight].
// 0 = No Collission
// 1 = Wall
// 2 = Striker 1
// 3 = Striker 2
// 4 = Striker 3
// 5 = Striker 4
// 6 = Striker 5

void initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime) {
	// Size of Screen
	const int MaxColI = putWidth;
	const int MaxRowI = putHeight;

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
	*DifficultyTime = TimeConst >> *Level;

	// Brick Constants
	const int brickHeight = 5;  // Brick size as function of Level! Increase difficulty!
	const int brickWidth = 20;
    uint8_t   Columns = (MaxColI-2)/brickWidth ;            // Fill out as many bricks as you can
    uint8_t   center = ((MaxColI-2) % brickWidth) / 2 + 1;  // Center the bricks; Not left align.
	const int Rows = 3;                                         // Rows should also be function of level.

	// Generate bricks in brickarray and draw in gameArray.
    int index = 7;
    for (int i = 0; i < Rows; i++){
        for (int r = 0; r < Columns; r++) {
            brickArray[index].posX = center + r*brickWidth;
			brickArray[index].posY = 5 + i*brickHeight;
			brickArray[index].MaxHP = 2*(*Level) + rand() % 3;
			brickArray[index].currHP = brickArray[index].MaxHP;
			brickArray[index].pwrUP = rand() % 2 == 0 ? 1 : 0; // Rand requires stdio.h; Alternative is analogread noise.
            for (int x = 0; x < brickWidth; x++){
                for(int y = 0; y < brickHeight; y++) {
                    gameArray[brickArray[index].posY + y][brickArray[index].posX + x] = index;
                }
			}
			index++;
        }
    }

	// Striker Initial Position
	Striker->currpos = putWidth / 2 - (Striker->strikersize/2);
    // Generate a striker 10% of width, in 5 segments.
    uint8_t value = 2;
	for (uint8_t i = 0; i < Striker->strikersize; i += Striker->strikerinc){
        for (uint8_t s = 0; s < Striker->strikerinc; s++){
            gameArray[putStrikerPos][Striker->currpos + i + s] = value;
        }
        value++;
	}

	Level++;
}
// Initialize vectors.
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy) {
    /*ball->PosVec.x = XPos << 14;
    ball->PosVec.y = YPos << 14;
    ball->VelVec.x = Vx << 14;
    ball->VelVec.y = Vy << 14;
    ball->NextPos.x = 0;
    ball->NextPos.y = 0;*/
    //
    ball->DegreeIndex = 320;
    ball->BallDirectionUp = 1;
    initVector(&ball->PrevPos, XPos, YPos);
    // Initialize direction vector.
    //initVector(&ball->DirVec, Vx, Vy);
    ball->DirVec.y = getSin(ball->DegreeIndex);
    ball->DirVec.x = getCos(ball->DegreeIndex);
    initVector(&ball->NextPos, XPos, YPos);
}

// Update ball next XY-position.
void updateBall(struct ball_t *ball, uint8_t velMod) {
    // Set next positions to next position.
    ball->PrevPos = ball->NextPos;
    // Calculate next x position using direction vector (velMod divedes)
    ball->NextPos.x = ball->PrevPos.x + (ball->DirVec.x >> velMod);
    // Calculate next y position using direction vector (velMod divedes)
    if ((ball->NextPos.y) >> 14 < putStrikerPos) {
        ball->NextPos.y = ball->PrevPos.y + (ball->DirVec.y >> velMod);
    }
    else {
        ball->NextPos.y = (putStrikerPos - 1) << 14;

    }
}

// Draw ball in the PuTTY terminal.
void drawBall(struct ball_t *ball){
    // Goto previous xy position (shift 14 bit to the left as 18.14 type)
    gotoXY(ball->PrevPos.x >> 14, ball->PrevPos.y >> 14);
    // Draw space char.
	putchar(32);
	// Goto next xy position (shift 14 bit to the left as 18.14 type)
    gotoXY(ball->NextPos.x >> 14, ball->NextPos.y >> 14);
    // Draw ball char.
    putchar(111);
}

void updateBallSpeed(struct ball_t *ball, int8_t velMod) {
	if (velMod < 0) {
		ball->DirVec.x >>= velMod;
		ball->DirVec.y >>= velMod;
	}
	else {
		ball->DirVec.x <<= velMod;
		ball->DirVec.y <<= velMod;
	}
}

void updateStriker(char gameArray[putHeight][putWidth], struct striker_t *striker, uint8_t position){
    striker->prevpos = striker->currpos;
    striker->currpos = position;

    gotoXY(256-5, striker->prevpos);
    for (int i = 0; i < 5; i++){
            gameArray[256-5][striker->prevpos + i] = 0;
            putchar(32);
    }

    gotoXY(256-5, striker->currpos);
    for (int i = 0; i < 5; i++){
            gameArray[256-5][striker->currpos + i] = i;
            putchar(223);
    }


}


uint16_t runGame(uint8_t *level) {
    // Local Game Data
    struct brick_t brickArray[maxBricks] = { };			// Maintain control of all Bricks. (Position, Health and Powerup)
	uint8_t gameArray[putHeight][putWidth] = { { } };	// Matrix "Image" of data. Used for collision Detection. Init to zero.
	uint8_t DifficultyTime;
    uint8_t Score = 0;
    char* CollisionDectectReturnAddr;
    char WhatNextAfterBallCollision = 0;
	// Game Instances
	struct ball_t ball1;							// Ball	(Possibly multiple)
	struct striker_t striker;                       // Striker (Only one)
    striker.strikersize = putWidth/10;
    striker.strikerinc = striker.strikersize/5;

    // Clear screen.
    clrscr();
    // Game Array for Collision purposes.
	// Values in Array:
	// 0 	= Air / No Collision.
	// 1 	= Wall / Collision.
	// 2-6 	= Striker Segments
	// 7-256= Brick in BrickArray.

    // Generate map for current level (Used for collision detection)
	initGameArray(gameArray, brickArray, &striker, level, &DifficultyTime);

    initBall(&ball1, putWidth/2, putStrikerPos - 10, -1, -1);


	// Draw gameArray index
//	for (uint8_t i = 0; i < putHeight; i++){
//		for (uint8_t r = 0; r < putWidth; r++){
//			printf("%d", gameArray[i][r] % 10);
//		}
//		if (i != putHeight -1) {
//		      printf("\r\n");
//		}
//    }
    gotoXY(0,0);

    // Generate Walls at edges
    fgcolor(15);
    for (int i = 0; i < putWidth; i++){
		putchar(178);
	}
	for (int i = 1; i < putHeight; i++){
		putchar(178);
		gotoXY(putWidth, i);
		putchar(178);
	}

    const int brickHeight = 5;  // Brick size as function of Level! Increase difficulty!
	const int brickWidth = 20;

	for (int i = 7; i < maxBricks; i++) {
        if (brickArray[i].currHP != 0){
            drawBox(&brickArray[i]);
        }
	}

    fgcolor(8);
    gotoXY(striker.currpos, putStrikerPos);
	for (int i = 0; i < striker.strikersize; i++){
        putchar(223);
	}

    fgcolor(15);
    drawBall(&ball1);

    uint16_t BallTimeCnt = 0;

    //// START GAME ////
    uint8_t gameEnabled = 1;
    while (gameEnabled) {

        if (clk.change == 1)  { // Timer update 1/100th of a second.
	        //LCDTimeCnt++;
	        BallTimeCnt++;
	        //StrikerTimeCnt++;
	        clk.change = 0;
	    }
	    // Control ball speed.
        else if (BallTimeCnt == 2) {

            // Update ball next XY-position.
            updateBall(&ball1, 0);

            // Return the address of the functions that has to be called after CollissionDectect
            CollisionDectectReturnAddr = CollisionDetect(gameArray, &ball1);

            // If CollissionDectect has returned a address.
            if (CollisionDectectReturnAddr != 0) {

                // Call return address and return what to do next.
                WhatNextAfterBallCollision = ((char (*)(void)) CollisionDectectReturnAddr)();

                // If WhatNextAfterBallCollision =
                // 1: Update ball angle
                // 2: End game,
                switch(WhatNextAfterBallCollision) {
                    case 1:
                        UpdateBallAngle(&ball1);
                        break;
                    case 2:
                        gameEnabled = 0;
                        break;
                }

            }

            // Draw ball in PuTTY console.
            drawBall(&ball1);

            // Reset ball speed.
            BallTimeCnt = 0;
	    }




    }



    return Score;
}


void drawBox(struct brick_t *brick){
        const int brickHeight = 5;  // Brick size as function of Level! Increase difficulty!
        const int brickWidth = 20;
        fgcolor(brick->currHP);

        for (int y = 0; y < brickHeight; y++){
            gotoXY(brick->posX, brick->posY + y);
                for(int x = 0; x < brickWidth; x++) {
                    putchar(178);
            }
        }
}


char BallHitWall() {
gotoXY(40,40);
 printf("Ball will hit the border         ");
  return 1;
}

char BallHitBrick() {
gotoXY(40,40);
 printf("Ball will hit the bricks         ");
 return 1;
}

char BallHitStricker1(){
gotoXY(40,40);

 printf("Ball will hit the stricker 1");
  return 1;
}

char BallHitStricker2(){
gotoXY(40,40);

 printf("Ball will hit the stricker 2");
  return 1;
}

char BallHitStricker3(){
gotoXY(40,40);

 printf("Ball will hit the stricker 3");
  return 1;
}

char BallHitStricker4(){
gotoXY(40,40);

 printf("Ball will hit the stricker 4");
  return 1;
}

char BallHitStricker5(){
gotoXY(40,40);

 printf("Ball will hit the stricker 5");
  return 1;
}

char BallHitStricker6(){
gotoXY(40,40);

 printf("Ball will hit the stricker 6");
 return 1;
}

char BallOutOfBoundary(){
gotoXY(40,40);

 printf("END GAME!          ");
  return 1;
}

// Return 1 if ball hit boundary.
char BallHitBoundary(struct ball_t *ball) {
    int16_t x = (ball->NextPos.x >> 14);

    if (x == 0 || x == putWidth) {
        return 1;
    }

    return 0;
}

//// Return
//// 0 is up.
//// 1 is down.
//// 2 is right.
////3 is left.
//char BallDirection(struct ball_t *ball) {
//    int16_t x = (ball->DirVec.x >> 14);
//    int16_t y = (ball->DirVec.y >> 14);
//
//    // Ball direction is up.
//    if ((x == -1 && y == -1) || (x == 0 && y == -1) || (x == 1 && y == -1)) {
//        return 0;
//    }
//    // Ball direction is down.
//    else if ((x == -1 && y == 1) || (x == 0 && y == 1) || (x == 1 && y == 1)) {
//        return 1;
//    }
//    // Ball direction is right.
//    else if (x == 1 && y == 0) {
//        return 2;
//    }
//    // Ball direction is left.
//    else if (x == -1 && y == 0) {
//        return 3;
//    }
//    return -1;
//}


void UpdateBallAngle(struct ball_t *ball) {
   //  struct vector_t XY;
    //int32_t x = ball->DirVec.x >> 14;
    //int32_t y = (ball->DirVec.y >> 14)* -1;
    // Angle of attack i
    // Normal degree 'a' (angle of attack)
    // a = 360 degree - 90 degree - i (angle of attack)= 270 degree - i
    // Normal degree 'r' (angle of reflection)
    // r = 360 degree - 90 degree + a= 270 degree + (270 degree - i) = 2 * 270 degree - i= 540 degree - i = 180 degree - i
   // uint16_t AngleOfAttack = 384 - ball->DegreeIndex;
   // int AngleOfReflection = 128 + ball->DegreeIndex;
    //ball->DirVec.x = 1 << 14;
  //  ball->DirVec.y = 0 << 14;
   // rotateVector(&ball->DirVec, 512 - (ball->DegreeIndex)*2);
  // BallDirection(ball);

    if (BallHitBoundary(ball) == 1) {
         ball->DegreeIndex = 256 - (ball->DegreeIndex) & 0x1FF;
    }
    else {
        ball->DegreeIndex = 512 - (ball->DegreeIndex) & 0x1FF;
    }


    ball->DirVec.x = getCos(ball->DegreeIndex);
    ball->DirVec.y = getSin(ball->DegreeIndex);
/*
    if (ball->BallDirectionUp == 1) {
        ball->NextPos.y = ((ball->NextPos.y >> 14) + 1) << 14;
    }
    else {
        ball->NextPos.y = ((ball->NextPos.y >> 14) - 1) << 14;
    }

    ball->BallDirectionUp = ball->BallDirectionUp == 1 ? 0:1;*/
    //ball->NextPos.y = ((ball->NextPos.y >> 14) + 1) << 14;
    //ball->DirVec.y = getCos(64);
  //  Arccos(y2/x2 << 14);
}


// Detects collision.
// gameArray:
// 0 = Air
// 1 = Wall
// 2 = Striker 1
// 3 = Striker 2
// 4 = Striker 3
// 5 = Striker 4
// 6 = Striker 5
// 7 >=  = Bricks
char* CollisionDetect(uint8_t gameArray[putHeight][putWidth], struct ball_t *ball) {

    // Positions. ball->NextPos is shifted 14 to the left because it is 18.14.
    uint8_t xPos = ball->NextPos.x >> 14;
    uint8_t yPos = ball->NextPos.y >> 14;

    // Get game data from array.
    uint8_t gameData = gameArray[yPos][xPos];

    // Check type of collision.
    switch(gameData) {
        case 1: return BallHitWall;
        case 2: return BallHitStricker1;
        case 3: return BallHitStricker2;
        case 4: return BallHitStricker3;
        case 5: return BallHitStricker4;
        case 6: return BallHitStricker5;
        case 7: return BallHitStricker6;
    }


    if ((yPos < putStrikerPos) && (gameData == 0)) {
        return 0;
    }
    else if ((yPos >= putStrikerPos) && (gameData == 0)) {
         return BallOutOfBoundary;
    }
    else {
        return BallHitBrick;
    }
}
/*
void CountDown(){

}
//int CollisionDetect(struct ball_t *ball, struct box_t *box){
//    char returnval = 0;
//    if ((ball->PosVec.x >> 14) == box->x1) {
//            returnval = 1;
//            if (ball->VelVec.y > 0){
//                    rotateVector(&ball->VelVec, -128);
//            }
//            else{
//                    rotateVector(&ball->VelVec, 128);
//            }
//    }
//    else if((ball->PosVec.x >> 14) == box->x2){
//            returnval = 1;
//            if (ball->VelVec.y > 0){
//                    rotateVector(&ball->VelVec, 128);
//            }
//            else{
//                    rotateVector(&ball->VelVec, -128);
//            }
//    }
//    if ((ball->PosVec.y >> 14) == box->y1) {
//            returnval = 1;
//            if (ball->VelVec.x > 0){
//                    rotateVector(&ball->VelVec, 128);
//            }
//            else{
//                    rotateVector(&ball->VelVec, -128);
//            }
//    }
//    else if ((ball->PosVec.y >> 14) == box->y2) {
//            returnval = 1;
//            if (ball->VelVec.x > 0){
//                    rotateVector(&ball->VelVec, -128);
//            }
//            else{
//                    rotateVector(&ball->VelVec, 128);
//            }
//    }
//    return returnval;
//}



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

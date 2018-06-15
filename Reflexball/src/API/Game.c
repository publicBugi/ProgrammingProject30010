#include "Game.h"


// Initialize ball vectors.
void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy) {
    ball->DegreeIndex = 320;
    initVector(&ball->PrevPos, XPos, YPos);
    ball->DirVec.y = getSin(ball->DegreeIndex);
    ball->DirVec.x = getCos(ball->DegreeIndex);
    initVector(&ball->NextPos, XPos, YPos);
}

// Update ball next XY-position.
void updateBall(struct ball_t *ball, uint8_t velMod) {
    int testx =  ball->NextPos.x >> 14;
    int testy =  ball->NextPos.y >> 14;
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
       int testx2 =  ball->NextPos.x >> 14;
    int testy2 =  ball->NextPos.y >> 14;
}

// Update the velocity of the ball
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

//// STRIKER FUNCTIONS ////
// Updates and Draws striker position
void updateStriker(char gameArray[putHeight][putWidth], struct striker_t *striker){
    striker->prevpos = striker->currpos;


    uint8_t Acceleration = readRoll(20);
    if (Acceleration < 10 && Acceleration < -10) {
        Acceleration = 0;
    }

    striker->currpos = striker->currpos + Acceleration;

    if (striker->currpos < 1 || striker->currpos > (putWidth - striker->strikersize - 1)) {
        striker->currpos = striker->prevpos;
    }



    int temp = striker->currpos;
    fgcolor(0);
    gotoXY(striker->prevpos, putStrikerPos);
    for (int i = 0; i < striker->strikersize; i++){
            gameArray[putStrikerPos][striker->prevpos + i] = 0;
            putchar(32);
    }

    fgcolor(8);
    gotoXY( striker->currpos, putStrikerPos);
    uint8_t value = 2;
	for (uint8_t i = 0; i < striker->strikersize; i += striker->strikerinc){
        for (uint8_t s = 0; s < striker->strikerinc; s++){
            gameArray[putStrikerPos][striker->currpos + i + s] = value;
            putchar(223);
        }
        value++;
	}
}

// Get data from controller + fit to screen.
void getStrikerPosition(struct striker_t *striker) {
    // Turn control to striker into usable data.

    // HARDWARE RANGE; -90 to 90: 0 = No roll.
    // STRIKER RANGE; 1 to putWidth - 1
    int8_t Acceleration = readRoll(20);
    striker->currpos = striker->currpos + Acceleration;

    if (striker->currpos < 1 || striker->currpos > putWidth - 1 - striker->strikersize) {
        striker->currpos = putWidth / 2;
    }
}


//// BRICKS ////

// Kill brick.
void KillBrick(uint16_t Brickindex, char gameArray[putHeight][putWidth], struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth) {
    // Change game array of brick to 0 (air).
    for (int x = 0; x < *brickWidth; x++){
        for(int y = 0; y < *brickHeight; y++) {
            gameArray[brick->posY + y][brick->posX + x] = 0;
        }

    }

}

// Print brick counter
void PrintBrickCounter(uint16_t BrickCounter) {
        // Change color to default.
                            fgcolor(15);
    gotoXY(10,80);
    printf("Brick counter: %d  ", BrickCounter);
}


void drawBox(struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth){
        fgcolor(brick->currHP);

        for (int y = 0; y < *brickHeight; y++){
            gotoXY(brick->posX, brick->posY + y);
                for(int x = 0; x < *brickWidth; x++) {
                    putchar(178);
            }
        }
}



//// GAME LOOP AND INITI ///
uint8_t initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime, uint8_t *brickHeight, uint8_t *brickWidth) {
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
	DifficultyTime = TimeConst >> *Level;

	// Brick Values
	*brickHeight -= *Level;  // Brick size as function of Level! Increase difficulty!
	*brickWidth -= *Level*3;

    uint8_t   Columns = (MaxColI-2)/(*brickWidth) ;            // Fill out as many bricks as you can
    uint8_t   center = ((MaxColI-2) % (*brickWidth)) / 2 + 1;  // Center the bricks; Not left align.
	uint8_t Rows = 2 + *Level;                                         // Rows should also be function of level.

	// Generate bricks in brickarray and draw in gameArray.
    int index = 7;
    for (int i = 0; i < Rows; i++){
        for (int r = 0; r < Columns; r++) {
            brickArray[index].posX = center + r*(*brickWidth);
			brickArray[index].posY = 5 + i*(*brickHeight);
			brickArray[index].MaxHP = 2*(*Level) + analogRand() % 3;
			brickArray[index].currHP = brickArray[index].MaxHP;
			brickArray[index].pwrUP = analogRand() % 2; // Rand requires stdio.h; Alternative is analogread noise.
            for (int x = 0; x < (*brickWidth); x++){
                for(int y = 0; y < (*brickHeight); y++) {
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
	return index - 7;
}

// Run game. Return
// 0: If player died
// 1: If complete level.
uint8_t runGame(uint8_t *level, uint16_t *PlayerScore, char Graph[512] , char LCDData[4][128]) {
    // Local Game Data
    struct brick_t brickArray[maxBricks] = { };			// Maintain control of all Bricks. (Position, Health and Powerup)
	uint8_t gameArray[putHeight][putWidth] = { { } };	// Matrix "Image" of data. Used for collision Detection. Init to zero.
	uint8_t DifficultyTime;

    char WhatNextAfterBallCollision = 0;
    uint16_t Brickindex;

    uint16_t BrickCounter;


    uint8_t brickHeight = 5;
    uint8_t brickWidth = 20;
    char str1[128];
	// Game Instances
	struct pwrUp powerup;
	struct ball_t ball1;							// Ball	(Possibly multiple)
	struct striker_t striker;                       // Striker (Only one)
	char* CollisionDectectReturnAddr;
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

    // Generate map for current level (Used for collision detection). Return numbers of bricks created.
	BrickCounter = initGameArray(gameArray, brickArray, &striker, level, &DifficultyTime, &brickHeight, &brickWidth);

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
//    gotoXY(0,0);

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

    // Generate bricks.
	for (int i = 7; i < maxBricks; i++) {
        if (brickArray[i].currHP != 0){
            drawBox(&brickArray[i], &brickHeight, &brickWidth);
        }
	}

    // Generate stricker.
    fgcolor(8);
    gotoXY(striker.currpos, putStrikerPos);
	for (int i = 0; i < striker.strikersize; i++){
        putchar(223);
	}

    fgcolor(15);
    drawBall(&ball1);

    uint16_t BallTimeCnt = 0;
    uint16_t StrikerTimeCnt = 0;
    // Print brick counter;
    PrintBrickCounter(BrickCounter);

    gotoXY(90,80);
    printf("Level %d  ", *level);

        sprintf(str1, "Brick counter: %03d", BrickCounter);
        LCDWrite(LCDData, str1, 1);
        sprintf(str1, "Score: %03d", *PlayerScore);
        LCDWrite(LCDData, str1, 2);
        lcd_update(Graph, LCDData);
    //// START GAME ////
    uint8_t gameEnabled = 1;

    while (gameEnabled) {

        if (clk.change == 1)  { // Timer update 1/100th of a second.
	        //LCDTimeCnt++;
	        BallTimeCnt++;
	        StrikerTimeCnt++;

	        clk.change = 0;
	    }

	    // Control ball speed.
        if (BallTimeCnt == 2) {

            // Update ball next XY-position.
            updateBall(&ball1, 0);

            // Return the address of the functions that has to be called after CollissionDectect
            CollisionDectectReturnAddr = CollisionDetect(gameArray, &ball1);

            // If CollissionDectect has returned a address.
            if (CollisionDectectReturnAddr != 0) {

                // Call return address and return what to do next.
                WhatNextAfterBallCollision = ((char (*)()) CollisionDectectReturnAddr)();

                // If WhatNextAfterBallCollision =
                // 0: Ball out of boundary.
                // 1: Ball hit stricker or wall.
                // 2: Bal hit a brick.
                switch(WhatNextAfterBallCollision) {

                    // Ball out of boundary.
                    case 0:
                        // Stop game.
                        gameEnabled = 0;

                        // Return player died.
                        return 0;

                        break;

                    // Ball hit stricker or wall.
                    case 1:
                        UpdateBallAngle(&ball1, gameArray);
                        break;

                    // Ball hit brick
                    case 2:

                        // Get brick index.
                        Brickindex = gameArray[ball1.NextPos.y >> 14][ball1.NextPos.x >> 14];

                        // Calculate and set new ball angle.
                        UpdateBallAngle(&ball1, gameArray);

                        // Prevent brick hit point of being negative.
                        if (brickArray[Brickindex].currHP > 0) {

                            // Decrement brick hit points.
                            brickArray[Brickindex].currHP--;

                            // Change brick color.
                            drawBox(&brickArray[Brickindex], &brickHeight, &brickWidth);


                        }

                        // If hit points is zero kill the brick.
                        if (brickArray[Brickindex].currHP == 0) {
                            // Decrement brick counter.
                            BrickCounter--;

                            // Increase score.
                            *PlayerScore += brickArray[Brickindex].MaxHP;

                            // Kill brick.
                            KillBrick(Brickindex, gameArray, &brickArray[Brickindex], &brickHeight, &brickWidth);

                            // Print brick counter;
                            PrintBrickCounter(BrickCounter);


        sprintf(str1, "Brick counter: %03d", BrickCounter);
        LCDWrite(LCDData, str1, 1);
        sprintf(str1, "Score: %03d", *PlayerScore);
        LCDWrite(LCDData, str1, 2);
        lcd_update(Graph, LCDData);
                        }

                        // If all bricks are killed.
                        if (BrickCounter == 0) {
                            // Stop game.
                            gameEnabled = 0;

                            return 1;

                        }


                        break;
                }

            }


            // Draw ball in PuTTY console.
            drawBall(&ball1);

            // Reset ball speed.
            BallTimeCnt = 0;
	    }
	    if (StrikerTimeCnt == 2) {
           // updateStriker(gameArray, &striker);
            StrikerTimeCnt = 0;
	    }
                            // Change color to default.
                            fgcolor(15);




    }


   // level++;


}


char BallHitWall() {
gotoXY(40,100);
 printf("Ball will hit the border          ");
  return 1;
}

// Return type of hit.
char BallHitBrick() {
gotoXY(40,100);
 printf("Ball will hit the bricks           ");
 return 2;
}

char BallHitStricker1(){
gotoXY(40,100);

 printf("Ball will hit the stricker 1");
  return 1;
}

char BallHitStricker2(){
gotoXY(40,100);

 printf("Ball will hit the stricker 2");
  return 1;
}

char BallHitStricker3(){
gotoXY(40,100);

 printf("Ball will hit the stricker 3");
  return 1;
}

char BallHitStricker4(){
gotoXY(40,100);

 printf("Ball will hit the stricker 4");
  return 1;
}

char BallHitStricker5(){
gotoXY(40,100);

 printf("Ball will hit the stricker 5");
  return 1;
}

char BallHitStricker6(){
gotoXY(40,100);

 printf("Ball will hit the stricker 6");
 return 1;
}

char BallOutOfBoundary(){
gotoXY(40,100);

 printf("END GAME!                    ");
  return 1;
}


//void CountDown(char *numberArray[]){
//  // Start at 4 to make sure the first second is at least a full second
//  for (int i = 4; i > 0; i--) {
//    uint8_t clkSec = clk->time_sec;
//    while(clkSec == clk->time_sec){}
//    // For the first value of I, print 3
//    if (i==4) {
//      PrintOutTextArray(numberArray[3][][], *countDownX, *countDownY, 5, 8);
//    }
//    // Print the rest of the numbers, every time the time_sec changes
//    else{
//      PrintOutTextArray(numberArray[i][][], *countDownX, *countDownY, 5, 8);
//    }
//  }
//}
//void CountDown(char *numberArray[]){
//  // Start at 4 to make sure the first second is at least a full second
//  for (int i = 4; i > 0; i--) {
//    uint8_t clkSec = clk.time_sec;
//    while(clkSec == clk.time_sec){}
//    // For the first value of I, print 3
//    if (i==4) {
//      PrintOutTextArray(numberArray[3][][], *countDownX, *countDownY, 5, 8);
//    }
//    // Print the rest of the numbers, every time the time_sec changes
//    else{
//      PrintOutTextArray(numberArray[i][][], *countDownX, *countDownY, 5, 8);
//    }
//  }
//}


// gameArray:
// 0 = Air
// 1 = Wall
// 2 = Striker 1
// 3 = Striker 2
// 4 = Striker 3
// 5 = Striker 4
// 6 = Striker 5
// 7 >=  = Bricks
// Return
// 0: Direction of ball attack is up.
// 1: Direction of ball attack is down.
// 2: Direction of ball attack }is right.
// 3: Direction of ball attack is left.
// 4: Direction of ball attack is corner.
char DirectionOfBallAttack(uint8_t gameArray[putHeight][putWidth], struct ball_t *ball) {

    // Positions. ball->PrevPos is shifted 14 to the left because it is 18.14.
    uint16_t xPos = ball->PrevPos.x >> 14;
    uint16_t yPos = ball->PrevPos.y >> 14;

    struct vector_t Top, Bottom;
    struct vector_t Left, Right;
    uint16_t GameDataTop, GameDataBottom, GameDataLeft, GameDataRight;


    // Top postion.
    Top.x = xPos;
    Top.y = yPos - 1 >= 0 ? yPos - 1 : 0;

    // Bottom postion.
    Bottom.x = xPos;
    Bottom.y = yPos + 1 < putHeight ? yPos + 1 : putHeight - 1;

     // Left postion.
    Left.x = xPos - 1 >= 0 ? xPos - 1 : 0;
    Left.y = yPos;

     // Right postion.
    Right.x = xPos + 1 < putWidth ? xPos + 1 :0;
    Right.y = yPos;


    // Get game data from array.
    GameDataTop = gameArray[Top.y][Top.x];
    GameDataBottom = gameArray[Bottom.y][Bottom.x];
    GameDataRight = gameArray[Right.y][Right.x];
    GameDataLeft = gameArray[Left.y][Left.x];

     // TEMPEARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.
    if (GameDataRight == 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom == 0) {
           return 1;
   }

     // Check for up attack.
    if (GameDataRight == 0 && GameDataLeft == 0 && GameDataTop != 0  && GameDataBottom == 0) {
            return 0;
    }

    // Check for down attack.
    if (GameDataRight == 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom != 0) {
            return 1;
    }

    // Check for right attack.
    if (GameDataRight != 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom == 0) {
            return 2;
    }

    // Check for left attack.
    if (GameDataRight == 0 && GameDataLeft != 0 && GameDataTop == 0  && GameDataBottom == 0) {
            return 3;
    }

    // Ball hit a corner.
    return 4;
}



void UpdateBallAngle(struct ball_t *ball, uint8_t gameArray[putHeight][putWidth]) {
    char DirectionOfBallAttack_Var;

   // rotateVector(&ball->DirVec, 512 - (ball->DegreeIndex)*2);


    // Get direction of ball attack.
    DirectionOfBallAttack_Var = DirectionOfBallAttack(gameArray, ball);

    //
    switch(DirectionOfBallAttack_Var) {
          // Ball side attack is left or right.
         case 0 ... 1:
            ball->DegreeIndex = 512 - (ball->DegreeIndex) & 0x1FF;
            ball->DirVec.x = getCos(ball->DegreeIndex);
            ball->DirVec.y = getSin(ball->DegreeIndex);
            break;
          // Ball side attack is down or up.
        case 2 ... 3:
            ball->DegreeIndex = 256 - (ball->DegreeIndex) & 0x1FF;
            ball->DirVec.x = getCos(ball->DegreeIndex);
            ball->DirVec.y = getSin(ball->DegreeIndex);
            break;
        // Roate 180 degree.
        default:
            ball->DegreeIndex = 256 - (ball->DegreeIndex) & 0x1FF;
            ball->DirVec.x = getCos(ball->DegreeIndex);
            ball->DirVec.y = getSin(ball->DegreeIndex);

            ball->DegreeIndex = 512 - (ball->DegreeIndex) & 0x1FF;
            ball->DirVec.x = getCos(ball->DegreeIndex);
            ball->DirVec.y = getSin(ball->DegreeIndex);
    }

    // Update next ball position.
    ball->NextPos.y = ball->PrevPos.y + (ball->DirVec.y);
    ball->NextPos.x = ball->PrevPos.x + (ball->DirVec.x);


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


void spawnPowerup(struct pwrUp *powerup, struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth) {

    if (powerup->alive == 0) {
        powerup->alive = 1;
        powerup->posX = brick->posX + *brickWidth/2;
        powerup->posY = brick->posY + *brickHeight/2;
        powerup->enable = 0;
    }
}

void updatePowerup(struct pwrUp *powerup) {
    if (powerup->alive == 1) {
        if (powerup->posY == putHeight){
                powerup->alive = 0;
        }
        else {
                powerup->posY++;
        }
    }
}

void drawPowerup(struct pwrUp *powerup){
    if (powerup->alive == 1) {
        gotoXY(powerup->posX, powerup->posY);
        fgcolor(6);
        putchar('*');

    }
}



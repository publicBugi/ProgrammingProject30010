#include "Game.h"

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
	*DifficultyTime = TimeConst >> *Level;

	// Brick Values
	*brickHeight -= *Level;  // Brick size as function of Level! Increase difficulty!
	*brickWidth -= *Level*3;

    uint8_t   Columns = (MaxColI-2)/(*brickWidth) ;            // Fill out as many bricks as you can
    uint8_t   center = ((MaxColI-2) % (*brickWidth)) / 2 + 1;  // Center the bricks; Not left align.
	uint8_t Rows = 1 + *Level;                                         // Rows should also be function of level.

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


    uint8_t brickHeight = 6;
    uint8_t brickWidth = 30;
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
	   // if (powerup.alive) {
       //     updatePowerup(&pwrUp);
        //    drawPowerup(&pwrUp);
	   // }

	    // Control ball speed.
        if (BallTimeCnt == 4) {

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

                        //    // Spawn a powerup!
                         //   if (brickArray[Brickindex].pwrUP && pwrUp.alive == 0) {
                         //       spawnPowerup(&pwrUp, brickArray[Brickindex], &brickHeight, &brickWidth);
                          //  }



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

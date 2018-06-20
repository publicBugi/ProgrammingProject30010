#include "Game.h"

//// GAME LOOP AND INITI ///
uint8_t initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[100], struct striker_t *Striker, uint8_t *Level, uint8_t *DifficultyTime, uint8_t *brickHeight, uint8_t *brickWidth) {
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
			brickArray[index].MaxHP = 2*(*Level) + DACRand() % 3;
			brickArray[index].currHP = brickArray[index].MaxHP;
			brickArray[index].pwrUP =  DACRand() % 2; // Rand requires stdio.h; Alternative is analogread noise.
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
/**
  * Descripton: Determines which player won.
  * Argument:  MaxPlayer: Number of players, PlayerScore1: Player one score, PlayerScore2: Player two socre
  * Return value: None.
  */
// Print end status.
void PrintVictory(uint8_t MaxPlayer, uint16_t PlayerScore1, uint16_t PlayerScore2) {
    char str1[19];

    // Clear screen.
    clrscr();
    // Write ready text.
    gotoXY(20,40);
    fgcolor(15);

		// If one player.
		if (MaxPlayer == 1) {
			PrintFromASCII("PLAYER 1 WINS",60,20);
		}
    // If two player.
    else if (MaxPlayer == 2) {

       if (PlayerScore1 > PlayerScore2) {
            //sprintf(str1, "GET READY PLAYER %d", i);
              PrintFromASCII("PLAYER 1 WINS",60,20);
        }
       else if (PlayerScore1 < PlayerScore2) {
            //sprintf(str1, "GET READY PLAYER %d", i);
              PrintFromASCII("PLAYER 2 WINS",60,20);
        }
       else if (PlayerScore1 == PlayerScore2) {
            //sprintf(str1, "GET READY PLAYER %d", i);
              PrintFromASCII("BOTH PLAYERS WIN",60,20);
        }

    }
		// Wait 3 seconds.
		wait(300);
}
/**
  * Descripton: Keeps track of player score and controlles creation of new levels with increasing degree of difficulty.
  * Argument:  MaxPlayer: Number of players.
  * Return value: None.
  */
void StartGameLoop(uint8_t MaxPlayer) {
  	char Graph[512] = {0};						// Graph: Pixel graph to push to LCD Screen (Redundant?)
	char LCDData[4][128] = { {0} };					// LCDData: Four lines of 128 Pixel lines. LCD Screen.

	// Input Variables
    char str1[19];
  	// Game data
	uint8_t level;
    uint16_t PlayerScore = 0;
    uint16_t PlayerScore1 = 0;
    uint16_t PlayerScore2 = 0;
    uint8_t ResultsFromGame = 1;

    level = 1;// Level counter; Controls game difficulty. Starts at level 1.



    // Run game and return
    // 0: If player died
    // 1: If complete level.
    for (int i = 1; i <= MaxPlayer; i++) {
        // Clear screen.
        clrscr();

        fgcolor(15);

        // Write ready text.
        gotoXY(10,40);

        sprintf(str1, "GET READY PLAYER %d", i);

        PrintFromASCII(str1,60,20);

        wait(200);

        // Run game until player die.
        while (ResultsFromGame == 1) {

            ResultsFromGame = runGame(&level, &PlayerScore, Graph, LCDData);

            // Run game and return
            // 0: If player died
            // 1: If complete level.
            if (ResultsFromGame == 1) {

                // Clear screen.
                clrscr();

                fgcolor(15);

                // Write ready text.
                gotoXY(10,40);

                PrintFromASCII("GAME LEVEL COMPLETED.",60,20);

                wait(200);

                // Increase level.
                level++;
            }

        }

        // Reset for 2 player (if 2 players).
        ResultsFromGame = 1;


        if (i == 1) {
                PlayerScore1 = PlayerScore;
        }
        else if (i == 2) {
                PlayerScore2 = PlayerScore;
        }
        // Reset score.
        PlayerScore = 0;

    }

    // Print victory.
    PrintVictory(MaxPlayer, PlayerScore1, PlayerScore2);
}
/**
  * Descripton: This function is the game kernel. This function calculate ball position, calls collision detection,
	*							update LCD, generate game world, update powerup.
  * Argument:  level: Level of game world, PlayerScore: Score of player, Graph[512]: LCD 512 bytes data, LCDData[4][128]: LCD Line array.
  * Return value: Return 0 (player died) or 1 (player completed level)
  */
// Run game. Return
// 0: If player died
// 1: If complete level.
uint8_t runGame(uint8_t *level, uint16_t *PlayerScore, char Graph[512] , char LCDData[4][128]) {
    // Local Game Data
    struct brick_t brickArray[maxBricks] = { };			// Maintain control of all Bricks. (Position, Health and Powerup)
	uint8_t gameArray[putHeight][putWidth] = { { } };	// Matrix "Image" of data. Used for collision Detection. Init to zero.
	uint8_t DifficultyTime;

    char WhatNextAfterBallCollision = 0;


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


    uint8_t currentHealth = 3;
    UpdateRGB(currentHealth);

    initPowerup(&powerup);

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

    // Generate striker.
    fgcolor(8);
    gotoXY(striker.currpos, putStrikerPos);
	for (int i = 0; i < striker.strikersize; i++){
        putchar(223);
	}

    fgcolor(15);
    drawBall(&ball1);

    uint32_t prevPowerStart = 0;
    uint32_t currTime = clk.time_hseconds, deltaTime = 0, prevTime;
    // Print brick counter;
    PrintBrickCounter(&BrickCounter);

    uint8_t ballDifficultyMod = 5;
    ballDifficultyMod -= ballDifficultyMod - *level > 0 ? 1 : 0;

    gotoXY(90,80);
    printf("Level %d  ", *level);

    char LCDHearts[7] = {0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x00};
    // Update LCD.
    ClearLineData(LCDData);
    LCDWrite(LCDData, LCDHearts, 0);
    sprintf(str1, "Brick counter: %03d", BrickCounter);
    LCDWrite(LCDData, str1, 1);
    sprintf(str1, "Score: %03d", *PlayerScore);
    LCDWrite(LCDData, str1, 2);
    lcd_update(Graph, LCDData);

    //// START GAME ////
    drawBall(&ball1);
    CountDown();

    uint8_t gameEnabled = 1;

    while (gameEnabled) {
        __disable_irq();
        prevTime = currTime;
        currTime = clk.time_hseconds;
        deltaTime = currTime - prevTime;
        __enable_irq();
	    // Control ball speed.
        if ((currTime % ballDifficultyMod) == 0 && currTime != prevTime) {

            // Calculate and update ball next XY-position.
            updateBall(&ball1, 0);

            // Return the address of the functions that will be called after CollissionDectect
            CollisionDectectReturnAddr = CollisionDetect(gameArray, &ball1);

            // If CollissionDectect has returned a address.
            if (CollisionDectectReturnAddr != 0) {

                // Call return address and do whats needed. Return what to do next.
                WhatNextAfterBallCollision = ((uint16_t (*)()) CollisionDectectReturnAddr)(&ball1, gameArray, brickArray, &brickHeight, &brickWidth, &BrickCounter, PlayerScore, &powerup);

                //uint16_t BallHitWall(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t *brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore) {

                // If return of WhatNextAfterBallCollision =
                // 0: Ball out of boundary.
                // 1: Ball hit striker or wall.
                // 2: Ball hit a brick.
                // 3: Level completed.
                switch(WhatNextAfterBallCollision) {

                    // Ball out of boundary.
                    case 0:
                        // Ball out of Bounds: END or RESTART game.
                        if (currentHealth > 1){
                            currentHealth--;
                            for (uint8_t i = 3; i > currentHealth; i--){
                                LCDHearts[2*i - 2] = 0x20;
                                LCDHearts[2*i - 1] = 0x20;
                            }
                            LCDWrite(LCDData, LCDHearts, 0);
                            lcd_update(Graph, LCDData);
                            UpdateRGB(currentHealth);
                            gotoXY(ball1.PrevPos.x >> 14, ball1.PrevPos.y >> 14);
                            // Draw space char.
                            putchar(32);
                            initBall(&ball1, putWidth/2, putStrikerPos - 10, -1, -1);
                            drawBall(&ball1);
                            CountDown();

                        }
                        else {
                            currentHealth--;
                            UpdateRGB(currentHealth);
                            ClearLineData(LCDData);
                            LCDWrite(LCDData, "You lose!", 0);
                            sprintf(str1, "Final score: %03d", *PlayerScore);
                            LCDWrite(LCDData, str1, 1);
                            LCDWrite(LCDData, "Insert coin to continue", 2);
                            lcd_update(Graph, LCDData);
                            gameEnabled = 0;
                            // Return player died.
                            return 0;
                        }

                        break;

                    // Ball hit striker or wall.
                    case 1:

                        playSound(800, 5);

                        break;

                    // Ball hit brick
                    case 2:

                        // Update LCD.
                        sprintf(str1, "Brick counter: %03d", BrickCounter);
                        LCDWrite(LCDData, str1, 1);
                        sprintf(str1, "Score: %03d", *PlayerScore);
                        LCDWrite(LCDData, str1, 2);
                        lcd_update(Graph, LCDData);

                        playSound(1200, 5);


                        break;

                    // Level completed.
                    case 3:
                        // Return to main: Level completed.
                        return 1;
                }
            }
            // Draw ball in PuTTY console.
            drawBall(&ball1);

	    }
	    if (currTime % 2 == 0 && currTime != prevTime) {
            updateStriker(gameArray, &striker);
	    }

        if (currTime - prevPowerStart > 1000 && powerup.enable) {
            prevPowerStart = 0;
            powerup.enable = 0;
            ballDifficultyMod--;
        }

        if (powerup.alive == 1 && currTime % 10 == 0 && currTime != prevTime) {

            updatePowerup(&powerup);
            if (gameArray[powerup.posY][powerup.posX] > 1 && gameArray[powerup.posY][powerup.posX] < 7 && powerup.enable == 0) {
                gotoXY(powerup.posX, powerup.posY-1);
                putchar(32);
                powerup.enable = 1;
                ballDifficultyMod++;
                prevPowerStart = currTime;
            }
            if (gameArray[powerup.posY][powerup.posX] == 0 && gameArray[powerup.posY - 1][powerup.posX] == 0) {
                drawPowerup(&powerup);
            }
        }
        // Change color to default.
        fgcolor(15);
    }
}

void CountDown(){
    for (uint8_t i = 3; i > 0; i--) {
			switch (i) {
				case 3:
				PrintFromASCII("3",97,40);
				break;
				case 2:
				PrintFromASCII("    ",97,40);
				PrintFromASCII("2",97,40);
				break;
				case 1:
				PrintFromASCII("    ",97,40);
				PrintFromASCII("1",97,40);
				break;
			}
		playSound(600,5);
        wait(100);
    }
	playSound(1200,5);
PrintFromASCII("    ",97,40);
}

#include "collision.h"





uint16_t BallHitWall(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup) {

gotoXY(40,100);
 printf("Ball will hit the border          ");
  UpdateBallAngle(ball1, gameArray, 1);
// Return to runGame: Ball hit wall.
  return  1;

}

// Return type of hit.
uint16_t BallHitBrick(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup) {


    gotoXY(40,100);
    printf("Ball will hit the bricks           ");

     // Get brick index.
    uint16_t Brickindex = gameArray[(ball1->NextPos.y) >> 14][(ball1->NextPos.x) >> 14];

    // Calculate and set new ball angle.
    UpdateBallAngle(ball1, gameArray, 1);

    // Prevent brick hit point of being negative.
    if (brickArray[Brickindex].currHP > 0) {

        // Decrement brick hit points.
        brickArray[Brickindex].currHP--;

        // Change brick color.
        drawBox(&brickArray[Brickindex], brickHeight, brickWidth);


    }

    // If brick hit points is zero
    if (brickArray[Brickindex].currHP == 0) {

        // Decrement brick counter.
        (*BrickCounter)--;

        // Increase score.
        (*PlayerScore) += brickArray[Brickindex].MaxHP;

        // Kill brick.
        KillBrick(Brickindex, gameArray, &brickArray[Brickindex], brickHeight, brickWidth);

        // Print brick counter;
        PrintBrickCounter(BrickCounter);

        // Spawn a powerup!
        if (brickArray[Brickindex].pwrUP == 1 && powerup->alive == 0 && powerup->enable == 0) {
            spawnPowerup(powerup, &brickArray[Brickindex], brickHeight, brickWidth);
        }


    }

    // If all bricks is killed.
    if ((*BrickCounter) == 0) {
        // Return to runGame: Level completed.
        return  3;

    }
    // Return to runGame: Ball hit a brick.
    return 2;
}

uint16_t BallHitStricker1(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);

 printf("Ball will hit the stricker 1");
 UpdateBallAngle(ball1, gameArray, 2);
  return 1;
}

uint16_t BallHitStricker2(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);
 UpdateBallAngle(ball1, gameArray, 3);
 printf("Ball will hit the stricker 2");
  return 1;
}

uint16_t BallHitStricker3(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);
 UpdateBallAngle(ball1, gameArray, 4);
 printf("Ball will hit the stricker 3");
  return 1;
}

uint16_t BallHitStricker4(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);
 UpdateBallAngle(ball1, gameArray, 5);
 printf("Ball will hit the stricker 4");
  return 1;
}

uint16_t BallHitStricker5(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);
 UpdateBallAngle(ball1, gameArray, 6);
 printf("Ball will hit the stricker 5");
  return 1;
}



uint16_t BallOutOfBoundary(struct ball_t *ball1, uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[maxBricks], uint8_t *brickHeight, uint8_t *brickWidth, uint16_t *BrickCounter, uint16_t *PlayerScore, struct pwrUp *powerup){
gotoXY(40,100);

 printf("END GAME!                    ");
  UpdateBallAngle(ball1, gameArray, 2);
    // Return to runGame: Ball out of boundary.
    return 0;
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



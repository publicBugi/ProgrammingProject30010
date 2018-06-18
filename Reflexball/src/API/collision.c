#include "collision.h"


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
//    if (GameDataRight == 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom == 0) {
//            return 1;
//    }

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



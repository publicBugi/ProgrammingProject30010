#include "ball.h"
 #define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )

#define FIX14_DIV(a, b)  ( ((a) << FIX14_SHIFT) / b )
#define FIRST_QUADRANT (Angle > 384 && Angle < 512)
#define SECOND_QUADRANT (Angle > 256 && Angle < 384)
#define THIRD_QUADRANT (Angle > 128 && Angle < 256)
#define FOURT_QUADRANT (Angle > 0 && Angle < 128)

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

    // Set next positions to next position.
    ball->PrevPos = ball->NextPos;
    // Calculate next x position using direction vector (velMod divedes)
    ball->NextPos.x = ball->PrevPos.x + (ball->DirVec.x >> velMod);
    // Calculate next y position using direction vector (velMod divedes)
   // if ((ball->NextPos.y) >> 14 < putStrikerPos) {
        ball->NextPos.y = ball->PrevPos.y + (ball->DirVec.y >> velMod);
   // }
    //else {
    //    ball->NextPos.y = (putStrikerPos - 1) << 14;

    //}

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
// 4: Direction of ball attack is upper left corner.
// 5: Direction of ball attack is upper right corner.
// 6: Direction of ball attack is lower left corner.
// 7: Direction of ball attack is lower right corner.
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

//     // If no controller TEMPEARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.
//    if (GameDataRight == 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom == 0) {
//        return 1;
//   }

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

    // Check for upper left corner.
    if (GameDataRight == 0 && GameDataLeft != 0 && GameDataTop != 0  && GameDataBottom == 0) {
            return 4;
    }

    // Check for upper right corner.
    if (GameDataRight != 0 && GameDataLeft == 0 && GameDataTop != 0  && GameDataBottom == 0) {
            return 5;
    }

    // Check for lower left corner.
    if (GameDataRight == 0 && GameDataLeft != 0 && GameDataTop == 0  && GameDataBottom != 0) {
            return 6;
    }

    // Check for lower right corner.
    if (GameDataRight != 0 && GameDataLeft == 0 && GameDataTop == 0  && GameDataBottom != 0) {
            return 7;
    }

    // Ball hit one of the four corners.
    //return 4;
}

int32_t GetDegree(uint8_t Up, int32_t Factor, int16_t DegreeIndex){
    int32_t Rand = (DACRand() % 64)-32;
    // Two formulas for calculating new ball angle.
    if (Up == 1) {
        return (( (128 * ( (3 << 14) + (Factor)) ) - ( (DegreeIndex & 0x1FF) * Factor ) ) >> 14) + Rand;
       // return ( (128 * ( (1 << 14) + Factor) ) - ( (DegreeIndex & 0x1FF) * Factor ) ) >> 14;
    }
    else {
        return ((Factor * (256 -  (DegreeIndex & 0x1FF) ) )  >> 14) + Rand;
    }
}

// Check new angle depeding on hit ball direction. This function prevents invalid ball angle.
// Return 1 if angle is ok.
char CheckAngle(char DirectionOfBallAttack, int32_t Angles) {
    // 0: Direction of ball attack is up.
    // 1: Direction of ball attack is down.
    // 2: Direction of ball attack is right.
    // 3: Direction of ball attack is left.
    // 4: Direction of ball attack is upper left corner.
    // 5: Direction of ball attack is upper right corner.
    // 6: Direction of ball attack is lower left corner.
    // 7: Direction of ball attack is lower right corner.
    int32_t Angle = Angles & 0x1FF;

    switch(DirectionOfBallAttack) {
        // Direction of ball attack is up.
        case 0:
            if (THIRD_QUADRANT || FOURT_QUADRANT) {
                return 1;
            };
        break;
        // 1: Direction of ball attack is down.
        case 1:
            if (FIRST_QUADRANT || SECOND_QUADRANT) {
                return 1;
            };
        break;
        // 2: Direction of ball attack is right.
        case 2:
            if (SECOND_QUADRANT || THIRD_QUADRANT) {
                return 1;
            };
        break;
        // 3: Direction of ball attack is left.
        case 3:
            if (FIRST_QUADRANT || FOURT_QUADRANT) {
                return 1;
            };
        break;
        // Direction of ball attack is upper left corner.
        case 4:
            if (FOURT_QUADRANT) {
                return 1;
            };
        break;
        // Direction of ball attack is upper right corner.
        case 5:
            if (THIRD_QUADRANT) {
                return 1;
            };
        break;
        // Direction of ball attack is lower left corner.
        case 6:
            if (FIRST_QUADRANT) {
                return 1;
            };
        break;
        // Direction of ball attack is lower right corner.
        case 7:
            if (SECOND_QUADRANT) {
                return 1;
            };
        break;
        default: return 0;
    }

 return 0;

}

void UpdateBallAngle(struct ball_t *ball, uint8_t gameArray[putHeight][putWidth], uint8_t TypeOfHit) {
    char DirectionOfBallAttack_Var;
    //uint16_t DegreeRef[2] = {512, 256};
   // int32_t DegreeRef[2] = {128, 128};
    uint8_t FromI, ToI;
    int32_t Factor = 0b00000000000000000100000000000000;
    int32_t Angle;
    //TypeOfHit:
    // 0:
    // 1: Brick
    // 2: Striker 1 Left end
    // 3: Striker 2 left medium
    // 4: Striker 3 central
    // 5: Striker 4 right medium
    // 6: Striker 4 right end
    uint8_t RunTime = 0;


      switch(TypeOfHit) {
                // Brick
                case 1:
                    // Format Q18.14. Factor 1.
                    Factor = 0b00000000000000000100000000000000;
                    break;
                // Striker 1 Left end
                case 2:
                    // Format Q18.14: Factor 1/3=2/6.
                    Factor = 0b00000000000000000001010101010101;
                    break;
                // Striker 2 left medium
                case 3:
                    // Format Q18.14: Factor 1/1.5=2/3.
                    Factor = 0b00000000000000000010101010101010;
                    break;
                // Striker 3 central
                case 4:
                    // Format Q18.14: Factor 1.
                    Factor = 0b00000000000000000100000000000000;
                    break;
                // Striker 4 right medium
                case 5:
                    // Format Q18.14: Factor 1.5.
                    Factor = 0b00000000000000000110000000000000;
                    break;
                break;
                // Striker 4 right end
                case 6:
                    // Format Q18.14: Factor 3.
                    Factor = 0b00000000000000001100000000000000;
                    break;
                break;
    }
    // Get direction of ball attack.
    DirectionOfBallAttack_Var = DirectionOfBallAttack(gameArray, ball);

    switch(DirectionOfBallAttack_Var) {
          // Ball side attack is down or up (including striker).
         case 0 ... 1:
            FromI = 0;
            ToI = 0;
            break;
          // Ball side attack is left or right.
        case 2 ... 3:
            FromI = 1;
            ToI = 1;
            break;
        // Roate 180 degree.
        case 4 ... 7:
            FromI = 0;
            ToI = 1;
    }

    // Loop through iterations.
    for (int i = FromI; i <= ToI; i ++) {

        // Check angle (infinite loop).
        for(;;) {
                ball->DegreeIndex = (i == 0) ? GetDegree(1, Factor, ball->DegreeIndex) : GetDegree(0, Factor, ball->DegreeIndex);

                // If angle is not ok try to generate another angle. If ball hit a corner ((FromI == 0 && ToI == 1) && i != 1)) CheckAngle function only calls the second time DegreeIndex is calculate.
                // If ball hit other than one of the corners CheckAngle calls.
                if (( (FromI == 0 && ToI == 1) && i != 1)  || CheckAngle(DirectionOfBallAttack_Var,  ball->DegreeIndex) == 1 ) {
                        // Abort this infinite loop.
                        break;
                }

        }

        ball->DirVec.x = getCos(ball->DegreeIndex);
        ball->DirVec.y = getSin(ball->DegreeIndex);
    }


//    // Loop through iterations.
//    for (int i = FromI; i <= ToI; i ++) {
//            ball->DegreeIndex = (i == 0) ? GetDegree(1, Factor, ball->DegreeIndex) : GetDegree(0, Factor, ball->DegreeIndex);
//            ball->DirVec.x = getCos(ball->DegreeIndex);
//            ball->DirVec.y = getSin(ball->DegreeIndex);
//
//    }
    gotoXY(150,100);
    printf("Ball angle: %d     ", ((ball->DegreeIndex & 0x1FF)*360)/512);
     gotoXY(40,100);
    // Update next ball position.
    ball->NextPos.y = ball->PrevPos.y + (ball->DirVec.y);
    ball->NextPos.x = ball->PrevPos.x + (ball->DirVec.x);


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

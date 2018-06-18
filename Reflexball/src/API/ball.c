#include "ball.h"

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

void GenerateGameArray() {

}
void initBall() {

}

void updateBall() {

}

void drawBall() {

}
//void initBall(struct ball_t *ball, int32_t XPos, int32_t YPos, int32_t Vx, int32_t Vy) {
//    ball->PosVec.x = XPos << 14;
//    ball->PosVec.y = YPos << 14;
//    ball->VelVec.x = Vx << 14;
//    ball->VelVec.y = Vy << 14;
//
//    /*initVector(ball->PosVec, int32_t XPos, int32_t YPos);
//    initVector(ball->VelVec, int32_t Vx, int32_t Vy);*/
//}
//
//void updateBall(struct ball_t *ball, int32_t k) {
//    ball->PosVec.x = ball->PosVec.x + (ball->VelVec.x >> k);
//    ball->PosVec.y = ball->PosVec.y + (ball->VelVec.y >> k);
//}
//
//void drawBall(struct ball_t *ball){
//    gotoXY(ball->PosVec.x >> 14, ball->PosVec.y >> 14);
//    putchar(111);
//}

void CountDown(char *numberArray[][][]){
  // Start at 4 to make sure the first second is at least a full second
  for (int i = 4; i > 0; i--) {
    uint8_t clkSec = clk->time_sec;
    while(clkSec == clk->time_sec){}
    // For the first value of I, print 3
    if (i==4) {
      PrintOutTextArray(numberArray[3][][], *countDownX, *countDownY, 5, 8);
    }
    // Print the rest of the numbers, every time the time_sec changes
    else{
      PrintOutTextArray(numberArray[i][][], *countDownX, *countDownY, 5, 8);
    }
  }
}

int CollisionDetect() {


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

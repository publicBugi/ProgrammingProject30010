#include "vectortrig.h"

/* Data Formats:
    2.14 Data format is a 16 Bit representation, where the 2 MSB Bits represent SIGN + 1 Bit value (Range -1 to 1). The remaining 14 bits is another whole number value that represents a decimal (Range 0.9999 to 0.0000).
    18.14 Data Format is essentially 2.14 with an addition 16 bits added unto the whole integer value.
    16.16 Data Format can be achieved by taking 18.14 and << 2.
*/

// Expand 18.14 to 16.16.
int32_t expand(int32_t i){
    return i << 2;
}

// Return Index within 0 - 512 Range.
int getIndex(int index){
    return index & 0x1FF;
}

// Return Sine of Index in LUT.c. (Circle with 512 Steps)
int32_t getSin(int index) {
    return (int32_t)SIN[getIndex(index)];

}

// Return Cosine of Index in LUT.c. (Circle with 512 Steps)
int32_t getCos(int index) {
    return (int32_t)SIN[getIndex(index+128)];
}

// Prints signed 16.16 Fixed point number. Input 18.14 Number.
void printFix(int32_t i) {
    i = expand(i);
	if ((i & 0x80000000) != 0) { //Handle negative numbers
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	//Print a maximum of 4 decimal digits to avoid overflow
}

// Initialize a vector. Struct in Header file.
void initVector(struct vector_t *v, int32_t x, int32_t y) {
    v->x = x << 14;
    v->y = y << 14;
}

// Given a vector, prints the (x,y) of the vector.
void printVector(struct vector_t *v) {
    printf("(");
    printFix(v->x);
    printf(", ");
    printFix(v->y);
    printf(")");
}

// Rotate given vector with degree given in 512 increments. (64 = 45 Degree, 128 = 90, etc.)
void rotateVector(struct vector_t *v, int index) {
    int32_t xprime = v->x * getCos(index) - v->y * getSin(index);
    int32_t yprime = v->x * getSin(index) + v->y * getCos(index);
    v->x = xprime >> 14;
    v->y = yprime >> 14;
}

// Translates vector with a given (x,y) value.
void translateVector(struct vector_t *v, int32_t x, int32_t y) {
    v->x += x << 14;
    v->y += y << 14;
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

int32_t To2d14(int natval, int decval) {
    return ((int32_t) natval << 14)  + decval;
}

void drawBall(struct ball_t *ball){
    gotoXY(ball->PosVec.x >> 14, ball->PosVec.y >> 14);
    putchar(111);
}

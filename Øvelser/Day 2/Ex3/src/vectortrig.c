#include "vectortrig.h"


int32_t expand(int32_t i){
    return i << 2;
}

int getIndex(int index){
    return index & 0x1FF;
}


int32_t getsin(int index) {
    return (int32_t)SIN[getIndex(index)];

}


int32_t getcos(int index) {
    return (int32_t)SIN[getIndex(index+128)];
}

void printFix(int32_t i) {
//Prints a signed 16.16 fixed point number
    i = expand(i);
	if ((i & 0x80000000) != 0) { //Handle negative numbers
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	//Print a maximum of 4 decimal digits to avoid overflow
}



void initVector(struct vector_t *v) {
    v->x = -4 << 14;
    v->y = 2 << 14;

}

void rotateVector(struct vector_t *v, int index) {

    int32_t xprime = v->x * getcos(index) - v->y * getsin(index);
    int32_t yprime = v->x * getsin(index) + v->y * getcos(index);
    v->x = xprime >> 14;
    v->y = yprime >> 14;
    printf("(");
    printFix(v->x);
    printf(", ");
    printFix(v->y);
    printf(")");

}
 // Shift for meget

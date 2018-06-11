#include "lut.h"
#include "30010_io.h"
#include "ansi.h"

#ifndef _VECTORTRIG_H_
#define _VECTORTRIG_H_

struct vector_t  {
    int32_t x, y;

};



struct box_t {
    char x1, y1, x2, y2;
};

int32_t getSin(int index);
int32_t getCos(int index);
void initVector(struct vector_t *v, int32_t x, int32_t y);
void printVector(struct vector_t *v);
void rotateVector(struct vector_t *v, int index);
void translateVector(struct vector_t *v, int32_t x, int32_t y);
 #endif

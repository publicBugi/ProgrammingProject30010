#include "lut.h"
#include <stdio.h>

#ifndef _VECTORTRIG_H_
#define _VECTORTRIG_H_
struct vector_t  {
    int32_t x, y;

};

int32_t getsin(int degree);
int32_t getcos(int index);
void initVector(struct vector_t *v);
void rotateVector(struct vector_t *v, int index);

 #endif

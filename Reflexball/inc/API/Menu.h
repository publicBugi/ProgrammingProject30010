
#ifndef _MENU_H_
#define _MENU_H_
#include "ansi.h"
//#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]));

void PrintOutTextArray(char TextArray[][], uint8_t xCor, uint8_t yCor);
void PrintMenu(int state, char ASCIIArray[][][]);
 #endif

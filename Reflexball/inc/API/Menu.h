
#ifndef _MENU_H_
#define _MENU_H_
#include "ansi.h"
#define ASCIIARRAYTYPE ASCIIArray[12][5][9]
#define TITLEASCIIARRAYTYPE ASCIITitleArray[9][9]
#define TEXTARRAYTYPE TextArray[9][9]

#define menuBlock1X 10
#define menuBlock1Y 10
#define menuBlock2X 10
#define menuBlock2Y 10
#define menuBlock3X 10
#define menuBlock3Y 10
//#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]));

void PrintOutTextArray(char TITLEASCIIARRAYTYPE, uint8_t xCor, uint8_t yCor);
void PrintMenu(int state, char ASCIIARRAYTYPE);
void PrintTitle(char TITLEASCIIARRAYTYPE);
void ClearMenuLines(uint8_t LineFrom, uint8_t LineTo);
 #endif

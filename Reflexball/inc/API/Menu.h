
#ifndef _MENU_H_
#define _MENU_H_
#include "ansi.h"
#include "charset.h"
#include "ROM.h"
#define ASCIIARRAYTYPE ASCIIArray[12][5][9]
#define TITLEASCIIARRAYTYPE ASCIITitleArray[9][9]
#define TEXTARRAYTYPE TextArray[9][9]

#define menuBlock1X 0
#define menuBlock1Y 0
#define menuBlock2X 0
#define menuBlock2Y 5
#define menuBlock3X 0
#define menuBlock3Y 10
//#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]));

// MenuArray: {Change to state? , Max menu}

static  const char MenuDataArray[4][2] = {{0,0},{2,3},{1,2},{3,3}};
void PrintOutTextArray(char *TextArray, uint8_t xCor, uint8_t yCor, uint8_t RowTotal, uint8_t ColTotal);
void ClearData(char ASCIIARRAYTYPE);
void PrintMenu(int state, char ASCIIARRAYTYPE);
void PrintTitle(char TITLEASCIIARRAYTYPE);
void UpdateState(int state, int selection);
void ClearLines(uint8_t LineFrom, uint8_t LineTo);
char ChangeSelection(char Up, char SelectionIndex, char MaxSelection);
void CreateMenuText(char ASCIIARRAYTYPE, uint8_t i, char* Text);
void Select(int  selection,  int  highlight,   char  ASCIIARRAYTYPE, int state);
 #endif

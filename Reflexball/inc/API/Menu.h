
#ifndef _MENU_H_
#define _MENU_H_
#include "ansi.h"
#include "charset.h"
#include "ROM.h"
#define ASCIIARRAYTYPE ASCIIArray[12][5][9]
#define TITLEASCIIARRAYTYPE ASCIITitleArray[9][9]
#define TEXTARRAYTYPE TextArray[9][9]

#define menuBlockX 0
#define menuBlock1Y 0
#define menuBlock2Y 5
#define menuBlock3Y 10

typedef int bool;
#define true 1
#define false 0

#define SELECT 1
#define DESELECT 0

#define UP 1
#define DOWN 0

#define ASCIIARRAYTYPE ASCIIArray[12][5][9]
#define TITLEASCIIARRAYTYPE ASCIITitleArray[9][9]



//#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]));

// MenuArray: {Change to state? , Max menu}
static  const char MenuDataArray[4][2] = {{0,0},{2,3},{1,2},{3,3}};

void PrintOutTextArray(char *TextArray, uint8_t xCor, uint8_t yCor, uint8_t RowTotal, uint8_t ColTotal);
void ClearData(char ASCIIARRAYTYPE);
void PrintMenu(int state, int *Newmenu);
void PrintTitle(char TITLEASCIIARRAYTYPE);
void ClearLines(uint8_t LineFrom, uint8_t LineTo);
char ChangeSelection(char Up, char SelectionIndex, char MaxSelection);
void CreateMenuText(char ASCIIARRAYTYPE, uint8_t i, char* Text);
void Select(int  selection,  int  highlight, int state);
char GetNextMenuBlockSelection(bool Up, char SelectionIndex, char MaxSelection);
void GotoMenuState(int state);
void UpdateState(int state, int selection, int *ChangeSelection);
uint8_t ReturnNextBlockSelectionNumber(uint8_t Up, int8_t CurrentBlockSelectionNumer);
 #endif

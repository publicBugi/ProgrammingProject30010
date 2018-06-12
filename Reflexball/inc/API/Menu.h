
#ifndef _MENU_H_
#define _MENU_H_
#include "ansi.h"
#include "charset.h"
typedef int bool;
#define true 1
#define false 0

#define ASCIIARRAYTYPE ASCIIArray[12][5][9]
#define TITLEASCIIARRAYTYPE ASCIITitleArray[9][9]


#define menuBlockX 0
#define menuBlock1Y 0
#define menuBlock2Y 5
#define menuBlock3Y 10
// ASCIIArray[] = ["Play game", "Highscore", "Help", "1 Player", "2 Player", "Initial 1","Score 1", "Initial 2","Score 2", "Initial 3","Score 3"]

//#define SIZE_OF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]));

// MenuArray: [MenuState][MenuBlockNum]:{Change to state? , Max menu}
// MenuDataArray[0] Main menu
// MenuDataArray[1] Player menu
// MenuDataArray[2] Score menu
// MenuDataArray[3] Help menu
static  const char MenuDataArray[4][3][2] = { {{2,3},{3,3},{4,3},{1,3}}, {{5,2},{6,2},{1,2},{1,2}} };



void PrintOutTextArray(char *TextArray, uint8_t xCor, uint8_t yCor, uint8_t RowTotal, uint8_t ColTotal);
void GotoMenuState(int state, char ASCIIARRAYTYPE);
void PrintTitle(char TITLEASCIIARRAYTYPE);
void UpdateState(int state, int selection);
void ClearLines(uint8_t LineFrom, uint8_t LineTo);
char GetNextMenuBlockSelection(char Up, char SelectionIndex, char MaxSelection);
void CreateMenuText(char ASCIIARRAYTYPE, uint8_t i, char* Text);
void Select(int  selection,  int  highlight,   char  ASCIIARRAYTYPE, int state);
void InitializeMenu(char ASCIIARRAYTYPE);
 #endif

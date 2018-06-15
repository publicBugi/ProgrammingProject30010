#ifndef _LCD_H
#define _LCD_H
#include "30010_io.h"

void ClearLineData(char LCDData[4][128]);
void LCDWrite(char LCDData[4][128], char* Text, int Line);
void CollectGraph(char *Graph, char LCDData[4][128]);
void lcd_update(char *Graph, char LCDData[4][128]);
void initLCD();
void Shift(char LCDData[4][128], uint8_t Line);
void lcd_update();
#endif

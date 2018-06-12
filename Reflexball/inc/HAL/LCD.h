#ifndef _LCD_H
#define _LCD_H
#include "30010_io.h"

void ClearLineData(struct LCDDataLine *LineData);
void LCDWrite(struct LCDDataLine *LineData, char* Text, int Line);
void CollectGraph(char *Graph, struct LCDDataLine *LineData);
void lcd_update(char *Graph, struct LCDDataLine *LineData);
void initLCD();
void Shift(struct LCDDataLine *LineData, uint8_t Line);
void lcd_update();
#endif

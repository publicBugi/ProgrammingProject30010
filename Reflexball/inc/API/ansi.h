#include "30010_io.h"
#include "string.h"

#ifndef _ANSI_H_
#define _ANSI_H_
#include "vectortrig.h"
void clrscr();
void clreol();
void gotoXY(uint8_t X, uint8_t Y);
void CursorUp(char n);
void CursorDown(char n);
void CursorRight(char n);
void CursorLeft(char n);
void SetUnderLine(char on);
void SetBlink(char on);
void SetReverse(char on);
void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void ShowWindow(char x1, char y1, char x2, char y2, char text[], uint8_t color, char style);
void initBox(struct box_t *box, char x1, char y1, char x2, char y2);
void drawBox(struct box_t *box);
#endif /* _ANSI_H_ */

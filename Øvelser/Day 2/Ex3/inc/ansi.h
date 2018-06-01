

/* Exported functions ------------------------------------------------------- */
void clrscr();
void clreol();
void gotoXY(uint8_t X, uint8_t Y);
void SetUnderLine(char on);
void SetBlink(char on);
void SetReverse(char on);
void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();


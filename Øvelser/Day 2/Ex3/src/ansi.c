#define ESC 0x1B

// Rydder terminal
void clrscr(){
    // Ryd terminal.
    printf("%c[%s", ESC, "2J");

    // Hjemposition for cursor.
    printf("%c[%s", ESC, "H");
}

// Rydder til enden af linjen
void clreol(){
    // Rydder til enden af linjen
    printf("%c[%s", ESC, "K");
}

// G�r til linje X og Y
void gotoXY(uint8_t X, uint8_t Y){

    printf("%c[%d;%dH", ESC, Y+1, X+1);
}

// Underline
void SetUnderLine(char on){
    printf("%c[%dm", ESC, (on == 1 ? 4 : 24));

}

// Blink
void SetBlink(char on){
    printf("%c[%dm", ESC, (on == 1 ? 5 : 25));

}

// Blink
void SetReverse(char on){
    printf("%c[%dm", ESC, (on == 1 ? 7 : 27));

}

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}


void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);  
}

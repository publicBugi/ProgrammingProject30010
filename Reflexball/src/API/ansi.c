#include "ansi.h"
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

void CursorUp(char n) {
    printf("\033[%cA\b", n);
}

void CursorDown(char n) {
    printf("\033[%cB\b", n);
}

void CursorRight(char n) {
    printf("\033[%cC\b", n);
}

void CursorLeft(char n) {
    printf("\033[%cD\b", n);
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

void ShowWindow(char x1, char y1, char x2, char y2, char text[], uint8_t color, char style){
    int i;
    char UpLeft = (style == 1) ? 201 : 218;
    char LeftTitle = (style == 1) ? 185 : 180;
    char RightTitle = (style == 1) ? 204 : 195;
    char Vertical = (style == 1) ? 186 : 179;
    char UpRight = (style == 1) ? 187 : 191;
    char Horizontal = (style == 1) ? 205 : 196;
    char DownLeft = (style == 1) ? 200 : 192;
    char DownRight = (style == 1) ? 188 : 217;

    // Ryd terminal.
    //clrscr();

    // Skift farve.
    fgcolor(15);
    bgcolor(0);

    if ((x2-x1) - 4 < 1) {
        printf("Fejl");
    }
    else {
    gotoXY(x1,y1);

    printf("%c", UpLeft);
    printf("%c", LeftTitle);

    // Skift farve.
    bgcolor(color);

    // Title p� vindue.
    for (i=0; i < (x2-x1) - 4 ; i++) {
        printf("%c", (i < strlen(text) ? text[i] : 32));
    }

    // Skift farve.
    fgcolor(15);
    bgcolor(0);

    printf("%c", RightTitle);
    printf("%c", UpRight);

    gotoXY(x1,y1+1);

    // Sidelinjer.
    for (i=y1 + 1; i < y2; i++) {

        printf("%c", Vertical);

        // G� til enden.
        gotoXY(x2-1,i);

        printf("%c", Vertical);

        // G� til n�ste linje.
        gotoXY(x1,i+1);
    }

    // Bundlinje.
    printf("%c", DownLeft);
    for (i=0; i < (x2-x1) - 2; i++) {
        printf("%c", Horizontal);
    }
    printf("%c", DownRight);
    }
}

void initBox(struct box_t *box, char x1, char y1, char x2, char y2){
    box->x1 = x1;
    box->y1 = y1;
    box->x2 = x2;
    box->y2 = y2;
}

void drawBox(struct box_t *box) {

    char UpLeft = 201;
    char Vertical = 186;
    char UpRight = 187;
    char Horizontal = 205;
    char DownLeft = 200;
    char DownRight = 188;

    int i;
    gotoXY(box->x1, box->y1);
    putchar(UpLeft);// Upper left corner
        for(i=box->x1+1; i < box->x2; i++){
        putchar(Horizontal);
    }
    putchar(UpRight);
    for(i=box->y1+1; i < box->y2; i++){
        gotoXY(box->x1,i);
        putchar(Vertical);
    }
    for(i=box->y1+1; i < box->y2; i++){
        gotoXY(box->x2,i);
        putchar(Vertical);
    }
    gotoXY(box->x1,box->y2);
    putchar(DownLeft);
    for(i=box->x1+1; i < box->x2; i++){
        putchar(Horizontal);
    }
    putchar(DownRight);
}

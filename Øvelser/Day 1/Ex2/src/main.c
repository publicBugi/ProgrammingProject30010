/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#define ESC 0x1B
#include "30010_io.h"
#include "ansi.h"
#include "string.h"

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

// Går til linje X og Y
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

int ShowWindow(char x1, char y1, char x2, char y2, char text[], uint8_t color, char style){
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
    clrscr();

    // Skift farve.
    fgcolor(15);
    bgcolor(0);

    if ((x2-x1) - 4 < 1) {
        printf("Fejl");
        return 0;
    }

    gotoXY(x1,y1);

    printf("%c", UpLeft);
    printf("%c", LeftTitle);

    // Skift farve.
    bgcolor(color);

    // Title på vindue.
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

        // Gå til enden.
        gotoXY(x2-1,i);

        printf("%c", Vertical);

        // Gå til næste linje.
        gotoXY(x1,i+1);
    }

    // Bundlinje.
    printf("%c", DownLeft);
    for (i=0; i < (x2-x1) - 2; i++) {
        printf("%c", Horizontal);
    }
    printf("%c", DownRight);
}

int main(void)
    {
         init_usb_uart( 9600 ); // Initialize USB serial at 9600 baud
         clrscr();


   // printf("test\n");
ShowWindow(10, 10, 100, 30, "kddfgdfdgdfg",1, 0);

        while(1){}
}

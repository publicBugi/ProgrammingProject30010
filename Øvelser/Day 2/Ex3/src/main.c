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
#include "lut.h"
#include "vectortrig.h"

int main(void)
    {
    //init_usb_uart(9600);
    init_usb_uart(115200); // Initialize USB serial at 9600 baud
    clrscr();

    int c, d;
    struct ball_t ball;
    initBall(&ball, 1, 1, 1, 1);
    while(1){
        clrscr();
        drawBox(10, 10, 100, 50);
        drawBox(30,25, 70, 30);
        drawBall(&ball);
        updateBall(&ball, 0);
        for (c = 1; c <= 32767; c++)
            for (d = 1; d <= 50; d++)
            {}
    }


    /*ShowWindow(10, 10, 100, 30, "kddfgdfdgdfg",1, 1);
    struct vector_t vec;
    initVector(&vec, 1, 1);
    gotoXY(0,0);
    printVector(&vec);
    rotateVector(&vec, 256);
    translateVector(&vec, 1, 1);
    gotoXY(0,1);
    printVector(&vec);
    rotateVector(&vec, 256);
    translateVector(&vec, 1, 1);
    gotoXY(0,2);
    printVector(&vec);*/

    while(1){}
}

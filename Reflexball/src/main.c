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
//#include "ansi.h"
//#include "lut.h"
//#include "vectortrig.h"
#include "GPIO.h"

int binary_conversion(int num)
{
    if (num == 0)
    {
        return 0;
    }
    else
    {
        return (num % 2) + 10 * binary_conversion(num / 2);
    }
}

int main(void)
    {
    uint16_t old;
    int JoyInput;
    int c = 0;
    init_usb_uart(9600); // Initialize USB serial at 115200 baud
   // clrscr();

    // Initialisering.
    Ini();



    while (1) {

    // Læs joystik indgange.
    JoyInput = readJoystick();
        if (JoyInput == 4) {
          SetLed(1, 0, 0);
        }

        if (JoyInput == 1) {
          SetLed(0, 1, 0);
        }

        if (JoyInput == 8) {
          SetLed(0, 0, 1);
        }

        if (JoyInput == 16) {
          SetLed(1, 1, 1);
        }

        if (JoyInput == 2) {
          SetLed(0, 0, 0);
        }
    // Hvis ændring i joystik indgange.
    if (JoyInput != old) {



        printf("%02d: %08d\n",c, binary_conversion(JoyInput));
        old = JoyInput;
        c++;
       }


    }


/*
    int c, d, cnt;
    struct ball_t ball;
    struct box_t Border;
    struct box_t ScoreBox;

    initBall(&ball, 11, 11, 1, 1);
    initBox(&Border, 10, 10, 100, 50);
    initBox(&ScoreBox, 45, 30, 55, 32);
    cnt = 0;
    drawBox(&Border);
    drawBox(&ScoreBox);
    while(1){
        //clrscr();
        gotoXY(1,1);
        printVector(&ball.PosVec);
        gotoXY(1,2);
        printVector(&ball.VelVec);
        gotoXY(10,0);
        printf("x1");
        gotoXY(0,10);
        printf("y1");
        gotoXY(100,0);
        printf("x2");
        gotoXY(0,50);
        printf("y2");
        gotoXY(46,31);
        printf("%i",cnt);
        //drawBox(&Border);
        //drawBox(&ScoreBox);
        drawBall(&ball);
        updateBall(&ball, 0);
        if (CollisionDetect(&ball, &Border)) {
                updateBall(&ball, 0);
                cnt++;
        }
        for (c = 1; c <= 32767; c++)
            for (d = 1; d <= 10; d++)
            {}
    }


    ShowWindow(10, 10, 100, 30, "kddfgdfdgdfg",1, 1);
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
    printVector(&vec);
*/
    printf("helllo world!\n");
    while(1){}
}

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

int main(void)
    {
    //init_usb_uart(9600);
    init_usb_uart(9600); // Initialize USB serial at 115200 baud
   // clrscr();


    IniJoy();

    while (1) {

        uint16_t Up = GPIOA->IDR & (0x0001 << 4);
        uint16_t Down = GPIOB->IDR & (0x0001 << 0);
        uint16_t Right = GPIOC->IDR & (0x0001 << 1);
        uint16_t Left = GPIOC->IDR & (0x0001 << 0);
        uint16_t Center = GPIOC->IDR & (0x0001 << 0);
        printf("Up: %d, Down: %d, Left: %d, Right: %d, Center: %d\n", Up, Down, Right, Left, Center);

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

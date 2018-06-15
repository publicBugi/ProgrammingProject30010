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
#include "stm32f30x.h"
#include "30010_io.h"
#include "ansi.h"
#include "lut.h"
#include "vectortrig.h"
#include "GPIO.h"
#include "LCD.h"
#include "Game.h"
#include "timer.h"
#include "i2c.h"
//#include "charset.h"

#define ESC 0x1B

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



void getSerialInput(char* input){
    int i;
    for (i=0; i < 6; i++) {
        input[i] = 0x00;
    }
    for (i=0; i < 6; i++) {
        char inputchar = uart_getc();
        if (inputchar == 0x0D ) {
            break;
        }
        else {
        input[i] = inputchar;
        }
    }
}



#define MMA7660Adress 0x4C << 1
int main(void)    {

	// Input Variables

	// Output Variables
	//char Graph[512] = {0};						// Graph: Pixel graph to push to LCD Screen (Redundant?)
	char LCDData[4][128] = { {0} };					// LCDData: Four lines of 128 Pixel lines. LCD Screen.

	// Game data
	uint8_t level;
    uint16_t PlayerScore = 0;
    uint8_t ResultsFromGame = 1;
	// Initialize functions
	init_usb_uart(115200); 	// Initialize USB serial at 115200 baud

	initGPIO();			   	// Enable GPIO Pins.

    initTime(&clk);			// Reset global time.

    initInterrupt();		// void getStrikerPosition(struct striker_t *striker)Enable Interrupt (1/100 sec Interrupt)

    initAnalog();			// Enable ADC Potentiometers

    I2C_init();              // Enable I2C Communication
    I2C_Write(MMA7660Adress, 0x07, 0x01); // Configure 3-Axis Accelerometer (Standard mode)


    //initLCD();			// Enable LCD Screen

	//initBall(&ball1, 1, 1, 1, 1); // Initialize ball (Which ball, Position, Velocity)

    //char Graph[512]; //Graph = Graph[0]
    //struct LCDDataLine LineData;

	//ClearLineData(&LineData);
	//lcd_update(Graph, &LineData);

	//ClearLineData[&LineData);
	//lcd_update[Graph, LCDData);

	//LCDWrite(LCDData, "Hello", 0);
	//LCDWrite(LCDData, "World!", 1);

    level = 1;// Level counter; Controls game difficulty. Starts at level 1.

    // Run game and return
    // 0: If player died
    // 1: If complete level.
    while (ResultsFromGame == 1) {

        ResultsFromGame = runGame(&level, &PlayerScore);

        if (ResultsFromGame == 1) {

        // Clear screen.
        clrscr();

        gotoXY(40,40);

        printf("            GAME LEVEL COMPLETE!                 ");
        // Increase level.
        level++;
        }
        else {

            // Clear screen.
            clrscr();

            gotoXY(40,40);

            printf("            GAME OVER!              ");
            gotoXY(40,41);

            printf("            Your score is %d               ", PlayerScore);
        }

    }


	/*while(1) {
	    if (clk.change == 1)  { // Timer update 1/100th of a second.
	        LCDTimeCnt++;
	        //BallTimeCnt++;
	        //StrikerTimeCnt++;
	        clk.change = 0;
	    }
	    if (LCDTimeCnt == 20) {
            sprintf(str1, "%04d", readAnalog(1));
            sprintf(str2, "%04d", readAnalog(2));
            LCDWrite(&LineData, str1, 2);
            LCDWrite(&LineData, str2, 3);
            lcd_update(Graph, &LineData);
            LCDTimeCnt = 0;
	    }
	    if (BallTimeCnt == DifficultyTime) {
            drawBall(&ball);
            updateBall(&ball, 0);
	        BallTimeCnt = 0;
	    }
	    if (StrikerTimeCnt == 20){
            updateStriker(gameArray ,&striker, readAnalog(1) >> 8);
            StrikerTimeCnt = 0;
	    }
	}

	/*
    while(1) {
        if (clk.change == 1) {
            CountInterrupt ++;
            clk.change = 0;
        }

        if (CountInterrupt == 20) {
            sprintf(str1, "%04ld", readAnalog(1));
            sprintf(str2, "%04ld", readAnalog(2));
            LCDWrite(&LineData, str1, 2);
            LCDWrite(&LineData, str2, 3);
            lcd_update(Graph, &LineData);
            CountInterrupt = 0;
        }



    }
	*/

    /*
    int prevJoystick = 0;
    struct time splitTime1;
    struct time splitTime2;
    initTime(&splitTime1);
    initTime(&splitTime2);
    ShowWindow(0,0,14,4, "Stopwatch", 5, 1);
    while(1) {
        if (clk.change == 1) {
            clk.change = 0;
            gotoXY(1,1);
            printf("%02d:%02d:%02d:%02lu", clk.time_hour, clk.time_min % 60, clk.time_sec % 60, clk.time_hseconds % 100);
        }
        gotoXY(1,2);
        printf("%02d:%02d:%02d:%02lu", splitTime1.time_hour, splitTime1.time_min % 60, splitTime1.time_sec % 60, splitTime1.time_hseconds % 100);
        gotoXY(1,3);
        printf("%02d:%02d:%02d:%02lu", splitTime2.time_hour, splitTime2.time_min % 60, splitTime2.time_sec % 60, splitTime2.time_hseconds % 100);
        gotoXY(9,9);

        getSerialInput(input);
        gotoXY(10,10);
        if (strcmp(input, "start")==0) {
            TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
        }
        else if (strcmp(input, "split1") == 0) {
                    __disable_irq();
                    splitTime1 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "split2") == 0) {
                    __disable_irq();
                    splitTime2 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "reset") == 0) {
                    TIM2->CR1 = 0x00000000;
                    initTime(&clk);
        }
       else if (strcmp(input, "help") == 0) {
                    printf("sdgajsgkljsgajhsdglkj");
       }
        else if (strcmp(input, "") == 0) {

       }
        else {
                    printf("start : start/stop timer\nsplit1 : split timer to slot 1\nsplit 2 : ");
        }
*/


        // JoyTimeCtrl();
        /*JoyInput = readJoystick();
        if (JoyInput != prevJoystick) {	// Has Joystick changed?
            prevJoystick = JoyInput;
            switch (JoyInput) {				// What did it change to?

                case 16 : 	// Center - Start/Stop
                    TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
                    break;
                case 4 :	// Left - Split time 1
                    __disable_irq();

        if (CountInterrupt == 20) {
            sprintf(str1, "%04ld", readAnalog(1));
            sprintf(str2, "%04ld", readAnalog(2));
            LCDWrite(&LineData, str1, 2);
            LCDWrite(&LineData, str2, 3);
            lcd_update(Graph, &LineData);
            CountInterrupt = 0;
        }



    }
	*/

    /*
    int prevJoystick = 0;
    struct time splitTime1;
    struct time splitTime2;
    initTime(&splitTime1);
    initTime(&splitTime2);
    ShowWindow(0,0,14,4, "Stopwatch", 5, 1);
    while(1) {
        if (clk.change == 1) {
            clk.change = 0;
            gotoXY(1,1);
            printf("%02d:%02d:%02d:%02lu", clk.time_hour, clk.time_min % 60, clk.time_sec % 60, clk.time_hseconds % 100);
        }
        gotoXY(1,2);
        printf("%02d:%02d:%02d:%02lu", splitTime1.time_hour, splitTime1.time_min % 60, splitTime1.time_sec % 60, splitTime1.time_hseconds % 100);
        gotoXY(1,3);
        printf("%02d:%02d:%02d:%02lu", splitTime2.time_hour, splitTime2.time_min % 60, splitTime2.time_sec % 60, splitTime2.time_hseconds % 100);
        gotoXY(9,9);

        getSerialInput(input);
        gotoXY(10,10);
        if (strcmp(input, "start")==0) {
            TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
        }
        else if (strcmp(input, "split1") == 0) {
                    __disable_irq();
                    splitTime1 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "split2") == 0) {
                    __disable_irq();
                    splitTime2 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "reset") == 0) {
                    TIM2->CR1 = 0x00000000;
                    initTime(&clk);
        }
       else if (strcmp(input, "help") == 0) {
                    printf("sdgajsgkljsgajhsdglkj");
       }
        else if (strcmp(input, "") == 0) {


    /*
    int prevJoystick = 0;
    struct time splitTime1;
    struct time splitTime2;
    initTime(&splitTime1);
    initTime(&splitTime2);
    ShowWindow(0,0,14,4, "Stopwatch", 5, 1);
    while(1) {
        if (clk.change == 1) {
            clk.change = 0;
            gotoXY(1,1);
            printf("%02d:%02d:%02d:%02lu", clk.time_hour, clk.time_min % 60, clk.time_sec % 60, clk.time_hseconds % 100);
        }
        gotoXY(1,2);
        printf("%02d:%02d:%02d:%02lu", splitTime1.time_hour, splitTime1.time_min % 60, splitTime1.time_sec % 60, splitTime1.time_hseconds % 100);
        gotoXY(1,3);
        printf("%02d:%02d:%02d:%02lu", splitTime2.time_hour, splitTime2.time_min % 60, splitTime2.time_sec % 60, splitTime2.time_hseconds % 100);
        gotoXY(9,9);

        getSerialInput(input);
        gotoXY(10,10);
        if (strcmp(input, "start")==0) {
            TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
        }
        else if (strcmp(input, "split1") == 0) {
                    __disable_irq();
                    splitTime1 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "split2") == 0) {
                    __disable_irq();
                    splitTime2 = clk;
                    __enable_irq();
        }
        else if (strcmp(input, "reset") == 0) {
                    TIM2->CR1 = 0x00000000;
                    initTime(&clk);
        }
       else if (strcmp(input, "help") == 0) {
                    printf("sdgajsgkljsgajhsdglkj");
       }
        else if (strcmp(input, "") == 0) {

       }
        else {
                    printf("start : start/stop timer\nsplit1 : split timer to slot 1\nsplit 2 : ");
        }
*/


        // JoyTimeCtrl();
        /*JoyInput = readJoystick();
        if (JoyInput != prevJoystick) {	// Has Joystick changed?
            prevJoystick = JoyInput;
            switch (JoyInput) {				// What did it change to?

                case 16 : 	// Center - Start/Stop
                    TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
                    break;
                case 4 :	// Left - Split time 1
                    __disable_irq();
                    splitTime1 = clk;
                    __enable_irq();
                    break;
                case 8 :	// Right - Split time 2
                    __disable_irq();
                    splitTime2 = clk;
                    __enable_irq();
                    break;
                case 2 :	// Down - Stop Clock, Reset time.
                    TIM2->CR1 = 0x00000000;
                    initTime(&clk);
                    break;
            }
        }

    }
*/
    /*while (1) {

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


    }*/


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
    //printf("helllo world!\n");
    while(1){}
}

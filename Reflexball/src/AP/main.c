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

struct time {
	uint32_t time_hseconds;
	uint8_t time_sec;
	uint8_t time_min;
	uint8_t time_hour;
	uint8_t change;
};


void initTime(volatile struct time *clk) {
	clk->time_hseconds = 0;
	clk->time_sec = 0;
	clk->time_min = 0;
	clk->time_hour = 0;
	clk->change = 1;
}

void incrementTime(volatile struct time *clk) {
    ++clk->time_hseconds;
	clk->time_sec = (clk->time_hseconds / 100);
	clk->time_min = (clk->time_sec / 60);
	clk->time_hour = clk->time_min / 60;
	clk->change = 1;
}

volatile struct time clk;

void TIM2_IRQHandler(void) {
	// Interrupt function!
	incrementTime(&clk);
	TIM2->SR &= ~0x0001; // End the interrupt.
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

void initInterrupt(){
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; 	// Clock line for timer 2
    TIM2->CR1 = 0x00000001; 				// Configure [0 0 0 0 UIF 0 CKD ARPE CMS DIR OPM UDIS CEN]
    TIM2->ARR = 0x0009C3FF;					// Relead Value = 63999 = 1/100 Second.
    TIM2->PSC = 0x00000000;					// Preset = 0;

    TIM2->DIER |= 0x0001;					// Timer 2 Interrupts Enabled
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);
}

int main(void)
    {
	init_usb_uart(115200); // Initialize USB serial at 115200 baud
	clrscr();

	initGPIO();
    initTime(&clk);
    initAnalog();
	initInterrupt();
    initLCD();

    char Graph[512]; //Graph = Graph[0]
    struct LCDDataLine LineData;
    memset(Graph, 0x00, 512);
	ClearLineData(&LineData);
	lcd_update(Graph, &LineData);

    LCDWrite(&LineData, "Hordur", 0);
    LCDWrite(&LineData, "Sebastian Frederik", 1);

    char str1[7];
    char str2[7];

    //int JoyInput;

    //char input[7];
    uint16_t LCDTimeCnt = 0;
    uint16_t BallTimeCnt = 0;
    uint16_t StrikerTimeCnt = 0;
    //uint16_t InterruptGame = 0;

	struct ball_t ball;
	struct striker_t striker;
	struct brick_t brickArray[256];
	char gameArray[256][256];
	int level = 1;
	int DifficultyTime;

	initGameArray(gameArray, brickArray, &striker, &level, &DifficultyTime);
	initBall(&ball, 1, 1, 1, 1);

	for (int i = 0; i < 256; i++){
		for (int r = 0; r < 256; r++){
            gotoXY(i,r);
			printf("%c", gameArray[i][r]);
		}
	}
	while(1) {
	    if (clk.change == 1)  { // Timer update 1/100th of a second.
	        LCDTimeCnt++;
	        BallTimeCnt++;
	        StrikerTimeCnt++;
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

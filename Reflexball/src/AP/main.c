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
    char str1[7];
	// Output Variables
	char Graph[512] = {0};						// Graph: Pixel graph to push to LCD Screen (Redundant?)
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


    initLCD();			// Enable LCD Screen

	//initBall(&ball1, 1, 1, 1, 1); // Initialize ball (Which ball, Position, Velocity)

    //char Graph[512]; //Graph = Graph[0]
    //struct LCDDataLine LineData;


//	ClearLineData(LCDData);
//	//lcd_update(Graph, &LineData);
//
//	//ClearLineData(&LineData);
//	lcd_update(Graph, LCDData);


	//LCDWrite(LCDData, "World!", 1);

    level = 1;// Level counter; Controls game difficulty. Starts at level 1.

    // Run game and return
    // 0: If player died
    // 1: If complete level.
    while (ResultsFromGame == 1) {

        ResultsFromGame = runGame(&level, &PlayerScore, Graph, LCDData);

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
    while(1){}
}

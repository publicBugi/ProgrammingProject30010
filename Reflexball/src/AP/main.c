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
#include "Menu.h"
#include "ROM.h"
#include "Game.h"
#include "timer.h"
#include "i2c.h"
//#include "charset.h"
#include "buzzer.h"

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

int main(void)   {

        // ASCII array.
        char ASCIIARRAYTYPE;

        int JoyInput, SelectedMenu;
        char EnableSelection = 1;
        char MenuState = 1;

  	char Graph[512] = {0};						// Graph: Pixel graph to push to LCD Screen (Redundant?)
	char LCDData[4][128] = { {0} };					// LCDData: Four lines of 128 Pixel lines. LCD Screen.

	// Input Variables
    char str1[7];
  	// Game data
	uint8_t level;
    uint16_t PlayerScore = 0;
    uint8_t ResultsFromGame = 1;


	// Output Variables

        clrscr();




	// Initialize functions
	init_usb_uart(115200); 	// Initialize USB serial at 115200 baud

        // Score data, we need to do this once
        uint16_t tempArray[12] = {0x41,0x42,0x43,1234,0x44,0x45,0x46,123,0x47,0x48,0x49,12};
        InitFlash();
        WriteToFlash(tempArray, 0x0800F800);


    	initGPIO();			   	// Enable GPIO Pins.
    initLED();
    initJoystick();
    initTime(&clk);			// Reset global time.

    initInterrupt();		// void getStrikerPosition(struct striker_t *striker)Enable Interrupt (1/100 sec Interrupt)

    initAnalog();			// Enable ADC Potentiometers

    I2C_init();              // Enable I2C Communication
    I2C_Write(MMA7660Adress, 0x07, 0x01); // Configure 3-Axis Accelerometer (Standard mode)
    initBuzzer();

    initLCD();			// Enable LCD Screen

    level = 1;// Level counter; Controls game difficulty. Starts at level 1.

    // Run game and return
    // 0: If player died
    // 1: If complete level.
    while (1) {
    HighscoreCheck(1000);
    char testChar[3];
    for(uint8_t i = 0; i < 3; i++) {
        testChar [i] = ReadFromFlash(0x0800F808+i*2);
    }
    uint16_t test = ReadFromFlash(0x0800F80E);
    gotoXY(1,1);
    printf("%c",testChar[0]);
    printf("%c",testChar[1]);
    printf("%c : ",testChar[2]);
    printf("%d",test);
    while(readJoystick>20){}
    }

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
    }
}

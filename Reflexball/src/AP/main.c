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
    int SelectedMenuBlock;
    char EnableSelection = 1;
    char MenuState = 1;





	// Output Variables




	// Initialize functions
	init_usb_uart(115200); 	// Initialize USB serial at 115200 baud

    fgcolor(15);

    // Print main menu.
    PrintMenu(1, &SelectedMenu);

    SelectedMenu = 1;
    SelectedMenuBlock = 1;

        // Score data, we need to do this once
        uint16_t tempArray[12] = {0x41,0x42,0x43,1234,0x44,0x45,0x46,123,0x47,0x48,0x49,12};
        InitFlash();
        WriteToFlash(tempArray);


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


    wait(300);

         // MAIN LOOP.
        while(1){

            // Read joystik.
            JoyInput = readJoystick();

            // If joystick up or down.
            if (EnableSelection == 1 && (JoyInput == 1 || JoyInput == 2)) {

              // Up
              if (JoyInput == 2) {

                // Deselect menu block.
                Select(SelectedMenuBlock,  DESELECT, SelectedMenu);

                // Get next menu block number.
                SelectedMenuBlock = ReturnNextBlockSelectionNumber(UP, SelectedMenuBlock);

                // Select menu block.
                Select(SelectedMenuBlock,  SELECT, SelectedMenu);


              }
              // Down
              else if (JoyInput == 1) {

                // Deselect menu block.
                Select(SelectedMenuBlock,  DESELECT, SelectedMenu);

                // Get next menu block number.
                SelectedMenuBlock = ReturnNextBlockSelectionNumber(DOWN, SelectedMenuBlock);

                // Select menu block.
                Select(SelectedMenuBlock,  SELECT, SelectedMenu);

              }

              // Disable joystick selection.
              EnableSelection = 0;
            }


            // If joystick is in neutral position.
            if (JoyInput == 0) {
                // Enable joystick selection.
                EnableSelection = 1;

            }

            // If joystick click.
            if (EnableSelection == 1 && JoyInput == 16) {
                // Get new menu state.
                UpdateState(SelectedMenu, SelectedMenuBlock, &SelectedMenu);
                SelectedMenuBlock = 1;

                // Change background to black.
                bgcolor(0);

                // Print new menu.
                PrintMenu(SelectedMenu, &SelectedMenu);

                // Disable joystick selection.
                EnableSelection = 0;
            }

        }


}

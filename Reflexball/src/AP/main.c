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

#define MMA7660Adress 0x4C << 1



int main(void)   {

    //// INITIALIZE ////

    globalTime = 0; // Set global Time to zero.

    // Uncomment to clear highscore
    //InitFlash();

    clearScore();   // If Score is noise, Set to ZERO; Else keep as is.

    initGPIO();			   	// Enable GPIO Clock Pins.

    initDACNoise();         // Enable DAC Noise generation.

    I2C_init();             // Enable I2C Communication

    // INPUTS
    I2C_Write(MMA7660Adress, 0x07, 0x01); // Configure 3-Axis Accelerometer (Standard mode)
    initAnalog();			// Enable ADC Potentiometers
    initJoystick();         // Enable joystick input.

    // OUTPUTS
    initBuzzer();
    initLCD();			    // Enable LCD Screen
    initLED();              // Enable LED

    initInterrupt();		// Enable 100 Hz Interrupt: globalTime increments.

    // ASCII array.
    char ASCIIARRAYTYPE;

    // MENU VARIABLES
    uint8_t SelectedMenu = 1;
    uint8_t SelectedMenuBlock = 1;
    uint16_t JoyInput;
    uint8_t EnableSelection = 1;

    // ENABLE PuTTy Connection
	init_usb_uart(115200); 	// Initialize USB serial at 115200 baud

    // Print main menu.
    fgcolor(15); // white
    PrintMenu(1, &SelectedMenu);

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

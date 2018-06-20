#include "Menu.h"


// Print text fra 2D array.
void PrintOutTextArray(char *TextArray, uint8_t xCor, uint8_t yCor, uint8_t RowTotal, uint8_t ColTotal) {

  // Move cursor to (xCor,yCor)
  gotoXY(xCor,yCor);

  // Run through rows
  for (int RowI = 0 ; RowI < RowTotal ; RowI++) {

    // Run trough columns.
    for (int ColI = 0 ; ColI < ColTotal ; ColI++) {

        // Print out text.
        printf("%c ", *(TextArray + RowI*ColTotal + ColI));

    }

    yCor++;

    // Go to new row.
    gotoXY(xCor, yCor);
  }
}
//// Print text fra 2D array.
//void PrintOutTextArray(char *TextArray, uint8_t xCor, uint8_t yCor, uint8_t RowTotal, uint8_t ColTotal) {
//
//  // Move cursor to (xCor,yCor)
//  gotoXY(xCor,yCor);
//
//  // Run through rows
//  for (int RowI = 0 ; RowI < RowTotal ; RowI++) {
//
//    // Run trough columns.
//    for (int ColI = 0 ; ColI < ColTotal ; ColI++) {
//
//        // Print out text.
//        printf("%c ", *(TextArray + RowI*ColTotal + ColI));
//
//    }
//
//    yCor++;
//
//    // Go to new row.
//    gotoXY(xCor, yCor);
//
//  }
//
//
//   // printf("dfg");
//   // printf("\nvalue: %c", h);
//  // Run trough columns.
////  for (int RowI = 0; RowI < MaxRowI; RowI++) {
////
////    // Run trough rows.
////    for (int ColI = 0; ColI < MaxColI; ColI++) {
////
////      // Print out char from text array.
////      printf("%c", TextArray[RowI][ColI]);
////
////    }
////
////    yCor++;
////
////    // Go to new row.
////    gotoXY(xCor, yCor);
////
////
////  }
//}


void ClearData(char ASCIIARRAYTYPE) {



    for (int i=0; i<12; i++) {

        for (int j=0; j<5; j++) {

            for (int g=0; g<9; g++) {

            ASCIIArray[i][j][g] = ' ';

            }

        }

    }

}

void CreateMenuText(char ASCIIARRAYTYPE, uint8_t i, char* Text) {

    // Top
    for (int g=0; g < 9; g++) {
        ASCIIArray[i][0][g] = '*';
    }

    // Bounds
    for (int g=1; g < 4; g++) {
        ASCIIArray[i][g][0] = '*';
        ASCIIArray[i][g][8] = '*';
    }

    // Bottom
    for (int g=0; g < 9; g++) {
        ASCIIArray[i][4][g] = '*';
    }


    // Insert text
    for (int j=0; j< strlen(Text); j++) {
            char t = Text[j];

            ASCIIArray[i][2][j+1] = t;

    }

}

/*
// Print title.
void PrintTitle(char TITLEASCIIARRAYTYPE) {

 // // Print
  //PrintOutTextArray(ASCIITitleArray, 0, 0);

}*/

//// Print main menu.
//void PrintMainMenu(){
//    PrintFromASCII("PLAY",75,20);
//    PrintFromASCII("HIGHSCORE",75,30);
//    PrintFromASCII("HELP",75,40);
//}
//
//// Player menu.
//void PrintPlayerMenu(char ASCIIARRAYTYPE){
//    PrintFromASCII("SINLGE PLAYER",75,20);
//    PrintFromASCII("PLAYER VS PLAYER",75,30);
//}

// Score menu.
//void PrintScoreMenu(){
//
//}
// Help menu.
void PrintHelp(){
    fgcolor(15);
    gotoXY(75,13);
  printf("To navigate the menu, use the joystick to highlight");
  gotoXY(75,14);
   printf("menu items and press the joystick to select a menu.");
   gotoXY(75,15);
   printf("When in the play menu, select either single player");
   gotoXY(75,16);
   printf("or player vs player. The player vs player mode will");
   gotoXY(75,17);
   printf("start the game for player 1 where, after player one");
   gotoXY(75,18);
   printf("has lost, player 2 plays his game. After the game, ");
   gotoXY(75,19);
   printf("the player(s) with the most points win, and if eligible, ");
   gotoXY(75,20);
   printf("will be taken to the highscore submission menu. ");
   gotoXY(75,21);
   printf("Entering the highscore menu will show the current ");
   gotoXY(75,22);
   printf("highscores for 5 second and then return to the main menu. ");
   gotoXY(75,23);
   printf("The game will do a short countdown before launching the ball. ");
   gotoXY(75,24);
   printf("When playing the game, have the USB cable pointed away ");
   gotoXY(75,25);
   printf("from you and tilt the microcontroller from");
   gotoXY(75,26);
   printf("left to right to move the striker.");
   gotoXY(75,27);
   printf("To get a high score, keep the ball in the air for");
   gotoXY(75,28);
   printf("a long time and remove as many bricks as possible.");
   gotoXY(75,29);
   printf("Each time the ball reaches the bottom of the screen,");
   gotoXY(75,30);
   printf("the player will lose a life. After all lifes");
   gotoXY(75,31);
   printf("have been lost, the game ends.");
   gotoXY(75,32);
   printf("Should you remove a brick a powerup has a chance to spawn");
   gotoXY(75,33);
   printf("and catching it with the striker, will slow");
   gotoXY(75,34);
   printf("the balls speed for 10 seconds.");
   gotoXY(75,35);
   printf("On the LCD display you will find information about");
   gotoXY(75,36);
   printf("your current game and the LED color will indicate your");
   gotoXY(75,37);
   printf("current amount of HP. In the highscore submission menu,");
   gotoXY(75,38);
   printf("use the left potentiometer to select each character.");
   gotoXY(75,39);
   printf("When you want to select that character,");
   gotoXY(75,40);
   printf("press the joystick button.");
   gotoXY(75,41);
   printf("Should you feel the need to pause the game or");
   gotoXY(75,42);
   printf("switch away from the game quick,");
   gotoXY(75,43);
   printf("use the boss key while playing the game.");
   gotoXY(75,44);
   printf("The boss key can be activated by pressing");
   gotoXY(75,45);
   printf("the joystick button while a game is running.");
   gotoXY(75,46);
   printf("When pressing the boss key, the screen will be covered");
   gotoXY(75,47);
   printf("with a blue screen of death similar layout.");
   gotoXY(75,48);
   printf("To resume, press the joystick button again.");
}

// Clear menu Lines.
void ClearLines(uint8_t LineFrom, uint8_t LineTo) {

  for (int i = LineFrom; i <= LineTo; i++) {

    // Goto XY.
    gotoXY(0,i);

    // Clear to the end of the line.
    clreol();
  }



}

// Return menu selection.
char ChangeSelection(char Up, char SelectionIndex, char MaxSelection) {

    // If count up.
    if (Up == 1) {
       SelectionIndex++;
    }
    else {
        SelectionIndex--;
    }
    // If max menu selection.
    if (SelectionIndex > MaxSelection) {
        SelectionIndex = 1;
    }
    else if (SelectionIndex < 1) {
        SelectionIndex = MaxSelection;
    }

    return SelectionIndex;


}

/**
  * Descripton:
  * Argument:
  * Return value:
  */
// Print the menu options.
void PrintMenu(int state, int *Newmenu) {

    // Menu sate.
    switch(state) {

        case 1: // Main menu.
            clrscr();
            fgcolor(15);
            ClearLines(20,45);
            GotoMenuState(1);
            //PrintMainMenu();
            break;
        case 2: // Play menu.
            ClearLines(20,45);
            GotoMenuState(2);

            break;
        case 3: // Highscore menu.
            clrscr();
             fgcolor(15);
            PrintFromASCII("REFLEXBALL",69,7);
            PrintScore();
            clrscr();
             *Newmenu = 1;
            GotoMenuState(1);

            break;
            case 4: // Help.
                ClearLines(20,45);
                PrintHelp();
                wait(500);
                clrscr();
                *Newmenu = 1;
                GotoMenuState(1);
            break;
        // Start game loop.
        case 5:
            StartGameLoop(1);

            // Clear screen.
            clrscr();
             *Newmenu = 1;
            GotoMenuState(1);

        break;
        case 6:
            StartGameLoop(2);

            // Clear screen.
            clrscr();
            *Newmenu = 1;
            GotoMenuState(1);
        break;
        }


}

/**
  * Descripton: This functions change and draw the menu. The state argument selects menu state.
  * Argument:  state: Menu state
  * Return value: None.
  */
// Print the menu options.
void GotoMenuState(int state ) {

    // Menu sate.
    switch(state) {

         // Main menu.
        case 1:
          clrscr();
          fgcolor(15);
            PrintFromASCII("REFLEXBALL",69,7);

          // Draw and select menu block 1.
          Select(1, SELECT, 1);

          // Draw menu block 2.
          Select(2, DESELECT, 1);

          // Draw menu block 3.
          Select(3, DESELECT, 1);
        break;

        // Play menu.
        case 2:
          clrscr();
           fgcolor(15);
            PrintFromASCII("REFLEXBALL",69,7);

          // Draw and select menu block.
          Select(1, SELECT, 2);

          // Draw menu block.
          Select(2, DESELECT, 2);

          // Draw menu block.
          Select(3, DESELECT, 2);
        break;

        // Highscore menu.
        case 3:
          ClearLines(20,30);
          //PrintScoreMenu(ASCIIArray);
        break;

        // Help.
        case 4:
          ClearLines(20,30);
          printf("HELP YOUR SELF! :)");
        break;


    }

}

// Return next menu block selection number.
char GetNextMenuBlockSelection(bool Up, char SelectionIndex, char MaxSelection) {

    // If count up.
    if (Up == 1) {
       SelectionIndex++;
    }
    else {
        SelectionIndex--;
    }
    // If max menu selection.
    if (SelectionIndex > MaxSelection) {
        SelectionIndex = 1;
    }
    else if (SelectionIndex < 1) {
        SelectionIndex = MaxSelection;
    }

    return SelectionIndex;


}

/**
  * Descripton: This function return the next block selection number.
  * Argument:  Up: Up selection, CurrentBlockSelectionNumer: Current block selection number.
  * Return value: Next block selection number.
  */
uint8_t ReturnNextBlockSelectionNumber(uint8_t Up, int8_t CurrentBlockSelectionNumer) {

    if (Up == 1) {
        CurrentBlockSelectionNumer++;
    }
    else {
        CurrentBlockSelectionNumer--;
    }


    if (CurrentBlockSelectionNumer > 3) {
        CurrentBlockSelectionNumer = 1;
    }
    else if (CurrentBlockSelectionNumer < 1) {
        CurrentBlockSelectionNumer = 3;
    }

    return CurrentBlockSelectionNumer;

}

/**
  * Descripton: This function deselect and select menu blocks..
  * Argument:  selection: Selection menu number, highlight: deselect/select, state: Menu state
  * Return value: None.
  */
void Select(int  selection,  int  highlight, int state) {
    if(highlight == 1){
    fgcolor(1);
    }
    else{
    fgcolor(15);
    }
    switch(state) {
        case 1 :
        switch(selection) {
            case 1:
                PrintFromASCII("PLAY",86,20);
                break;
            case 2:
               PrintFromASCII("HIGHSCORE",72,30);
               break;
            case 3:
               PrintFromASCII("HELP",88,40);
               break;
        }
        break;
        case 2:
        switch(selection) {
            case 1:
               PrintFromASCII("SINGLE PLAYER",62,20);
               break;
            case 2:
               PrintFromASCII("PLAYER VS PLAYER",53,30);
               break;
            case 3:
               PrintFromASCII("RETURN",81,40);
               break;
        }
        break;
        case 3:
        switch(selection) {
            PrintScore();
        }
        break;
        case 4:

            fgcolor(15);
            printf("HELP YOURSELF! :)");
            break;
        }
}

// Call function in Menu, whenever user press Joystick button.
void UpdateState(int state, int selection, int *Newmenu) {
	switch(state) {
		case 1 : // Titlepage
		switch(selection) {
			case 1 : // Play
			*Newmenu = 2;
            break;
			case 2 : // Highscore
			*Newmenu  = 3;
            break;
			case 3 : // Help
			*Newmenu  = 4;
			break;
		}
		break;
		// Player menu.
		case 2 :
            switch(selection) {
			case 1 : // 1 player
			*Newmenu = 5;
            break;
			case 2 : // 2 player
			*Newmenu  = 6;
            break;
			case 3 : // Return to main menu.
			*Newmenu  = 1;
			break;
		}
		break;
		/*
		* case 2 :
		* Next state = Game State?
		*/
//		case 3 : // Highscore
//		*ChangeSelection  = 1;
//        break;
//		case 4 : // Help
//		*ChangeSelection  = 1;
//        break;
	}
//	selection = 1;
}

void PrintEnd(char ASCIIEnd, int titleX, int titleY) {

PrintOutTextArray(ASCIIEnd, titleX-10, titleY-10, 5, 9);

}
/*
void UpdateHighScore() {

}
*/

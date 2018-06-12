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

void ClearData(char ASCIIARRAYTYPE) {

    for (int i=0; i<12; i++) {
        for (int j=0; j<5; j++) {
            for (int g=0; g<9; g++) {
            ASCIIArray[i][j][g] = ' ';
            }
        }
    }
}


void InitializeMenu(char ASCIIARRAYTYPE){

  // Clear ASCIIArray.
  ClearData(ASCIIArray);

  // Create menu text.
  CreateMenuText(ASCIIArray, 0, "Play");
  CreateMenuText(ASCIIArray, 1, "Score");
  CreateMenuText(ASCIIArray, 2, "Help");
  CreateMenuText(ASCIIArray, 3, "1 player");
  CreateMenuText(ASCIIArray, 4, "2 player");

}


// Print title.
void PrintTitle(char TITLEASCIIARRAYTYPE) {

 // Print
  PrintOutTextArray(ASCIITitleArray, 5, 0, 9, 9);

}

// // Print main menu.
// void PrintMainMenu(char ASCIIARRAYTYPE){
//
//   int x = 0;
//   int y = 0;
//
//
//   // Print text from ASCIIArray.
//   for (int i = 0; i <= 2; i++) {
//
//     // Print text.
//     PrintOutTextArray(ASCIIArray[i],x,y,5,9);
//
//     y += 5;
//
//   }
//
// }

// // Player menu.
// void PrintPlayerMenu(char ASCIIARRAYTYPE){
//
//     // Select menu.
//     Select(1, 1, ASCIIArray, 2);
//
//     // Select menu.
//     Select(2, 0, ASCIIArray, 2);
// }

// // Score menu.
// void PrintScoreMenu(char ASCIIARRAYTYPE){
//
//   int x = 10;
//   int y = 10;
//
//
//   // Run through ASCIIArray.
//   for (int i = 5; i <= 10; i=i+2) {
//     // Print 'inital' text.
//    // PrintOutTextArray(ASCIIArray[i], x, y);
//
//     x += 20;
//
//     // Print 'score' text.
//    // PrintOutTextArray(ASCIIArray[i+1], x, y);
//
//   }
//
//     y += 20;
//
//
//
//
// }
// // Help menu.
// void PrintHelp(char ASCIIARRAYTYPE){
//
//
//
// }

// Clear menu Lines.
void ClearLines(uint8_t LineFrom, uint8_t LineTo) {

  for (int i = LineFrom; i <= LineTo; i++) {

    // Goto XY.
    gotoXY(0,i);

    // Clear to the end of the line.
    clreol();
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

// Print the menu options.
void GotoMenuState(int state, char ASCIIARRAYTYPE) {

  // Select(Selection, highlight, ASCIIArray, MenuState)

  switch(state) {

     // Main menu.
    case 1:
      ClearLines(20,30);

      // Draw and select menu block.
      Select(1, SELECT, ASCIIArray, 1);

      // Draw menu block.
      Select(2, DESELECT, ASCIIArray, 1);

      // Draw menu block.
      Select(3, DESELECT, ASCIIArray, 1);
    break;

    // Play menu.
    case 2:
      ClearLines(20,30);
      // Draw and select menu block.
      Select(1, SELECT, ASCIIArray, 2);

      // Draw menu block.
      Select(2, SELECT, ASCIIArray, 2);
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

    // 1 Player.
    case 5:
      ClearLines(20,30);
    //  PrintScoreMenu(ASCIIArray);
    break;
    // 2 Player.

    case 6:
      ClearLines(20,30);
    //  PrintScoreMenu(ASCIIArray);
    break;
  }

}

void Select(int  selection,  int  highlight,   char  ASCIIARRAYTYPE, int state) {
    if(highlight == 0){
    bgcolor(0);
    }
    else{
    bgcolor(1);
    }
    switch(state) {
        case 1 :
        switch(selection) {
            case 1:
                PrintOutTextArray(ASCIIArray[0], menuBlockX, menuBlock1Y, 5, 9);
                break;
            case 2:
               PrintOutTextArray(ASCIIArray[1], menuBlockX, menuBlock2Y, 5, 9);
               break;
            case 3:
               PrintOutTextArray(ASCIIArray[2], menuBlockX, menuBlock3Y, 5, 9);
               break;
        }
        break;
        case 2:
        switch(selection) {
            case 1:
               PrintOutTextArray(ASCIIArray[3], menuBlockX, menuBlock1Y, 5, 9);
               break;
            case 2:
               PrintOutTextArray(ASCIIArray[4], menuBlockX, menuBlock2Y, 5, 9);
               break;
        }
        break;
        case 3:
        switch(selection) {
            case 1:
               PrintOutTextArray(ASCIIArray[5], menuBlockX, menuBlock1Y, 5, 9);
               break;
            case 2:
                PrintOutTextArray(ASCIIArray[6], menuBlockX, menuBlock2Y, 5, 9);
                break;
            case 3:
                PrintOutTextArray(ASCIIArray[7], menuBlockX, menuBlock3Y, 5, 9);
                break;
        }
        break;
        case 4:
            bgcolor(0);
            PrintOutTextArray(ASCIIArray[8], menuBlockX, menuBlock1Y, 5, 9);
            break;
        }



}

// // Call function in Menu, whenever user press Joystick button.
// void UpdateState(int state, int selection) {
//
// 	switch(state) {
// 		case 1 : // Titlepage
// 		switch(selection) {
// 			case 1 : // Play
// 			state = 2;
//             break;
// 			case 2 : // Highscore
// 			state = 3;
//             break;
// 			case 3 : // Help
// 			state = 4;
// 			break;
// 		}
// 		/*
// 		* case 2 :
// 		* Next state = Game State?
// 		*/
// 		case 3 : // Highscore
// 		state = 1;
//         break;
// 		case 4 : // Help
// 		state = 1;
//         break;
// 	}
// 	selection = 1;
//
// }

void PrintEnd(char ASCIIEnd, int titleX, int titleY) {
PrintOutTextArray(ASCIIEnd, titleX-10, titleY-10,5, 9);
}

void UpdateHighScore() {

}

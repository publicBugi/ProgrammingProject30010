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


   // printf("dfg");
   // printf("\nvalue: %c", h);
  // Run trough columns.
//  for (int RowI = 0; RowI < MaxRowI; RowI++) {
//
//    // Run trough rows.
//    for (int ColI = 0; ColI < MaxColI; ColI++) {
//
//      // Print out char from text array.
//      printf("%c", TextArray[RowI][ColI]);
//
//    }
//
//    yCor++;
//
//    // Go to new row.
//    gotoXY(xCor, yCor);
//
//
//  }
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


// Print title.
void PrintTitle(char TITLEASCIIARRAYTYPE) {

 // // Print
  //PrintOutTextArray(ASCIITitleArray, 0, 0);

}

// Print main menu.
void PrintMainMenu(char ASCIIARRAYTYPE){

  int x = 0;
  int y = 0;


  // Print text from ASCIIArray.
  for (int i = 0; i <= 2; i++) {

    // Print text.
    PrintOutTextArray(ASCIIArray[i],x,y,5,9);

    y += 5;

  }

}

// Player menu.
void PrintPlayerMenu(char ASCIIARRAYTYPE){
  int x = 0;
  int y = 0;

//  // Print text from ASCIIArray.
//  for (int i = 3; i <= 4; i++) {
//
//    // Print text.
//   PrintOutTextArray(ASCIIArray[i],x,y, 5, 9);
//
//    y += 5;
//
//  }
    // Select menu.
    Select(1, 1, ASCIIArray, 2);

    // Select menu.
    Select(2, 0, ASCIIArray, 2);
}

// Score menu.
void PrintScoreMenu(char ASCIIARRAYTYPE){

  int x = 10;
  int y = 10;


  // Run through ASCIIArray.
  for (int i = 5; i <= 10; i=i+2) {
    // Print 'inital' text.
   // PrintOutTextArray(ASCIIArray[i], x, y);

    x += 20;

    // Print 'score' text.
   // PrintOutTextArray(ASCIIArray[i+1], x, y);

  }

    y += 20;




}
// Help menu.
void PrintHelp(char ASCIIARRAYTYPE){
  printf("HELP YOUR SELF! :)");


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

// Print the menu options.
void PrintMenu(int state, char ASCIIARRAYTYPE) {

  // ASCIIArray[] = ["Play game", "Highscore", "Help", "1 Player", "2 Player", "Initial 1","Score 1", "Initial 2","Score 2", "Initial 3","Score 3"]


  switch(state) {

    case 1: // Main menu.
    ClearLines(0,30);
    PrintMainMenu(ASCIIArray);
    break;

    case 2: // Play menu.
    ClearLines(20,30);
    PrintPlayerMenu(ASCIIArray);
    break;
    case 3: // Highscore menu.
    ClearLines(20,30);
    PrintScoreMenu(ASCIIArray);
    break;
    case 4: // Help.
    ClearLines(20,30);
    PrintScoreMenu(ASCIIArray);
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
                PrintOutTextArray(ASCIIArray[0], menuBlock1X, menuBlock1Y, 5, 9);
                break;
            case 2:
               PrintOutTextArray(ASCIIArray[1], menuBlock2X, menuBlock2Y, 5, 9);
               break;
            case 3:
               PrintOutTextArray(ASCIIArray[2], menuBlock3X, menuBlock3Y, 5, 9);
               break;
        }
        break;
        case 2:
        switch(selection) {
            case 1:
               PrintOutTextArray(ASCIIArray[3], menuBlock1X, menuBlock1Y, 5, 9);
               break;
            case 2:
               PrintOutTextArray(ASCIIArray[4], menuBlock2X, menuBlock2Y, 5, 9);
               break;
        }
        break;
        case 3:
        switch(selection) {
            case 1:
               PrintOutTextArray(ASCIIArray[5], menuBlock1X, menuBlock1Y, 5, 9);
               break;
            case 2:
                PrintOutTextArray(ASCIIArray[6], menuBlock2X, menuBlock2Y, 5, 9);
                break;
            case 3:
                PrintOutTextArray(ASCIIArray[7], menuBlock3X, menuBlock3Y, 5, 9);
                break;
        }
        break;
        case 4:
            bgcolor(0);
            PrintOutTextArray(ASCIIArray[8], menuBlock1X, menuBlock1Y, 5, 9);
            break;
        }



}

// Call function in Menu, whenever user press Joystick button.
void UpdateState(int state, int selection) {

	switch(state) {
		case 1 : // Titlepage
		switch(selection) {
			case 1 : // Play
			state = 2;
            break;
			case 2 : // Highscore
			state = 3;
            break;
			case 3 : // Help
			state = 4;
			break;
		}
		/*
		* case 2 :
		* Next state = Game State?
		*/
		case 3 : // Highscore
		state = 1;
        break;
		case 4 : // Help
		state = 1;
        break;
	}
	selection = 1;

}

void PrintEnd(char ASCIIEnd, int titleX, int titleY) {
PrintOutTextArray(ASCIIEnd, titleX-10, titleY-10, 5, 9);
}

void UpdateHighScore() {

}

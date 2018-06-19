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

// Print main menu.
void PrintMainMenu(){
    PrintFromASCII("PLAY",75,20);
    PrintFromASCII("HIGHSCORE",75,30);
    PrintFromASCII("HELP",75,40);
}

// Player menu.
void PrintPlayerMenu(char ASCIIARRAYTYPE){
    PrintFromASCII("SINLGE PLAYER",75,20);
    PrintFromASCII("PLAYER VS PLAYER",75,30);
}

// Score menu.
void PrintScoreMenu(){
    PrintScore();
}
// Help menu.
void PrintHelp(){
  printf("HELP YOURSELF! :)");
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
    ClearLines(20,45);
    PrintMainMenu();
    break;
    case 2: // Play menu.
    ClearLines(20,45);
    PrintPlayerMenu(ASCIIArray);
    break;
    case 3: // Highscore menu.
    ClearLines(20,45);
    PrintScoreMenu();
    break;
    case 4: // Help.
    ClearLines(20,45);
    PrintHelp();
    break;
  }

}

void Select(int  selection,  int  highlight, int state) {
    if(highlight == 0){
    fgcolor(1);
    }
    else{
    fgcolor(15);
    }
    switch(state) {
        case 1 :
        switch(selection) {
            case 1:
                PrintFromASCII("PLAY",75,20);
                break;
            case 2:
               PrintFromASCII("HIGHSCORE",75,30);
               break;
            case 3:
               PrintFromASCII("HELP",75,40);
               break;
        }
        break;
        case 2:
        switch(selection) {
            case 1:
               PrintFromASCII("SINGLE PLAYER",75,20);
               break;
            case 2:
               PrintFromASCII("PLAYER VS PLAYER",75,30);
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
/*
void UpdateHighScore() {

}
*/

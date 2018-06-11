

// Print text fra 2D array.
void PrintOutTextArray(char TextArray[][]) {
//  int total = sizeof(TextArray);
  //int col = sizeof(TextArray[0]);
//  int row = total / col;

  int MaxColI = sizeof(TextArray) / sizeof(ASCIITitle[0][0]);
  int MaxRowI = sizeof(TextArray) / MaxColI;

  // Run trough columns.
  for (int RowI = 0; RowI < MaxRowI; RowI++) {

    // Run trough rows.
    for (int ColI = 0; ColI < MaxColI; ColI++) {

      // Print out char from text array.
      printf("%c", TextArray[RowI][ColI]);

    }

  }
}


// Print title.
void PrintTitle(char ASCIITitle[][], uint8_t titleX, uint8_t titleY) {

  // Move cursor to (titleX,titleY)
  gotoXY(titleX,titleY);

  // Print
  PrintOutTextArray(ASCIITitle);

}

// Print the menu options.
void PrintMenu(int state, char ASCIIArray[][][]) {
  char From, To;
// ASCIIArray[] = ["Play game", "Highscore", "Help", "1 Player", "2. Player", "Initial","Score"]
  switch(state) {

      case 1: // Play menu
        From = 0;
        To = 2;

      case 2: // Highscore menu
        From = 3;
        To = 4;
  }


}

void Select(int  *selection,  int  *high-light,   char  ASCIIArray[][][], int *state) {
    if(high-light == 0){
    bgcolor(0);
    }
    else{
    bgcolor(1);
    }
    switch(state) {
        case 1 :
        switch(selection) {
            case 1:
                PrintOutTextArray(ASCIIArray[0][][], menuBlock1X, menuBlock1Y);
            case 2:
                PrintOutTextArray(ASCIIArray[1][][], menuBlock2X, menuBlock2Y);
            case 3:
                PrintOutTextArray(ASCIIArray[2][][], menuBlock3X, menuBlock3Y);
        }
        case 2:
        switch(selection) {
            case 1:
                PrintOutTextArray(ASCIIArray[3][][], menuBlock1X, menuBlock1Y);
            case 2:
                PrintOutTextArray(ASCIIArray[4][][], menuBlock2X, menuBlock2Y);
        }
        case 3:
        switch(selection) {
            case 1:
                PrintOutTextArray(ASCIIArray[5][][], menuBlock1X, menuBlock1Y);
            case 2:
                PrintOutTextArray(ASCIIArray[6][][], menuBlock2X, menuBlock2Y);
            case 3:
                PrintOutTextArray(ASCIIArray[7][][], menuBlock3X, menuBlock3Y);
        }
        case 4:
            bgcolor(0);
            PrintOutTextArray(ASCIIArray[8][][], menuBlock1X, menuBlock1Y);
        }


    }


    bgcolor(0);
    selection
    ==

    =
}

// Call function in Menu, whenever user press Joystick button.
void UpdateState(int *state, int *selection) {
	switch(state) {
		case 1 : // Titlepage
		switch(selection) {
			case 1 : // Play
			state = 2;

			case 2 : // Highscore
			state = 3;

			case 3 : // Help
			state = 4;
		}
		/*
		* case 2 :
		* Next state = Game State?
		*/
		case 3 : // Highscore
		state = 1;

		case 4 : // Help
		state = 1;

	}
	selection = 0;

}

void PrintEnd(char ASCIIEnd, int titleX, title Y) {

}

void UpdateHighScore() {

}

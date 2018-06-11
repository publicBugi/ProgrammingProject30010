

// Print text fra 2D array.
void PrintOutTextArray(char TextArray[][], uint8_t xCor, uint8_t yCor) {

  int MaxColI = sizeof(TextArray) / sizeof(ASCIITitle[0][0]);
  int MaxRowI = sizeof(TextArray) / MaxColI;

  // Move cursor to (xCor,yCor)
  gotoXY(xCor,yCor);

  // Run trough columns.
  for (int RowI = 0; RowI < MaxRowI; RowI++) {

    // Run trough rows.
    for (int ColI = 0; ColI < MaxColI; ColI++) {

      // Print out char from text array.
      printf("%c", TextArray[RowI][ColI]);

    }

    yCor++;

    // Go to new row.
    gotoXY(xCor, yCor);


  }
}


// Print title.
void PrintTitle(char ASCIITitle[][]) {

  // Print
  PrintOutTextArray(ASCIITitle, 0, 0);

}

// Print main menu.
void PrintMainMenu(char ASCIIArray[][][]){

  x = 10;
  y = 10;

  // ASCIIArray[] = ["Play game", "Highscore", "Help", "1 Player", "2. Player", "Initial","Score"]

  // Print text from ASCIIArray.
  for (int i = 0; i <= 2; i++) {

    // Print text.
    PrintOutTextArray(ASCIIArray[i],x,y);

    y += 20;

  }

}

// Player menu.
void PrintPlayerMenu(char ASCIIArray[][][]){
  x = 10;
  y = 10;

  // Print text from ASCIIArray.
  for (int i = 3; i <= 4; i++) {

    // Print text.
    PrintOutTextArray(ASCIIArray[i],x,y);

    y += 20;

  }


}

// Score menu.
void PrintScoreMenu(char ASCIIArray[][][]){

  x = 10;
  y = 10;


  // Run through ASCIIArray.
  for (int i = 5; i <= 10; i=i+2) {
    // Print 'inital' text.
    PrintOutTextArray(ASCIIArray[i], x, y);

    x += 20;

    // Print 'score' text.
    PrintOutTextArray(ASCIIArray[i+1], x, y);

  }

    y += 20;

  }


}
// Help menu.
void PrintHelp(char ASCIIArray[][][]){
  printf("HELP YOUR SELF! :)");


}

// Clear Menu Lines.
void ClearMenuLines(uint8_t LineFrom, uint8_t LineTo) {

  for (int i = LineFrom; i <= LineTo; i++) {

    // Goto XY.
    gotoXY(i,0);

    // Clear to the end of the line.
    clreol();
  }



}

// Print the menu options.
void PrintMenu(int state, char ASCIIArray[][][]) {

  // ASCIIArray[] = ["Play game", "Highscore", "Help", "1 Player", "2 Player", "Initial 1","Score 1", "Initial 2","Score 2", "Initial 3","Score 3"]


  switch(state) {

    case 1: // Main menu.
    ClearMenuLines(20,30);
    PrintMainMenu(ASCIIArray[][][]);

    case 2: // Play menu.
    ClearMenuLines(20,30);
    PrintPlayerMenu(ASCIIArray[][][]);

    case 3: // Highscore menu.
    ClearMenuLines(20,30);
    PrintScoreMenu(ASCIIArray[][][]);

    case 4: // Help.
    ClearMenuLines(20,30);
    PrintScoreMenu(ASCIIArray[][][]);

  }

}

void Select() {

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

void PrintEnd() {

}

void UpdateHighScore() {

}

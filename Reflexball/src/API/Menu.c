void PrintTitle(char ASCIITitle[], uint8_t titleX, uint8_t titleY) {
  // Move cursor to (titleX,titleY)
  gotoXY(titleX,titleY);

  //size_t NumberOfElements = sizeof(ASCIITitle)/sizeof(ASCIITitle[0]);

  // Run trough columns
  for (int RowI = 0; RowI < 5; RowI++) {
    for (int ColI = 0; ColI < 9; ColI++) {

      
    }
  }

}

void PrintMenu() {

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

}

void PrintEnd() {

}

void UpdateHighScore() {

}

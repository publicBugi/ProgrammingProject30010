void PrintTitle(){


}

void PrintMenu() {

}

void Select(int  *selection,  int  *high-light,   char  ASCIIArray[][][], int *state) {
    switch(state) {
        case 1 :
        switch(selection) {
            case 1:
            switch(high-light) {
                case 0:
            }
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

}

void PrintEnd() {

}

void UpdateHighScore() {

}

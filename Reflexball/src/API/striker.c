#include "striker.h"

//// STRIKER FUNCTIONS ////
// Updates and Draws striker position
void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker){
    striker->prevpos = striker->currpos;


    striker->currpos = striker->currpos - readRoll(20, 2);

    // Keep striker within bounds
    if (striker->currpos < 1 || striker->currpos > (putWidth - striker->strikersize - 1)) {
        striker->currpos = striker->prevpos;
    }



    fgcolor(0);
    gotoXY(striker->prevpos, putStrikerPos);
    for (int i = 0; i < striker->strikersize; i++){
            gameArray[putStrikerPos][striker->prevpos + i] = 0;
            putchar(32);
    }

    fgcolor(8);
    gotoXY( striker->currpos, putStrikerPos);
    uint8_t value = 2;
	for (uint8_t i = 0; i < striker->strikersize; i += striker->strikerinc){
        for (uint8_t s = 0; s < striker->strikerinc; s++){
            gameArray[putStrikerPos][striker->currpos + i + s] = value;
            putchar(223);
        }
        value++;
	}
}



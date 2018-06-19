#include "striker.h"

//// STRIKER FUNCTIONS ////
// Updates and Draws striker position
void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker){
    striker->prevpos = striker->currpos;


    uint32_t Roll = readRoll(5,3);
    if (Roll < 5 && Roll > -5){
        Roll = 0;
    }
    striker->currpos = striker->currpos - Roll;

    // Keep striker within bounds
    if (striker->currpos < 1 || striker->currpos > (putWidth - striker->strikersize - 1)) {
        striker->currpos = striker->prevpos;
    }

    fgcolor(0);
    gotoXY(striker->prevpos, putStrikerPos);

    int8_t diff = striker->currpos - striker->prevpos;
    if (diff < 0){
        gotoXY(striker->prevpos+striker->strikersize + diff, putStrikerPos);
        for (int i = 0; i > diff; i--){
            gameArray[putStrikerPos][striker->prevpos - i + striker->strikersize] = 0;
            putchar(32);
        }
    }
    else {
        gotoXY(striker->prevpos, putStrikerPos);
        for (int i = 0; i < diff; i++){
            gameArray[putStrikerPos][striker->prevpos + i] = 0;
            putchar(32);
    }
    }


    fgcolor(15);
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



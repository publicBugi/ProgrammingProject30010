#include "striker.h"

/* Developer    : Hørdur Andreasen
 * Description  : Update Striker based on readRoll(). Keep within Bounds + Deadzone.
 * Argument     : GameArray (Update striker collision), Striker (update Striker position)
 * Return value : Void
 */
void updateStriker(uint8_t gameArray[putHeight][putWidth], struct striker_t *striker){

    // Set Previous position to current position
    striker->prevpos = striker->currpos;

    // Read roll, and maintain Deadzone (Adjust to fit)
    uint32_t Roll = readRoll(5,3);
    if (Roll < 5 && Roll > -5){
        Roll = 0;
    }

    // Calculate new position
    striker->currpos = striker->currpos - Roll;

    // Keep striker within bounds
    if (striker->currpos < 1 || striker->currpos > (putWidth - striker->strikersize - 1)) {
        striker->currpos = striker->prevpos;
    }

    // Remove portion of striker that is different from gameArray and PuTTy
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

    // Overwrite previous Striker and portion not in PuTTY or GameArray.
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



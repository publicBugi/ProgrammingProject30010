#include "bricks.h"


//// BRICKS ////

// Kill brick.
void KillBrick(uint16_t Brickindex, uint8_t gameArray[putHeight][putWidth], struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth) {
    // Change game array of brick to 0 (air).
    for (int x = 0; x < *brickWidth; x++){
        for(int y = 0; y < *brickHeight; y++) {
            gameArray[brick->posY + y][brick->posX + x] = 0;
        }

    }

}

// Print brick counter
void PrintBrickCounter(uint16_t *BrickCounter) {
   // Change color to default.
    fgcolor(15);
    gotoXY(10,80);
    printf("Brick counter: %d  ", *BrickCounter);
}

/* Developer    : Hørdur Andreasen
 * Description  : Draw a brick; Color depending on it's HP. No HP Sets it to black.
 * Argument     : brick, brickHeight, brickWidth.
 * Return value : Void
 */
void drawBox(struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth){
        fgcolor(brick->currHP);

        for (int y = 0; y < *brickHeight; y++){
            gotoXY(brick->posX, brick->posY + y);
                for(int x = 0; x < *brickWidth; x++) {
                    putchar(178);
            }
        }
}


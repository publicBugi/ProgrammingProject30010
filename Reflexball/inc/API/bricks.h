#ifndef _BRICKS_H_
#define _BRICKS_H_

#include "30010_io.h"
#include "ansi.h"
#define putHeight 50
#define putWidth 200

struct brick_t {
    uint8_t posX, posY, MaxHP, currHP, pwrUP;
};

void KillBrick(uint16_t Brickindex, uint8_t gameArray[putHeight][putWidth], struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth);
void drawBox(struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth);


/* Developer    : Hørdur Andreasen
 * Description  : Draw a brick; Color depending on it's HP. No HP Sets it to black.
 * Argument     : brick, brickHeight, brickWidth.
 * Return value : Void
 */
void PrintBrickCounter(uint16_t *BrickCounter);
 #endif

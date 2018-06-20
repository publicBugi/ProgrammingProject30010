#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "30010_io.h"
#include "bricks.h"
#include "ansi.h"

struct pwrUp {
    uint8_t posX, posY;     // Position.
    uint8_t alive;          // Is alive? Will not spawn if set.
    uint8_t enable;         // Is enabled? Will not spawn if set; Lasts 10 seconds.
};

/* Developer    : Hørdur Andreasen
 * Description  : Set Alive and Enabled to 0.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void initPowerup(struct pwrUp *powerup);

/* Developer    : Hørdur Andreasen
 * Description  : Spawn powerup in center of brick.
 * Argument     : Powerup, Brick, BrickHeight and Width. Uses brick data to position in center.
 * Return value : Void
 */
void spawnPowerup(struct pwrUp *powerup, struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth);

/* Developer    : Hørdur Andreasen
 * Description  : Update the position, and kill if out of bounds.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void updatePowerup(struct pwrUp *powerup);

/* Developer    : Hørdur Andreasen
 * Description  : Remove and Draw.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void drawPowerup(struct pwrUp *powerup);

 #endif

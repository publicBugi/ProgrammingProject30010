#include "powerup.h"

/* Developer    : Hørdur Andreasen
 * Description  : Set Alive and Enabled to 0.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void initPowerup(struct pwrUp *powerup) {
    powerup->alive = 0;
    powerup->enable = 0;
}

/* Developer    : Hørdur Andreasen
 * Description  : Spawn powerup in center of brick.
 * Argument     : Powerup, Brick, BrickHeight and Width. Uses brick data to position in center.
 * Return value : Void
 */
void spawnPowerup(struct pwrUp *powerup, struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth) {

    if (powerup->alive == 0) {
        powerup->alive = 1;
        powerup->posX = brick->posX + *brickWidth/2;
        powerup->posY = brick->posY + *brickHeight/2;
        powerup->enable = 0;
    }
}

/* Developer    : Hørdur Andreasen
 * Description  : Update the position, and kill if out of bounds.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void updatePowerup(struct pwrUp *powerup) {
    if (powerup->alive == 1) {
        if (powerup->posY == putHeight){
                gotoXY(powerup->posX, powerup->posY);
                putchar(32);
                powerup->alive = 0;
        }
        else {
                powerup->posY++;
        }
    }
}

/* Developer    : Hørdur Andreasen
 * Description  : Remove and Draw.
 * Argument     : Powerup = Update values.
 * Return value : Void
 */
void drawPowerup(struct pwrUp *powerup){
    if (powerup->alive == 1) {
        gotoXY(powerup->posX, powerup->posY - 1);
        putchar(32);
        gotoXY(powerup->posX, powerup->posY);
        fgcolor(6);
        putchar('*');
    }
}


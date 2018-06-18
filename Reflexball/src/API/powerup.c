#include "powerup.h"


void spawnPowerup(struct pwrUp *powerup, struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth) {

    if (powerup->alive == 0) {
        powerup->alive = 1;
        powerup->posX = brick->posX + *brickWidth/2;
        powerup->posY = brick->posY + *brickHeight/2;
        powerup->enable = 0;
    }
}

void updatePowerup(struct pwrUp *powerup) {
    if (powerup->alive == 1) {
        if (powerup->posY == putHeight){
                powerup->alive = 0;
        }
        else {
                powerup->posY++;
        }
    }
}

void drawPowerup(struct pwrUp *powerup){
    if (powerup->alive == 1) {
        gotoXY(powerup->posX, powerup->posY);
        fgcolor(6);
        putchar('*');

    }
}


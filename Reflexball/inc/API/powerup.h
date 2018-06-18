#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "30010_io.h"
#include "bricks.h"
#include "ansi.h"

struct pwrUp {
    uint8_t posX, posY;
    uint8_t alive;
    uint8_t enable;
};

void initPowerup(struct pwrUp *powerup);
void spawnPowerup(struct pwrUp *powerup, struct brick_t *brick, uint8_t *brickHeight, uint8_t *brickWidth);
void updatePowerup(struct pwrUp *powerup);
void drawPowerup(struct pwrUp *powerup);

 #endif

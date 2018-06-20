#ifndef _GAME_H_
#define _GAME_H_

#include "30010_io.h"
#include "vectortrig.h"
#include "timer.h"
#include "GPIO.h"
#include "striker.h"
#include "ball.h"
#include "collision.h"
#include "powerup.h"
#include "bricks.h"
#include "buzzer.h"
#include "rom.h"

#define putHeight 50
#define putWidth 200
#define putStrikerPos putHeight - 2
#define maxBricks 100

/* Developer    : Hørdur Andreasen
 * Description  : Generate level; Random Bricks, Collision Array (gameArray) and set striker.
 * Argument     : gameArray (Collision), brickArray (Brick Instances), Striker (Striker Instance), level (Difficulty Modifier), BrickHeight and BrickWidth = Box size.
 * Return value : Void
 */
uint8_t initGameArray(uint8_t gameArray[putHeight][putWidth], struct brick_t brickArray[100], struct striker_t *Striker, uint8_t *Level, uint8_t *brickHeight, uint8_t *brickWidth);


void StartGameLoop(uint8_t MaxPlayer);

/* Developer    : Hørdur Andreasen & Frederik Skov
 * Description  : run a level of the game: Generates a game and loops until level is over.
 * Argument     : level, Score, Graph and LCD Data
 * Return value : Void
 */
uint8_t runGame(uint8_t *level, uint16_t *PlayerScore, char Graph[512] , char LCDData[4][128]);

/* Developer    : Hørdur Andreasen
 * Description  : Initial Draw of game.
 * Argument     : brickArray (Brick Instances), Striker (Striker Instance), BrickHeight and BrickWidth = Box size.
 * Return value : Void
 */
void drawGame(struct brick_t brickArray[], uint8_t *brickHeight, uint8_t *brickWidth, struct striker_t *striker, struct ball_t *ball);

void CountDown();
 #endif

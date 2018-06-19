
#ifndef _ROM_H_
#define _ROM_H_


#include "stm32f30x_conf.h"
#include "ansi.h"
#include "30010_io.h"
#include "menu.h"
#include "joystick.h"
#include "analog.h"

#define ADDRESS 0x0800F800
#define SCOREARRAY data[12]

extern const char ASCII_table[43][4][11];
extern const char BOSSKEY_BSOD[943];


void InitFlash();
void WriteToFlash(uint16_t SCOREARRAY);
uint16_t ReadFromFlash(uint32_t address);
void PrintFromASCII(char* text, uint8_t drawX, uint8_t drawY);
void PrintScore();
void Bosskey();
uint8_t HighscoreCheck (uint16_t score);
void SubmitHighscore(uint8_t HighscoreLevel);
char CharSelect();

 #endif

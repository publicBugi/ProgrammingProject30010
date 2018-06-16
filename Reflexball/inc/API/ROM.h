#include "stm32f30x_conf.h"
#include "ansi.h"
#include "30010_io.h"

#define ADDRESS 0x0800F800
#define ASCIICHARARRAY data[36][4][10]

extern const uint32_t char_flash[43];
extern const uint8_t char_width[43];
extern const char ASCII_table[43][4][11];


void InitFlash();
void WriteToFlash(uint8_t ASCIICHARARRAY, uint32_t address, uint8_t arraySize);
void ReadFromFlash(char* text, uint8_t drawX, uint8_t drawY);
void ReadFromASCII(char* text, uint8_t drawX, uint8_t drawY);

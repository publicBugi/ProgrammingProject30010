#include "stm32f30x_conf.h"
#include "ansi.h"

#define ADDRESS 0x0800F800
#define ASCIICHARARRAY data[36][4][10]

extern const uint32_t char_flash[43];
extern const uint8_t char_width[43];

void InitFlash();
void WriteToFlash(uint8_t ASCIICHARARRAY, uint32_t address);
void ReadFromFlash(char* text, uint8_t drawX, uint8_t drawY);

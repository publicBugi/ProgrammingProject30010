#include "ROM.h"

const uint32_t char_location[43] = {
  0x0800F000, 0x0800F018, 0x0800F024, 0x0800F038, 0x0800F04C,
  0x0800F064, 0x0800F078, 0x0800F08C, 0x0800F0A4, 0x0800F0B8,

  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000,

  0x0800F800, 0x0800F81C, 0x0800F830, 0x0800F848, 0x0800F860,
  0x0800F874, 0x0800F888, 0x0800F8A0, 0x0800F8B8, 0x0800F8CC,
  0x0800F8E4, 0x0800F8FC, 0x0800F914, 0x0800F934, 0x0800F94C,
  0x0800F968, 0x0800F97C, 0x0800F998, 0x0800F9AC, 0x0800F9C0,
  0x0800F9DC, 0x0800F9F8, 0x0800FA14, 0x0800FA3C, 0x0800FA54,
  0x0800FA70};

const uint8_t char_width[43] = {
  6, 3, 5, 5, 6, 5, 5, 6, 5, 5,

  0, 0, 0, 0, 0, 0, 0,

  7, 5, 6, 6, 5, 5, 6, 6, 5, 6, 6, 6, 8,
  6, 7, 5, 7, 5, 5, 7, 7, 7, 10, 6, 7, 5};

void InitFlash() {
    FLASH_Unlock(); //Unlock the flash
    FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
    FLASH_ErasePage(ADDRESS); //Erase the flash storage on the last address
    FLASH_Lock(); //Lock the flash
}

void WriteToFlash(uint8_t ASCIICHARARRAY, uint32_t address) {
    uint16_t location = 0;
    FLASH_Unlock();
    for (uint8_t i = 0; i < 26; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            for (uint8_t k = 0; k < 10; k++) {
                if(data[i][j][k] == 0){
                    k=10;
                }
                FLASH_ProgramHalfWord(address+location, data[i][j][k]);
                location++;
            }
        }
    }
    FLASH_Lock();
}

void ReadFromFlash(uint32_t address, char* text, uint8_t drawX, uint8_t drawY) {
    for (uint8_t i = 0; i < 4; i++) {
        gotoXY(drawX,drawY+i);
        for (uint8_t j = 0; j < strlen(text); j++) {
            for (uint8_t k = 0; k < char_width[text[j]-0x30]; k++) {
                char tempChar = char_flash[k+char_width[text[j]-0x30]*i];
                printf("%c", tempChar);
            }
        }
    }
}

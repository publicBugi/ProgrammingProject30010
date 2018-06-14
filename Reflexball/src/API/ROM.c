#include "ROM.h"

void InitFlash() {
    FLASH_Unlock(); //Unlock the flash
    FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
    FLASH_ErasePage(ADDRESS); //Erase the flash storage on the last address
    FLASH_Lock(); //Lock the flash
}

void WriteToFlash(uint8_t ASCIICHARARRAY) {
    uint16_t location = 0;
    FLASH_Unlock();
    for (uint8_t i = 0; i < 36; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            for (uint8_t k = 0; k < 10; k++) {
                FLASH_ProgramHalfWord(ADDRESS+location*2, data[i][j][k]);
            }
        }
    }
    FLASH_Lock();
}

#include "ROM.h"

void WriteToFlash() {
FLASH_Unlock();
FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
FLASH_ErasePage(0x0800F800);
}


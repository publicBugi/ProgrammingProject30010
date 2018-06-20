#include "joystick.h"

void initJoystick() {


    // PA4: Ryder register.
    GPIOA->MODER &= ~((0x00000003) << (4 * 2));


    // PA4: Ryder push/pull register.
    GPIOA->PUPDR &= ~((0x00000003) << (4 * 2));


    // PB0 & PB5: Ryder register.
    GPIOB->MODER &= ~((0x00000C03) << (0 * 2));


    // PB0 & PB5: Ryder push/pull register.
    GPIOB->PUPDR &= ~((0x00000C03) << (0 * 2));



    // PC0 & PC1: Ryder register.
    GPIOC->MODER &= ~((0x0000000F) << (0 * 2));


    // PC0 & PC1: Ryder push/pull register.
    GPIOC->PUPDR &= ~((0x0000000F) << (0 * 2));


}
/**
  * Descripton:  This function reads position of the joystick.
  * Argument:
  * Return value:
  */
uint8_t readJoystick() {
        uint16_t Up = (GPIOA->IDR & (0x0001 << 4)) >> 4;
        uint16_t Down = (GPIOB->IDR & (0x0001 << 0)) << 1;
        uint16_t Left = (GPIOC->IDR & (0x0001 << 1)) << 1;
        uint16_t Right = (GPIOC->IDR & (0x0001 << 0)) << 3;
        uint16_t Center = (GPIOB->IDR & (0x0001 << 5)) >> 1;

        return Up + Down + Left + Right + Center;
}

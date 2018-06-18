#include "HDInitializering.h"



//void InitJoystick() {
//    // PA4: Ryder register.
//    GPIOA->MODER &= ~((0x00000003) << (4 * 2));
//
//
//    // PA4: Ryder push/pull register.
//    GPIOA->PUPDR &= ~((0x00000003) << (4 * 2));
//
//
//    // PB0 & PB5: Ryder register.
//    GPIOB->MODER &= ~((0x00000C03) << (0 * 2));
//
//
//    // PB0 & PB5: Ryder push/pull register.
//    GPIOB->PUPDR &= ~((0x00000C03) << (0 * 2));
//
//
//
//    // PC0 & PC1: Ryder register.
//    GPIOC->MODER &= ~((0x0000000F) << (0 * 2));
//
//
//    // PC0 & PC1: Ryder push/pull register.
//    GPIOC->PUPDR &= ~((0x0000000F) << (0 * 2));
//
//}
//
//void HDInitialization() {
//
//    // Initialize USB serial at 115200 baud.
//    init_usb_uart(115200);
//
//    // Aktivere klokken for GPIO port A
//    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
//
//     // Aktivere klokken for GPIO port B.
//    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
//
//     // Aktivere klokken for GPIO port C.
//    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
//
//    // Initialization of joystick.
//    InitJoystick();
//    // Change background.
//    bgcolor(0);
//}

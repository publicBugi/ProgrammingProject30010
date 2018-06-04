#include "GPIO.h"

void Ini() {
    // Aktivere klokken for GPIO port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

     // Aktivere klokken for GPIO port B.
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;

     // Aktivere klokken for GPIO port C.
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
    IniJoy();

    IniLED();
}

void IniJoy() {


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

void IniLED() {

    // PA9: Ryder register.
    GPIOA->OSPEEDR &= ~((0x00000003) << (9 * 2));

    // PA9: Sætter hastighed.
    GPIOA->OSPEEDR |= ((0x00000002) << (9 * 2));

    // PA9: Ryder register..
    GPIOA->OTYPER &= ~ ((0x00000001) << (9));

    // PA9: Push pull.
    GPIOA->OTYPER |= ((0x00000000) << (9));

    // PA9: Ryder register.
    GPIOA->MODER &= ~((0x00000003) << (9 * 2));

    // PA9: Sætter til udgang.
    GPIOA->MODER |= ((0x00000001) << (9 * 2));


    // PB4: Ryder register.
    GPIOB->OSPEEDR &= ~((0x00000003) << (4 * 2));

    // PB4: Sætter hastighed.
    GPIOB->OSPEEDR |= ((0x00000002) << (4 * 2));

    // PB4: Ryder register..
    GPIOB->OTYPER &= ~ ((0x00000001) << (4));

    // PB4: Push pull.
    GPIOB->OTYPER |= ((0x00000000) << (4));

    // PB4: Ryder register.
    GPIOB->MODER &= ~((0x00000003) << (4 * 2));

    // PB4: Sætter til udgang.
    GPIOB->MODER |= ((0x00000001) << (4 * 2));



    // PC7: Ryder register.
    GPIOC->OSPEEDR &= ~((0x00000003) << (7 * 2));

    // PC7: Sætter hastighed.
    GPIOC->OSPEEDR |= ((0x00000002) << (7 * 2));

    // PC7: Ryder register..
    GPIOC->OTYPER &= ~ ((0x00000001) << (7));

    // PC7: Push pull.
    GPIOC->OTYPER |= ((0x00000000) << (7));

    // PC7: Ryder register.
    GPIOC->MODER &= ~((0x00000003) << (7 * 2));

    // PC7: Sætter til udgang.
    GPIOC->MODER |= ((0x00000001) << (7 * 2));
}

void SetLed(char R, char G, char B) {

    if (R == 1) {
        // Rød-LED
        GPIOB->ODR  &= ~(0x0001 << 4);
    }
    else {
        GPIOB->ODR  |= (0x0001 << 4);
    }

    if (G == 1) {
        // Grøn-LED.
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else {
        GPIOC->ODR |= (0x0001 << 7);
    }


    if (B == 1) {
         // Blå-LED.
        GPIOA->ODR &= ~(0x0001<< 9);
    }
    else {
        GPIOA->ODR |= (0x0001 << 9);
    }



}


uint8_t readJoystick() {
        uint16_t Up = (GPIOA->IDR & (0x0001 << 4)) >> 4;
        uint16_t Down = (GPIOB->IDR & (0x0001 << 0)) << 1;
        uint16_t Left = (GPIOC->IDR & (0x0001 << 1)) << 1;
        uint16_t Right = (GPIOC->IDR & (0x0001 << 0)) << 3;
        uint16_t Center = (GPIOB->IDR & (0x0001 << 5)) >> 1;

        return Up + Down + Left + Right + Center;

}

#include "led.h"


void initLED() {

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

void UpdateRGB(int playerHP) {
  switch(playerHP) {
    case 3:
    SetLed(0,1,0); // Green
    break;
    case 2:
    SetLed(1,1,0); // Yellow
    break;
    case 1:
    SetLed(1,0,0); // Red
    break;
    case 0:
    SetLed(0,0,0); // Black
    break;
  }
}


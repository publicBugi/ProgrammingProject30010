#include "GPIO.h"

void initGPIO() {
    // Aktivere klokken for GPIO port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
      // Aktivere klokken for GPIO port B.
      //
      RCC->AHBENR |= RCC_AHBPeriph_GPIOB;

       // Aktivere klokken for GPIO port C.
      RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
}

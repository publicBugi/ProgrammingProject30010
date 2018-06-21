#include "GPIO.h"
/* Developer    : Hørdur Andreasen
 * Description  : Deprecated function: Only function is to enable pin clocks.
 * Argument     : None
 * Return value : Void
 */
void initGPIO() {
    // Aktivere klokken for GPIO port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
      // Aktivere klokken for GPIO port B.
      //
      RCC->AHBENR |= RCC_AHBPeriph_GPIOB;

       // Aktivere klokken for GPIO port C.
      RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
}

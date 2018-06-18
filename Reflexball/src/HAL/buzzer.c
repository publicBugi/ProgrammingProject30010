#include "buzzer.h"

#define PRESCALER_VALUE 0

void initBuzzer(){

    RCC->APB1ENR |= 0x00000001; // Enable clock line to timer 2;

    TIM2->CR1   = 0x0000; // Disable timer
    TIM2->ARR   = 1000; // Set auto reload value
    TIM2->PSC   = PRESCALER_VALUE; // Set pre-scaler value
    TIM2->CR1  |= 0x0001; // Enable timer

    TIM2->CCER &= ~TIM_CCER_CC3P; // Clear CCER register
    TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output

    TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
    TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1

    TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |=  TIM_OCPreload_Enable;
    TIM2->CCR3 = 500; // Set duty cycle to 50 %

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock line for GPIO bank B
    GPIOB->MODER   &= ~(0x00000003 << (10 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000002 << (10 * 2));    // Set mode register

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
}

void setFreq(uint16_t freq) {
    uint32_t reload = 64e6 / freq / (PRESCALER_VALUE + 1) - 1;

    TIM2->ARR  = reload; // Set auto reload value
    TIM2->CCR3 = reload/2; // Set compare register

    TIM2->EGR |= 0x01;
}


void playSound(uint16_t freq, uint8_t duration) {
    setFreq(freq);
    wait(duration);
    setFreq(0);
}

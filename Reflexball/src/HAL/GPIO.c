#include "GPIO.h"


uint8_t readJoystick() {
        uint16_t Up = (GPIOA->IDR & (0x0001 << 4)) >> 4;
        uint16_t Down = (GPIOB->IDR & (0x0001 << 0)) << 1;
        uint16_t Left = (GPIOC->IDR & (0x0001 << 1)) << 1;
        uint16_t Right = (GPIOC->IDR & (0x0001 << 0)) << 3;
        uint16_t Center = (GPIOB->IDR & (0x0001 << 5)) >> 1;

        return Up + Down + Left + Right + Center;
}



uint8_t ReadGyro(){



}

void UpdateLCD() {

}

void UpdateRGB(int playerHP) {
  switch(playerHP) {
    case 3:
    SetLed(0,1,0);
    break;
    case 2:
    SetLed(1,1,0);
    break;
    case 1:
    SetLed(1,0,0);
    break;
    case 0:
    SetLed(0,0,0);
    break;
  }
}

void BuzzerSound() {

}

void Potentiometer() {

}


void initGPIO() {


    initLED();
}



void initLED() {

    // PA9: Ryder register.
    GPIOA->OSPEEDR &= ~((0x00000003) << (9 * 2));

    // PA9: S�tter hastighed.
    GPIOA->OSPEEDR |= ((0x00000002) << (9 * 2));

    // PA9: Ryder register..
    GPIOA->OTYPER &= ~ ((0x00000001) << (9));

    // PA9: Push pull.
    GPIOA->OTYPER |= ((0x00000000) << (9));

    // PA9: Ryder register.
    GPIOA->MODER &= ~((0x00000003) << (9 * 2));

    // PA9: S�tter til udgang.
    GPIOA->MODER |= ((0x00000001) << (9 * 2));


    // PB4: Ryder register.
    GPIOB->OSPEEDR &= ~((0x00000003) << (4 * 2));

    // PB4: S�tter hastighed.
    GPIOB->OSPEEDR |= ((0x00000002) << (4 * 2));

    // PB4: Ryder register..
    GPIOB->OTYPER &= ~ ((0x00000001) << (4));

    // PB4: Push pull.
    GPIOB->OTYPER |= ((0x00000000) << (4));

    // PB4: Ryder register.
    GPIOB->MODER &= ~((0x00000003) << (4 * 2));

    // PB4: S�tter til udgang.
    GPIOB->MODER |= ((0x00000001) << (4 * 2));



    // PC7: Ryder register.
    GPIOC->OSPEEDR &= ~((0x00000003) << (7 * 2));

    // PC7: S�tter hastighed.
    GPIOC->OSPEEDR |= ((0x00000002) << (7 * 2));

    // PC7: Ryder register..
    GPIOC->OTYPER &= ~ ((0x00000001) << (7));

    // PC7: Push pull.
    GPIOC->OTYPER |= ((0x00000000) << (7));

    // PC7: Ryder register.
    GPIOC->MODER &= ~((0x00000003) << (7 * 2));

    // PC7: S�tter til udgang.
    GPIOC->MODER |= ((0x00000001) << (7 * 2));
}

void SetLed(char R, char G, char B) {

    if (R == 1) {
        // R�d-LED
        GPIOB->ODR  &= ~(0x0001 << 4);
    }
    else {
        GPIOB->ODR  |= (0x0001 << 4);
    }

    if (G == 1) {
        // Gr�n-LED.
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else {
        GPIOC->ODR |= (0x0001 << 7);
    }


    if (B == 1) {
         // Bl�-LED.
        GPIOA->ODR &= ~(0x0001<< 9);
    }
    else {
        GPIOA->ODR |= (0x0001 << 9);
    }



}

// Enable PAO and PA1 as inputs, and configure voltage dividers on MBED Board.
void initAnalog() {
	// PA0: Clear conf register
    GPIOA->MODER &= ~((0x00000003) << (0 * 2));
    // PA0: Set as regular input.
    GPIOA->MODER |= ((0x00000001) << (0 * 2));
	// PA0: CLear pull reg / Set no pull.
    GPIOA->PUPDR &= ~((0x00000003) << (0 * 2));
    // PA1: Clear conf register
    GPIOA->MODER &= ~((0x00000003) << (1 * 2));
    // PA1: Set as regular input.
    GPIOA->MODER |= ((0x00000001) << (1 * 2));
	// PA1: CLear pull reg / Set no pull.
    GPIOA->PUPDR &= ~((0x00000003) << (1 * 2));

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6;
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;

    ADC1->CR = 0x0000000;
    ADC1->CFGR &= 0xFDFFC007;
    ADC1->SQR1 &= ~ADC_SQR1_L;

    ADC1->CR |= 0x10000000;
	for(int i = 0; i < 1000; i++) {}

	ADC1->CR |= 0x80000000;
	while (!(ADC1->CR & 0x80000000));
	for (int i = 0; i < 100; i++) {}

	ADC1->CR |= 0x00000001;
	while(!(ADC1->ISR & 0x00000001));
}

uint16_t readAnalog(char channel) {
	uint16_t analogVal= 0;
	switch (channel) {
		case 1:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
		break;
		case 2:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
		break;
	}
	ADC_StartConversion(ADC1);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
	analogVal = ADC_GetConversionValue(ADC1);
	return analogVal;
}


// printf("%02ld", readAnalog(1));
// char str[7];
// sprintf(str, "%02ld", readAnalog(1));
//

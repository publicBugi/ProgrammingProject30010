#include "analog.h"

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

    // PA7: Clear conf register
    GPIOA->MODER &= ~((0x00000003) << (7 * 2));
    // PA7: Set as regular input.
    GPIOA->MODER |= ((0x00000001) << (7 * 2));
	// PA7: CLear pull reg / Set no pull.
    GPIOA->PUPDR &= ~((0x00000003) << (7 * 2));

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6;
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;

    ADC1->CR = 0x0000000;
    ADC1->CFGR &= 0xFDFFC007;
    ADC1->SQR1 &= ~ADC_SQR1_L;

    ADC1->CR |= 0x10000000;
	for(uint16_t i = 0; i < 1000; i++) {}

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

uint16_t analogRand() {
    uint16_t analogVal = 0;
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
    analogVal = ADC_GetConversionValue(ADC1);
    return analogVal;
}

void initDACNoise(){

    RCC->APB1ENR |= RCC_APB1Periph_DAC;

    // ENABLE DAC Noise Generation.
    DAC->CR &= 0x00000000;
    DAC->CR |= 0x00000B7D;          // Configure DAC: Mask = 1011 (All bits) ; Wave = Noise (01); Trigger = Software (111); Trigger enabled (1); Buffer disabled (0); DAC Channel Enable (1).
    DAC->DHR8R1 &= 0x00000000;
    DAC->DHR8R1 |= 0x000000AB;      // Random Data.
}

uint16_t DACRand(){
    uint16_t Random;
    DAC->SWTRIGR |= 0x00000001;     // Set Software trigger (Generate Random Value)

    while (DAC->SWTRIGR == 1);      // Wait until Trigger flag resets (Hardware Reset)

    return Random = DAC->DOR1;      // Return Random data from DOR1 Register.
}

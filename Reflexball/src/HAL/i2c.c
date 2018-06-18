#include "i2c.h"

void I2C_Write(uint16_t address, uint8_t reg, uint8_t val) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_Reload_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TCR) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_AutoEnd_Mode, I2C_No_StartStop); // Resend address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, val); // Transfer data

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag
}


void I2C_Read(uint16_t address, uint8_t reg, int8_t* vals, uint8_t n) {
    int8_t val = 0;

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET); // Wait until free

    I2C_TransferHandling(I2C1, address, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write); // Initiate transfer

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET); // Wait until free

    I2C_SendData(I2C1, reg); // Send register address

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TC) == RESET); // Wait until free

    I2C_TransferHandling(I2C1, address, n, I2C_AutoEnd_Mode, I2C_Generate_Start_Read); // Resend address

    for (uint8_t i = 0 ; i < n ; i++) {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET); // Wait until free

        if (n > 1) { vals[i] = I2C_ReceiveData(I2C1); }
        else { val = I2C_ReceiveData(I2C1); } // Transfer data
    }

    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET); // Wait for stop flag

    I2C_ClearFlag(I2C1, I2C_FLAG_STOPF); // Clear stop flag

    *vals = val;
}

void I2C_init()
{

    /**************/
    /**** GPIO ****/
    /**************/
    RCC->AHBENR |= 0x00040000; // Enable clock for GPIO Bank B

    // Configure pin PB4 for 2 MHz output
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2) | 0x00000003 << (10 * 2));    // Clear speed register
    GPIOB->OSPEEDR |=  (0x00000002 << (4 * 2) | 0x00000002 << (10 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (4)     | 0x0001     << (10));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0000     << (4)     | 0x0000     << (10));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (4 * 2) | 0x00000003 << (10 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000001 << (4 * 2) | 0x00000001 << (10 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (4 * 2) | 0x00000003 << (10 * 2));    // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000001 << (4 * 2) | 0x00000001 << (10 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

//    // Set pin PB4 high
//    GPIOB->ODR |= 0x0001 << 4;


    /*************/
    /**** I2C ****/
    /*************/
    RCC->APB1ENR |=  0x00200000; // Enable clock for I2C1

    GPIOB->AFR[8 >> 0x03] &= ~(0x0000000F << ((8 & 0x00000007) * 4)); // Clear alternate function for PB8
    GPIOB->AFR[8 >> 0x03] |=  (0x00000004 << ((8 & 0x00000007) * 4)); // Set alternate 4 function for PB8
    GPIOB->AFR[9 >> 0x03] &= ~(0x0000000F << ((9 & 0x00000007) * 4)); // Clear alternate function for PB9
    GPIOB->AFR[9 >> 0x03] |=  (0x00000004 << ((9 & 0x00000007) * 4)); // Set alternate 4 function for PB9

    // Configure pins PB8 and PB9 for 10 MHz alternate function
    GPIOB->OSPEEDR &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear speed register
    GPIOB->OSPEEDR |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER  &= ~(0x0001     << (8)     | 0x0001     << (9));        // Clear output type register
    GPIOB->OTYPER  |=  (0x0001     << (8)     | 0x0001     << (9));        // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear mode register
    GPIOB->MODER   |=  (0x00000002 << (8 * 2) | 0x00000002 << (9 * 2));    // Set mode register (0x00 - Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR   &= ~(0x00000003 << (8 * 2) | 0x00000003 << (9 * 2));    // Clear push/pull register
    GPIOB->PUPDR   |=  (0x00000001 << (8 * 2) | 0x00000001 << (9 * 2));    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

    I2C1->CR1 &= ~0x00000001;  // Disable I2C1 peripheral during config
    I2C1->CR1 &= 0x00CFE0FF;   // Clear config
    I2C1->CR1 |= 0x00000000;   // Set Analog filter (0x00000000 - Enabled, 0x00001000 - Disabled)
    I2C1->CR1 |= 0x00 << 8;    // Set digital filter (0x00 - 0x0F)
    I2C1->TIMINGR = 0x10805E89 & 0xF0FFFFFF; // Set timing register to 0x10805E89. See reference manual for more
    I2C1->CR1  |= 0x00000001;  // Enable I2C1 peripheral
    I2C1->OAR1  = 0x00000000;  // Clear own address register 1
    I2C1->OAR2  = 0x00000000;  // Clear own address register 2
    I2C1->OAR1 |= 0x00000000;  // Configure for 7-bit address (0x00000000 - 7-bit, 0x00000400 - 10-bit)
    I2C1->OAR1 |= 0xAB;        // Set own address to 0xAB
    I2C1->OAR1 |= 0x00008000;  // Enable own address acknowledgment
    I2C1->CR1  |= 0x00000000;  // Set mode (0x00000000 - I2C, 0x00200000 - SMBus Device, 0x00100000 - SMBus Host)
    I2C1->CR2  &= 0x07FF7FFF;  // Clear config 2
    I2C1->CR2  |= 0x00000000;  // Configure acknowledgment (0x00000000 - Enabled, 0x00008000 - Disabled)


//    uint8_t tempData[2];
//    while(1) {
//        // Read temperature
//        I2C_Read(0x90, 0x00, tempData, 2);
//
//        if (tempData[0] > 26) {
//            GPIOB->ODR &= ~(0x0001 << 4);
//        } else {
//            GPIOB->ODR |=  (0x0001 << 4);
//        }
//    }

}


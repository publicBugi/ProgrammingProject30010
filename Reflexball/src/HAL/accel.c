#include "accel.h"

#define MMA7660Adress 0x4C << 1 // I2C Address of MM7660 3-Axis Accelerometer
// Get ROLL data from Accelerometer
int32_t readRoll(uint8_t Average, uint8_t Sensitivity) {
    int32_t avgRoll = 0;
    int8_t IC2_VAL = 0;
    // Take the average of AVERAGE measurements.
    for (uint8_t i = 0; i < Average; i++) {
        I2C_Read(MMA7660Adress, 0x01, &IC2_VAL, 1);
        //IC2_VAL &= 0x3F; // Save first 6 Bits; Dont care about Alarm signal.
        IC2_VAL <<= 2;
        avgRoll += IC2_VAL;
    }
    avgRoll /= Average;
    avgRoll >>= Sensitivity; // Divide Value.
    return avgRoll;
}

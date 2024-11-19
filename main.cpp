/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "inc/SCD4x_driver.hpp"

// Blinking rate in milliseconds
#define POLLING_RATE 5000ms
#define I2C_ADDRESS (0x62 << 1)
#define START_PERIOD_MEASURE_BYTE1      (0x21)
#define START_PERIOD_MEASURE_BYTE2      (0xB1)
#define READ_SENSOR_BYTE1               (0xEC)
#define READ_SENSOR_BYTE2               (0x05)


int main() {
    // Initialize the driver
    SCD4x_driver SCD4x(P1_I2C_SDA, P1_I2C_SCL, 0x62);

    // Start periodic measurement
    SCD4x.startMeasurement();

    while (1) {
        printf("Read measure\n\r");

        if (!SCD4x.readData()) {
            printf("Co2 is %ld ppm\n\rTemp is %ld°C\n\rHumid is %ld %%\n\r", 
                   SCD4x.getCO2(), SCD4x.getTemperature(), SCD4x.getHumidity());
        }

        ThisThread::sleep_for(5000ms);
    }
}


//#include "mbed.h"
//I2C i2c(I2C_SDA , I2C_SCL);
//const int addr7bit = 0x48;      // 7-bit I2C address
//const int addr8bit = 0x48 << 1; // 8-bit I2C address, 0x90
//int main() {
//    char cmd[2];
//    while (1) {
//        cmd[0] = 0x01;
//        cmd[1] = 0x00;
//        // read and write takes the 8-bit version of the address.
//        // set up configuration register (at 0x01)
//        i2c.write(addr8bit, cmd, 2);
//        ThisThread::sleep_for(500);
//        // read temperature register
//        cmd[0] = 0x00;
//        i2c.write(addr8bit, cmd, 1);
//        i2c.read( addr8bit, cmd, 2);
//        float tmp = (float((cmd[0]<<8)|cmd[1]) / 256.0);
//        printf("Temp = %.2f\n", tmp);
//  }
//}
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define POLLING_RATE 5000ms
#define I2C_ADDRESS (0x62 << 1)
#define START_PERIOD_MEASURE_BYTE1      (0x21)
#define START_PERIOD_MEASURE_BYTE2      (0xB1)
#define READ_SENSOR_BYTE1               (0xEC)
#define READ_SENSOR_BYTE2               (0x05)

I2C i2c(P1_I2C_SDA , P1_I2C_SCL);

int main()
{
    int ret = 0;
    char start_period_cmd[2] = {START_PERIOD_MEASURE_BYTE1, START_PERIOD_MEASURE_BYTE2};
    char read_sensor_cmd[2] = {READ_SENSOR_BYTE1, READ_SENSOR_BYTE2};
    char read_data_buffer[3];

    int data = 0;

    ret = i2c.write (I2C_ADDRESS, start_period_cmd, 2, false);
    if (ret != 0)
        printf("I2C Start measure error: %d\n\r", ret);

    while (1)
    {
        printf("Read measure\n\r");
        ret = i2c.write(I2C_ADDRESS, read_sensor_cmd, 2, true);

        if(ret != 0)
            printf("I2C Write Error: %d\n\r", ret);

        if (ret == 0)
        {
            ret = i2c.read( I2C_ADDRESS, read_data_buffer, 3);
            data = (read_data_buffer[0]<<8) | (read_data_buffer[1]<<0);
            if (ret == 0)
                printf("Data is %d, 0x%04x ppm\n\r", data, data);
            else
                printf("I2C Read Error: %d\n\r", ret);
        }
            

        ThisThread::sleep_for(POLLING_RATE);
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
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define POLLING_RATE     250ms

InterruptIn mypin(BUTTON1); // change this to the button on your board
DigitalOut myled(LED1);

void led_on_off()
{
    myled = !myled;
}

int main()
{

    mypin.rise(&led_on_off);

    mypin.fall(&led_on_off);

    // press the button and see the console / led change
    while (1) {
        //printf("mypin has value : %d \n\r", mypin.read());
        ThisThread::sleep_for(POLLING_RATE);
    }
}
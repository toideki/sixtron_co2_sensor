/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define POLLING_RATE     100ms

InterruptIn mypin(BUTTON1); // change this to the button on your board
DigitalOut myled(LED1);
Timer t;
bool t_has_value = false;

void led_on()
{
    t.reset();
    t.start();
    t_has_value = false;
    myled = !myled;
}

void led_off()
{
    t.stop();
    t_has_value = true;
    myled = !myled;
}

int main()
{

    mypin.rise(&led_on);

    mypin.fall(&led_off);

    // press the button and see the console / led change
    while (1) {
        
        if (t_has_value) {
            t_has_value = false;
            printf("The time taken was %llu milliseconds\n", t.elapsed_time().count());
        }

        ThisThread::sleep_for(POLLING_RATE);
    }
}
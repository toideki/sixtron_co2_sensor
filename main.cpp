/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define POLLING_RATE 100ms

InterruptIn mypin(BUTTON1); // change this to the button on your board
DigitalOut myled(LED1);
Timer t;
bool t_has_value = false;
Ticker flipper;
float tick_value = 0.5;

void led_on()
{

    myled = !myled;

    // t.reset();
    // t.start();
    // t_has_value = false;
    // myled = !myled;
}
void ChangeFreq()
{
    tick_value = tick_value + 1.0;

    if (tick_value <= 0.0)
        tick_value = 0.5;

    flipper.detach();
    flipper.attach(&led_on, tick_value);
}

void led_off()
{
    t.stop();
    t_has_value = true;
    myled = !myled;
}

int main()
{

    mypin.rise(&ChangeFreq);

    // mypin.fall(&led_off);
    flipper.attach(&led_on, tick_value);

    // press the button and see the console / led change
    while (1)
    {
        /*if (t_has_value) {
        t_has_value = false;
        printf("The time taken was %llu milliseconds\n", t.elapsed_time().count());
        }*/

        ThisThread::sleep_for(POLLING_RATE);
    }
}

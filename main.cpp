/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

//#include "inc/SCD4x_driver.hpp"

// Blinking rate in milliseconds
#define POLLING_RATE    5000ms
#define PRINT_NUM       (100)

DigitalOut led1(LED1);
DigitalOut led2(LED2);

Mutex mutex_pp;

Thread thread1(osPriorityNormal, 1024, nullptr, nullptr);
Thread thread2(osPriorityNormal, 1024, nullptr, nullptr);

void ping_thread() {
    int i = PRINT_NUM;
    while (--i > 0) {
        {
            mutex_pp.lock();
            printf("Ping\n\r");
            mutex_pp.unlock();
        }
        //mutex_pp.unlock();
        ThisThread::sleep_for(1000ms);
    }
}
 
void pong_thread() {
    int i = PRINT_NUM;
    while (--i > 0) {
        {
            mutex_pp.lock();
            printf("Pong\n\r");
            mutex_pp.unlock();
        }
        ThisThread::sleep_for(1000ms);
    }
}

int main() {
    thread2.start(pong_thread);
    thread1.start(ping_thread);

    while(1)
    {
        led1 = !led1;
        mutex_pp.trylock();
        printf("Alive!\n\r");
        mutex_pp.unlock();
        ThisThread::sleep_for(5000ms);
    }
    return 0;
}

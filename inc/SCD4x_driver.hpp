#include "mbed.h"

#ifndef SENSOR_DRIVER_HPP
#define SENSOR_DRIVER_HPP

class SCD4x_driver {
public:
    SCD4x_driver(PinName sda, PinName scl, int address);

    int startMeasurement();
    int stopMeasurement();

    int readData();

    long int getCO2();
    long int getTemperature();
    long int getHumidity();

private:
    I2C i2c;
    int i2c_address;
    long int co2;
    long int temp;
    long int humid;
    Mutex mutex;
};

#endif

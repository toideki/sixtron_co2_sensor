#include "mbed.h"

#ifndef SENSOR_DRIVER_HPP
#define SENSOR_DRIVER_HPP

class SCD4x_driver {
public:
    SCD4x_driver(PinName sda, PinName scl, int address);

    void startMeasurement();

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

    static constexpr char START_PERIOD_MEASURE_BYTE1 = 0x21;
    static constexpr char START_PERIOD_MEASURE_BYTE2 = 0xB1;
    static constexpr char READ_SENSOR_BYTE1 = 0xEC;
    static constexpr char READ_SENSOR_BYTE2 = 0x05;
};

#endif

#include "mbed.h"

#ifndef SENSOR_DRIVER_HPP
#define SENSOR_DRIVER_HPP

class SCD4x_driver {
public:
    // Constructor to initialize the driver
    SCD4x_driver(PinName sda, PinName scl, int address);

    // Start the measurement process
    void startMeasurement();

    // Read data from the sensor
    int readData();

    // Getter functions to access sensor data
    long int getCO2();
    long int getTemperature();
    long int getHumidity();

private:
    I2C i2c;
    int i2c_address;
    long int co2;
    long int temp;
    long int humid;
    Mutex mutex;  // Mutex for thread safety

    // Constants for sensor communication
    static constexpr char START_PERIOD_MEASURE_BYTE1 = 0x21;
    static constexpr char START_PERIOD_MEASURE_BYTE2 = 0xB1;
    static constexpr char READ_SENSOR_BYTE1 = 0xEC;
    static constexpr char READ_SENSOR_BYTE2 = 0x05;
};

#endif // SENSOR_DRIVER_HPP

#include "SCD4x_driver.hpp"

SCD4x_driver::SCD4x_driver(PinName sda, PinName scl, int address)
    : i2c(sda, scl), i2c_address(address << 1), co2(0), temp(0), humid(0) {}

int SCD4x_driver::startMeasurement() {
    char start_period_cmd[2] = {0x21, 0xB1};
    return i2c.write(i2c_address, start_period_cmd, 2, false);
}

int  SCD4x_driver::stopMeasurement() {
    char start_period_cmd[2] = {0x3F, 0x86};
    return i2c.write(i2c_address, start_period_cmd, 2, false);
}

int SCD4x_driver::readData() {
    char read_sensor_cmd[2] = {0xEC, 0x05};
    char read_data_buffer[9];

    mutex.lock();
    int ret = i2c.write(i2c_address, read_sensor_cmd, 2, true);
    if (ret != 0) {
        mutex.unlock();
        return ret;
    }

    ret = i2c.read(i2c_address, read_data_buffer, sizeof(read_data_buffer));
    if (ret != 0) {
        mutex.unlock();
        return ret;
    }

    co2 = (read_data_buffer[0] << 8) | read_data_buffer[1];
    temp = -45 + 175 * (((read_data_buffer[3] << 8) | read_data_buffer[4])) / 65535;
    humid = 100 * ((read_data_buffer[6] << 8) | read_data_buffer[7]) / 65535;
    mutex.unlock();
    return ret;
}

long int SCD4x_driver::getCO2() {
    return co2;
}

long int SCD4x_driver::getTemperature() {
    return temp;
}

long int SCD4x_driver::getHumidity() {
    return humid;
}
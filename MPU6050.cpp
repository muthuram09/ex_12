#include "MPU6050.h"

MPU6050::MPU6050(TwoWire &w) : _wire(&w), _address(0x68) {}

bool MPU6050::begin(uint8_t address) {
    _address = address;
    _wire->begin();
    
    // Wake up device
    writeByte(0x6B, 0x00); // PWR_MGMT_1 register
    delay(100);
    
    // Configure gyro range (±500°/s)
    writeByte(0x1B, 0x08); // GYRO_CONFIG register
    // Configure accelerometer range (±8g)
    writeByte(0x1C, 0x10); // ACCEL_CONFIG register
    
    return true;
}

void MPU6050::readRawData(int16_t* accel, int16_t* gyro) {
    uint8_t buffer[14];
    readBytes(0x3B, 14, buffer);
    
    accel[0] = (buffer[0] << 8) | buffer[1];
    accel[1] = (buffer[2] << 8) | buffer[3];
    accel[2] = (buffer[4] << 8) | buffer[5];
    gyro[0] = (buffer[8] << 8) | buffer[9];
    gyro[1] = (buffer[10] << 8) | buffer[11];
    gyro[2] = (buffer[12] << 8) | buffer[13];
}

void MPU6050::writeByte(uint8_t reg, uint8_t data) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(data);
    _wire->endTransmission();
}

uint8_t MPU6050::readByte(uint8_t reg) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(_address, (uint8_t)1);
    return _wire->read();
}

void MPU6050::readBytes(uint8_t reg, uint8_t count, uint8_t* data) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(_address, count);
    for (uint8_t i = 0; i < count; i++) {
        data[i] = _wire->read();
    }
}
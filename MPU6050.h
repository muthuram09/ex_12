#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <Arduino.h>
#include <Wire.h>

class MPU6050 {
public:
    MPU6050(TwoWire &w = Wire);
    bool begin(uint8_t address = 0x68);
    void readRawData(int16_t* accel, int16_t* gyro);
    
private:
    TwoWire *_wire;
    uint8_t _address;
    void writeByte(uint8_t reg, uint8_t data);
    uint8_t readByte(uint8_t reg);
    void readBytes(uint8_t reg, uint8_t count, uint8_t* data);
};

#endif
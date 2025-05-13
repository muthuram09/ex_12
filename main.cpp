#include <Arduino.h>
#include "MPU6050.h"

MPU6050 imu;

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    // Try both possible addresses
    if (!imu.begin(0x68)) {
      Serial.println("Trying alternate address 0x69...");
      if (!imu.begin(0x69)) {
          Serial.println("Failed to initialize MPU6050 at either address!");
          while (1);
      }
  }
    
    if (!imu.begin()) {
        Serial.println("Failed to initialize MPU6050!");
        while (1);
    }
    
    Serial.println("MPU6050 initialized successfully");
}

void loop() {
    int16_t accel[3], gyro[3];
    imu.readRawData(accel, gyro);
    
    Serial.print("Accel: ");
    Serial.print(accel[0]); Serial.print("\t");
    Serial.print(accel[1]); Serial.print("\t");
    Serial.print(accel[2]); Serial.print("\t");
    
    Serial.print("Gyro: ");
    Serial.print(gyro[0]); Serial.print("\t");
    Serial.print(gyro[1]); Serial.print("\t");
    Serial.println(gyro[2]);
    
    delay(200); // 10Hz update rate
}
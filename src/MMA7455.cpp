#include "MMA7455.h"

MMA7455::MMA7455() : offsets{0, 0, 0} {}

void MMA7455::begin() {
    Wire.beginTransmission(MMA7455_ADDR);
    Wire.write(0x16); // Mode control
    Wire.write(0x05); // 2G sensitivity
    Wire.endTransmission();
}

CalibrationOffsets MMA7455::calibrate() {
    const int numSamples = 1000;
    int32_t xSum = 0, ySum = 0, zSum = 0;

    for (int i = 0; i < numSamples; i++) {
        int8_t x, y, z;
        readRawData(x, y, z);
        xSum += x;
        ySum += y;
        zSum += z;
        delay(10);
    }

    offsets.x_offset = -static_cast<float>(xSum) / numSamples;
    offsets.y_offset = -static_cast<float>(ySum) / numSamples;
    offsets.z_offset = 64.0 - (static_cast<float>(zSum) / numSamples);
    return offsets;
}

void MMA7455::readRawData(int8_t &x, int8_t &y, int8_t &z) {
    Wire.beginTransmission(MMA7455_ADDR);
    Wire.write(0x06);
    Wire.endTransmission(false);
    Wire.requestFrom(MMA7455_ADDR, 3);

    if (Wire.available() == 3) {
        x = Wire.read();
        y = Wire.read();
        z = Wire.read();
    } else {
        x = y = z = 0;
    }
}

void MMA7455::getGForce(float &x, float &y, float &z) {
    int8_t rawX, rawY, rawZ;
    readRawData(rawX, rawY, rawZ);
    x = rawX * INV_FACTOR;
    y = rawY * INV_FACTOR;
    z = rawZ * INV_FACTOR;
}

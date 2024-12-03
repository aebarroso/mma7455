#ifndef MMA7455_H
#define MMA7455_H

#include <Wire.h>

#define MMA7455_ADDR 0x1D
#define DELAY_VAL 5000

struct CalibrationOffsets {
    float x_offset;
    float y_offset;
    float z_offset;
};

class MMA7455 {
public:
    MMA7455();
    void begin();
    CalibrationOffsets calibrate();
    void readRawData(int8_t &x, int8_t &y, int8_t &z);
    void getGForce(float &x, float &y, float &z);

private:
    CalibrationOffsets offsets;
    constexpr static float INV_FACTOR = 1.0 / 64.0; // 2G: 64
};

#endif

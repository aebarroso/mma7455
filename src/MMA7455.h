#ifndef MMA7455_H
#define MMA7455_H

#include <Wire.h>

#define MMA7455_ADDR 0x1D

// Sensitivity 2g: 0x05, 4g: 0x09, 8g: 0x01
#define SENSIVITY 0x05
// Z stationary | 2g = 64 | 4g = 32 | 8g = 16
#define FACTOR 64.0
#define MODE_CONTROL 0x16
// Defenition of each axis memory slot
#define X_OUT 0x06
#define Y_OUT 0x07
#define Z_OUT 0x08
#define DELAY_VAL 5000

struct CalibrationOffsets {
  float x_offset;
  float y_offset;
  float z_offset;
};

// #########################################
// Methods available
void startMMA7455();
CalibrationOffsets calibrateAccelerometer();
int8_t readRegister(uint8_t reg);
float getGFroce(uint8_t reg);
#endif

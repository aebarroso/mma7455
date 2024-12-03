#include <Wire.h>
#include "MMA7455.h"

MMA7455 accelerometer;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Starting MMA7455...");
    accelerometer.begin();

    CalibrationOffsets offsets = accelerometer.calibrate();
}

void loop() {
    float x, y, z;
    accelerometer.getGForce(x, y, z);
    Serial.printf("X: %.2f, Y: %.2f, Z: %.2f\n", x, y, z);
    delay(200);
}

#include <Wire.h>
#include "MMA7455.h"

// #########################################
// MMA7455 Setup
void startMMA7455(){
  
  Wire.beginTransmission(MMA7455_ADDR);
  Wire.write(MODE_CONTROL);
  Wire.write(SENSIVITY);
  Wire.endTransmission();
}

// #########################################
// Sensor calibration 
CalibrationOffsets calibrateAccelerometer(){
  int numSamples = 1000;
  int g = 64;
  double xSum = 0, ySum = 0, zSum = 0;

  Serial.println("Calibrating accelerometer.... ");
  delay(200);

  for (int i = 0; i < numSamples; i++){
    xSum += readRegister(X_OUT);
    ySum += readRegister(Y_OUT);
    zSum += readRegister(Z_OUT); 
    delay(10);
  }

  float xAvg = xSum / numSamples;
  float yAvg = ySum / numSamples;
  float zAvg = zSum / numSamples;

  CalibrationOffsets offsets;
  
  offsets.x_offset = -xAvg;
  offsets.y_offset = -yAvg;
  offsets.z_offset = g - zAvg;

  Serial.println("Calibration complete!");
  Serial.print("X Offset: ");
  Serial.println(offsets.x_offset);
  Serial.print("Y Offset: ");
  Serial.println(offsets.y_offset);
  Serial.print("Z Offset: ");
  Serial.println(offsets.z_offset);

  delay(DELAY_VAL);
  return offsets;
}

// #########################################
// Read raw values from sensor
int8_t readRegister(uint8_t reg){
  
  Wire.beginTransmission(MMA7455_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MMA7455_ADDR, 1);

  if(Wire.available()){
    return Wire.read();
  } else {
    Serial.println("Error reading data");
    return 0;
  }
}

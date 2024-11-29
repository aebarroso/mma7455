#include <Wire.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>


#include "src/MMA7455.h"


CalibrationOffsets offsets;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  Serial.println("Starting MMA7455");
  startMMA7455();

  offsets = calibrateAccelerometer();
}

void loop() {
  // put your main code here, to run repeatedly:
  float x = readRegister(X_OUT);
  float y = readRegister(Y_OUT);
  float z = readRegister(Z_OUT);

  Serial.print("X:");
  Serial.println(x / 64);
  Serial.print("Y:");
  Serial.println(y / 64);
  Serial.print("Z:");
  Serial.println(z / 64);

  delay(100);
}

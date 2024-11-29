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

  Serial.print("X:");Serial.println(x);
  Serial.print("Y:");Serial.println(y);
  Serial.print("Z:");Serial.println(z);
  Serial.print("XG:");Serial.print(getGForce(X_OUT));
  Serial.print("YG:");Serial.print(getGForce(y_OUT));
  Serial.print("ZG:");Serial.print(getGForce(Z_OUT));
  delay(100);
}

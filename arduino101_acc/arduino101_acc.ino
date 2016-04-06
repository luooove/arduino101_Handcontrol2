/*
   Copyright (c) 2015 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   Lwwwwicense along with this librarwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwy; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

/*
   This sketch example demonstrates how the BMI160 on the
   Intel(R) Curie(TM) module can be used to read accelerometer data
*/
#include <CurieIMU.h>
int up = 2, down = 3, left = 4, right = 5, fire = 6,fireinput=7;
int calibrateOffsets = 1; // int to determine whether calibration takes place or not
int axRaw, ayRaw, azRaw;         // raw accelerometer values
float ax, ay, az;
void setup() {
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(fire, OUTPUT);
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  if (calibrateOffsets == 1) {
    // use the code below to calibrate accel/gyro offset values
    Serial.println("Internal sensor offsets BEFORE calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
    Serial.println("");

    Serial.print("Starting Acceleration calibration...");
    CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
    Serial.println(" Done");

    Serial.println("Internal sensor offsets AFTER calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
    Serial.println("");
  }

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
}


void juge()
{
  if (ax > 0.2)//ax大于0，后退
  {
    Serial.println("down");
    digitalWrite(up, 0);
    digitalWrite(down, 1);
    digitalWrite(left, 0) ;
    digitalWrite(right, 0) ;
    digitalWrite(fire, 0) ;
  }
  else if (ax < (-0.2)) //小于0，前进
  {
    Serial.println("up");
    digitalWrite(up, 1);
    digitalWrite(down, 0) ;
    digitalWrite(left, 0) ;
    digitalWrite(right, 0);
    digitalWrite(fire, 0) ;
  }
  else if (ay > 0.2)//ay大于0，右
  {
    Serial.println("right");
    digitalWrite(up, 0) ;
    digitalWrite(down, 0);
    digitalWrite(left, 0);
    digitalWrite(right, 1);
    digitalWrite(fire, 0) ;
  }
  else if (ay < (-0.2)) //ay大于0，左
  {
    Serial.println("left");
    digitalWrite(up, 0);
    digitalWrite(down, 0);
    digitalWrite(left, 1);
    digitalWrite(right, 0);
    digitalWrite(fire, 0) ;
  }
  else if (digitalRead(fireinput))
  {
    Serial.println("fire");
    digitalWrite(up, 0);
    digitalWrite(down, 0);
    digitalWrite(left, 0);
    digitalWrite(right, 0);
    digitalWrite(fire, 1) ;
  }
  else//否则不操作
  {
    Serial.println("releaseAll");
    digitalWrite(up, 0);
    digitalWrite(down, 0);
    digitalWrite(left, 0);
    digitalWrite(right, 0);
    digitalWrite(fire, 0) ;
  }
}


void loop() {


  // read raw accelerometer measurements from device
  CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);

  // convert the raw accelerometer data to G's
  ax = convertRawAcceleration(axRaw);
  ay = convertRawAcceleration(ayRaw);
  az = convertRawAcceleration(azRaw);

  // display tab-separated accelerometer x/y/z values
  Serial.print("a:\t");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print(az);
  Serial.println();
  juge();
  // wait 5 seconds
  delay(10);
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767

  float a = (aRaw * 2.0) / 32768.0;

  return a;
}

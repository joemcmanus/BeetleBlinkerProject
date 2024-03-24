// Program to monitor voltage used by a blinker relay in a 66 VW Beetle
// then change in current will trigger a relay lighting the in-dash indicator.
//
// Parts required:
// - Sparkfun Redboard https://www.sparkfun.com/products/15123
// - Sparkfun Qwiic Relay https://www.sparkfun.com/products/15093
// - Adafruit INA260 https://www.adafruit.com/product/4226
//
// Joe McManus josephmc@alumni.cmu.edu
// version 0.2 2024.03.23
// Copyright (C) 2024 Joe McManus
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//See <http://www.gnu.org/licenses/>.
#include <Adafruit_INA260.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Relay.h"

Adafruit_INA260 ina260 = Adafruit_INA260();

#define RELAY_ADDR 0x18
Qwiic_Relay relay(RELAY_ADDR);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  Serial.println("Adafruit INA260 Test");

  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    while (1)
      ;
  }
  Serial.println("Found INA260 chip");
  if (!relay.begin())
    Serial.println("Check connections to Qwiic Relay.");
  else
    Serial.println("Ready to flip some switches.");
}

void loop() {
  Serial.print("Current: ");
  int currentMa = ina260.readCurrent();
  Serial.print(currentMa);
  Serial.println(" mA");

  if (currentMa >= 50) {
    relay.turnRelayOn();
  } else {
    delay(100);
    relay.turnRelayOff();
  }
  delay(50);
}

/*
A sketch to detect a live wire and illinute an LED
Parts: 
 - https://www.sparkfun.com/products/15795
 - https://www.sparkfun.com/products/23880
 - Example code: https://github.com/sparkfun/SparkFun_TMAG5273_Arduino_Library
*/

#include <Wire.h>  // Used to establish serial communication on the I2C bus
#include "SparkFun_TMAG5273_Arduino_Library.h"

TMAG5273 sensor;  // Initialize hall-effect sensor

// I2C default address
uint8_t i2cAddress = TMAG5273_I2C_ADDRESS_INITIAL;



int RXLED = 17;   // The RX LED has a defined Arduino pin
int blinker = 0;  //an int to hold if we should blink or not

void setup() {
  Wire.begin();
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  Serial.begin(9600);  //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");

  // If begin is successful (0), then start example
  if (sensor.begin(i2cAddress, Wire) == 1) {
    Serial.println("Connected to sensor");
  } else  // Otherwise, infinite loop
  {
    Serial.println("Device failed to setup - Freezing code.");
    while (1)
      ;  // Runs forever
  }
}

void blink(int RXLED) {
  digitalWrite(RXLED, LOW);
  delay(500);
  digitalWrite(RXLED, HIGH);
}

void loop() {
  digitalWrite(RXLED, HIGH);  // In this weird world HIGH means off ?

  if (sensor.getMagneticChannel() != 0) {
    //sensor.setTemperatureEn(true); This just doesn't work

    float magX = sensor.getXData();
    float magY = sensor.getYData();
    float magZ = sensor.getZData();

    Serial.print("(");
    Serial.print(magX);
    Serial.print(", ");
    Serial.print(magY);
    Serial.print(", ");
    Serial.println(magZ);

    if (magX >= 0.70) {
      blinker = 1;
    }
    if (magY <= -0.90) {
      blinker = 1;
    }
    if (magZ <= -0.90) {
      blinker = 1;
    }
    //if (blinker == 1) {
    //  blink(RXLED);
    //  blinker = 0;
    // }
  }
  delay(100);  // wait for a second
}


/*
A sketch to detect a live wire and illinute an LED
Parts: 
 - ACS723 Hall Effect Sensor https://www.sparkfun.com/products/13679
 - Pro Micro C https://www.sparkfun.com/products/15795
 - Example code: https://github.com/sparkfun/Current_Sensor_Breakout-ACS723
*/

const int analogInPin = A0; // VOUT from sensor
// Number of samples to average the reading over
// Change this to make the reading smoother... but beware of buffer overflows!
const int avgSamples = 10 ;

int sensorValue = 0;

float sensitivity = 100.0 / 500.0; //100mA per 500mV = 0.2
float Vref = 2500; // Output voltage with no current: ~ 2500mV or 2.5V

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("Initializing");
}

int LED = A5;

void loop() {
    sensorValue = 0;
  digitalWrite(LED, LOW);  // Turn off the LED in case it is on for some reason
  // read the analog in value:
  for (int i = 0; i < avgSamples; i++)
  {
    
    sensorValue += analogRead(analogInPin);

    // wait 2 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(2);

  }

  sensorValue = sensorValue / avgSamples;

  // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV
  // The voltage is in millivolts
  float voltage = 4.88 * sensorValue;

  // This will calculate the actual current (in mA)
  // Using the Vref and sensitivity settings you configure
  float current = (voltage - Vref) * sensitivity;
  Serial.println(voltage);
  digitalWrite(LED, HIGH);
  delay(100);  // wait for a .5 second
}

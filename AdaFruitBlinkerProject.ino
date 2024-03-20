#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();

int LED = A1;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  Serial.println("Adafruit INA260 Test");

  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    while (1);
  }
  Serial.println("Found INA260 chip");
}

void loop() {
  Serial.print("Current: ");
  int currentMa =ina260.readCurrent();
  Serial.print(currentMa);
  Serial.println(" mA");

  Serial.print("Bus Voltage: ");
  Serial.print(ina260.readBusVoltage());
  Serial.println(" mV");

  Serial.print("Power: ");
  Serial.print(ina260.readPower());
  Serial.println(" mW");

  Serial.println();
  if ( currentMa >= 50 ){ 
    digitalWrite(LED, HIGH);
    } else { 
      delay(100);
digitalWrite(LED, LOW);
    }
  delay(50);
}

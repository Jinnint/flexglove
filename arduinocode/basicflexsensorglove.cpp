//note, cut jumper wire on one of flex sensors and sauder to SDA.

#include <SparkFun_ADS1015_Arduino_Library.h>

ADS1015 pinkySensor;
ADS1015 indexSensor;
uint16_t hand[4] = {0, 0, 0, 0};

void setup() { 
  Wire.begin();
  Serial.begin(115200);

  if (pinkySensor.begin(ADS1015_ADDRESS_SDA) == false) {
     Serial.println("Pinky not found. Check wiring.");
     while (1);
  }
  if (indexSensor.begin(ADS1015_ADDRESS_GND) == false) {
     Serial.println("Index not found. Check wiring.");
     while (1);
  }  
  pinkySensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); 
  indexSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); 
}

void loop() {  
  uint16_t data;
  for (int finger = 0; finger < 2; finger++) {
    hand[finger] = indexSensor.getAnalogData(finger);
    hand[finger + 2] = pinkySensor.getAnalogData(finger);
  }
  for (int finger = 0; finger < 4; finger++)
  {
    Serial.print(finger);
    Serial.print(": ");
    Serial.print(hand[finger]);
    Serial.print(" ");
  }
  Serial.println();
}
// Code by Andy England, edited by meh

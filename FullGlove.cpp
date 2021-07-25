#include <bluefruit.h>
#include <SparkFun_ADXL345.h>
#include <SparkFun_ADS1015_Arduino_Library.h>

BLEUart bleuart; 
ADXL345 adxl = ADXL345(); 
ADS1015 indexSensor;
ADS1015 pinkySensor;
uint16_t hand[4] = {0, 0, 0, 0};

void setup() {
  Wire.begin();
  Serial.begin(9600); // Serial is the USB serial port
  adxl.powerOn(); 
  
  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Jeff");
  bleuart.begin();

  // Start advertising device and bleuart services
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  // Set advertising interval (in unit of 0.625ms):
  Bluefruit.Advertising.setInterval(32, 244);
  // number of seconds in fast mode:
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);  

    //Set up each sensor, change the addresses based on the location of each sensor
  
     if (indexSensor.begin(ADS1015_ADDRESS_GND) == false) {
     while(indexSensor.begin(ADS1015_ADDRESS_GND) == false) {
      
      bleuart.print("Index not found. Check wiring.");
     }
     }  
     if (pinkySensor.begin(ADS1015_ADDRESS_SDA) == false) {
     while(pinkySensor.begin(ADS1015_ADDRESS_SDA) == false) {
      
      bleuart.print("Pinky not found. Check wiring.");
     }
     } 
     
  indexSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS);
  pinkySensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS);

  
  adxl.setRangeSetting(16); 
  adxl.setSpiBit(0);
}

void loop() {
  
  uint16_t data;
  int x,y,z;  
 /* 
  adxl.readAccel(&x, &y, &z);
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z); 
  bleuart.print("x");
  bleuart.print(x);
  bleuart.print("y");
  bleuart.print(y);
  bleuart.print("z");
  bleuart.println(z); 
 */  
  for (int finger = 0; finger < 2; finger++) {
    hand[finger] = indexSensor.getAnalogData(finger);
    hand[finger + 2] = pinkySensor.getAnalogData(finger);
  }
  for (int finger = 0; finger < 4; finger++)
  {
    bleuart.print(hand[finger]);
    bleuart.print(" ");
    bleuart.print(finger);
    Serial.print(" ");
    Serial.print(finger);
    Serial.print(": ");
    Serial.print(hand[finger]);

  }
  Serial.println();
}

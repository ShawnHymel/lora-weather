/**
 * BME280 Test
 * 
 * Author: Shawn Hymel
 * Date: April 17, 2019
 * 
 * Reads temperature, humidity, and pressure data from BME280
 * and prints it to the serial console every 3 seconds.
 * 
 * Required libraries:
 *  - https://github.com/adafruit/Adafruit_Sensor
 *  - https://github.com/adafruit/Adafruit_BME280_Library
 *  
 * License: Beerware
 */

#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Parameters
const int WAIT_TIME = 3000;             // ms

// Pins
// SPI:
// MOSI = 11
// MISO = 12
// SCK = 13
const int BME_CS_PIN = 10;

// Communicate with BME280 over SPI
Adafruit_BME280 bme(BME_CS_PIN);

void setup() {
  
  Serial.begin(9600);

   // Initialize BME280
  if ( !bme.begin() ) {
    Serial.println("Could not find BME280 on SPI bus");
    while(1);
  }
  Serial.println("BME280 initialized");
}

void loop() {
  
  // Read data
  float temp = bme.readTemperature();
  float humd = bme.readHumidity();
  float pres = bme.readPressure() / 100.0;

  // Print out data
  Serial.println();
  Serial.print("Temperature: ");
  Serial.print(temp, 1);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humd, 1);
  Serial.println("%");
  Serial.print("Pressure: ");
  Serial.print(pres, 1);
  Serial.println(" hPa");
  
  delay(WAIT_TIME);
}

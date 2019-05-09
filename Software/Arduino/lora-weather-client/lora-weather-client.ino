/**
 * LoRa Weather Client
 * 
 * Author: Shawn Hymel
 * Date: March 23, 2019
 * 
 * Transmits temperature, humidity, and pressure data over raw
 * LoRa radio. Reads data from BME280 sensor and transmits with
 * following packet:
 * 
 * | 1B From Addr | 1B To Addr | 2B Temp | 2B Humd | 2B Pres |
 *
 * Note that temperature, humidity, and pressure values are
 * scaled up by 10 and rounded to nearest integer before being
 * sent. The server will need to scale received values by 1/10.
 * This is to avoid sending full floating point values.
 * 
 * Required libraries:
 *  - http://www.airspayce.com/mikem/arduino/RadioHead/ (v1.59)
 *  - https://github.com/adafruit/Adafruit_Sensor
 *  - https://github.com/adafruit/Adafruit_BME280_Library
 * 
 * License: Beerware
 */

#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <RH_RF95.h>

#define DEBUG 0

// Parameters
const uint8_t LORA_NODE_ADDR = 0x01;    // This node's address
const uint8_t LORA_SERVER_ADDR = 0x00;  // LoRa receiving address
const int WAIT_TIME = 3000;             // ms
const int TX_BUF_SIZE = 8;              // Transmit buffer size
const float RFM_FREQ = 915.0;           // Frequency for RFM95W
const int RFM_TX_POWER = 17;            // 5..23 dBm, 13 dBm is default

// Pins
// SPI:
// MOSI = 11
// MISO = 12
// SCK = 13
const int RFM_RST_PIN = 2;
const int RFM_INT_PIN = 3;
const int RFM_CS_PIN = 4;
const int BME_CS_PIN = 10;

// Instance of radio driver over SPI
RH_RF95 rfm(RFM_CS_PIN, RFM_INT_PIN);

// Communicate with BME280 over SPI
Adafruit_BME280 bme(BME_CS_PIN);

// Transmit buffer
uint8_t tx_buf[TX_BUF_SIZE];

void setup() {

#if DEBUG
  Serial.begin(9600);
#endif

  // Manually reset RFM95W
  pinMode(RFM_RST_PIN, OUTPUT);
  digitalWrite(RFM_RST_PIN, HIGH);
  delay(100);
  digitalWrite(RFM_RST_PIN, LOW);
  delay(10);
  digitalWrite(RFM_RST_PIN, HIGH);
  delay(10);

  // Initialize RFM95W
  if ( !rfm.init() ) {
#if DEBUG
    Serial.println("Could not initialize RFM95");
#endif
    while(1);
  }
#if DEBUG
  Serial.println("RFM95 initialized");
#endif

  // Set RFM95W frequency
  if ( !rfm.setFrequency(RFM_FREQ) ) {
#if DEBUG
    Serial.println("Could not set frequency on RFM95");
#endif
    while(1);
  }
#if DEBUG
  Serial.print("RFM95 frequency set to ");
  Serial.print(RFM_FREQ);
  Serial.print(" MHz");
#endif

  // Set RFM95W transmit power from PA_BOOST pin
  rfm.setTxPower(RFM_TX_POWER, false);

  // Initialize BME280
  if ( !bme.begin() ) {
#if DEBUG
    Serial.println("Could not find BME280 on SPI bus");
#endif
    while(1);
  }
#if DEBUG
    Serial.println("BME280 initialized");
#endif
}

void loop() {
  
  // Read data
  float temp = bme.readTemperature();
  float humd = bme.readHumidity();
  float pres = bme.readPressure() / 100.0;
  
  // Scale (x10) and round data
  int16_t tempt = (int16_t)((temp * 10.0) + 0.5);
  int16_t humdt = (int16_t)((humd * 10.0) + 0.5);
  int16_t prest = (int16_t)((pres * 10.0) + 0.5);

#if DEBUG
  Serial.print("Temperature: ");
  Serial.print(temp, 1);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humd, 1);
  Serial.println("%");
  Serial.print("Pressure: ");
  Serial.print(pres, 1);
  Serial.println(" hPa");
#endif
  
  // Stuff buffer
  tx_buf[0] = LORA_NODE_ADDR;     // From address (this node) [1 byte]
  tx_buf[1] = LORA_SERVER_ADDR;   // To address (server) [1 byte]
  tx_buf[2] = (0xff & tempt);     // Temperature [2 bytes] little-endian
  tx_buf[3] = (0xff & (tempt >> 8));
  tx_buf[4] = (0xff & humdt);     // Humidity [2 bytes] little-endian
  tx_buf[5] = (0xff & (humdt >> 8));
  tx_buf[6] = (0xff & prest);     // Pressure [2 bytes] little-endian
  tx_buf[7] = (0xff & (prest >> 8));

#if DEBUG
  Serial.print("Sending buffer:");
  for ( int i = 0; i < TX_BUF_SIZE; i++) {
    Serial.print(" 0x");
    Serial.print(tx_buf[i], HEX);
  }
  Serial.println();
  Serial.println();
#endif

  // Send data to server
  rfm.send(tx_buf, TX_BUF_SIZE);
  rfm.waitPacketSent();

  delay(WAIT_TIME);
}

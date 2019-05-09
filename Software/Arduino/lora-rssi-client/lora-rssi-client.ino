/**
 * LoRa Echo Client
 * 
 * Author: Shawn Hymel
 * Date: May 8, 2019
 * 
 * Sends packet to station. Reply will be RSSI value seen at server.
 * 
 * Required libraries:
 *  - http://www.airspayce.com/mikem/arduino/RadioHead/ (v1.59)
 *  - https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library
 * 
 * License: Beerware
 */

// Uncomment if you want to use an OLED to display the RSSI
#define OLED

#include <SPI.h>
#include <Wire.h>
#include <RH_RF95.h>

#ifdef OLED
#include "SFE_MicroOLED.h"
#endif

// Parameters
const int TIMEOUT = 1000;               // Time (ms) to wait for a reply
const int WAIT_TIME = 200;              // Time (ms) between transmits
const int TX_BUF_SIZE = 8;              // Transmit buffer size (bytes)
const uint8_t RX_BUF_SIZE = 8;          // Receive buffer size (bytes)
const float RFM_FREQ = 915.0;           // Frequency for RFM95W
const int RFM_TX_POWER = 17;            // 5..23 dBm, 13 dBm is default
#ifdef OLED
const int OLED_DC_JUMPER = 1;           // Position of DC jumper
#endif

// Pins
// SPI:
// MOSI = 11
// MISO = 12
// SCK = 13
const int RFM_RST_PIN = 2;
const int RFM_INT_PIN = 3;
const int RFM_CS_PIN = 4;
const int BME_CS_PIN = 10;
const int LED_PIN = 7;
#ifdef OLED
const int OLED_RST = 9;
#endif

// Instance of radio driver over SPI
RH_RF95 rfm(RFM_CS_PIN, RFM_INT_PIN);

// Transmit buffer (constant)
const uint8_t tx_buf[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};

// Receive buffer
uint8_t rx_buf[RX_BUF_SIZE];

// OLED object
#ifdef OLED
MicroOLED oled(OLED_RST, OLED_DC_JUMPER);
#endif

void setup() {

  // Set up Serial
  Serial.begin(9600);

  // Set up OLED
#ifdef OLED
  delay(100);
  Wire.begin();
  oled.begin();
  oled.clear(ALL);
  oled.setFontType(1);
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
    Serial.println("Could not initialize RFM95");
    while(1);
  }
  Serial.println("RFM95 initialized");

  // Set RFM95W frequency
  if ( !rfm.setFrequency(RFM_FREQ) ) {
    Serial.println("Could not set frequency on RFM95");
    while(1);
  }
  Serial.print("RFM95 frequency set to ");
  Serial.print(RFM_FREQ);
  Serial.println(" MHz");

}

void loop() {

#ifdef OLED
  int mid_x = oled.getLCDWidth() / 2;
  int mid_y = oled.getLCDHeight() / 2;
#endif

  // Send data to server
  rfm.send(tx_buf, TX_BUF_SIZE);
  rfm.waitPacketSent();

  // Wait for a reply from server
  if (rfm.waitAvailableTimeout(TIMEOUT)) { 
    uint8_t rx_buf_size = RX_BUF_SIZE;  // Dunno why they want a pointer...
    if (rfm.recv(rx_buf, &rx_buf_size)) {
      Serial.print("Server RSSI:\t-");
      Serial.println(rx_buf[0]);
#ifdef OLED
      oled.clear(PAGE);
      if ( rx_buf[0] < 255 ) {
        oled.setCursor(mid_x - 12, mid_y - 8);
        oled.print(-1 * rx_buf[0]);
      } else {
        oled.setCursor(mid_x - 2, mid_y - 8);
        oled.print("ERROR");
      }
      oled.display();
#endif
    } else {
      Serial.println("Receive failed");
#ifdef OLED
      oled.clear(PAGE);
      oled.setCursor(0, mid_y - 8);
      oled.print("Rx Fail");
      oled.display();
#endif
    }
  } else {
    Serial.println("No reply, is the echo server running?");
#ifdef OLED
    oled.clear(PAGE);
    oled.setCursor(0, mid_y - 8);
    oled.print("NoReply");
    oled.display();
#endif
  }

  delay(WAIT_TIME);
}

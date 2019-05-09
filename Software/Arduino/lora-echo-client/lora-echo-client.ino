/**
 * LoRa Echo Client
 * 
 * Author: Shawn Hymel
 * Date: March 24, 2019
 * 
 * Sends packet to station. Waits for echoed reply. Turns LED 
 * on if sent and received packets match.
 * 
 * Required libraries:
 *  - http://www.airspayce.com/mikem/arduino/RadioHead/ (v1.59)
 * 
 * License: Beerware
 */

#include <SPI.h>

#include <RH_RF95.h>

// Parameters
const int TIMEOUT = 1000;               // Time (ms) to wait for a reply
const int WAIT_TIME = 100;              // Time (ms) between transmits
const int TX_BUF_SIZE = 8;              // Transmit buffer size (bytes)
const uint8_t RX_BUF_SIZE = 8;          // Receive buffer size (bytes)
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
const int LED_PIN = 7;

// Instance of radio driver over SPI
RH_RF95 rfm(RFM_CS_PIN, RFM_INT_PIN);

// Transmit buffer
uint8_t tx_buf[TX_BUF_SIZE];

// Receive buffer
uint8_t rx_buf[RX_BUF_SIZE];

void setup() {

  Serial.begin(9600);

  // Set up LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

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
  Serial.print(" MHz");

}

void loop() {
  
  // Stuff buffer
  tx_buf[0] = 0x12;
  tx_buf[1] = 0x34;
  tx_buf[2] = 0x56;
  tx_buf[3] = 0x78;
  tx_buf[4] = 0x90;
  tx_buf[5] = 0xab;
  tx_buf[6] = 0xcd;
  tx_buf[7] = 0xef;

  // Print what we're sending
  Serial.println();
  Serial.print("Sending:\t");
  for ( int i = 0; i < TX_BUF_SIZE; i++) {
    Serial.print(" 0x");
    Serial.print(tx_buf[i], HEX);
  }
  Serial.println();

  // Send data to server
  rfm.send(tx_buf, TX_BUF_SIZE);
  rfm.waitPacketSent();

  // Wait for a reply from server
  if (rfm.waitAvailableTimeout(TIMEOUT)) { 
    uint8_t rx_buf_size = RX_BUF_SIZE;  // Dunno why they want a pointer...
    if (rfm.recv(rx_buf, &rx_buf_size)) {
      Serial.print("Received:\t");
      for ( int i = 0; i < RX_BUF_SIZE; i++) {
        Serial.print(" 0x");
        Serial.print(rx_buf[i], HEX);
      }
      Serial.println();
      //Serial.print("RSSI: ");
      //Serial.println(rfm.lastRssi(), DEC);    

      // Turn on LED if transmit matches receive buffer
      if ( memcmp(tx_buf, rx_buf, TX_BUF_SIZE) == 0 ) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }

    } else {
      Serial.println("Receive failed");
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    Serial.println("No reply, is the echo server running?");
    digitalWrite(LED_PIN, LOW);
  }

  delay(WAIT_TIME);
}

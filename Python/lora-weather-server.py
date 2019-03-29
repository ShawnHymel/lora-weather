# LoRa Weather Server
#
# Author: Shawn Hymel
# Date: March 23, 2019
#
# Receives and display temperature, humidity, and pressure data from raw LoRa 
# radio. Run with lora-weather-client.ino on Arduino.
#
# License: Beerware

import time
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
import adafruit_rfm9x

# Configure RFM9x LoRa Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)

# Attempt to set up the RFM9x module
try:
    rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 915.0)
    print('RFM9x detected')
except RuntimeError:
    print('RFM9x error')


# Wait for LoRa packets
while True:
    packet = None
    packet = rfm9x.receive()
    if packet != None:
        
        print("Received:",  str(packet))
        
        # Split packet
        from_addr = packet[0]
        to_addr = packet[1]
        temp = int.from_bytes(packet[2:4], byteorder='little') / 10.0
        humd = int.from_bytes(packet[4:6], byteorder='little') / 10.0
        pres = int.from_bytes(packet[6:8], byteorder='little') / 10.0

        # Print results
        print("From:", from_addr)
        print("To:", to_addr)
        print("Temperature:", temp, "C")
        print("Humidity:", humd, "%")
        print("Pressure:", pres, "hPa")
        print()
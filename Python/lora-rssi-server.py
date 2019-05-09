# LoRa RSSI Server
#
# Author: Shawn Hymel
# Date: May 8, 2019
#
# Checks known packet and sends back RSSI
#
# Required packages:
#  pip install adafruit-circuitpython-rfm9x
#
# License: Beerware

import time
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
import adafruit_rfm9x

# Expected message from client
EXP_MSG = bytearray([0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef])

# Configure RFM9x LoRa Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)

# Attempt to set up the RFM9x module
try:
    rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 915.0)
    rfm9x.tx_power = 17
    print('RFM9x detected')
except RuntimeError:
    print('RFM9x error')


# Wait for LoRa packets
while True:
    packet = None
    packet = rfm9x.receive()
    if packet != None:        
        rssi = rfm9x.rssi
        print("Received:",  str(packet))
        print("RSSI:", abs(rssi))
        if packet == EXP_MSG:
            print("Messages match")
            rfm9x.send(bytearray([abs(rssi)]))
        else:
            rfm9x.send(bytearray([0xff]))
# LoRa Echo Server
#
# Author: Shawn Hymel
# Date: March 24, 2019
#
# Repeats back any LoRa packet received.
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
        print("Received:",  str(packet))
        rfm9x.send(packet)

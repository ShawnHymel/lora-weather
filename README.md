LoRa Weather Station
====================

![Arduino LoRa and BME280 client](https://raw.githubusercontent.com/ShawnHymel/lora-weather/master/Images/arduino-client_1000px.jpg)

LoRa client and server. Arduino reads temperature, humidity, and pressure data from BME280 sensor and sends it over a simple LoRa wireless connection to a Raspberry Pi.

Required Parts
--------------

 - Arduino UNO
 - 2x Adafruit RFM95W LoRa Breakout
 - Adafruit BME280 Breakout
 - Raspberry Pi 3 Model B
 - 2x Breadboards
 - Jumper wires

Hardware Setup
--------------

Connect the Arduino as shown:

![Arduino radio and sensor connections](https://raw.githubusercontent.com/ShawnHymel/lora-weather/master/Images/arduino-client_bb.png)

Connect the Raspberry Pi as shown:

![Raspberry Pi radio connections](https://raw.githubusercontent.com/ShawnHymel/lora-weather/master/Images/rpi-server_bb.png)

Server Software
---------------

Install Raspbian (with Desktop) on the Raspberry Pi. From a console, run the following command to install the RFM9x Python package:

```
pip install adafruit-circuitpython-rfm9x
```

Go into the *Python* directory of this repo and run *lora-weather-server.py*.

```
python lora-weather-server.py
```

Arduino Software
----------------

Install the following libraries for Arduino:
 - [RadioHead v1.59](http://www.airspayce.com/mikem/arduino/RadioHead/)
 - [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
 - [Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library)
 
Upload the *lora-weather-client.ino* to the Arduino (found in the *Arduino* directory of this repository).

Running
-------

The Arduino should begin sending temperature, humidity, and pressure data to the Raspberry Pi at regular intervals. Check the console output to see the sensor data.

![Sensor data printed to Raspberry Pi screen](https://raw.githubusercontent.com/ShawnHymel/lora-weather/master/Images/rpi-server-receiving_1000px.jpg)

License
-------

The code is beerware; if you see me at the local, and you've found the code helpful, please buy me a round!
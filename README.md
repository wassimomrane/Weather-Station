# Weather-Station

# ESP32 Web Server with Real-Time Temperature and Humidity Monitoring

This project implements a web server using an ESP32 microcontroller and a DHT11 sensor to monitor temperature and humidity in real time.  
The ESP32 hosts a responsive web interface that displays live sensor readings without page refresh, accessible from any device on the same local network.

---

## Project Overview

The ESP32 reads temperature and humidity data from a DHT11 sensor and serves this data through a built-in web server.  
A modern web interface built with HTML, CSS, and JavaScript dynamically updates the values using asynchronous HTTP requests.

---

## Hardware Requirements

- ESP32 development board  
- DHT11 temperature and humidity sensor  
- Jumper wires  
- USB cable  
- WiFi network  

---

## Hardware Connections

| DHT11 Pin | ESP32 Pin |
|---------|----------|
| VCC     | 3.3V     |
| DATA    | GPIO 4   |
| GND     | GND      |

Note: The DATA pin can be changed in the code if required.

---

## Software Requirements

- Arduino IDE  
- ESP32 board package installed  
- Required libraries:
  - DHT sensor library (Adafruit)
  - Adafruit Unified Sensor

---

## Features

- Real-time temperature and humidity monitoring
- Embedded web server running on ESP32
- Responsive and modern web interface
- Dynamic data update without page refresh
- Access via IP address or mDNS hostname
- Compatible with mobile and desktop browsers

---

## Installation and Setup

1. Clone or download this repository.
2. Open the project in Arduino IDE.
3. Install the required libraries from the Arduino Library Manager.
4. Update the WiFi credentials in the code:
   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";

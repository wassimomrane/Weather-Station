# Weather-Station

This project creates a simple web server using an ESP32 that monitors temperature and humidity in real-time via a DHT11 sensor and serves the data as JSON over HTTP.

Features

Connects ESP32 to a Wi-Fi network.

Reads temperature and humidity from the DHT11 sensor.

Serves sensor data in JSON format via HTTP (/sensor endpoint).

Easy to access from any device on the same network.

Hardware Required

ESP32 development board

DHT11 temperature and humidity sensor

Jumper wires

USB cable for programming

Software & Libraries

Arduino IDE

Libraries:

WiFi.h – for Wi-Fi connectivity

DHT.h – to read data from the DHT11 sensor

ArduinoJson.h – to format the sensor data as JSON

Wiring

DHT11 Data Pin → ESP32 GPIO 4

VCC → 3.3V

GND → GND

Installation

Install the required libraries via Arduino Library Manager.

Open the code in Arduino IDE.

Update Wi-Fi credentials:

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";


Upload the code to your ESP32 board.

Open the Serial Monitor to find the ESP32 IP address.

Usage

Connect a device to the same Wi-Fi network.

Open a browser and go to:

http://<ESP32_IP>/sensor


You will see JSON data like:

{
  "temperature": 24.5,
  "humidity": 60.2
}

How It Works

ESP32 connects to Wi-Fi and starts a web server on port 80.

When a client requests /sensor, the ESP32:

Reads temperature and humidity from DHT11.

Creates a JSON object with the data.

Sends the JSON response to the client.

Notes

Ensure the ESP32 and your device are on the same network.

You can reset the ESP32 to get a new IP if needed.

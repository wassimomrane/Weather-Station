#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <ESPmDNS.h>

// ----------- WiFi Credentials -----------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ----------- DHT Configuration ----------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ----------- Web Server -----------------
WebServer server(80);

// ----------- HTML Page ------------------
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 DHT Server</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      background: linear-gradient(135deg, #667eea, #764ba2);
      color: white;
    }
    h1 {
      margin-top: 30px;
    }
    .card {
      background: white;
      color: black;
      padding: 20px;
      margin: 20px auto;
      width: 250px;
      border-radius: 15px;
      box-shadow: 0 4px 10px rgba(0,0,0,0.3);
    }
    .temp {
      color: #e74c3c;
      font-size: 36px;
    }
    .hum {
      color: #3498db;
      font-size: 36px;
    }
  </style>
</head>
<body>

  <h1>ESP32 DHT Server</h1>

  <div class="card">
    <h3>Temperature</h3>
    <div class="temp"><span id="temp">--</span> °C</div>
  </div>

  <div class="card">
    <h3>Humidity</h3>
    <div class="hum"><span id="hum">--</span> %</div>
  </div>

<script>
setInterval(() => {
  fetch("/data")
    .then(response => response.json())
    .then(data => {
      document.getElementById("temp").innerHTML = data.temperature;
      document.getElementById("hum").innerHTML = data.humidity;
    });
}, 2000);
</script>

</body>
</html>
)rawliteral";

// ----------- Handlers -------------------
void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    server.send(500, "application/json", "{\"error\":\"Sensor error\"}");
    return;
  }

  String json = "{";
  json += "\"temperature\":" + String(temperature, 2) + ",";
  json += "\"humidity\":" + String(humidity, 2);
  json += "}";

  server.send(200, "application/json", json);
}

// ----------- Setup ----------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("mDNS started: http://esp32.local");
  }

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
  Serial.println("Web server started");
}

// ----------- Loop -----------------------
void loop() {
  server.handleClient();
}

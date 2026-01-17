#include <WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>

// Configuration Wi-Fi
const char* ssid = "Redmi Note 11";
const char* password = "12345678";

// Configuration DHT
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Serveur Web
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi...");
  }
  Serial.println("Connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  // Démarrer le serveur
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/sensor") != -1) {
      // Lire les données du capteur
      float temperature = dht.readTemperature();
      float humidity = dht.readHumidity();

      // Créer un objet JSON
      StaticJsonDocument<200> jsonDoc;
      jsonDoc["temperature"] = temperature;
      jsonDoc["humidity"] = humidity;

      String jsonResponse;
      serializeJson(jsonDoc, jsonResponse);

      // Répondre avec les données JSON
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.println();
      client.println(jsonResponse);
    }
  }
}

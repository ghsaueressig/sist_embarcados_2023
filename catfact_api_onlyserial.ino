#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 

const char* ssid = "Redmieder";
const char* password = "w8a3ev79";

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  // Conecte-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

// Faça uma solicitação HTTP GET para a API
  HTTPClient http;
  http.begin("https://catfact.ninja/fact");
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();

    // Crie um objeto JSON para fazer o parsing
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Obtenha o fato do gato
    const char* catFact = doc["fact"];

    // Imprima o fato na tela
    Serial.println("Fato do gato: " + String(catFact));
  } else {
    Serial.println("Erro na solicitação HTTP");
  }

  http.end();
}

void loop() {
  // Seu código de loop aqui
}
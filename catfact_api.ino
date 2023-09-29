#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

    // Limpe o display
    display.clearDisplay();

    // Exiba o fato do gato no display
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Fato do gato:");
    Serial.println("Fato do gato: " + String(catFact));
    display.setCursor(0, 16);
    display.println(catFact);
    display.display();
  } else {
    Serial.println("Erro na solicitação HTTP");
  }

  http.end();
}

void loop() {
  // Seu código de loop aqui
}
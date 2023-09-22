#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 4 // Pino ao qual o sensor DHT11 está conectado
#define DHTTYPE DHT11 // Tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("Erro ao iniciar o display SSD1306"));
    for(;;);
  }
  dht.begin();
  display.display(); // Inicializar com o buffer vazio
  delay(2000); // Pequeno atraso para exibir a inicialização
  display.clearDisplay(); // Limpar o buffer
}

void loop() {
  delay(2000); // Aguardar 2 segundos entre as leituras

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println(F("Falha ao ler o sensor DHT11!"));
    return;
  }

  Serial.print(F("Temperatura: "));
  Serial.print(temperatura);
  Serial.print(F(" °C | Umidade: "));
  Serial.print(umidade);
  Serial.println(F("%"));

  display.clearDisplay(); // Limpar o buffer do display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("Temp: "));
  display.print(temperatura);
  display.println(F(" C"));
  display.print(F("Umidade: "));
  display.print(umidade);
  display.println(F("%"));
  display.display(); // Mostrar as informações no display
}

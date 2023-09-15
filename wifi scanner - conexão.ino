#include <WiFi.h>

const char* ssid = "iot";
const char* password = "iot@123@";

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  //iniciar serial
  Serial.begin(9600);

  //conectando ao wifi
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...")
  }
  Serial.println("Conexão bem sucedida!");
  Serial.print("Endereço IP atribuído: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Procurando redes sem fio...")
  int n = WiFi.scanNetworks();
  Serial.println("Feito.");
  if (n == 0){
    Serial.println("Não há wifi disponível.")
  }
  else{
    for (int i = 0; i<n;++i){
      Serial.print(n);
      Serial.print(i+1);
      Serial.print(": ";)
      Serial.print(WiFi.SSID(i));
      delay(100);
      Serial.print("Potência do sinal: ");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" Criptografia: ");
      Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " ": "*");
      delay(100);
    }
  }
}

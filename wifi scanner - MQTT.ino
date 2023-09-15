#include <PubSubClient.h>
#include <WiFi.h>

String hostname = "ESP-GUILHERME_S"

const char* ssid = "iot";
const char* password = "iot@123@";

const char* mqtt_broker = "test.mosquitto.org";
const char* topic = "aula6";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  //iniciar serial
  Serial.begin(9600);

  //conectando ao wifi
  WiFi.begin(ssid,password);
  conecta();
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...")
  }
  Serial.println("Conexão bem sucedida!");
  Serial.print("Endereço IP atribuído: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  client.loop();
}

void conectamqtt(){
  client.setServer(mqtt_broker,mqtt_port);
  client.setCallback(callback());
  while (!client.connected()){
    Serial.println("Conectando-se ao Broker.");
  }
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length){
  Serial.println("Nova mensagem no tópico ");
  Serial.println(topic);
  Serial.print("Mensagem: ");
  for (int i=0;i<length;i++){
    Serial.println((char) payload[i]);
  }
  Serial.println("###############");
}
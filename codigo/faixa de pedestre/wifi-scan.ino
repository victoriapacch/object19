#include <WiFi.h>
#include <PubSubClient.h>

// WIFI
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topico_faixa = "iot/faixa";

WiFiClient espClient;
PubSubClient client(espClient);

// PINOS
#define TRIG_PIN 5
#define ECHO_PIN 18

bool pedestreDetectado = false;

// -------------------------
void setupWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
}

// -------------------------
void reconnectMQTT() {
  while (!client.connected()) {
    client.connect("ESP32_Faixa");
  }
}

// -------------------------
float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  return duracao * 0.034 / 2.0;
}

// -------------------------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  setupWifi();
  client.setServer(mqtt_server, 1883);
}

// -------------------------
void loop() {

  if (!client.connected()) reconnectMQTT();
  client.loop();

  float distancia = medirDistancia();

  bool estadoAtual = (distancia > 0 && distancia < 100);

  if (estadoAtual != pedestreDetectado) {

    pedestreDetectado = estadoAtual;

    if (pedestreDetectado) {
      Serial.println("PEDESTRE DETECTADO");
      client.publish(topico_faixa, "Pedestre detectado");
    } else {
      Serial.println("AREA LIVRE");
      client.publish(topico_faixa, "Area livre");
    }
  }

  delay(200);
}

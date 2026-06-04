#include <WiFi.h>
#include <PubSubClient.h>

// WIFI
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topico_onibus = "iot/onibus";

WiFiClient espClient;
PubSubClient client(espClient);

// PINOS
#define BUZZER_PIN 4
#define BUTTON_PIN 16

bool ultimoEstadoBotao = HIGH;

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
    client.connect("ESP32_Onibus");
  }
}

// -------------------------
void bipCurto() {
  tone(BUZZER_PIN, 2500);
  delay(120);
  noTone(BUZZER_PIN);
}

// -------------------------
void somTravessia() {
  bipCurto();
  delay(120);
  bipCurto();
  delay(700);
  bipCurto();
  delay(120);
  bipCurto();
}

// -------------------------
void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  setupWifi();
  client.setServer(mqtt_server, 1883);
}

// -------------------------
void loop() {

  if (!client.connected()) reconnectMQTT();
  client.loop();

  bool estadoAtual = digitalRead(BUTTON_PIN);

  if (ultimoEstadoBotao == HIGH && estadoAtual == LOW) {

    Serial.println("BOTAO PRESSIONADO");

    client.publish(topico_onibus, "Solicitacao de acessibilidade");

    bipCurto();

    delay(5000);

    somTravessia();
  }

  ultimoEstadoBotao = estadoAtual;

  delay(50);
}

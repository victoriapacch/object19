#include <WiFi.h>
#include <PubSubClient.h>

// ==========================
// WIFI
// ==========================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==========================
// MQTT
// ==========================
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ==========================
// PINOS
// ==========================
#define TRIG_PIN    5
#define ECHO_PIN    18
#define BUZZER_PIN  4
#define BUTTON_PIN  16

bool ultimoEstadoBotao = HIGH;

// ==========================
// WIFI
// ==========================
void setupWifi() {

  Serial.println("Conectando ao WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ==========================
// MQTT
// ==========================
void reconnectMQTT() {

  while (!client.connected()) {

    Serial.print("Conectando ao MQTT...");

    if (client.connect("ESP32_Mobilidade")) {

      Serial.println(" conectado!");

    } else {

      Serial.print(" erro: ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

// ==========================
// SENSOR ULTRASSÔNICO
// ==========================
float medirDistancia() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);

  return duracao * 0.034 / 2.0;
}

// ==========================
// BIP CURTO
// ==========================
void bipCurto() {

  tone(BUZZER_PIN, 2500);
  delay(120);
  noTone(BUZZER_PIN);
}

// ==========================
// SOM DE TRAVESSIA
// pi pi ... pi pi
// ==========================
void somTravessia() {

  // pi pi
  bipCurto();
  delay(120);
  bipCurto();

  // pausa maior
  delay(700);

  // pi pi
  bipCurto();
  delay(120);
  bipCurto();
}

// ==========================
// SETUP
// ==========================
void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  setupWifi();

  client.setServer(mqtt_server, 1883);

  Serial.println("Sistema iniciado!");
}

// ==========================
// LOOP
// ==========================
void loop() {

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  // ==========================
  // SENSOR DA FAIXA
  // ==========================

  float distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia > 0 && distancia < 100) {

  Serial.println("PEDESTRE DETECTADO");

  client.publish(
    "iot/faixa",
    "Pedestre detectado na faixa"
  );

} else {

  Serial.println("NENHUM PEDESTRE DETECTADO");

  client.publish(
    "iot/faixa",
    "Nenhum pedestre detectado"
  );
}

delay(100);

  // ==========================
  // BOTAO DO PONTO DE ONIBUS
  // ==========================

  bool estadoAtual = digitalRead(BUTTON_PIN);

  if (ultimoEstadoBotao == HIGH && estadoAtual == LOW) {

    Serial.println("BOTAO PRESSIONADO");

    client.publish(
      "iot/onibus",
      "Solicitacao de acessibilidade"
    );

    // Bip imediato ao pressionar
    bipCurto();

    Serial.println("Aguardando 5 segundos...");
    delay(5000);

    Serial.println("ONIBUS CHEGOU / PODE ATRAVESSAR");

    // pi pi ... pi pi
    somTravessia();
  }

  ultimoEstadoBotao = estadoAtual;

  delay(50);
}

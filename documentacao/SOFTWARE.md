# Documentação do Software

## Linguagem

C++

## Ambiente de Desenvolvimento

Arduino IDE

## Bibliotecas

### WiFi.h

Responsável pela conexão com a rede sem fio.

### PubSubClient.h

Responsável pela implementação do protocolo MQTT.

## Funções Principais

### setup()

Inicialização dos pinos, Wi-Fi e MQTT.

### loop()

Leitura contínua dos sensores e processamento dos eventos.

### conectarWiFi()

Realiza a conexão do ESP32 à rede.

### conectarMQTT()

Estabelece comunicação com o broker MQTT.

### detectarPedestre()

Calcula a distância utilizando o HC-SR04.

### acionarBuzzer()

Ativa a sinalização sonora.

## Fluxo

Inicialização → Wi-Fi → MQTT → Leitura Sensor → Publicação MQTT → Acionamento → Repetição

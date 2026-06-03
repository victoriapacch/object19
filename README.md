# Sistema Inteligente de Mobilidade Urbana Acessível

## Descrição

Este projeto apresenta uma solução baseada em Internet das Coisas (IoT) voltada para mobilidade urbana e acessibilidade. O sistema integra uma faixa de pedestres inteligente e um ponto de ônibus acessível, utilizando sensores e atuadores conectados à internet por meio do protocolo MQTT.

O objetivo é aumentar a segurança dos pedestres e auxiliar pessoas com deficiência visual por meio de sinalizações automáticas e monitoramento em tempo real.

---

## Funcionalidades

### Faixa de Pedestres Inteligente

* Detecção de pedestres utilizando sensor ultrassônico HC-SR04.
* Processamento dos dados pelo ESP32.
* Publicação dos eventos em um broker MQTT.
* Possibilidade de integração com sistemas de monitoramento.

### Ponto de Ônibus Acessível

* Acionamento por botão ou evento remoto.
* Emissão de sinal sonoro através de buzzer piezoelétrico.
* Registro dos eventos via MQTT.
* Auxílio à orientação de pessoas com deficiência visual.

---

## Tecnologias Utilizadas

### Hardware

* ESP32 DevKit V1
* Sensor Ultrassônico HC-SR04
* Buzzer Piezoelétrico
* Protoboard
* Jumpers

### Software

* Arduino IDE
* Linguagem C++
* Wokwi Simulator
* MQTT
* Wi-Fi

### Bibliotecas

* WiFi.h
* PubSubClient.h

---

## Arquitetura do Sistema

HC-SR04 → ESP32 → Wi-Fi → Broker MQTT → Dashboard

Botão → ESP32 → Buzzer → MQTT

---

## Fluxo de Funcionamento

1. O ESP32 conecta-se à rede Wi-Fi.
2. O ESP32 conecta-se ao Broker MQTT.
3. O sensor ultrassônico realiza leituras periódicas.
4. Caso um pedestre seja detectado, uma mensagem MQTT é enviada.
5. O sistema registra o evento.
6. O buzzer pode ser acionado localmente ou remotamente.
7. O evento é publicado no broker MQTT.

---

## Como Executar

### Instalação da Arduino IDE

Baixe a Arduino IDE:

https://www.arduino.cc/en/software

### Instalação da Placa ESP32

1. Abra a Arduino IDE.
2. Acesse Preferências.
3. Adicione a URL:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

4. Instale a plataforma ESP32 pelo Gerenciador de Placas.

### Instalação das Bibliotecas

Instale:

* WiFi
* PubSubClient

### Configuração Wi-Fi

Alterar no código:

```cpp
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
```

### Configuração MQTT

```cpp
const char* mqtt_server = "broker.hivemq.com";
```

### Upload

1. Conecte o ESP32.
2. Selecione a placa correta.
3. Faça upload do código.

---

## Estrutura do Projeto

```text
Projeto-IoT-Mobilidade-Urbana
│
├── codigo
│   └── sistema_iot.ino
│
├── docs
│   ├── fluxograma.png
│   ├── arquitetura.png
│   ├── circuito.png
│   ├── mqtt.png
│   └── resultados.png
│
├── artigo
│   └── artigo_final.pdf
│
└── README.md
```

---

## Comunicação MQTT

### Broker

broker.hivemq.com

### Porta

1883

### Tópicos

```text
mobilidade/pedestre
mobilidade/buzzer
```

### Exemplo de Payload

Detecção de Pedestre:

```json
{
  "pedestre": true
}
```

Acionamento do Buzzer:

```json
{
  "buzzer": "ON"
}
```

---

## Possíveis Melhorias Futuras

* Integração com aplicativo móvel.
* Dashboard web para monitoramento.
* Inclusão de sensores ambientais.
* Alimentação por energia solar.
* Reconhecimento de fluxo de pedestres por visão computacional.

---

## Autores

Alexandre Henrique de Souza Araújo

Vitória Pacheco Pontes Pereira

Kevin Caldas Mendes

Universidade Presbiteriana Mackenzie

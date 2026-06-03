# Documentação do Código-Fonte

## Arquivo Principal

### wifi-scan.ino

Este arquivo contém todo o firmware responsável pelo funcionamento do sistema de mobilidade urbana acessível.

O software foi desenvolvido utilizando a linguagem C++ no ambiente Arduino IDE e executado em um microcontrolador ESP32 DevKit V1.

---

## Bibliotecas Utilizadas

### WiFi.h

Responsável por estabelecer a conexão do ESP32 com uma rede Wi-Fi.

Funções utilizadas:

* WiFi.begin()
* WiFi.status()
* WiFi.localIP()

---

### PubSubClient.h

Biblioteca responsável pela implementação do protocolo MQTT.

Funções utilizadas:

* client.connect()
* client.publish()
* client.loop()

---

## Configuração da Rede

```cpp
const char* ssid = "Wokwi-GUEST";
const char* password = "";
```

Realiza a conexão do dispositivo à rede sem fio utilizada durante os testes.

---

## Configuração MQTT

```cpp
const char* mqtt_server = "broker.hivemq.com";
```

Broker MQTT utilizado para envio e recebimento de mensagens.

Porta:

```cpp
1883
```

---

## Definição dos Pinos

| Componente      | GPIO    |
| --------------- | ------- |
| Trigger HC-SR04 | GPIO 5  |
| Echo HC-SR04    | GPIO 18 |
| Buzzer          | GPIO 4  |
| Botão           | GPIO 16 |

---

## Função setupWifi()

Responsável por conectar o ESP32 à rede Wi-Fi.

Fluxo:

1. Inicia a conexão.
2. Aguarda a autenticação.
3. Obtém endereço IP.
4. Exibe informações no Monitor Serial.

---

## Função reconnectMQTT()

Responsável por conectar o dispositivo ao Broker MQTT.

Fluxo:

1. Verifica conexão.
2. Realiza tentativa de conexão.
3. Aguarda em caso de falha.
4. Mantém o sistema conectado.

---

## Função medirDistancia()

Responsável pela leitura do sensor ultrassônico HC-SR04.

Fluxo:

1. Gera pulso de trigger.
2. Recebe eco.
3. Calcula distância.
4. Retorna o valor em centímetros.

Fórmula utilizada:

Distância = (Tempo × 0,034) / 2

---

## Função bipCurto()

Emite um sinal sonoro curto utilizando o buzzer.

Frequência:

2500 Hz

Duração:

120 ms

---

## Função somTravessia()

Produz o padrão sonoro utilizado para acessibilidade.

Sequência:

Pi Pi → Pausa → Pi Pi

---

## Função setup()

Responsável pela inicialização do sistema.

Atividades:

* Inicialização serial
* Configuração dos GPIOs
* Conexão Wi-Fi
* Configuração MQTT

---

## Função loop()

Executa continuamente:

1. Verificação da conexão MQTT.
2. Leitura do sensor ultrassônico.
3. Publicação dos eventos MQTT.
4. Monitoramento do botão.
5. Acionamento do buzzer.

---

## Tópicos MQTT

### Faixa Inteligente

Tópico:

```text
iot/faixa
```

Mensagens:

```text
Pedestre detectado na faixa
```

```text
Nenhum pedestre detectado
```

---

### Ponto de Ônibus Acessível

Tópico:

```text
iot/onibus
```

Mensagem:

```text
Solicitacao de acessibilidade
```

---

## Fluxo Geral do Sistema

Sensor HC-SR04
↓
ESP32
↓
Publicação MQTT
↓
Broker MQTT

Botão
↓
ESP32
↓
Buzzer
↓
Publicação MQTT

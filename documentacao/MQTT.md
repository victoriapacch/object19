# Documentação MQTT

## Objetivo

Permitir comunicação entre dispositivos IoT e plataformas de monitoramento através da internet.

## Broker MQTT

broker.hivemq.com

## Porta

1883

## Protocolo

MQTT 3.1.1

## Publicação

### Tópico

```text
mobilidade/pedestre
```

### Payload

```json
{
  "status":"detectado"
}
```

## Acionamento Sonoro

### Tópico

```text
mobilidade/buzzer
```

### Payload

```json
{
  "status":"ativado"
}
```

## Fluxo de Comunicação

1. Sensor detecta pedestre.
2. ESP32 processa informação.
3. ESP32 publica mensagem MQTT.
4. Broker recebe a mensagem.
5. Dashboard ou cliente MQTT recebe o evento.
6. Atuador pode ser acionado.

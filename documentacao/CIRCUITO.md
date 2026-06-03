# Documentação do Circuito

## Arquivo

diagram.json

Este arquivo descreve o circuito eletrônico utilizado na plataforma Wokwi.

---

## Componentes Utilizados

### ESP32 DevKit V1

Função:

Unidade central de processamento e comunicação MQTT.

---

### Sensor Ultrassônico HC-SR04

Função:

Detectar a presença de pedestres.

Conexões:

| HC-SR04 | ESP32   |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | GPIO 5  |
| ECHO    | GPIO 18 |

---

### Botão

Função:

Solicitação de acessibilidade no ponto de ônibus.

Conexões:

| Botão      | ESP32   |
| ---------- | ------- |
| Terminal 1 | GPIO 16 |
| Terminal 2 | GND     |

---

### Buzzer

Função:

Emitir sinal sonoro para orientação de pessoas com deficiência visual.

Conexões:

| Buzzer   | ESP32  |
| -------- | ------ |
| Positivo | GPIO 4 |
| Negativo | GND    |

---

## Funcionamento

Quando o sensor detecta um pedestre a menos de 100 cm:

1. O ESP32 processa a leitura.
2. Uma mensagem MQTT é publicada.
3. O evento é registrado.

Quando o botão é pressionado:

1. O ESP32 publica uma mensagem MQTT.
2. O buzzer emite um sinal sonoro.
3. Após cinco segundos é reproduzido o padrão de travessia.

---

## Ambiente de Simulação

O circuito foi desenvolvido e validado utilizando a plataforma Wokwi.

https://wokwi.com/

O ambiente permitiu validar o comportamento do hardware antes da implementação física.

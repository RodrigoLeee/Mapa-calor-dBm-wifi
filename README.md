# 📡 Projeto IoT: Monitoramento do Sinal Wi-Fi com ESP32

## 📝 Descrição
Este projeto visa medir e monitorar a potência do sinal Wi-Fi (em dBm) utilizando um ESP32. Os dados coletados são:

- Exibidos na porta serial da Arduino IDE.
- Publicados em tempo real em uma plataforma online via MQTT.
- Representados graficamente como um histórico de tempo x dBm na plataforma.

### 🧪 Teste especial
Um dos testes realizados incluiu o uso de um elevador no Inteli para simular uma gaiola de Faraday. O sinal foi monitorado durante o bloqueio e após 5 segundos fora do elevador, registrando o comportamento do sinal na dashboard.

## 🖥️ Configuração do Ambiente

1. **Hardware Necessário:**
   - ESP32
   - Conexão Wi-Fi disponível

2. **Software Utilizado:**
   - Arduino IDE
   - Plataforma MQTT compatível (exemplo: Adafruit IO ou ThingsBoard)

3. **Bibliotecas Necessárias:**
   - `WiFi.h`
   - `thingProperties.h`

## ⚙️ Como Funciona o Código

### 🌐 Conexão Wi-Fi
O ESP32 se conecta à rede Wi-Fi especificada por `SSID` e `PASS`. Caso a conexão falhe, o dispositivo tenta reconectar automaticamente em intervalos regulares.

### ☁️ Publicação MQTT
A intensidade do sinal Wi-Fi (“RSSI”) é capturada usando `WiFi.RSSI()` e enviada à plataforma MQTT configurada na nuvem.

### 📊 Visualização dos Dados
Na plataforma online, os dados são apresentados como um gráfico em tempo real, permitindo acompanhar o histórico do sinal.

## 📜 Estrutura do Código

```cpp
#include <WiFi.h>
#include "thingProperties.h"

void setup() {
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  Serial.begin(115200);
  reconnectWiFi();
}

void loop() {
  ArduinoCloud.update();
  reconnectCloud();

  if (WiFi.status() == WL_CONNECTED) {
    sinal = WiFi.RSSI();
    Serial.print("Intensidade do sinal (dBm): ");
    Serial.println(sinal);
  } else {
    reconnectWiFi();
  }
}

void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }
}

void reconnectCloud() {
  if (!ArduinoCloud.connected()) {
    while (!ArduinoCloud.connected()) {
      ArduinoCloud.update();
      delay(1000);
    }
  }
}

void onSinalChange() {
  Serial.println("Valor atualizado na nuvem.");
}
```

## 🔬 Resultados

1. **Cenários Testados:**
   - Corredores do Inteli.
   - Elevador como gaiola de Faraday.
   - Dentro da sala de aula.

2. **Observações:**
   - O sinal diminuiu drasticamente dentro do elevador.
   - Houve recuperação imediata ao sair do elevador.

## 🎥 Demonstração em Vídeo


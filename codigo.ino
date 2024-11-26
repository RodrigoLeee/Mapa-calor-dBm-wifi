#include <WiFi.h>
#include "thingProperties.h"

void setup() {
  // Inicializa a conexão com a nuvem
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Configura a porta serial para depuração
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Iniciando...");

  // Conecta ao Wi-Fi
  reconnectWiFi();
}

void loop() {
  // Atualiza o estado da conexão com a nuvem
  ArduinoCloud.update();

  reconnectCloud();

  // Se estiver conectado, envia o RSSI
  if (WiFi.status() == WL_CONNECTED) {
    sinal = WiFi.RSSI();
    Serial.print("Intensidade do sinal (dBm): ");
    Serial.println(sinal);
  } else {
    Serial.println("Wi-Fi desconectado! Tentando reconectar...");
    reconnectWiFi();
  }

  
}
// Função para reconectar ao WiFi
void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    WiFi.begin(SSID, PASS);
    unsigned long startAttemptTime = millis();

    // Timeout de 10 segundos para tentar reconectar ao WiFi
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFi reconectado com sucesso!");
    } else {
      Serial.println("\nNão foi possível reconectar ao WiFi.");
    }
  }
}

// Função para reconectar ao Arduino IoT Cloud
void reconnectCloud() {
  reconnectWiFi(); // Primeiro garante que o WiFi está conectado

  if (WiFi.status() == WL_CONNECTED && !ArduinoCloud.connected()) {
    Serial.println("Conexão com a nuvem perdida. Tentando reconectar...");

    unsigned long startAttemptTime = millis();

    // Timeout de 15 segundos para evitar loops infinitos
    while (!ArduinoCloud.connected() && millis() - startAttemptTime < 15000) {
      ArduinoCloud.update();
      delay(1000);
      Serial.println("Tentando reconectar à Arduino IoT Cloud...");
    }

    if (ArduinoCloud.connected()) {
      Serial.println("Reconexão à nuvem bem-sucedida!");
    } else {
      Serial.println("Não foi possível reconectar à nuvem.");
    }
  }
}

void onSinalChange() {
  // Função chamada quando a variável 'sinal' muda na nuvem
  Serial.println("Valor de 'sinal' atualizado na nuvem.");
}

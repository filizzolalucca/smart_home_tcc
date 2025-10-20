#include <Arduino.h>
#include "config.h"
#include "atuadores.h"

bool modoEconomia = false;
bool modoSeguranca = false;
bool l3Ligado = false;

bool modoEconomiaAnterior = false;
bool modoSegurancaAnterior = false;
unsigned long tempoDesligamentoSeguranca = 0;

void atualizaL3() {
  if (modoEconomia != modoEconomiaAnterior) {
    modoEconomiaAnterior = modoEconomia;

    if (!modoEconomia && l3Ligado) {
      digitalWrite(L3, HIGH);
    }
  }

  if (l3Ligado && modoEconomia) {
    int valorLuz = analogRead(SENSOR_LUZ);
    int brilho = map(valorLuz, 0, 1023, 255, 0);
    analogWrite(L3, brilho);
  }
}

void gerenciaModoSeguranca() {
    static bool s1Resetado = false;

 if (modoSeguranca != modoSegurancaAnterior) {
    modoSegurancaAnterior = modoSeguranca;

    if (!modoSeguranca) {
      tempoDesligamentoSeguranca = millis();
      s1Resetado = false;
    }
  }

  if (!modoSeguranca && !s1Resetado && (millis() - tempoDesligamentoSeguranca) >= 10000) {
    feedS1->save(0);
    s1Resetado = true;
    Serial.println(">>> Modo segurança desligado, resetando S1 para 0");
  }
}

void handleL1(AdafruitIO_Data *data) {
  digitalWrite(L1, data->isTrue() ? HIGH : LOW);
}

void handleL2(AdafruitIO_Data *data) {
  digitalWrite(L2, data->isTrue() ? HIGH : LOW);
}

void handleL3(AdafruitIO_Data *data) {
  l3Ligado = data->isTrue();
  if (!l3Ligado) digitalWrite(L3, LOW);
  else if (!modoEconomia) digitalWrite(L3, HIGH);
}

void handleModoEconomia(AdafruitIO_Data *data) {
  modoEconomia = data->isTrue();
}

void handleModoSeguranca(AdafruitIO_Data *data) {
  modoSeguranca = data->isTrue();
}

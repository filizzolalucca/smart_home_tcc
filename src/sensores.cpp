#include <Arduino.h>
#include "config.h"
#include "sensores.h"

int ultimaLeituraSensores = 0;
int ultimaLeituraTempUmidade = 0;
extern bool modoSeguranca;

void handleDigitalSensorTEMP() {
  if ((millis() - ultimaLeituraTempUmidade) > 60000) {
    enviaDHT();
    ultimaLeituraTempUmidade = millis();
  }
}

void handleDigitalSensorBTN() {
  leituraSensorBTN();
}

void handleDigitalSensorProx() {
  if ((millis() - ultimaLeituraSensores) > 8000) {
    leituraSensorDigital();
    ultimaLeituraSensores = millis();
  }
}

void enviaDHT() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (!isnan(temperatura) && !isnan(umidade)) {
    feedSensorUmidade->save(umidade);
    feedSensorTemperatura->save(temperatura);
  }
}

bool ultimoStatusS1 = false;
bool ultimoStatusBTN = false;

void leituraSensorDigital() {
  bool statusS1 = digitalRead(S1);
  if (modoSeguranca && statusS1 != ultimoStatusS1) {
    feedS1->save(statusS1);
    ultimoStatusS1 = statusS1;
  }
}

void leituraSensorBTN() {
  bool statusBTN = digitalRead(BT);
  if (statusBTN != ultimoStatusBTN) {
    feedBTN->save(statusBTN);
    ultimoStatusBTN = statusBTN;
  }
}

#include <Arduino.h>
#include "config.h"
#include "sensores.h"

int ultimaLeituraSensores = 0;
int ultimaLeituraTempUmidade = 0;

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

void leituraSensorDigital() {
  bool statusS1 = digitalRead(S1);
  feedS1->save(statusS1);
}

void leituraSensorBTN() {
  bool statusBTN = digitalRead(BT);
  feedBTN->save(statusBTN);
}

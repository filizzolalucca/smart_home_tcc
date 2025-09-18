#include <Arduino.h>
#include "config.h"
#include "sensores.h"
#include "atuadores.h"
#include "configSeguranca.h"

DHT dht(DHTPIN, DHTTYPE);

AdafruitIO_WiFi io(ConfigSeguranca::IO_USERNAME, ConfigSeguranca::IO_KEY,
                   ConfigSeguranca::WIFI_SSID, ConfigSeguranca::WIFI_PASS);
                   
// feeds (iniciais)
AdafruitIO_Feed *feedL1 = io.feed("l1");
AdafruitIO_Feed *feedL2 = io.feed("l2");
AdafruitIO_Feed *feedL3 = io.feed("l3");
AdafruitIO_Feed *feedS1 = io.feed("s1");
AdafruitIO_Feed *feedBTN = io.feed("BTN");
AdafruitIO_Feed *feedModoEconomia = io.feed("modoeconomia");
AdafruitIO_Feed *feedModoSeguranca = io.feed("modoseguranca");
AdafruitIO_Feed *feedSensorUmidade = io.feed("sensorUmidade");
AdafruitIO_Feed *feedSensorTemperatura = io.feed("sensorTemperatura");

void conectaBroker() {
  io.connect();

  feedL1->onMessage(handleL1);
  feedL2->onMessage(handleL2);
  feedL3->onMessage(handleL3);
  feedModoEconomia->onMessage(handleModoEconomia);
  feedModoSeguranca->onMessage(handleModoSeguranca);

  while (io.status() < AIO_CONNECTED) {
    delay(500);
  }

  feedL1->get();
  feedL2->get();
  feedL3->get();
  feedModoEconomia->get();
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(BT, INPUT_PULLUP);

  dht.begin();
  conectaBroker();
}

void loop() {
  io.run();

  if (io.status() == AIO_NET_DISCONNECTED || io.status() == AIO_DISCONNECTED) {
    conectaBroker();
  }

  handleDigitalSensorProx();
  handleDigitalSensorTEMP();
  handleDigitalSensorBTN();

  atualizaL3();
  gerenciaModoSeguranca();
}

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include  <DHT.h>
#include <AdafruitIO_WiFi.h>

// ----- PINOS -----
#define DHTPIN D4
#define DHTTYPE DHT22

#define L1 D3
#define L2 D7
#define L3 D1
#define BT D5
#define S1 D2
#define SENSOR_LUZ A0

// ----- OBJETOS GLOBAIS -----
extern DHT dht;

extern AdafruitIO_Feed *feedL1;
extern AdafruitIO_Feed *feedL2;
extern AdafruitIO_Feed *feedL3;
extern AdafruitIO_Feed *feedS1;
extern AdafruitIO_Feed *feedBTN;
extern AdafruitIO_Feed *feedModoEconomia;
extern AdafruitIO_Feed *feedModoSeguranca;
extern AdafruitIO_Feed *feedSensorUmidade;
extern AdafruitIO_Feed *feedSensorTemperatura;

// Função de conexão
void conectaBroker();

#endif

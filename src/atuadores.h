#ifndef ATUADORES_H
#define ATUADORES_H

void handleL1(AdafruitIO_Data *data);
void handleL2(AdafruitIO_Data *data);
void handleL3(AdafruitIO_Data *data);

void handleModoEconomia(AdafruitIO_Data *data);
void handleModoSeguranca(AdafruitIO_Data *data);

void atualizaL3();
void gerenciaModoSeguranca();

#endif

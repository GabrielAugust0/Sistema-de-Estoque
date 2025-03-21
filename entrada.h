#ifndef ENTRADA_H
#define ENTRADA_H

#include <stdbool.h>

void limparBuffer();
int lerInteiro(const char *msg);
float lerFloat(const char *msg);
void lerString(const char *msg, char *destino, int tamanho_max);
bool validarString(const char *str);

#endif
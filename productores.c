#include "productores.h"
#include <stdio.h>
#include <string.h>

productor parsear_productor(char *productor_string) {
  // el productor, por ser regular, es de la forma
  // S->a | S->aT | S->Ta, de estos dos ultimos uno solo
  productor prod = {};
  char *noterminal;
  char *resultado;
  char *ok;
  char *saveptr2;

  noterminal = strtok_r(productor_string, "->", &saveptr2);
  if (!noterminal) {
    return prod;
  }

  resultado = strtok_r(NULL, "->", &saveptr2);
  if (!resultado) {
    return prod;
  }

  ok = strcpy(prod.resultado, resultado);
  if (!ok) {
    return prod;
  }
  prod.noterminal = noterminal[0];

  printf("productor parseado: %c->%s\n", prod.noterminal, prod.resultado);

  return prod;
}

void parsear_productores(productor *dest, char *productores) {
  printf("str_productores_adentro: %s\n", productores);
  char prod_token[10];
  char *delimiter = ",";
  char *saveptr1;
  char *token;

  int i = 0;
  token = strtok_r(productores, delimiter, &saveptr1);
  while (token) {
    strcpy(prod_token, token);
    printf("procesando token %d: %s\n", i, prod_token);

    dest[i] = parsear_productor(prod_token);
    i++;

    token = strtok_r(NULL, delimiter, &saveptr1);
  }
}

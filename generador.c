#include "generador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *generar_palabra(gramatica gram) {
  char palabra[100] = {};
  char producto_inicial[5];
  srand(time(NULL));

  strcpy(producto_inicial,
         get_producto_random(hallar_productor(gram.productores, CANT_AXIOMAS,
                                       gram.axioma_inicial)));

  sprintf(palabra, "%s", producto_inicial);

  return palabra;
}

char *get_producto_random(productor prod) {
  char *tok;
  char buffer[100][5];
  const char delim[] = "|";

  tok = strtok(prod.resultado, delim);
  if (!tok) {
    return prod.resultado;
  }

  // es multiparte
  int i = 0;
  while (tok) {
    strcpy(buffer[i], tok);
    tok = strtok(NULL, delim);
  }
  return buffer[rand() % (i + 1)];
}

productor hallar_productor(productor *productores, int size, char axioma) {
  productor prod = {};
  for (int i = 0; i < size; i++) {
    if (axioma == productores[i].noterminal) {
      return productores[i];
    }
  }
  return prod;
}
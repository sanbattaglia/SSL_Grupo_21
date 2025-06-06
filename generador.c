#include "generador.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// NOTA: CORREGIR LOS RETORNOS DE PUNTEROS AL STACK XD

char *generar_palabra(gramatica gram) {
  char palabra[100] = {};
  productor ultimo_prod;
  srand(time(NULL));

  // caso base -- inicia palabra
  ultimo_prod =
      hallar_productor(gram.productores, CANT_AXIOMAS, gram.axioma_inicial);
  strcpy(palabra, get_producto_random(ultimo_prod));

  // hacer funcion vvvvvvvvvvv
  // hallar_no_terminal(ultimo_prod.resultado, gram.no_terminales) -> char noterminal --
  // que despues se lo podes pasar a hallar_productor para seguir iterando

  // hacer funcion vvvvvvvv
  // extender_palabra(palabra, sig_prod, gram.lado);
  // que tome la palabra y el productor a insertar, y lo inserte

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
    i++;
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

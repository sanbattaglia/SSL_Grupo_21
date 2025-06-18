#include "generador.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generar_palabra(char *placeholder, gramatica gram) {
  char buffer[100] = {};
  char buffer_palabra[1000] = {};
  productor ultimo_prod;
  srand(time(NULL));

  // caso base -- inicia palabra
  ultimo_prod =
      hallar_productor(gram.productores, CANT_AXIOMAS, gram.axioma_inicial);
  get_producto_random(buffer, ultimo_prod);
  strcpy(buffer_palabra, buffer);

  // hacer funcion vvvvvvvvvvv
  // hallar_no_terminal(ultimo_prod.resultado, gram.no_terminales) -> char
  // noterminal -- que despues se lo podes pasar a hallar_productor para seguir
  // iterando

  // hacer funcion vvvvvvvv
  // extender_palabra(palabra, sig_prod, gram.lado);
  // que tome la palabra y el productor a insertar, y lo inserte
}

void get_producto_random(char *placeholder, productor prod) {
  char *tok;
  char buffer[100][5];
  const char delim[] = "|";

  tok = strtok(prod.resultado, delim);
  if (!tok) {
    strcpy(placeholder, prod.resultado);
    return;
  }

  // es multiparte
  int i = 0;
  while (tok) {
    strcpy(buffer[i], tok);
    tok = strtok(NULL, delim);
    i++;
  }
  strcpy(placeholder, buffer[rand() % (i + 1)]);
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

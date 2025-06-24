#include "validacion.h"
#include <string.h>

int es_terminal(char c, char *terminales) {
  return strchr(terminales, c) != NULL;
}

int es_no_terminal(char c, char *no_terminales) {
  return strchr(no_terminales, c) != NULL;
}

int validar_formato(char *produccion, char *terminales, char *no_terminales, int *modo) {
  int len = strlen(produccion);

  if (len == 1) {
    // A → a
    return es_terminal(produccion[0], terminales);
  } else if (len == 2) {
    if (es_terminal(produccion[0], terminales) && es_no_terminal(produccion[1], no_terminales)) {
      if (*modo == -1) *modo = IZQ;
      return *modo == IZQ;
    }
    if (es_no_terminal(produccion[0], no_terminales) && es_terminal(produccion[1], terminales)) {
      if (*modo == -1) *modo = DER;
      return *modo == DER;
    }
  }

  return 0;
}

int es_gramatica_regular(gramatica *g) {
  int modo = -1; // -1: sin definir, 1: derecha, 0: izquierda

  for (int i = 0; i < CANT_AXIOMAS; i++) {
    if (g->productores[i].noterminal == 0) continue;

    char copia[100];
    strcpy(copia, g->productores[i].resultado);

    char *token = strtok(copia, "|");
    while (token != NULL) {
      if (!validar_formato(token, g->terminales, g->no_terminales, &modo)) {
        return 0;
      }
      token = strtok(NULL, "|");
    }
  }
  return 1;
}
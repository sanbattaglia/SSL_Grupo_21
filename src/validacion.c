#include "validacion.h"
#include <string.h>

int es_terminal(char c, char *terminales) {
  return strchr(terminales, c) != NULL;
}

int es_no_terminal(char c, char *no_terminales) {
  return strchr(no_terminales, c) != NULL;
}

int validar_formato(char *produccion, char *terminales, char *no_terminales,
                    int *modo) {
  int len = strlen(produccion);

  if (len == 1 && produccion[0] == '~') {
    return 1; // palabra vacia es válida
  }

  if (len == 1) {
    // A → a
    return es_terminal(produccion[0], terminales);
  } else if (len == 2) {
    if (es_terminal(produccion[0], terminales) &&
        es_no_terminal(produccion[1], no_terminales)) {
      if (*modo == -1)
        *modo = IZQ;
      return *modo == IZQ;
    }
    if (es_no_terminal(produccion[0], no_terminales) &&
        es_terminal(produccion[1], terminales)) {
      if (*modo == -1)
        *modo = DER;
      return *modo == DER;
    }
  }

  return 0;
}

int tiene_palabra_vacia(gramatica *g, char no_terminal) {
  for (int i = 0; i < CANT_AXIOMAS; i++) {
    if (g->productores[i].noterminal == no_terminal) {
      char copia[100];
      strcpy(copia, g->productores[i].resultado);

      char *token = strtok(copia, "|");
      while (token != NULL) {
        if (strlen(token) == 1 && token[0] == '~') {
          return 1;
        }
        token = strtok(NULL, "|");
      }
    }
  }
  return 0;
}

int cuenta_palabras_vacias(gramatica *g) {
  int count = 0;
  for (int i = 0; i < CANT_AXIOMAS; i++) {
    if (g->productores[i].noterminal == 0)
      continue;

    if (tiene_palabra_vacia(g, g->productores[i].noterminal)) {
      count++;
    }
  }
  return count;
}

int axioma_inicial_tiene_palabra_vacia(gramatica *g) {
  return tiene_palabra_vacia(g, g->axioma_inicial);
}

int palabra_vacia_en_resultado_de_otro_productor(gramatica *g) {
  if (!axioma_inicial_tiene_palabra_vacia(g)) {
    return 0; // si el axioma inicial no tiene palabra vacía, no hay problema
  }

  // Verificar si algún productor (que no sea el axioma inicial) genera el
  // axioma inicial
  for (int i = 0; i < CANT_AXIOMAS; i++) {
    if (g->productores[i].noterminal == 0 ||
        g->productores[i].noterminal == g->axioma_inicial) {
      continue;
    }

    char copia[100];
    strcpy(copia, g->productores[i].resultado);

    char *token = strtok(copia, "|");
    while (token != NULL) {
      // Verificar si alguna producción contiene el axioma inicial
      for (int j = 0; j < strlen(token); j++) {
        if (token[j] == g->axioma_inicial) {
          return 1; // El axioma inicial aparece en resultado de otro productor
        }
      }
      token = strtok(NULL, "|");
    }
  }
  return 0;
}

int es_gramatica_regular(gramatica *g) {
  int modo = -1; // -1: sin definir, 1: derecha, 0: izquierda

  int palabras_vacias = cuenta_palabras_vacias(g);
  if (palabras_vacias > 1) {
    return 0; // más de una palabra vacía
  }
  if (palabras_vacias == 1 && !axioma_inicial_tiene_palabra_vacia(g)) {
    return 0; // hay palabra vacía pero no está en el axioma inicial
  }

  if (palabra_vacia_en_resultado_de_otro_productor(g)) {
    return 0;
  }

  for (int i = 0; i < CANT_AXIOMAS; i++) {
    if (g->productores[i].noterminal == 0)
      continue;

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
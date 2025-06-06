#include "productores.h"

#include <stdio.h>

#define CANT_AXIOMAS 25
#define IZQ 1
#define DER 0

typedef struct {
  char no_terminales[CANT_AXIOMAS];
  char terminales[50];
  productor productores[CANT_AXIOMAS];
  char axioma_inicial;
  char lado;
} gramatica;

char *generar_palabra(gramatica gram);
char *get_producto_random(productor prod);
productor hallar_productor(productor *productores, int size, char axioma);
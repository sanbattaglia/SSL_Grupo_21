#include <stdio.h>
#include <string.h>

#include "src/generador.h"
#include "src/validacion.h"

void print_uno_a_uno(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    printf("  %c\n", str[i]);
  }
}

void print_productor(productor prod) {
  printf("%c->%s\n", prod.noterminal, prod.resultado);
}

int main(int argc, char **argv) {
  gramatica gram = {};
  char str_productores[100];

  strcpy(gram.no_terminales, argv[1]);
  strcpy(gram.terminales, argv[2]);
  strcpy(str_productores, argv[3]);
  printf("string productores: %s\n", str_productores);
  parsear_productores(gram.productores, str_productores);
  gram.axioma_inicial = argv[4][0];

  // Valida que la gramática sea regular
  if (!es_gramatica_regular(&gram)) {
    printf(" Error: La gramática ingresada no es regular.\n");
    return 1;
  }

  printf(" Gramática válida. Procediendo a generar palabras...\n");


  printf("------------\n");
  printf("no terminales: %s\n", gram.no_terminales);
  printf("terminales: %s\n", gram.terminales);
  printf("axioma inicial: %c\n", gram.axioma_inicial);
  printf("------------\n\n");

  // logica de validacion de GR
  gram.lado = IZQ;

  // generacion de palabras
  char palabra[1000] = {};
  generar_palabra(palabra, gram);
  printf("palabra generada --> %s\n", palabra);
}

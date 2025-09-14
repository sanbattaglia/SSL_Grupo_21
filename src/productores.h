#ifndef PRODUCTORES_H 
#define PRODUCTORES_H

typedef struct {
  char noterminal;
  char resultado[100];
} productor;

void print_uno_a_uno(char *str);
void parsear_productores(productor *dest, char *productores);
productor parsear_productor(char *productor_string);

#endif
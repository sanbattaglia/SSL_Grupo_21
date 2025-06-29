#ifndef VALIDADOR_H
#define VALIDADOR_H

#include "generador.h"

int es_terminal(char c, char *terminales);
int es_no_terminal(char c, char *no_terminales);
int validar_formato(char *produccion, char *terminales, char *no_terminales, int *modo);
int tiene_palabra_vacia(gramatica *g, char no_terminal);
int cuenta_palabras_vacias(gramatica *g);
int axioma_inicial_tiene_palabra_vacia(gramatica *g);
int palabra_vacia_en_resultado_de_otro_productor(gramatica *g);
int es_gramatica_regular(gramatica *g);

#endif
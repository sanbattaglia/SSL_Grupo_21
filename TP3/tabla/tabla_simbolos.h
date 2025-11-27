#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "../include/defs.h"


typedef struct Simbolo {
    char* nombre;
    TipoDato tipo;
    CategoriaSimbolo categoria;
    Valor valor;
    struct Simbolo* siguiente;
} Simbolo;


void inicializar_tabla();
void insertar_simbolo(char* nombre, TipoDato tipo, CategoriaSimbolo categoria);
Simbolo* buscar_simbolo(char* nombre);
void set_valor_simbolo(char* nombre, Valor valor);
void set_valor_inicial(char* nombre, Valor valor); // Usada para constantes
Valor get_valor_simbolo(char* nombre);
void liberar_tabla();

#endif // TABLA_SIMBOLOS_H

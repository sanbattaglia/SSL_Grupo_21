#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"

// Puntero al inicio de la lista enlazada
static Simbolo* cabeza = NULL;

// Func auxiliar para duplicar cadenas
char* duplicar_cadena(char* s) {
    if (s == NULL) return NULL;
    char* nuevo = (char*)malloc(strlen(s) + 1);
    if (nuevo == NULL) {
        fprintf(stderr, "Error: Memoria insuficiente.\n");
        exit(1);
    }
    strcpy(nuevo, s);
    return nuevo;
}

void inicializar_tabla() {
    cabeza = NULL;
}

void insertar_simbolo(char* nombre, TipoDato tipo, CategoriaSimbolo categoria) {
    // Verificar si ya existe
    if (buscar_simbolo(nombre) != NULL) {
        fprintf(stderr, "Error semantico: La variable '%s' ya existe.\n", nombre);
        exit(1);
    }

    // Crear nuevo nodo
    Simbolo* nuevo = (Simbolo*)malloc(sizeof(Simbolo));
    if (nuevo == NULL) {
        fprintf(stderr, "Error: Memoria insuficiente.\n");
        exit(1);
    }

    nuevo->nombre = duplicar_cadena(nombre);
    nuevo->tipo = tipo;
    nuevo->categoria = categoria;
    
    // Inicializar valores en 0 / NULL
    nuevo->valor.valor_int = 0;
    nuevo->valor.valor_string = NULL;

    // Insertar al principio de la lista
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

Simbolo* buscar_simbolo(char* nombre) {
    Simbolo* actual = cabeza;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void set_valor_simbolo(char* nombre, Valor valor) {
    Simbolo* s = buscar_simbolo(nombre);
    if (s == NULL) {
        fprintf(stderr, "Error semantico: '%s' no esta declarado.\n", nombre);
        exit(1);
    }
    if (s->categoria == C_CONST) {
        fprintf(stderr, "Error semantico: No se puede modificar la constante '%s'.\n", nombre);
        exit(1);
    }
    
    // Actualizar valor según el tipo
    if (s->tipo == T_ENTERO) {
        s->valor.valor_int = valor.valor_int;
    } else {
        // Liberar string anterior si existe
        if (s->valor.valor_string != NULL) {
            free(s->valor.valor_string);
        }
        s->valor.valor_string = duplicar_cadena(valor.valor_string);
    }
}

// Func para dar valor inicial a las constantes
void set_valor_inicial(char* nombre, Valor valor) {
    Simbolo* s = buscar_simbolo(nombre);
    if (s == NULL) return; 
    
    if (s->tipo == T_ENTERO) {
        s->valor.valor_int = valor.valor_int;
    } else {
        s->valor.valor_string = duplicar_cadena(valor.valor_string);
    }
}

Valor get_valor_simbolo(char* nombre) {
    Simbolo* s = buscar_simbolo(nombre);
    if (s == NULL) {
        fprintf(stderr, "Error semantico: '%s' no existe.\n", nombre);
        exit(1);
    }
    return s->valor;
}

void liberar_tabla() {
    Simbolo* actual = cabeza;
    while (actual != NULL) {
        Simbolo* temp = actual;
        actual = actual->siguiente;
        
        free(temp->nombre);
        if (temp->tipo == T_STRING && temp->valor.valor_string != NULL) {
            free(temp->valor.valor_string);
        }
        free(temp);
    }
}

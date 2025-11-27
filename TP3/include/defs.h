#ifndef DEFS_H
#define DEFS_H

// Tipos de datos MICRO
typedef enum {
    T_ENTERO,
    T_STRING
} TipoDato;

// Categorías de símbolos
typedef enum {
    C_VAR,
    C_CONST
} CategoriaSimbolo;

// Almacenar el valor de un símbolo
typedef struct {
    int valor_int;
    char* valor_string;
} Valor;

// Resultados de expresiones (usada en parser)
typedef struct {
    TipoDato tipo;
    Valor valor;
} ResultadoExpr;

#endif // DEFS_H

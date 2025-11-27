%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defs.h"
#include "../tabla/tabla_simbolos.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char *s);

// Func auxiliar para operaciones
ResultadoExpr operar(ResultadoExpr op1, ResultadoExpr op2, int es_suma);

%}

%union {
    int entero;
    char* cadena;
    ResultadoExpr expr_val;
}

%token INICIO FIN LEER ESCRIBIR CONST INT STRING
%token ASIGNACION SUMA RESTA COMA PUNTOYCOMA PARENIZQUIERDO PARENDERECHO
%token <cadena> ID CONSTANTE_CADENA
%token <entero> CONSTANTE_ENTERA

%type <expr_val> expresion primaria

%%

objetivo: programa;

programa: INICIO listaSentencias FIN { 
    printf("Ejecucion finalizada con exito.\n"); 
    YYACCEPT; 
};

listaSentencias: sentencia listaSentencias
               | sentencia
               ;

sentencia: declaracion
         | asignacion
         | entrada
         | salida
         ;

declaracion: tipo ID PUNTOYCOMA {
                // Declarar variable
                insertar_simbolo($2, $<entero>1, C_VAR);
                free($2); // Liberar memoria del nombre temporal
             }
           | CONST tipo ID ASIGNACION expresion PUNTOYCOMA {
                // Verificar tipos
                if ($<entero>2 != $5.tipo) {
                    yyerror("Error: El tipo de la constante no coincide con el valor.");
                }
                // Declarar constante
                insertar_simbolo($3, $<entero>2, C_CONST);
                // Asignar valor inicial
                set_valor_inicial($3, $5.valor);
                
                free($3);
                if ($5.tipo == T_STRING) free($5.valor.valor_string);
             }
           ;

tipo: INT { $<entero>$ = T_ENTERO; }
    | STRING { $<entero>$ = T_STRING; }
    ;

asignacion: ID ASIGNACION expresion PUNTOYCOMA {
    Simbolo* s = buscar_simbolo($1);
    if (s == NULL) {
        char msg[100];
        sprintf(msg, "Error: Variable '%s' no declarada", $1);
        yyerror(msg);
    }
    if (s->tipo != $3.tipo) {
        yyerror("Error: Tipos incompatibles en asignacion");
    }
    
    set_valor_simbolo($1, $3.valor);
    
    free($1);
    if ($3.tipo == T_STRING) free($3.valor.valor_string);
}

entrada: LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PUNTOYCOMA;

listaIdentificadores: ID {
                        Simbolo* s = buscar_simbolo($1);
                        if (s == NULL) {
                            char msg[100];
                            sprintf(msg, "Error: Variable '%s' no declarada", $1);
                            yyerror(msg);
                        }
                        
                        if (s->tipo == T_ENTERO) {
                            printf("Ingrese valor (entero) para %s: ", $1);
                            if (scanf("%d", &s->valor.valor_int) != 1) {
                                yyerror("Error en tiempo de ejecucion: Se esperaba un numero entero.");
                            }
                        } else {
                            printf("Ingrese valor (texto) para %s: ", $1);
                            char buffer[1024];
                            scanf("%s", buffer);
                            // Liberar anterior si existe
                            if (s->valor.valor_string) free(s->valor.valor_string);
                            // Copiar nuevo valor
                            s->valor.valor_string = malloc(strlen(buffer) + 1);
                            strcpy(s->valor.valor_string, buffer);
                        }
                        free($1);
                    }
                    | ID COMA listaIdentificadores {
                        // Misma logica que arriba
                        Simbolo* s = buscar_simbolo($1);
                        if (s == NULL) {
                            char msg[100];
                            sprintf(msg, "Error: Variable '%s' no declarada", $1);
                            yyerror(msg);
                        }
                        
                        if (s->tipo == T_ENTERO) {
                            printf("Ingrese valor (entero) para %s: ", $1);
                            if (scanf("%d", &s->valor.valor_int) != 1) {
                                yyerror("Error en tiempo de ejecucion: Se esperaba un numero entero.");
                            }
                        } else {
                            printf("Ingrese valor (texto) para %s: ", $1);
                            char buffer[1024];
                            scanf("%s", buffer);
                            if (s->valor.valor_string) free(s->valor.valor_string);
                            s->valor.valor_string = malloc(strlen(buffer) + 1);
                            strcpy(s->valor.valor_string, buffer);
                        }
                        free($1);
                    }
                    ;

salida: ESCRIBIR PARENIZQUIERDO listaExpresiones PARENDERECHO PUNTOYCOMA;

listaExpresiones: expresion {
                    if ($1.tipo == T_ENTERO) printf("%d", $1.valor.valor_int);
                    else printf("%s", $1.valor.valor_string);
                    
                    if ($1.tipo == T_STRING) free($1.valor.valor_string);
                  }
                | expresion COMA {
                    if ($1.tipo == T_ENTERO) printf("%d", $1.valor.valor_int);
                    else printf("%s", $1.valor.valor_string);
                    
                    if ($1.tipo == T_STRING) free($1.valor.valor_string);
                  } listaExpresiones
                ;

expresion: primaria { $$ = $1; }
         | expresion SUMA primaria { $$ = operar($1, $3, 1); }
         | expresion RESTA primaria { $$ = operar($1, $3, 0); }
         ;

primaria: ID {
            Simbolo* s = buscar_simbolo($1);
            if (s == NULL) {
                char msg[100];
                sprintf(msg, "Error: Variable '%s' no declarada", $1);
                yyerror(msg);
            }
            $$.tipo = s->tipo;
            if (s->tipo == T_ENTERO) {
                $$.valor.valor_int = s->valor.valor_int;
            } else {
                // Copiar string
                $$.valor.valor_string = malloc(strlen(s->valor.valor_string) + 1);
                strcpy($$.valor.valor_string, s->valor.valor_string);
            }
            free($1);
          }
        | CONSTANTE_ENTERA {
            $$.tipo = T_ENTERO;
            $$.valor.valor_int = $1;
        }
        | CONSTANTE_CADENA {
            $$.tipo = T_STRING;
            $$.valor.valor_string = $1;
        }
        | PARENIZQUIERDO expresion PARENDERECHO { $$ = $2; }
        ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error en linea %d: %s\n", yylineno, s);
    exit(1);
}

ResultadoExpr operar(ResultadoExpr op1, ResultadoExpr op2, int es_suma) {
    ResultadoExpr res;
    
    if (op1.tipo != op2.tipo) {
        yyerror("Error: No se pueden operar tipos distintos.");
    }
    
    res.tipo = op1.tipo;
    
    if (res.tipo == T_ENTERO) {
        if (es_suma) res.valor.valor_int = op1.valor.valor_int + op2.valor.valor_int;
        else res.valor.valor_int = op1.valor.valor_int - op2.valor.valor_int;
    } else {
        if (!es_suma) yyerror("Error: No se pueden restar cadenas.");
        
        // Concatenar strings
        res.valor.valor_string = malloc(strlen(op1.valor.valor_string) + strlen(op2.valor.valor_string) + 1);
        strcpy(res.valor.valor_string, op1.valor.valor_string);
        strcat(res.valor.valor_string, op2.valor.valor_string);
        
        free(op1.valor.valor_string);
        free(op2.valor.valor_string);
    }
    return res;
}

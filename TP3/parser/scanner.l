%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defs.h"
#include "parser.tab.h" // Generado por Bison

void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          ({LETRA}|_)({LETRA}|{DIGITO}|_)*
CONST_INT   {DIGITO}+
CONST_STR   \"[^\"]*\"

%%

"inicio"    { return INICIO; }
"fin"       { return FIN; }
"leer"      { return LEER; }
"escribir"  { return ESCRIBIR; }
"const"     { return CONST; }
"int"       { return INT; }
"string"    { return STRING; }

":="        { return ASIGNACION; }
"+"         { return SUMA; }
"-"         { return RESTA; }
","         { return COMA; }
";"         { return PUNTOYCOMA; }
"("         { return PARENIZQUIERDO; }
")"         { return PARENDERECHO; }

{ID}        { yylval.cadena = strdup(yytext); return ID; }
{CONST_INT} { yylval.entero = atoi(yytext); return CONSTANTE_ENTERA; }
{CONST_STR} { 
    char* txt = yytext;
    int len = strlen(txt);
    char* res = malloc(len); // Longitud máxima posible
    int i, j = 0;
    // Omitir comillas iniciales y finales
    for (i = 1; i < len - 1; i++) {
        if (txt[i] == '\\' && txt[i+1] == 'n') {
            res[j++] = '\n';
            i++;
        } else {
            res[j++] = txt[i];
        }
    }
    res[j] = '\0';
    yylval.cadena = res;
    return CONSTANTE_CADENA; 
}

"//".*      { /* Ignorar comentarios */ }
[ \t\n\r]   { /* Ignorar espacios en blanco */ }

.           { 
    char msg[50];
    sprintf(msg, "Error lexico: Caracter desconocido '%s'", yytext);
    yyerror(msg);
}

%%

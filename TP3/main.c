#include <stdio.h>
#include <stdlib.h>
#include "tabla/tabla_simbolos.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    int opcion;
    char nombreArchivo[256];

    printf("INTÉRPRETE MICRO\n");
    printf("Seleccione el tipo de entrada:\n");
    printf("1. Entrada estándar (Consola)\n");
    printf("2. Archivo\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if (opcion == 2) {
        printf("Ingrese la ruta del archivo: ");
        scanf("%s", nombreArchivo);
        yyin = fopen(nombreArchivo, "r");
        if (!yyin) {
            perror("Error al abrir el archivo");
            return 1;
        }
    } else {
        printf("Ingrese el programa (termine con Ctrl+D o Ctrl+Z):\n");
        yyin = stdin;
    }

    inicializar_tabla();
    yyparse();
    liberar_tabla();

    if (opcion == 2) fclose(yyin);
    
    return 0;
}

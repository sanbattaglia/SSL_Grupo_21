#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
   char terminales[10];
   char noTerminales[10];
   
} gramatica;


int main(){

    gramatica grIngresada;

    printf("Ingrese los simbolos terminales (sin espacios, ej: abc): ");
    scanf("%s", grIngresada.terminales);

    printf("Ingrese los simbolos no terminales (sin espacios, ej: ST): ");
    scanf("%s", grIngresada.noTerminales);

    // Mostrar lo ingresado para verificar
    printf("\nTerminales ingresados: %s\n", grIngresada.terminales);
    printf("No terminales ingresados: %s\n", grIngresada.noTerminales);

    return 0;
}
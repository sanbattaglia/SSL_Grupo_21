/* Arranco TP2 */

#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 300

int contar_oraciones(FILE *archivo) {
    
    char linea[MAX_LINE];
    int oraciones = 0;
    
    fseek(archivo, 0, SEEK_SET);
    
    while (fgets(linea, MAX_LINE, archivo) != NULL) {
        
        for (int i = 0; linea[i] != '\0'; i++) {
            if (linea[i] == '.' || linea[i] == '!' || linea[i] == '?') {
                
                if (linea[i + 1] == '\0' || linea[i + 1] == '\n' || 
                    linea[i + 1] == ' ' || isupper(linea[i + 2])) {
                    oraciones++;
                }
            }
        }
    }
    
    return oraciones;
}

int main() {
    
    FILE *archivo = fopen("breve_historia.txt", "r");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }
    
    int total_oraciones = contar_oraciones(archivo);
    printf("a) Cantidad de oraciones procesadas: %d\n", total_oraciones);
    
    fclose(archivo);
    
    return 0;
}
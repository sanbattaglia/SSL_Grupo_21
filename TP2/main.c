#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *leer_archivo(const char *archivo) {
  FILE *f = fopen(archivo, "r");
  if (!f) {
    fprintf(stderr, "Error abriendo archivo");
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  long longitud = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buffer = malloc(longitud + 1);
  if (!buffer) {
    fprintf(stderr, "No se pudo reservar memoria para leer el archivo");
    fclose(f);
    exit(1);
  }

  fread(buffer, 1, longitud, f);
  buffer[longitud] = '\0';
  fclose(f);

  return buffer;
}

int main() {

  const char *texto = leer_archivo("breve_historia.txt");
  printf("Archivo leido:\n%s\n\nFin Archivo\n", texto);
  return 0;
}
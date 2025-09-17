#include "resolucion.h"

void a_contar_oraciones(const char *texto) {
  regex_t regex;
  regmatch_t match[1];
  // vamos a contar que una oracion termina con un . un ? o un !
  const char *patron = "[^.?!]+[.?!]"; // cualquier cosa que no sea .?! al menos
                                       // una vez, y un .?!
  int ret, cuenta = 0;
  const char *p = texto;

  // Compilar regex
  if (regcomp(&regex, patron, REG_EXTENDED)) {
    fprintf(stderr, "No se pudo compilar la regex\n");
    exit(1);
  }

  while ((ret = regexec(&regex, p, 1, match, 0)) == 0) {
    cuenta++;
    // avanzar puntero - moverlo despues del ultimo match
    p += match[0].rm_eo;
  }

  printf("Cantidad de oraciones: %d\n", cuenta);

  regfree(&regex);
}
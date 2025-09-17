#include "resolucion.h"
#include <string.h>

int recorrer_oraciones(const char *texto) {
  regex_t regex;
  regmatch_t match[1];
  // vamos a contar que una oracion termina con un . un ? o un !
  const char *patron = "[^.?!]+[.?!]"; // cualquier cosa que no sea .?! al menos
                                       // una vez, y un .?!
  int ret, cuenta = 0;
  const char *p = texto;
  char oracion[1000];

  // Compilar regex
  if (regcomp(&regex, patron, REG_EXTENDED)) {
    fprintf(stderr, "No se pudo compilar la regex\n");
    exit(1);
  }

  while ((ret = regexec(&regex, p, 1, match, 0)) == 0) {
    // sumar el offset de p
    strncpy(oracion, p + match[0].rm_so, match[0].rm_eo - match[0].rm_so);

    /*
    van las llamadas a las funciones ed cada punto
    a_contar_oraciones(oracion, cuenta)
    b_mostrar_indepencia(oracion, lista_matches_b)
    c_blablabla(oracion, lista_matches_c)
    */

    // avanzar puntero - moverlo despues del ultimo match
    p += match[0].rm_eo;
  }

  regfree(&regex);
}

void a_contar_oraciones(const char *oracion, int *cuenta) {
  if (oracion != NULL) {
    (*cuenta) += 1;
  }
}
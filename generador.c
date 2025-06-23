/*
################################################################
################################################################
#####                                                      #####
##### BORRAR PRINTFS DE LOGS COMENTADOS EN COMMIT FINAL XD #####
#####                                                      #####
################################################################
################################################################
*/
#include "generador.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANO_BUFF_PALABRA 1000
#define TAMANO_BUFF 100
#define LONG_MAX_POSIBLE_RES 5

void generar_palabra(char *placeholder, gramatica gram) {
  char buffer[TAMANO_BUFF] = {};
  char buffer_palabra[TAMANO_BUFF_PALABRA] = {};
  productor ultimo_prod;
  srand(time(NULL));

  // caso base -- inicia palabra
  ultimo_prod =
      hallar_productor(gram.productores, CANT_AXIOMAS, gram.axioma_inicial);
  get_producto_random(buffer, ultimo_prod);
  strcpy(buffer_palabra, buffer);

  if ('\0' == hallar_no_terminal(buffer_palabra, gram.no_terminales)) {
    // el axioma inicial es un solo terminal o palabra vacia
    strcpy(placeholder, buffer_palabra);
    return;
  }

  char anterior_noterm;
  int counter = 0;
  do {
    anterior_noterm = hallar_no_terminal(buffer_palabra, gram.no_terminales);
    if ('\0' == anterior_noterm) {
      break;
    }
    ultimo_prod =
        hallar_productor(gram.productores, CANT_AXIOMAS, anterior_noterm);
    counter++;
    printf("%s -> ", buffer_palabra);
  } while (extender_palabra(buffer_palabra, ultimo_prod) && counter < 20);

  printf("%s\n", buffer_palabra);
  strcpy(placeholder, buffer_palabra);
}

int extender_palabra(char *str_palabra, productor prod_res) {
  char *pos_no_term;
  pos_no_term =
      strchr(str_palabra, prod_res.noterminal); // busca el noterminal en el str

  // si es null no tiene el no terminal, la palabra termina y devuelvo
  if (!pos_no_term) {
    return 0;
  }

  char prod_random[TAMANO_BUFF];
  char temp[TAMANO_BUFF_PALABRA];
  get_producto_random(prod_random, prod_res);

  // esta al ppio, es reg x izq
  if (pos_no_term == str_palabra) {
    strcpy(temp, str_palabra + 1);
    strcpy(str_palabra, prod_random);
    strcat(str_palabra, temp);
  } else { // esta al final del str, en algun lado del buffer
    int len = strlen(str_palabra);
    str_palabra[len - 1] = '\0';
    strcat(str_palabra, prod_random);
  }
  return 1;
}

char hallar_no_terminal(char *resultado, char *no_terminales) {
  // avanzas por los caracteres del resultado del producto
  for (char *p = resultado; *p != '\0'; p++) {
    // si encontras el caracter actual en lista de no terminales
    if (strchr(no_terminales, *p)) {
      // printf("ENCONTRE EL NOTERM: %c\n", *p);
      return *p;
    }
  }
  // printf("No encontre NOTERM\n");
  return '\0';
}

void get_producto_random(char *placeholder, productor prod) {
  char *tok;
  char buffer[TAMANO_BUFF][LONG_MAX_POSIBLE_RES];
  const char delim[] = "|";

  tok = strtok(prod.resultado, delim);
  if (!tok) {
    strcpy(placeholder, prod.resultado);
    // printf("unico: %s", prod.resultado);
    return;
  }

  // es multiparte
  int i = 0;
  // printf("para %c -> ", prod.noterminal);
  while (tok) {
    strcpy(buffer[i], tok);
    // printf("%s|", tok);
    tok = strtok(NULL, delim);
    i++;
  }
  char *elegido = buffer[rand() % i];
  // printf("\n  elegido: %s\n", elegido);
  strcpy(placeholder, elegido);
}

productor hallar_productor(productor *productores, int size, char axioma) {
  productor prod = {};
  for (int i = 0; i < size; i++) {
    if (axioma == productores[i].noterminal) {
      return productores[i];
    }
  }
  return prod;
}
